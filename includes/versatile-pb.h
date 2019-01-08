
#ifndef _REALVIEW_PBX_A9_H_
#define _REALVIEW_PBX_A9_H_


/*Peripheral struct definitions*/
typedef volatile struct uart{
	unsigned int DR;
	unsigned int RSR;
	unsigned int const reserved0[4];
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
	unsigned int IMSC;
	unsigned int Control;
	unsigned int const RIS;
	unsigned int const MIS;
	unsigned int ICR;
	unsigned int const UPCURR;
	unsigned int const LPCURR;
	unsigned int const reserved0[115];
	unsigned int Pallette[128];
	unsigned int reserved1[760];
	unsigned int const PERIPHID0;
	unsigned int const PERIPHID1;
	unsigned int const PERIPHID2;
	unsigned int const PERIPHID3;
	unsigned int const PCELLID0;
	unsigned int const PCELLID1;
	unsigned int const PCELLID2;
	unsigned int const PCELLID3;
	
}CLCD_Type;

typedef volatile struct scr{
	unsigned int const ID;
	unsigned int const SW;
	unsigned int LED;
	unsigned int OSC0;
	unsigned int const reserved0[3];
	unsigned int OSC1;
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
	unsigned int const reserved3[2];
	unsigned int const _24MHZ;
	unsigned int const MISC;
	unsigned int const reserved4[8];
	unsigned int const TEST_OSC0;
	unsigned int const reserved5[4];

}SCR_Type;

typedef volatile struct timer{
	unsigned int LOAD;
	unsigned int const VALUE;
	unsigned int CONTROL;
	unsigned int INTCLR;
	unsigned int const RIS;
	unsigned int const MIS;
	unsigned int BGLOAD;
	unsigned int const reserved0[1];
	//TImer 2 registers
	unsigned int T2LOAD;
	unsigned int const T2VALUE;
	unsigned int T2CONTROL;
	unsigned int T2INTCLR;
	unsigned int const T2RIS;
	unsigned int const T2MIS;
	unsigned int T2BGLOAD;
	unsigned int const reserved1[944];
	unsigned int ITCR;
	unsigned int ITOP;
	unsigned int const reserved2[54];
	unsigned int const PERIPHID0;
	unsigned int const PERIPHID1;
	unsigned int const PERIPHID2;
	unsigned int const PERIPHID3;
	unsigned int const PCELLID0;
	unsigned int const PCELLID1;
	unsigned int const PCELLID2;
	unsigned int const PCELLID3;
	
}TIMER_Type;


typedef volatile struct vic{
	unsigned int const IRQSTATUS;
	unsigned int const FIQSTATUS;
	unsigned int const RAWINTR;
	unsigned int INTSELECT;
	unsigned int INTENABLE;
	unsigned int INTENCLEAR;
	unsigned int SOFTINT;
	unsigned int SOFTINTCLEAR;
	unsigned int PROTECTION;
	unsigned int VECTADDR;
	unsigned int DEFVECTADDR;
	unsigned int const reserved0[50];
	unsigned int VECTADDR0;
	unsigned int VECTADDR1;
	unsigned int VECTADDR2;
	unsigned int VECTADDR3;
	unsigned int VECTADDR4;
	unsigned int VECTADDR5;
	unsigned int VECTADDR6;
	unsigned int VECTADDR7;
	unsigned int VECTADDR8;
	unsigned int VECTADDR9;
	unsigned int VECTADDR10;
	unsigned int VECTADDR11;
	unsigned int VECTADDR12;
	unsigned int VECTADDR13;
	unsigned int VECTADDR14;
	unsigned int VECTADDR15;
	unsigned int const reserved1[48];
	unsigned int VECTCNTL0;
	unsigned int VECTCNTL1;
	unsigned int VECTCNTL2;
	unsigned int VECTCNTL3;
	unsigned int VECTCNTL4;
	unsigned int VECTCNTL5;
	unsigned int VECTCNTL6;
	unsigned int VECTCNTL7;
	unsigned int VECTCNTL8;
	unsigned int VECTCNTL9;
	unsigned int VECTCNTL10;
	unsigned int VECTCNTL11;
	unsigned int VECTCNTL12;
	unsigned int VECTCNTL13;
	unsigned int VECTCNTL14;
	unsigned int VECTCNTL15;
	unsigned int const reserved2[872];
	unsigned int const PERIPHID0;
	unsigned int const PERIPHID1;
	unsigned int const PERIPHID2;
	unsigned int const PERIPHID3;
	unsigned int const PCELLID0;
	unsigned int const PCELLID1;
	unsigned int const PCELLID2;
	unsigned int const PCELLID3;

}VIC_Type;


#define ENSET ENABLE
#define PICENSET PICENABLE

typedef volatile struct sic{
	unsigned int const STATUS;
	unsigned int const RAWSTAT;
	unsigned int ENABLE;
	unsigned int ENCLR;
	unsigned int SOFTINTSET;
	unsigned int SOFTINTCLR;
	unsigned int const reserved0[2];
	unsigned int PICENABLE;
	unsigned int PICENCLR;
}SIC_Type;

typedef volatile struct kbm{
	unsigned int ICR;
	unsigned const int STAT;
	unsigned int DATA;
	unsigned int CLKDIV;
	unsigned int IR;
	unsigned const char reserved0[235];
}KBM_Type;

/*Peripheral Base Addresses*/
#define UART_BASE 		((unsigned int)0x101F1000)
#define CLCD_BASE		((unsigned int)0x10120000)
#define SCR_BASE		((unsigned int)0x10000000)
#define TIMER_BASE		((unsigned int)0x101E2000)
#define VIC_BASE		((unsigned int)0x10140000)
#define KB_BASE			((unsigned int)0x10006000)
#define MOUSE_BASE		((unsigned int)0x10007000)
#define SIC_BASE		((unsigned int)0x10003000)


/*Peripherals memory map*/
#define UART0_BASE 		(UART_BASE + 0x0000)
#define UART1_BASE		(UART_BASE + 0x1000)
#define UART2_BASE		(UART_BASE + 0x2000)
#define TIMER01_BASE		(TIMER_BASE + 0x000)
#define TIMER23_BASE		(TIMER_BASE + 0x1000)

/*Peripherals decelaration*/

#define UART0			((UART_Type *)UART0_BASE)
#define UART1			((UART_Type *)UART1_BASE)
#define UART2			((UART_Type *)UART2_BASE)
#define UART3			((UART_Type *)UART3_BASE)
#define CLCD			((CLCD_Type *)CLCD_BASE)
#define SCR			((SCR_Type *)SCR_BASE)
#define TIMER01			((TIMER_Type *)TIMER01_BASE)
#define TIMER23			((TIMER_Type *)TIMER23_BASE)
#define VIC			((VIC_Type *)VIC_BASE)
#define KB			((KBM_Type *)KB_BASE)
#define MOUSE			((KBM_Type *)MOUSE_BASE)
#define SIC			((SIC_Type *)SIC_BASE)




#endif
