/*
 * otg.h
 *
 *  Created on: 09-01-2016
 *      Author: Tomek
 */

#ifndef STM32F401_OTG_H_
#define STM32F401_OTG_H_

#include <stm32f401/stm32f401.h>

/* base */
#define OTG_BASE            				(0x50000000)
/* scb */
#define OTG									((otg_t *)OTG_BASE)

/* usb core registers */
typedef struct {
	reg32_t GOTGCTL;
	reg32_t GOTGINT;
	reg32_t GAHBCFG;
	reg32_t GUSBCFG;
	reg32_t GRSTCTL;
	reg32_t GINTSTS;
	reg32_t GINTMSK;
	reg32_t GRXSTSR;
	reg32_t GRXSTSP;
	reg32_t GRXFSIZ;
	reg32_t DIEPTXF0_HNPTXFSIZ; /* ???? */
	reg32_t HNPTXSTS;
	reg32_t _RESERVED0[2];
	reg32_t GCCFG;
	reg32_t CID;
	reg32_t _RESERVED1[48];
	reg32_t HPTXFSIZ;
	reg32_t DIEPTXF[0x0F];
} otg_t;

/*  Bit definition for OTG_GOTGCTL register  */
#define OTG_GOTGCTL_SRQSCS                  (0x00000001)
#define OTG_GOTGCTL_SRQ                     (0x00000002)
#define OTG_GOTGCTL_HNGSCS                  (0x00000100)
#define OTG_GOTGCTL_HNPRQ                   (0x00000200)
#define OTG_GOTGCTL_HSHNPEN                 (0x00000400)
#define OTG_GOTGCTL_DHNPEN                  (0x00000800)
#define OTG_GOTGCTL_CIDSTS                  (0x00010000)
#define OTG_GOTGCTL_DBCT                    (0x00020000)
#define OTG_GOTGCTL_ASVLD                   (0x00040000)
#define OTG_GOTGCTL_BSVLD                   (0x00080000)

/*  Bit definition for OTG_GOTGINT register  */
#define OTG_GOTGINT_SEDET                   (0x00000004)
#define OTG_GOTGINT_SRSSCHG                 (0x00000100)
#define OTG_GOTGINT_HNSSCHG                 (0x00000200)
#define OTG_GOTGINT_HNGDET                  (0x00020000)
#define OTG_GOTGINT_ADTOCHG                 (0x00040000)
#define OTG_GOTGINT_DBCDNE                  (0x00080000)

/*  Bit definition for OTG_GAHBCFG register  */
#define OTG_GAHBCFG_GINT                    (0x00000001)
#define OTG_GAHBCFG_HBSTLEN                 (0x0000001E)
#define OTG_GAHBCFG_HBSTLEN_0               (0x00000002)
#define OTG_GAHBCFG_HBSTLEN_1               (0x00000004)
#define OTG_GAHBCFG_HBSTLEN_2               (0x00000008)
#define OTG_GAHBCFG_HBSTLEN_3               (0x00000010)
#define OTG_GAHBCFG_DMAEN                   (0x00000020)
#define OTG_GAHBCFG_TXFELVL                 (0x00000080)
#define OTG_GAHBCFG_PTXFELVL                (0x00000100)

/*  Bit definition for OTG_GUSBCFG register  */
#define OTG_GUSBCFG_TOCAL                   (0x00000007)
#define OTG_GUSBCFG_TOCAL_0                 (0x00000001)
#define OTG_GUSBCFG_TOCAL_1                 (0x00000002)
#define OTG_GUSBCFG_TOCAL_2                 (0x00000004)
#define OTG_GUSBCFG_PHYSEL                  (0x00000040)
#define OTG_GUSBCFG_SRPCAP                  (0x00000100)
#define OTG_GUSBCFG_HNPCAP                  (0x00000200)
#define OTG_GUSBCFG_TRDT                    (0x00003C00)
#define OTG_GUSBCFG_TRDT_0                  (0x00000400)
#define OTG_GUSBCFG_TRDT_1                  (0x00000800)
#define OTG_GUSBCFG_TRDT_2                  (0x00001000)
#define OTG_GUSBCFG_TRDT_3                  (0x00002000)
#define OTG_GUSBCFG_PHYLPCS                 (0x00008000)
#define OTG_GUSBCFG_ULPIFSLS                (0x00020000)
#define OTG_GUSBCFG_ULPIAR                  (0x00040000)
#define OTG_GUSBCFG_ULPICSM                 (0x00080000)
#define OTG_GUSBCFG_ULPIEVBUSD              (0x00100000)
#define OTG_GUSBCFG_ULPIEVBUSI              (0x00200000)
#define OTG_GUSBCFG_TSDPS                   (0x00400000)
#define OTG_GUSBCFG_PCCI                    (0x00800000)
#define OTG_GUSBCFG_PTCI                    (0x01000000)
#define OTG_GUSBCFG_ULPIIPD                 (0x02000000)
#define OTG_GUSBCFG_FHMOD                   (0x20000000)
#define OTG_GUSBCFG_FDMOD                   (0x40000000)
#define OTG_GUSBCFG_CTXPKT                  (0x80000000)

