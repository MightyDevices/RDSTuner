/*
 * startup.c
 *
 *  Created on: 23-04-2012
 *      Author: Tomek
 */

#include <stm32l476/rcc.h>
#include <stm32l476/nvic.h>
#include <stm32l476/syscfg.h>
#include <stm32l476/scb.h>
#include <stm32l476/wwdg.h>
#include <sys/regs.h>
#include <stdint.h>

#define DEBUG
#include <dev/debug.h>

/* includes for int/exc handlers */
#include <dev/usart1.h>
#include <dev/extimux.h>
#include <dev/bu1924.h>

/* data pointers */
/* bss section */
extern uint32_t __bss_start, __bss_end;
/* initialized data section */
extern uint32_t __data_start, __data_end, __datai_start;
/* exception & interrupt vectors location */
extern uint32_t __flash_vectors;
/* initial stack pointer */
extern uint32_t __stack;

/* main program routine */
extern int main(void);

/* default handler */
void __attribute__((naked)) DefaultHandler(void)
{
	/* read stack pointer */
	uint32_t *s = (uint32_t *)Regs_ReadMSP();
	/* read ipsr */
	uint32_t ipsr = Regs_ReadIPSR();
	/* critical nesting counter */
	extern int critical_nesting_cnt;

	/* kick wwdg so that we have time to send info over debug iface */
	WWDG->CR = WWDG_CR_T;

	/* display warning */
	dprintf_c("default handler reached!\n", 0);
	dprintf_c("msp = 0x%x, ipsr = 0x%x\n", s, ipsr);
	/* display registers */
	dprintf_c("r0 = %x, r1 = %x\n",  s[0], s[1]);
	dprintf_c("r2 = %x, r3 = %x\n",  s[2], s[3]);
	dprintf_c("r12 = %x, lr = %x\n", s[4], s[5]);
	dprintf_c("pc = %x, psr = %x\n", s[6], s[7]);
	/* display active interrupts */
	dprintf_c("ispr0 = %x, ispr1 = %x\n", NVIC->ISPR[0], NVIC->ISPR[1]);
	dprintf_c("ispr2 = %x, ispr3 = %x\n", NVIC->ISPR[2], NVIC->ISPR[3]);
	dprintf_c("iabr0 = %x, iabr1 = %x\n", NVIC->IABR[0], NVIC->IABR[1]);
	dprintf_c("iabr2 = %x, iabr3 = %x\n", NVIC->IABR[2], NVIC->IABR[3]);
	/* fault registers */
	dprintf_c("cfsr = %x, hfsr = %x\n", SCB->CFSR, SCB->HFSR);
	dprintf_c("mmar = %x, bfar = %x\n", SCB->MMAR, SCB->BFAR);
	/* display critical section info */
	dprintf_c("critical nesting = %d\n", critical_nesting_cnt);

	/* safety feature, in case main has returned (should never happen) */
	SCB->AIRCR = SCB_AIRCR_SYSRESETREQ | SCB_AIRCR_VECTKEYSTAT;
}

