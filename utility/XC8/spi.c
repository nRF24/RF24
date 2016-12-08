
#include"xc8_config.h"
#include"spi.h"

unsigned long mtime;

long millis(void)
{
    return mtime;
}


#define NREP (_XTAL_FREQ/(4000l*10)) 
//ms delay
void delay(uint16_t val)
{
unsigned int  i;
unsigned int j;

 for (i =0; i< val; i++)
 {
 
  for (j =0 ; j < NREP; j++)
   {
    __asm
	NOP
	NOP
	NOP
	NOP
	NOP
    NOP
	NOP
	NOP
	NOP
	NOP
    __endasm;
   }
 }
}


#define UNREP (_XTAL_FREQ/(4000000l))

void delayMicroseconds(uint8_t d)
{
    unsigned int i,j; 
    for(i=0;i<d;i++)
      for (j =0 ; j < UNREP; j++)
      {
       __asm
	   NOP
      __endasm;
   }
}



void SPI_begin(void)
{
#ifdef _18F4550
//RF_MISO 
    TRISBbits.TRISB0=1; //33
//RF_CLK  
    TRISBbits.TRISB1=0; //34
//RF_MOSI 
    TRISCbits.TRISC7=0; //26   
#else  //PIC18F4620  
//RF_MISO 
    TRISCbits.TRISC4=1; 
//RF_CLK  
    TRISCbits.TRISC3=0;
//RF_MOSI 
    TRISCbits.TRISC5=0;
#endif

#ifdef _16F877A   
    SSPCON=0x00;
    //SSPSTATbits.CKE=1;
    //SSPSTATbits.SMP=0;//0
    //SMP CKE D/A P S R/W UA BF
    SSPSTAT=0b01000000;
    //SSPCONbits.CKP=0;
    //SSPCONbits.SSPM=1;// FOSC/16
    //SSPCONbits.SSPEN=1;
    //WCOL SSPOV SSPEN  CKP SSPM3  SSPM2 SSPM1 SSPM0
    SSPCON=0b00100001;
#else
    SSPCON1=0x00;
    //SSPSTATbits.CKE=1;
    //SSPSTATbits.SMP=0;//0
    //SMP CKE D/A P S R/W UA BF
    SSPSTAT=0b01000000;
    //SSPCON1bits.SSPEN=0;
    //SSPCON1bits.CKP=0;
    //SSPCON1bits.SSPM=1;// FOSC/16
    //SSPCON1bits.SSPEN=1;   
    //WCOL SSPOV SSPEN  CKP SSPM3  SSPM2 SSPM1 SSPM0
    SSPCON1=0b00100001;
#endif    
}

uint8_t SPI_transfer(uint8_t data)
{
    SSPSTATbits.BF = 0;
    SSPBUF = data;  // Put value into SPI buffer
    while (!SSPSTATbits.BF);         // Wait for the transfer to finish
    return SSPBUF;
}
        