/*  Bit definition for OTG_GRSTCTL register  */
#define OTG_GRSTCTL_CSRST                   (0x00000001)
#define OTG_GRSTCTL_HSRST                   (0x00000002)
#define OTG_GRSTCTL_FCRST                   (0x00000004)
#define OTG_GRSTCTL_RXFFLSH                 (0x00000010)
#define OTG_GRSTCTL_TXFFLSH                 (0x00000020)

#define OTG_GRSTCTL_TXFNUM                  (0x000007C0)
#define OTG_GRSTCTL_TXFNUM_0                (0x00000040)
#define OTG_GRSTCTL_TXFNUM_1                (0x00000080)
#define OTG_GRSTCTL_TXFNUM_2                (0x00000100)
#define OTG_GRSTCTL_TXFNUM_3                (0x00000200)
#define OTG_GRSTCTL_TXFNUM_4                (0x00000400)
#define OTG_GRSTCTL_DMAREQ                  (0x40000000)
#define OTG_GRSTCTL_AHBIDL                  (0x80000000)

/*  Bit definition for OTG_GINTSTS register  */
#define OTG_GINTSTS_CMOD                    (0x00000001)
#define OTG_GINTSTS_MMIS                    (0x00000002)
#define OTG_GINTSTS_OTGINT                  (0x00000004)
#define OTG_GINTSTS_SOF                     (0x00000008)
#define OTG_GINTSTS_RXFLVL                  (0x00000010)
#define OTG_GINTSTS_NPTXFE                  (0x00000020)
#define OTG_GINTSTS_GINAKEFF                (0x00000040)
#define OTG_GINTSTS_BOUTNAKEFF              (0x00000080)
#define OTG_GINTSTS_ESUSP                   (0x00000400)
#define OTG_GINTSTS_USBSUSP                 (0x00000800)
#define OTG_GINTSTS_USBRST                  (0x00001000)
#define OTG_GINTSTS_ENUMDNE                 (0x00002000)
#define OTG_GINTSTS_ISOODRP                 (0x00004000)
#define OTG_GINTSTS_EOPF                    (0x00008000)
#define OTG_GINTSTS_IEPINT                  (0x00040000)
#define OTG_GINTSTS_OEPINT                  (0x00080000)
#define OTG_GINTSTS_IISOIXFR                (0x00100000)
#define OTG_GINTSTS_PXFR_INCOMPISOOUT       (0x00200000)
#define OTG_GINTSTS_DATAFSUSP               (0x00400000)
#define OTG_GINTSTS_HPRTINT                 (0x01000000)
#define OTG_GINTSTS_HCINT                   (0x02000000)
#define OTG_GINTSTS_PTXFE                   (0x04000000)
#define OTG_GINTSTS_CIDSCHG                 (0x10000000)
#define OTG_GINTSTS_DISCINT                 (0x20000000)
#define OTG_GINTSTS_SRQINT                  (0x40000000)
#define OTG_GINTSTS_WKUINT                  (0x80000000)

/*  Bit definition for OTG_GINTMSK register  */
#define OTG_GINTMSK_MMISM                   (0x00000002)
#define OTG_GINTMSK_OTGINT                  (0x00000004)
#define OTG_GINTMSK_SOFM                    (0x00000008)
#define OTG_GINTMSK_RXFLVLM                 (0x00000010)
#define OTG_GINTMSK_NPTXFEM                 (0x00000020)
#define OTG_GINTMSK_GINAKEFFM               (0x00000040)
#define OTG_GINTMSK_GONAKEFFM               (0x00000080)
#define OTG_GINTMSK_ESUSPM                  (0x00000400)
#define OTG_GINTMSK_USBSUSPM                (0x00000800)
#define OTG_GINTMSK_USBRST                  (0x00001000)
#define OTG_GINTMSK_ENUMDNEM                (0x00002000)
#define OTG_GINTMSK_ISOODRPM                (0x00004000)
#define OTG_GINTMSK_EOPFM                   (0x00008000)
#define OTG_GINTMSK_EPMISM                  (0x00020000)
#define OTG_GINTMSK_IEPINT                  (0x00040000)
#define OTG_GINTMSK_OEPINT                  (0x00080000)
#define OTG_GINTMSK_IISOIXFRM               (0x00100000)
#define OTG_GINTMSK_PXFRM_IISOOXFRM         (0x00200000)
#define OTG_GINTMSK_FSUSPM                  (0x00400000)
#define OTG_GINTMSK_PRTIM                   (0x01000000)
#define OTG_GINTMSK_HCIM                    (0x02000000)
#define OTG_GINTMSK_PTXFEM                  (0x04000000)
#define OTG_GINTMSK_CIDSCHGM                (0x10000000)
#define OTG_GINTMSK_DISCINT                 (0x20000000)
#define OTG_GINTMSK_SRQIM                   (0x40000000)
#define OTG_GINTMSK_WUIM                    (0x80000000)