/* reset handler */
void ResetHandler(void)
{
	/* data initialization pointers */
	volatile uint32_t *start, *end, *starti;

	/* disable interrupts */
	STM32_DISABLEINTS();

	/* disable interrupt generation */
	RCC->CIER = 0;

	/* enable msi */
	RCC->CR |= RCC_CR_MSION;
	/* wait till its enabled */
	while (!(RCC->CR & RCC_CR_MSIRDY));

	/* select frequency range (4MHz) */
	RCC->CR = (RCC->CR & ~RCC_CR_MSIRANGE) | RCC_CR_MSIRANGE_6;
	/* apply range */
	RCC->CR |= RCC_CR_MSIRGSEL;

	/* select hsi as a system clock */
	RCC->CFGR = RCC_CFGR_SW_MSI;
	/* wait till its selected */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_MSI);

	/* disable all other clocks */
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_HSION | RCC_CR_PLLON);

	/* default state of ahb peripheral clocks  */
	RCC->AHB1ENR = 0; RCC->AHB2ENR = 0; RCC->AHB3ENR = 0;
	/* disable all apb peripheral clocks */
	RCC->APB1ENR1 = 0; RCC->APB1ENR2 = 0; RCC->APB2ENR = 0;

	/* reset all peripherals */
	RCC->AHB1RSTR = 0xffffffff; RCC->AHB2RSTR = 0xffffffff;
	RCC->AHB3RSTR = 0xffffffff; RCC->APB1RSTR1 = 0xffffffff;
	RCC->APB1RSTR2 = 0xffffffff; RCC->APB2RSTR = 0xffffffff;

	/* disable reset */
	RCC->AHB1RSTR = 0x0; RCC->AHB2RSTR = 0x0;
	RCC->AHB3RSTR = 0x0; RCC->APB1RSTR1 = 0x0;
	RCC->APB1RSTR2 = 0x0; RCC->APB2RSTR = 0x0;

	/* disable interrupts 0-31 */
	NVIC->ICER[0] = 0xffffffff;
	/* disable interrupts 32-64 */
	NVIC->ICER[1] = 0xffffffff;
	/* clear pending interrupts: 0-31 */
	NVIC->ICPR[0] = 0xffffffff;
	/* clear pending interrupts: 32-64 */
	NVIC->ICPR[1] = 0xffffffff;

	/* set vector table offset: code memory start */
	SCB->VTOR = (uint32_t)&__flash_vectors;

	/* copy data section */
	/* data start pointer */
	start = &__data_start;
	/* data end pointer */
	end = &__data_end;
	/* data start (in flash) pointer */
	starti = &__datai_start;

	/* copy */
	while (start < end)
		*start++ = *starti++;

	/* zero bss section */
	/* start of bss section */
	start = &__bss_start;
	/* end of bss section */
	end = &__bss_end;

	/* zero all words */
	while (start < end)
		*start++ = 0;

	/* enable interrupts globally */
	STM32_ENABLEINTS();

	/* jump to main program routine */
	main();

	/* safety feature, in case main has returned (should never happen) */
	SCB->AIRCR = SCB_AIRCR_SYSRESETREQ | SCB_AIRCR_VECTKEYSTAT;
}


