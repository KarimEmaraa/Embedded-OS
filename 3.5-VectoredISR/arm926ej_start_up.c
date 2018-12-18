
#define VIC_BASE_ADDR 0x10140000

extern unsigned int  vectors_start, vectors_end;
extern unsigned char _bss_start, _bss_end;

void DefaultHandler(void);
void KBM_handler(void);
void Timer01_handler(void);
void Timer23_handler(void);
void UART0_handler(void);
void UART1_handler(void);
void WD_handler(void); //watch dog

enum _ints_sources {
	_WD,
	_SW,	
	_CommsRX,	//DEGUB RX
	_CommsTX,	//DEBUG TX
	_TIMER12,	//TIMER01
	_TIMER23,	//TIMER23
	_GPIO0,
	_GPIO1,
	_GPIO2,
	_GPIO3,
	_RTC,
	_SSP,
	_UART0,
	_UART1,
	_UART2,
	_SCI,
	_CLCDC,
	_DMA,
	_PWRFAIL,
	_MBX,
	_RESERVED0,
	_DISKONCHIP,
	_MCI0A,
	_RESERVED1,
	_AACI,
	_ETHERNET,
	_USB,
	_EXPANSION0,
	_EXPANSION1,
	_RESERVED2,
	_RESERBED3,
	_SIC			//Secondary interrupt controller KBM HERE
};


void copy_exceptions(void)
{
	unsigned int * vect_src = &vectors_start;
	unsigned int * vect_dest = (unsigned int *)0;
	while(vect_src != (&vectors_end))
	{
		*vect_dest = *vect_src;
		vect_dest++;
		vect_src++;
	}
}

void init_sections(void)
{
	unsigned char * bss_start = &_bss_start;
	unsigned char * bss_end = &_bss_end;
	while(bss_start <= bss_end)
		*bss_start++ = 0;
}

void (* const vects[16])(void) =  //vects and interrupt_sources MUST match
{
	WD_handler,			//Watch dog
	Timer01_handler,		//Timer01
	Timer23_handler,
	UART0_handler,			//uart1
	KBM_handler,			//kbm
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
	DefaultHandler,
};

unsigned int interrupt_sources[16] = {			//vects and interrupt_sources MUST match
	_WD,
	_TIMER12,
	_TIMER23,
	_UART0,
	_SIC,	//AKA KBD device
	

};


void copy_vectors(void)
{
	for(unsigned int i = 0x100, j = 0; i <= 0x13c; i+=4, j++)
	{
		*((unsigned int *)(VIC_BASE_ADDR+i)) = (unsigned int)vects[j];
	}
	
	for(unsigned int i = 0x200, j = 0; i <= 0x23c; i+=4, j++)
	{	
		*((unsigned int *)(VIC_BASE_ADDR + i)) = 0x20 + interrupt_sources[j]; //enable interrupt and select source
	}
	*((int *)(VIC_BASE_ADDR+0x0C)) = 0;
}