/*  Bit definition for OTG_GRXSTSR register  */
#define OTG_GRXSTSR_EPNUM                   (0x0000000F)
#define OTG_GRXSTSR_BCNT                    (0x00007FF0)
#define OTG_GRXSTSR_DPID                    (0x00018000)
#define OTG_GRXSTSR_PKTSTS                  (0x001E0000)

/*  Bit definition for OTG_GRXSTSP register  */
#define OTG_GRXSTSP_EPNUM                   (0x0000000F)
#define OTG_GRXSTSP_BCNT                    (0x00007FF0)
#define OTG_GRXSTSP_DPID                    (0x00018000)
#define OTG_GRXSTSP_PKTSTS                  (0x001E0000)

/*  Bit definition for OTG_GRXFSIZ register  */
#define OTG_GRXFSIZ_RXFD                    (0x0000FFFF)

/*  Bit definition for OTG_GCCFG register  */
#define OTG_GCCFG_PWRDWN                  	(0x00010000)
#define OTG_GCCFG_I2CPADEN                	(0x00020000)
#define OTG_GCCFG_VBUSASEN                	(0x00040000)
#define OTG_GCCFG_VBUSBSEN                	(0x00080000)
#define OTG_GCCFG_SOFOUTEN                	(0x00100000)
#define OTG_GCCFG_NOVBUSSENS              	(0x00200000)

/*  Bit definition for OTG_CID register  */
#define OTG_CID_PRODUCT_ID              	(0xFFFFFFFF)

/*  Bit definition for OTG_HPTXFSIZ register  */
#define OTG_HPTXFSIZ_PTXSA                  (0x0000FFFF)
#define OTG_HPTXFSIZ_PTXFD                  (0xFFFF0000)

/*  Bit definition for OTG_DIEPTXF register  */
#define OTG_DIEPTXF_INEPTXSA                (0x0000FFFF)
#define OTG_DIEPTXF_INEPTXFD                (0xFFFF0000)

/* base */
#define OTG_DEV_BASE            			(OTG_BASE + 0x800)
/* scb */
#define OTG_DEV								((otg_dev_t *)OTG_DEV_BASE)

/* usb device registers */
typedef struct {
	reg32_t DCFG;
	reg32_t DCTL;
	reg32_t DSTS;
	reg32_t _RESERVED0;
	reg32_t DIEPMSK;
	reg32_t DOEPMSK;
	reg32_t DAINT;
	reg32_t DAINTMSK;
	reg32_t _RESERVED1;
	reg32_t _RESERVED2;
	reg32_t DVBUSDIS;
	reg32_t DVBUSPULSE;
	reg32_t DTHRCTL;
	reg32_t DIEPEMPMSK;
} otg_dev_t;

/*  Bit definition for OTG_DCFG register  */
#define OTG_DCFG_DSPD                    	(0x00000003)
#define OTG_DCFG_DSPD_0                  	(0x00000001)
#define OTG_DCFG_DSPD_1                  	(0x00000002)
#define OTG_DCFG_NZLSOHSK                	(0x00000004)
#define OTG_DCFG_DAD                     	(0x000007F0)
#define OTG_DCFG_DAD_0                   	(0x00000010)
#define OTG_DCFG_DAD_1                   	(0x00000020)
#define OTG_DCFG_DAD_2                   	(0x00000040)
#define OTG_DCFG_DAD_3                   	(0x00000080)
#define OTG_DCFG_DAD_4                   	(0x00000100)
#define OTG_DCFG_DAD_5                   	(0x00000200)
#define OTG_DCFG_DAD_6                   	(0x00000400)
#define OTG_DCFG_PFIVL                   	(0x00001800)
#define OTG_DCFG_PFIVL_0                 	(0x00000800)
#define OTG_DCFG_PFIVL_1                 	(0x00001000)
#define OTG_DCFG_PERSCHIVL               	(0x03000000)
#define OTG_DCFG_PERSCHIVL_0             	(0x01000000)
#define OTG_DCFG_PERSCHIVL_1             	(0x02000000)

/*  Bit definition for OTG_DCTL register  */
#define OTG_DCTL_RWUSIG                  	(0x00000001)
#define OTG_DCTL_SDIS                    	(0x00000002)
#define OTG_DCTL_GINSTS                  	(0x00000004)
#define OTG_DCTL_GONSTS                  	(0x00000008)
#define OTG_DCTL_TCTL                    	(0x00000070)
#define OTG_DCTL_TCTL_0                  	(0x00000010)
#define OTG_DCTL_TCTL_1                  	(0x00000020)
#define OTG_DCTL_TCTL_2                  	(0x00000040)
#define OTG_DCTL_SGINAK                  	(0x00000080)
#define OTG_DCTL_CGINAK                  	(0x00000100)
#define OTG_DCTL_SGONAK                  	(0x00000200)
#define OTG_DCTL_CGONAK                  	(0x00000400)
#define OTG_DCTL_POPRGDNE                	(0x00000800)