/* init vector table */
uint32_t vectors[] __attribute__ ((section(".vectors"))) = {
	/* initial stack pointer */
	(uint32_t)&__stack,
	/* initial reset handler */
	(uint32_t)ResetHandler,
	/* nmi */
	(uint32_t)DefaultHandler,
	/* hard fault */
	(uint32_t)DefaultHandler,
	/* reserved */
	0, 0, 0, 0, 0, 0, 0,
	/* svc */
	(uint32_t)DefaultHandler,
	/* reserved */
	0, 0,
	/* pend sv */
	(uint32_t)DefaultHandler,
	/* systick */
	(uint32_t)DefaultHandler,


	/* 0: WWDG */
	(uint32_t)DefaultHandler,
	/* 1: EXTI16 / PVD */
	(uint32_t)DefaultHandler,
	/* 2: EXTI21 / TAMP_STAMP */
	(uint32_t)DefaultHandler,
	/* 3: EXTI22 / RTC_WKUP */
	(uint32_t)DefaultHandler,
	/* 4: FLASH */
	(uint32_t)DefaultHandler,
	/* 5: RCC */
	(uint32_t)DefaultHandler,
	/* 6: EXTI0 */
	(uint32_t)DefaultHandler,
	/* 7: EXTI1 */
	(uint32_t)DefaultHandler,
	/* 8: EXTI2 */
	(uint32_t)DefaultHandler,
	/* 9: EXTI3 */
	(uint32_t)DefaultHandler,
	/* 10: EXTI4 */
	(uint32_t)DefaultHandler,
	/* 11: DMA1C1 */
	(uint32_t)DefaultHandler,
	/* 12: DMA1C2 */
	(uint32_t)DefaultHandler,
	/* 13: DMA1C3 */
	(uint32_t)DefaultHandler,
	/* 14: DMA1C4 */
	(uint32_t)USART1_DMA1Ch4Isr,
	/* 15: DMA1C5 */
	(uint32_t)DefaultHandler,
	/* 16: DMA1C6 */
	(uint32_t)DefaultHandler,
	/* 17: DMA1C7 */
	(uint32_t)DefaultHandler,
	/* 18: ADC1_2 */
	(uint32_t)DefaultHandler,
	/* 19: CAN1_TX */
	(uint32_t)DefaultHandler,
	/* 20: CAN1_RX0 */
	(uint32_t)DefaultHandler,
	/* 21: CAN1_RX1 */
	(uint32_t)DefaultHandler,
	/* 22: CAN1_SCE */
	(uint32_t)DefaultHandler,
	/* 23: EXTI5_9 */
	(uint32_t)ExtiMux_Exti5_9Isr,
	/* 24: TIM1_BRK_TIM15 */
	(uint32_t)DefaultHandler,
	/* 25: TIM1_UP_TIM16 */
	(uint32_t)DefaultHandler,
	/* 26: TIM1_TRG_COM_TIM17 */
	(uint32_t)DefaultHandler,
	/* 27: TIM1_CC */
	(uint32_t)DefaultHandler,
	/* 28: TIM2 */
	(uint32_t)DefaultHandler,
	/* 29: TIM3 */
	(uint32_t)DefaultHandler,
	/* 30: TIM4 */
	(uint32_t)DefaultHandler,
	/* 31: I2C1_EV */
	(uint32_t)DefaultHandler,
	/* 32: I2C1_ER */
	(uint32_t)DefaultHandler,
	/* 33: I2C2_EV */
	(uint32_t)DefaultHandler,
	/* 34: I2C2_ER */
	(uint32_t)DefaultHandler,
	/* 35: SPI1 */
	(uint32_t)DefaultHandler,
	/* 36: SPI2 */
	(uint32_t)BU1924_Spi2Isr,
	/* 37: USART1 */
	(uint32_t)DefaultHandler, //Slip1_USART1Isr,
	/* 38: USART2 */
	(uint32_t)DefaultHandler,
	/* 39: USART3 */
	(uint32_t)DefaultHandler,
	/* 40: EXTI10_15 */
	(uint32_t)ExtiMux_Exti10_15Isr,
	/* 41: EXTI17/RTC_ALARM */
	(uint32_t)DefaultHandler,
	/* 42: DFSDM3 */
	(uint32_t)DefaultHandler,
	/* 43: TIM8_BRK */
	(uint32_t)DefaultHandler,
	/* 44: TIM8_UP */
	(uint32_t)DefaultHandler,
	/* 45: TIM8_TRGCOM */
	(uint32_t)DefaultHandler,
	/* 46: TIM8_CC */
	(uint32_t)DefaultHandler,
	/* 47: ADC3 */
	(uint32_t)DefaultHandler,
	/* 48: FMC */
	(uint32_t)DefaultHandler,
	/* 49: SDMMC */
	(uint32_t)DefaultHandler,
	/* 50: TIM5 */
	(uint32_t)DefaultHandler,
	/* 51: SPI3 */
	(uint32_t)DefaultHandler,
	/* 52: USART4 */
	(uint32_t)DefaultHandler,
	/* 53: USART5 */
	(uint32_t)DefaultHandler,
	/* 54: TIM6_DACUNDER */
	(uint32_t)DefaultHandler,
	/* 55: TIM7 */
	(uint32_t)DefaultHandler,
	/* 56: DMA2C1 */
	(uint32_t)DefaultHandler,
	/* 57: DMA2C2 */
	(uint32_t)DefaultHandler,
	/* 58: DMA2C3 */
	(uint32_t)DefaultHandler,
	/* 59: DMA2C4 */
	(uint32_t)DefaultHandler,
	/* 60: DMA2C5 */
	(uint32_t)DefaultHandler,
	/* 61: DFSDM0 */
	(uint32_t)DefaultHandler,
	/* 62: DFSDM1 */
	(uint32_t)DefaultHandler,
	/* 63: DFSDM2 */
	(uint32_t)DefaultHandler,
	/* 64: COMP1/COMP2 */
	(uint32_t)DefaultHandler,
	/* 65: LPTIM1 */
	(uint32_t)DefaultHandler,
	/* 66: LPTIM2 */
	(uint32_t)DefaultHandler,
	/* 67: OTG_FS */
	(uint32_t)DefaultHandler,
	/* 68: DMA2C6 */
	(uint32_t)DefaultHandler,
	/* 69: DMA2C7 */
	(uint32_t)DefaultHandler,
	/* 70: LPUART */
	(uint32_t)DefaultHandler,
	/* 71: QUADSPI */
	(uint32_t)DefaultHandler,
	/* 72: I2C3_EV */
	(uint32_t)DefaultHandler,
	/* 73: I2C3_ER */
	(uint32_t)DefaultHandler,
	/* 74: SAI1 */
	(uint32_t)DefaultHandler,
	/* 75: SAI2 */
	(uint32_t)DefaultHandler,
	/* 76: SWPMI1 */
	(uint32_t)DefaultHandler,
	/* 77: TSC */
	(uint32_t)DefaultHandler,
	/* 78: LCD */
	(uint32_t)DefaultHandler,
	/* 79: AES */
	(uint32_t)DefaultHandler,
	/* 81: FPU */
	(uint32_t)DefaultHandler,
};
