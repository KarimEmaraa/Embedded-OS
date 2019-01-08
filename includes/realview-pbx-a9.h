
#ifndef _REALVIEW_PBX_A9_H_
#define _REALVIEW_PBX_A9_H_

/*Peripheral struct definitions*/
typedef volatile struct uart{
	unsigned int DR;
	unsigned int DSR;
	unsigned int reserved0[4];
	unsigned int FR;
	unsigned int const reserved1[1];
	unsigned int LPR;
	unsigned int IBRD;
	unsigned int FBRD;
	unsigned int LCR_H;
	unsigned int TCR;
	unsigned int IFLS;
	unsigned int IMSC;
	unsigned int const RIS;
	unsigned int const MIS;
	unsigned int ICR;
	unsigned int MACR;
	unsigned int const reserved2[997];
	unsigned int const UARTPeriphID0;
	unsigned int const UARTPeriphID1;
	unsigned int const UARTPeriphID2;
	unsigned int const UARTPeriphID3;
	unsigned int const UARTPCellID0;
	unsigned int const UARTPCellID1;
	unsigned int const UARTPCellID2;
	unsigned int const UARTPCellID3;
}UART_Type;

typedef volatile struct clcd{

	unsigned int Timing0;
	unsigned int Timing1;
	unsigned int Timing2;
	unsigned int Timing3;
	unsigned int UPBASE;
	unsigned int LPBASE;
	unsigned int Control;
	unsigned int IMSC;
	unsigned int const RIS;
	unsigned int const MIS;
	unsigned int ICR;
	unsigned int const UPCURR;
	unsigned int const LPCURR;
	unsigned int const reserved0[115];
	unsigned int Pallette[128];
	unsigned int const reserved1[256];
	unsigned int CursorImage[256];
	unsigned int CrsrCtrl;
	unsigned int CrsrConfig;
	unsigned int CrsrPalette0;
	unsigned int CrsrPalette1;
	unsigned int CrsrXY;
	unsigned int CrsrClip;
	unsigned int reserved2[2];
	unsigned int CrsrIMSC;
	unsigned int CrsrICR;
	unsigned int CrsrRIS;
	unsigned int CrsrMIS;
	unsigned int const reserved3[236];
	unsigned int const CLCDPERIPHID0;
	unsigned int const CLCDPERIPHID1;
	unsigned int const CLCDPERIPHID2;
	unsigned int const CLCDPERIPHID3;
	unsigned int const CLCDPCELLID0;
	unsigned int const CLCDPCELLID1;
	unsigned int const CLCDPCELLID2;
	unsigned int const CLCDPCELLID3;
	
}CLCD_Type;

typedef volatile struct scr{
	unsigned int const ID;
	unsigned int const SW;
	unsigned int LED;
	unsigned int OSC0;
	unsigned int OSC1;
	unsigned int OSC2;
	unsigned int OSC3;
	unsigned int OSC4;
	unsigned int LOCK;
	unsigned int _100HZ;
	unsigned int const reserved1[2];
	unsigned int const FLAGS;
	unsigned int FLAGSSET;
	unsigned int FLAGSCLR;
	unsigned int const NVFLAGS;
	unsigned int NVFLAGSSET;
	unsigned int NVFLAGSCLR;
	unsigned int RESETCTL;
	unsigned int const reserved2[1];
	unsigned int const MCI;
	unsigned int FLASH;
	unsigned int CLCD;
	unsigned int const reserved3[1];
	unsigned int const CFGSW;
	unsigned int const _24MHZ;
	unsigned int const MISC;
	unsigned int DMAPSR;
	unsigned int const PEX_STAT;
	unsigned int PCI_STAT;
/*TO BE CONTIUNED*/
	unsigned int const reserved4[1];
	unsigned int const TEST_OSC0;
	unsigned int const reserved5[4];

}SCR_Type;

/*Peripheral Base Addresses*/
#define UART_BASE 		((unsigned int)0x10009000)
#define CLCD_BASE		((unsigned int)0x10020000)
#define SCR_BASE		((unsigned int)0x10000000)


/*Peripherals memory map*/
#define UART0_BASE 		(UART_BASE + 0x0000)
#define UART1_BASE		(UART_BASE + 0x1000)
#define UART2_BASE		(UART_BASE + 0x2000)
#define UART3_BASE		(UART_NASE + 0x3000)

/*Peripherals decelaration*/

#define UART0			((UART_Type *)UART0_BASE)
#define UART1			((UART_Type *)UART1_BASE)
#define UART2			((UART_Type *)UART2_BASE)
#define UART3			((UART_Type *)UART3_BASE)
#define CLCD			((CLCD_Type *)CLCD_BASE)
#define SCR			((SCR_Type *)SCR_BASE)	
		




#endif