/*  Bit definition for OTG_DSTS register  */
#define OTG_DSTS_SUSPSTS                 	(0x00000001)
#define OTG_DSTS_ENUMSPD                 	(0x00000006)
#define OTG_DSTS_ENUMSPD_0               	(0x00000002)
#define OTG_DSTS_ENUMSPD_1               	(0x00000004)
#define OTG_DSTS_EERR                    	(0x00000008)
#define OTG_DSTS_FNSOF                   	(0x003FFF00)

/*  Bit definition for OTG_DIEPMSK register  */
#define OTG_DIEPMSK_XFRCM                   (0x00000001)
#define OTG_DIEPMSK_EPDM                    (0x00000002)
#define OTG_DIEPMSK_TOM                     (0x00000008)
#define OTG_DIEPMSK_ITTXFEMSK               (0x00000010)
#define OTG_DIEPMSK_INEPNMM                 (0x00000020)
#define OTG_DIEPMSK_INEPNEM                 (0x00000040)
#define OTG_DIEPMSK_TXFURM                  (0x00000100)
#define OTG_DIEPMSK_BIM                     (0x00000200)

/*  Bit definition for OTG_DOEPMSK register  */
#define OTG_DOEPMSK_XFRCM                   (0x00000001)
#define OTG_DOEPMSK_EPDM                    (0x00000002)
#define OTG_DOEPMSK_STUPM                   (0x00000008)
#define OTG_DOEPMSK_OTEPDM                  (0x00000010)
#define OTG_DOEPMSK_B2BSTUP                 (0x00000040)
#define OTG_DOEPMSK_OPEM                    (0x00000100)
#define OTG_DOEPMSK_BOIM                    (0x00000200)

/*  Bit definition for OTG_DAINT register  */
#define OTG_DAINT_IEPINT                  	(0x0000FFFF)
#define OTG_DAINT_OEPINT                  	(0xFFFF0000)

/*  Bit definition for OTG_DAINTMSK register  */
#define OTG_DAINTMSK_IEPM                   (0x0000FFFF)
#define OTG_DAINTMSK_OEPM                   (0xFFFF0000)

/*  Bit definition for OTG_DVBUSDIS register  */
#define OTG_DVBUSDIS_VBUSDT                 (0x0000FFFF)

/*  Bit definition for OTG_DVBUSPULSE register  */
#define OTG_DVBUSPULSE_DVBUSP               (0x00000FFF)

/*  Bit definition for OTG_DTHRCTL register  */
#define OTG_DTHRCTL_NONISOTHREN             (0x00000001)
#define OTG_DTHRCTL_ISOTHREN                (0x00000002)
#define OTG_DTHRCTL_TXTHRLEN                (0x000007FC)
#define OTG_DTHRCTL_TXTHRLEN_0              (0x00000004)
#define OTG_DTHRCTL_TXTHRLEN_1              (0x00000008)
#define OTG_DTHRCTL_TXTHRLEN_2              (0x00000010)
#define OTG_DTHRCTL_TXTHRLEN_3              (0x00000020)
#define OTG_DTHRCTL_TXTHRLEN_4              (0x00000040)
#define OTG_DTHRCTL_TXTHRLEN_5              (0x00000080)
#define OTG_DTHRCTL_TXTHRLEN_6              (0x00000100)
#define OTG_DTHRCTL_TXTHRLEN_7              (0x00000200)
#define OTG_DTHRCTL_TXTHRLEN_8              (0x00000400)
#define OTG_DTHRCTL_RXTHREN                 (0x00010000)
#define OTG_DTHRCTL_RXTHRLEN                (0x03FE0000)
#define OTG_DTHRCTL_RXTHRLEN_0              (0x00020000)
#define OTG_DTHRCTL_RXTHRLEN_1              (0x00040000)
#define OTG_DTHRCTL_RXTHRLEN_2              (0x00080000)
#define OTG_DTHRCTL_RXTHRLEN_3              (0x00100000)
#define OTG_DTHRCTL_RXTHRLEN_4              (0x00200000)
#define OTG_DTHRCTL_RXTHRLEN_5              (0x00400000)
#define OTG_DTHRCTL_RXTHRLEN_6              (0x00800000)
#define OTG_DTHRCTL_RXTHRLEN_7              (0x01000000)
#define OTG_DTHRCTL_RXTHRLEN_8              (0x02000000)
#define OTG_DTHRCTL_ARPEN                   (0x08000000)

