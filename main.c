//#include"uart3.h"
//#include"gpio.h"

//RegisterdefinitionsforClockEnable
#define SYSCTL_RCGCUART_R ( *((volatile unsigned long*) 0x400FE618))
#define SYSCTL_RCGCGPIO_R  ( * ((volatile unsigned long*) 0x400FE608))

//RegisterdefinitionsforGPIOPortD
#define GPIO_PORTD_AFSEL_R ( * ((volatile unsigned long*) 0x40007420))
#define GPIO_PORTD_PCTL_R ( * ((volatile unsigned long*) 0x4000752C))
#define GPIO_PORTD_DEN_R ( * ((volatile unsigned long*) 0x4000751C))
#define GPIO_PORTD_DIR_R ( * ((volatile unsigned long*) 0x40007400))
#define GPIO_PORTD_LOCK_R ( * ((volatile unsigned long*) 0x40007520))
#define GPIO_PORTD_CR_R (*( ( volatile unsigned long *) 0x40007524 ) )
//#define GPIOPORTDCRR ( * ((volatile unsigned long*) 0x40007524))

//RegisterdefinitionsforUART2module
#define UART2_CTL_R ( * ((volatile unsigned long*) 0x4000E030))//CONTROL
#define UART2_IBRD_R ( * ((volatile unsigned long*) 0x4000E024))//BAUD_INT
#define UART2_FBRD_R ( * ((volatile unsigned long*) 0x4000E028))//BAUD_FRAC
#define UART2_LCRH_R ( * ((volatile unsigned long*) 0x4000E02C))//LINE_CONTROL
#define UART2_CC_R ( * ((volatile unsigned long*) 0x4000EFC8))//clock_config
#define UART2_FR_R ( * ((volatile unsigned long*) 0x4000E018))//FLAG
#define UART2_DR_R ( * ((volatile unsigned long*) 0x4000E000))//DATA

//MacrosforinitializationandconfigurationofUART2
#define UART2_CLK_EN  0x00000004//EnableclockforUART2
#define GPIO_PORTD_CLK_EN  0x00000008//EnableclockforGPIOPORTD

#define GPIO_PORTD_UART2_CFG  0x000000C0//Digitalenable    FOR PIN 6 7
//Activatealternatefunction
//forPD6andPD7
#define GPIO_PCTL_PD6_U2RX 0x01000000//ConfigurePD6asU2RX
#define GPIO_PCTL_PD7_U2TX 0x10000000//ConfigurePD7asU2TX
#define GPIO_PORTD_UNLOCK_CR 0x4C4F434B//UnlockCommitregister
#define GPIO_PORTD_CR_EN 0x000000FF//Disablewriteprotection

#define UART_CS_SysClk 0x00000000//UsesystemasUARTclock              
#define UART_CS_PIOSC 0x00000005//UsePIOSCasUARTclock
#define UART_LCRH_WLEN_8 0x00000000//8bitwordlength
#define UART_LCRH_FEN 0x00000010//EnableUARTFIFOs
#define UART_FR_TXFF 0x00000020//UARTTransmitFIFOFull
#define UART_FR_RXFE 0x00000010//UARTReceiveFIFOEmpty
#define UART_CTL_UARTEN 0x00000001//EnableUART
#define UART_LB_EN 0x00000080//UseUARTinLoopbackmode

//Functiondefinitions
unsigned char UART_Rx(void);
void UART_Tx(unsigned char data);
void UART_Tx_String (char*pt);
void UART_Rx_String(char*bufPt,unsigned short max);

//IntializeandconfigureUART
void UART_Init(void)
	{

//EnableclockforUART2andGPIOPortD
SYSCTL_RCGCUART_R |= 0x00000004; //ActivateUART2
SYSCTL_RCGCGPIO_R |= 0x00000008 ;//ActivatePortD

//ConfigurationtousePD6andPD7asUART
GPIO_PORTD_LOCK_R=0x4C4F434B;//Unlockcommitregister
GPIO_PORTD_CR_R |= 0x000000FF;    //EnableU2TxonPD7

GPIO_PORTD_DEN_R|= 0x000000C0;//EnabledigitalI/OonPD6

GPIO_PORTD_AFSEL_R|= 0x000000C0;//Enablealt.func.onPD6-7
GPIO_PORTD_PCTL_R|=0x11000000;

//ConfigurationofUART2module
		
UART2_CTL_R &= ~(0x00000001); //DisableUART
//IBRD=int(16,000,000/(16*115,200))=int(8.6805)
UART2_IBRD_R=104;
//FBRD=int(0.6805*64+0.5)=44
UART2_FBRD_R=11;
//8-bitwordlength,noparitybit,onestopbit,FIFOsenable
UART2_LCRH_R=0x00000020;
UART2_CC_R=0x00000000;//UsesystemclockasUARTclock
//UART2CTLR|=UARTLBEN;//Enableloopbackmode
UART2_CTL_R|=0x00000001;//EnableUART2

}

//WaitforinputandreturnsitsASCIIvalue
unsigned char UART_Rx(void)
	{
while((UART2_FR_R & UART_FR_RXFE)!=0);  //UART_FR_RXFE=1 means receiver fifo donot have data           ??
return((unsigned char)(UART2_DR_R & 0xFF));
}

/*Accepts ASCII characters from the serial port and
adds them to a string.Itechoeseachcharacterasit
is in putted.*/
void UART_Rx_String(char*pt,unsigned short max)
	{
int length=0;
char character;

character = UART_Rx();
if(length < max)
	{
*pt=character;
pt++;
length++;
UART_Tx(character);
}

*pt=0;
}

//Output8-bittoserialport
void UART_Tx(unsigned char data)
	{
while((UART2_FR_R & UART_FR_TXFF)!=0);
UART2_DR_R = data;
}


//Outputacharacterstringtoserialport
void UART_Tx_String (char *pt)
	{
while ( *pt)
	{
UART_Tx ( *pt);
pt++;
	}
}

int main(void)
	{

char string[17];

UART_Init();

//Theinputgivenusingkeyboardisdisplayedonhyperterminal
//.i.e.,dataisechoed
//UART_Tx_String( "Enter Text:");

while(1)
	{
UART_Rx_String(string,16);
	
	
	
	}
}