# RDSTuner 📻

Code for controlling LC72131 based tuner with BU1924 RDS decoder.

I've connected STM32L476 (from Nucleo-L476RG board) to some no-name FM/AM tuner that comes from Marantz amplifier. The tuner was broken down, and after doing the repair I needed to be able to do some testing.

This is what this code does:
+ setting new frequency in 100kHz increments after the 'User' button is pressed (communication with LC72131 PLL)
+ reading and decoding RDS data stream that comes from BU1924 using STM32 SPI in slave mode, basic info only, station name, radio texts, nothing fancy.

STM <-> PLL Connections:

+ PC9 - PLLSCK
+ PC8 - PLLDI
+ PC6 - PLLDO (currently unused)
+ PC5 - PLLCE

STM <-> RDS Connections:

+ PB13 (SPI2_SCK) - RDSCLK
+ PB15 (SPI2_MOSI) - RDSDAT

STM <-> PC Connections

+ PA9 (UART1_TXD) - RDS decoded data & debug information (230400 bauds, 8N1)

Simply type in "make all" to build binary image and upload it at the beginning of the flash memory.