/*  Bit definition for OTG_DIEPEMPMSK register  */
#define OTG_DIEPEMPMSK_INEPTXFEM            (0x0000FFFF)

/*  Bit definition for OTG_DEACHINT register  */
#define OTG_DEACHINT_IEP1INT                (0x00000002)
#define OTG_DEACHINT_OEP1INT                (0x00020000)


/* base */
#define OTG_EPIN_BASE            			(OTG_BASE + 0x900)
/* addresses */
#define OTG_EP0IN							((otg_epin_t *)OTG_EPIN_BASE + 0x00)
#define OTG_EP1IN							((otg_epin_t *)OTG_EPIN_BASE + 0x20)
#define OTG_EP2IN							((otg_epin_t *)OTG_EPIN_BASE + 0x40)
#define OTG_EP3IN							((otg_epin_t *)OTG_EPIN_BASE + 0x60)

/* input endpoint register */
typedef struct {
	reg32_t DIEPCTL;
	reg32_t _RESERVED0;
	reg32_t DIEPINT;
	reg32_t _RESERVED1;
	reg32_t DIEPTSIZ;
	reg32_t DIEPDMA;
	reg32_t DTXFSTS;
	reg32_t _RESERVED2;
} otg_epin_t;

/*  Bit definition for OTG_DIEPCTL register  */
#define OTG_DIEPCTL_MPSIZ                   (0x000007FF)
#define OTG_DIEPCTL_USBAEP                  (0x00008000)
#define OTG_DIEPCTL_EONUM_DPID              (0x00010000)
#define OTG_DIEPCTL_NAKSTS                  (0x00020000)
#define OTG_DIEPCTL_EPTYP                   (0x000C0000)
#define OTG_DIEPCTL_EPTYP_0                 (0x00040000)
#define OTG_DIEPCTL_EPTYP_1                 (0x00080000)
#define OTG_DIEPCTL_STALL                   (0x00200000)
#define OTG_DIEPCTL_TXFNUM                  (0x03C00000)
#define OTG_DIEPCTL_TXFNUM_0                (0x00400000)
#define OTG_DIEPCTL_TXFNUM_1                (0x00800000)
#define OTG_DIEPCTL_TXFNUM_2                (0x01000000)
#define OTG_DIEPCTL_TXFNUM_3                (0x02000000)
#define OTG_DIEPCTL_CNAK                    (0x04000000)
#define OTG_DIEPCTL_SNAK                    (0x08000000)
#define OTG_DIEPCTL_SD0PID_SEVNFRM          (0x10000000)
#define OTG_DIEPCTL_SODDFRM                 (0x20000000)
#define OTG_DIEPCTL_EPDIS                   (0x40000000)
#define OTG_DIEPCTL_EPENA                   (0x80000000)

/*  Bit definition for OTG_DIEPINT register  */
#define OTG_DIEPINT_XFRC                    (0x00000001)
#define OTG_DIEPINT_EPDISD                  (0x00000002)
#define OTG_DIEPINT_TOC                     (0x00000008)
#define OTG_DIEPINT_ITTXFE                  (0x00000010)
#define OTG_DIEPINT_INEPNE                  (0x00000040)
#define OTG_DIEPINT_TXFE                    (0x00000080)
#define OTG_DIEPINT_TXFIFOUDRN              (0x00000100)
#define OTG_DIEPINT_BNA                     (0x00000200)
#define OTG_DIEPINT_PKTDRPSTS               (0x00000800)
#define OTG_DIEPINT_BERR                    (0x00001000)
#define OTG_DIEPINT_NAK                     (0x00002000)

/*  Bit definition for OTG_DIEPTSIZ register  */
#define OTG_DIEPTSIZ_XFRSIZ                 (0x0007FFFF)
#define OTG_DIEPTSIZ_PKTCNT                 (0x1FF80000)
#define OTG_DIEPTSIZ_MULCNT                 (0x60000000)

/*  Bit definition for OTG_DIEPDMA register  */
#define OTG_DIEPDMA_DMAADDR                 (0xFFFFFFFF)

/*  Bit definition for OTG_DTXFSTS register  */
#define OTG_DTXFSTS_INEPTFSAV               (0x0000FFFF)


/* base */
#define OTG_EPOUT_BASE            			(OTG_BASE + 0xB00)
/* addresses */
#define OTG_EP0OUT							((otg_epout_t *)OTG_EPOUT_BASE + 0x00)
#define OTG_EP1OUT							((otg_epout_t *)OTG_EPOUT_BASE + 0x20)
#define OTG_EP2OUT							((otg_epout_t *)OTG_EPOUT_BASE + 0x40)
#define OTG_EP3OUT							((otg_epout_t *)OTG_EPOUT_BASE + 0x60)

/* output endpoint registers */
typedef struct {
	reg32_t DOEPCTL;
	reg32_t _RESERVED0;
	reg32_t DOEPINT;
	reg32_t _RESERVED1;
	reg32_t DOEPTSIZ;
	reg32_t DOEPDMA;
	reg32_t _RESERVED2[2];
} otg_epout_t;

/*  Bit definition for OTG_DOEPCTL register  */
#define OTG_DOEPCTL_MPSIZ                   (0x000007FF)
#define OTG_DOEPCTL_USBAEP                  (0x00008000)
#define OTG_DOEPCTL_NAKSTS                  (0x00020000)
#define OTG_DOEPCTL_SD0PID_SEVNFRM          (0x10000000)
#define OTG_DOEPCTL_SODDFRM                 (0x20000000)
#define OTG_DOEPCTL_EPTYP                   (0x000C0000)
#define OTG_DOEPCTL_EPTYP_0                 (0x00040000)
#define OTG_DOEPCTL_EPTYP_1                 (0x00080000)
#define OTG_DOEPCTL_SNPM                    (0x00100000)
#define OTG_DOEPCTL_STALL                   (0x00200000)
#define OTG_DOEPCTL_CNAK                    (0x04000000)
#define OTG_DOEPCTL_SNAK                    (0x08000000)
#define OTG_DOEPCTL_EPDIS                   (0x40000000)
#define OTG_DOEPCTL_EPENA                   (0x80000000)

/*  Bit definition for OTG_DOEPINT register  */
#define OTG_DOEPINT_XFRC                    (0x00000001)
#define OTG_DOEPINT_EPDISD                  (0x00000002)
#define OTG_DOEPINT_STUP                    (0x00000008)
#define OTG_DOEPINT_OTEPDIS                 (0x00000010)
#define OTG_DOEPINT_B2BSTUP                 (0x00000040)
#define OTG_DOEPINT_NYET                    (0x00004000)

/*  Bit definition for OTG_DOEPTSIZ register  */
#define OTG_DOEPTSIZ_XFRSIZ                 (0x0007FFFF)
#define OTG_DOEPTSIZ_PKTCNT                 (0x1FF80000)
#define OTG_DOEPTSIZ_STUPCNT                (0x60000000)
#define OTG_DOEPTSIZ_STUPCNT_0              (0x20000000)
#define OTG_DOEPTSIZ_STUPCNT_1              (0x40000000)


/* base */
#define OTG_HOST_BASE            			(OTG_BASE + 0x400)
/* addresses */
#define OTG_HOST							((otg_host_t *)OTG_HOST_BASE)

/* host mode registers */
typedef struct {
	reg32_t HCFG;
	reg32_t HFIR;
	reg32_t HFNUM;
	reg32_t _RESERVED0;
	reg32_t HPTXSTS;
	reg32_t HAINT;
	reg32_t HAINTMSK;
	reg32_t _RESERVED1[9];
	reg32_t HPRT;
} otg_host_t;

/*  Bit definition for OTG_HCFG register  */
#define OTG_HCFG_FSLSPCS                 	(0x00000003)
#define OTG_HCFG_FSLSPCS_0               	(0x00000001)
#define OTG_HCFG_FSLSPCS_1               	(0x00000002)
#define OTG_HCFG_FSLSS                   	(0x00000004)

/*  Bit definition for OTG_HFIR register  */
#define OTG_HFIR_FRIVL                   	(0x0000FFFF)

/*  Bit definition for OTG_HFNUM register  */
#define OTG_HFNUM_FRNUM                   	(0x0000FFFF)
#define OTG_HFNUM_FTREM                   	(0xFFFF0000)

/*  Bit definition for OTG_HPTXSTS register  */
#define OTG_HPTXSTS_PTXFSAVL                (0x0000FFFF)
#define OTG_HPTXSTS_PTXQSAV                 (0x00FF0000)
#define OTG_HPTXSTS_PTXQSAV_0               (0x00010000)
#define OTG_HPTXSTS_PTXQSAV_1               (0x00020000)
#define OTG_HPTXSTS_PTXQSAV_2               (0x00040000)
#define OTG_HPTXSTS_PTXQSAV_3               (0x00080000)
#define OTG_HPTXSTS_PTXQSAV_4               (0x00100000)
#define OTG_HPTXSTS_PTXQSAV_5               (0x00200000)
#define OTG_HPTXSTS_PTXQSAV_6               (0x00400000)
#define OTG_HPTXSTS_PTXQSAV_7               (0x00800000)
#define OTG_HPTXSTS_PTXQTOP                 (0xFF000000)
#define OTG_HPTXSTS_PTXQTOP_0               (0x01000000)
#define OTG_HPTXSTS_PTXQTOP_1               (0x02000000)
#define OTG_HPTXSTS_PTXQTOP_2               (0x04000000)
#define OTG_HPTXSTS_PTXQTOP_3               (0x08000000)
#define OTG_HPTXSTS_PTXQTOP_4               (0x10000000)
#define OTG_HPTXSTS_PTXQTOP_5               (0x20000000)
#define OTG_HPTXSTS_PTXQTOP_6               (0x40000000)
#define OTG_HPTXSTS_PTXQTOP_7               (0x80000000)

/*  Bit definition for OTG_HAINT register  */
#define OTG_HAINT_HAINT                   	(0x0000FFFF)

/*  Bit definition for OTG_HAINTMSK register  */
#define OTG_HAINTMSK_HAINTM                 (0x0000FFFF)

/*  Bit definition for OTG_HPRT register  */
#define OTG_HPRT_PCSTS                   	(0x00000001)
#define OTG_HPRT_PCDET                   	(0x00000002)
#define OTG_HPRT_PENA                    	(0x00000004)
#define OTG_HPRT_PENCHNG                 	(0x00000008)
#define OTG_HPRT_POCA                    	(0x00000010)
#define OTG_HPRT_POCCHNG                 	(0x00000020)
#define OTG_HPRT_PRES                    	(0x00000040)
#define OTG_HPRT_PSUSP                   	(0x00000080)
#define OTG_HPRT_PRST                    	(0x00000100)
#define OTG_HPRT_PLSTS                   	(0x00000C00)
#define OTG_HPRT_PLSTS_0                 	(0x00000400)
#define OTG_HPRT_PLSTS_1                 	(0x00000800)
#define OTG_HPRT_PPWR                    	(0x00001000)
#define OTG_HPRT_PTCTL                   	(0x0001E000)
#define OTG_HPRT_PTCTL_0                 	(0x00002000)
#define OTG_HPRT_PTCTL_1                 	(0x00004000)
#define OTG_HPRT_PTCTL_2                 	(0x00008000)
#define OTG_HPRT_PTCTL_3                 	(0x00010000)
#define OTG_HPRT_PSPD                    	(0x00060000)
#define OTG_HPRT_PSPD_0                  	(0x00020000)
#define OTG_HPRT_PSPD_1                  	(0x00040000)


/* base */
#define OTG_HC_BASE            				(OTG_BASE + 0x500)
/* addresses */
#define OTG_HC0								((otg_hc_t *)OTG_HC_BASE + 0x00)
#define OTG_HC1								((otg_hc_t *)OTG_HC_BASE + 0x20)
#define OTG_HC2								((otg_hc_t *)OTG_HC_BASE + 0x40)
#define OTG_HC3								((otg_hc_t *)OTG_HC_BASE + 0x60)
#define OTG_HC4								((otg_hc_t *)OTG_HC_BASE + 0x80)
#define OTG_HC5								((otg_hc_t *)OTG_HC_BASE + 0xA0)
#define OTG_HC6								((otg_hc_t *)OTG_HC_BASE + 0xC0)
#define OTG_HC7								((otg_hc_t *)OTG_HC_BASE + 0xE0)

/* host channel registers */
typedef struct {
	reg32_t HCCHAR;
	reg32_t HCSPLT;
	reg32_t HCINT;
	reg32_t HCINTMSK;
	reg32_t HCTSIZ;
	reg32_t HCDMA;
	reg32_t _RESERVED0[2];
} otg_hc_t;

/*  Bit definition for OTG_HCCHAR register  */
#define OTG_HCCHAR_MPSIZ                   	(0x000007FF)
#define OTG_HCCHAR_EPNUM                   	(0x00007800)
#define OTG_HCCHAR_EPNUM_0                 	(0x00000800)
#define OTG_HCCHAR_EPNUM_1                 	(0x00001000)
#define OTG_HCCHAR_EPNUM_2                 	(0x00002000)
#define OTG_HCCHAR_EPNUM_3                 	(0x00004000)
#define OTG_HCCHAR_EPDIR                   	(0x00008000)
#define OTG_HCCHAR_LSDEV                   	(0x00020000)
#define OTG_HCCHAR_EPTYP                   	(0x000C0000)
#define OTG_HCCHAR_EPTYP_0                 	(0x00040000)
#define OTG_HCCHAR_EPTYP_1                 	(0x00080000)
#define OTG_HCCHAR_MC                      	(0x00300000)
#define OTG_HCCHAR_MC_0                    	(0x00100000)
#define OTG_HCCHAR_MC_1                    	(0x00200000)
#define OTG_HCCHAR_DAD                     	(0x1FC00000)
#define OTG_HCCHAR_DAD_0                   	(0x00400000)
#define OTG_HCCHAR_DAD_1                   	(0x00800000)
#define OTG_HCCHAR_DAD_2                   	(0x01000000)
#define OTG_HCCHAR_DAD_3                   	(0x02000000)
#define OTG_HCCHAR_DAD_4                   	(0x04000000)
#define OTG_HCCHAR_DAD_5                   	(0x08000000)
#define OTG_HCCHAR_DAD_6                   	(0x10000000)
#define OTG_HCCHAR_ODDFRM                  	(0x20000000)
#define OTG_HCCHAR_CHDIS                   	(0x40000000)
#define OTG_HCCHAR_CHENA                   	(0x80000000)

/*  Bit definition for OTG_HCSPLT register  */
#define OTG_HCSPLT_PRTADDR                 	(0x0000007F)
#define OTG_HCSPLT_PRTADDR_0               	(0x00000001)
#define OTG_HCSPLT_PRTADDR_1               	(0x00000002)
#define OTG_HCSPLT_PRTADDR_2               	(0x00000004)
#define OTG_HCSPLT_PRTADDR_3               	(0x00000008)
#define OTG_HCSPLT_PRTADDR_4               	(0x00000010)
#define OTG_HCSPLT_PRTADDR_5               	(0x00000020)
#define OTG_HCSPLT_PRTADDR_6               	(0x00000040)
#define OTG_HCSPLT_HUBADDR                 	(0x00003F80)
#define OTG_HCSPLT_HUBADDR_0               	(0x00000080)
#define OTG_HCSPLT_HUBADDR_1               	(0x00000100)
#define OTG_HCSPLT_HUBADDR_2               	(0x00000200)
#define OTG_HCSPLT_HUBADDR_3               	(0x00000400)
#define OTG_HCSPLT_HUBADDR_4               	(0x00000800)
#define OTG_HCSPLT_HUBADDR_5               	(0x00001000)
#define OTG_HCSPLT_HUBADDR_6               	(0x00002000)
#define OTG_HCSPLT_XACTPOS                 	(0x0000C000)
#define OTG_HCSPLT_XACTPOS_0               	(0x00004000)
#define OTG_HCSPLT_XACTPOS_1               	(0x00008000)
#define OTG_HCSPLT_COMPLSPLT               	(0x00010000)
#define OTG_HCSPLT_SPLITEN                 	(0x80000000)

/*  Bit definition for OTG_HCINT register  */
#define OTG_HCINT_XFRC                    	(0x00000001)
#define OTG_HCINT_CHH                     	(0x00000002)
#define OTG_HCINT_AHBERR                  	(0x00000004)
#define OTG_HCINT_STALL                   	(0x00000008)
#define OTG_HCINT_NAK                     	(0x00000010)
#define OTG_HCINT_ACK                     	(0x00000020)
#define OTG_HCINT_NYET                    	(0x00000040)
#define OTG_HCINT_TXERR                   	(0x00000080)
#define OTG_HCINT_BBERR                   	(0x00000100)
#define OTG_HCINT_FRMOR                   	(0x00000200)
#define OTG_HCINT_DTERR                   	(0x00000400)

/*  Bit definition for OTG_HCINTMSK register  */
#define OTG_HCINTMSK_XFRCM                  (0x00000001)
#define OTG_HCINTMSK_CHHM                   (0x00000002)
#define OTG_HCINTMSK_AHBERR                 (0x00000004)
#define OTG_HCINTMSK_STALLM                 (0x00000008)
#define OTG_HCINTMSK_NAKM                   (0x00000010)
#define OTG_HCINTMSK_ACKM                   (0x00000020)
#define OTG_HCINTMSK_NYET                   (0x00000040)
#define OTG_HCINTMSK_TXERRM                 (0x00000080)
#define OTG_HCINTMSK_BBERRM                 (0x00000100)
#define OTG_HCINTMSK_FRMORM                 (0x00000200)
#define OTG_HCINTMSK_DTERRM                 (0x00000400)

/*  Bit definition for OTG_HCTSIZ register  */
#define OTG_HCTSIZ_XFRSIZ                   (0x0007FFFF)
#define OTG_HCTSIZ_PKTCNT                   (0x1FF80000)
#define OTG_HCTSIZ_DOPING                   (0x80000000)
#define OTG_HCTSIZ_DPID                     (0x60000000)
#define OTG_HCTSIZ_DPID_0                   (0x20000000)
#define OTG_HCTSIZ_DPID_1                   (0x40000000)

/*  Bit definition for OTG_HCDMA register  */
#define OTG_HCDMA_DMAADDR                   (0xFFFFFFFF)


/* base */
#define OTG_PCGC_BASE            			(OTG_BASE + 0xE00)
/* scb */
#define OTG_PCGC							((otg_pcgc_t *)OTG_PCGC_BASE)

/* usb power and clock gating registers */
typedef struct {
	reg32_t PCGCR;
} otg_pcgc_t;

/*  Bit definition for OTG_PCGCR register  */
#define OTG_PCGCR_STPPCLK                 	(0x00000001)
#define OTG_PCGCR_GATEHCLK                	(0x00000002)
#define OTG_PCGCR_PHYSUSP                 	(0x00000010)


#endif /* STM32F401_OTG_H_ */
