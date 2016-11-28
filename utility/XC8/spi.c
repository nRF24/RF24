
#include"xc8_config.h"
#include"spi.h"

unsigned long mtime;


void pinMode(uint8_t pin,uint8_t mode)
{
  switch(pin)
  {
    case 1: TRISEbits.RE3=mode; break;
    case 2: TRISAbits.RA0=mode; break;
    case 3: TRISAbits.RA1=mode; break;
    case 4: TRISAbits.RA2=mode; break;
    case 5: TRISAbits.RA3=mode; break;
    case 6: TRISAbits.RA4=mode; break;
    case 7: TRISAbits.RA5=mode; break;
    case 8: TRISEbits.RE0=mode; break;
    case 9: TRISEbits.RE1=mode; break;
    case 10: TRISEbits.RE2=mode; break;
    //case 11: VDD; break;
    //case 12: VSS; break;
    case 13: TRISAbits.RA7=mode; break;
    case 14: TRISAbits.RA6=mode; break;
    case 15: TRISCbits.RC0=mode; break;
    case 16: TRISCbits.RC1=mode; break;
    case 17: TRISCbits.RC2=mode; break;
    case 18: TRISCbits.RC3=mode; break;
    case 19: TRISDbits.RD0=mode; break;
    case 20: TRISDbits.RD1=mode; break;
    case 21: TRISDbits.RD2=mode; break;
    case 22: TRISDbits.RD3=mode; break;
    case 23: TRISCbits.RC4=mode; break;
    case 24: TRISCbits.RC5=mode; break;
    case 25: TRISCbits.RC6=mode; break;
    case 26: TRISCbits.RC7=mode; break;
    case 27: TRISDbits.RD4=mode; break;
    case 28: TRISDbits.RD5=mode; break;
    case 29: TRISDbits.RD6=mode; break;
    case 30: TRISDbits.RD7=mode; break;
    //case 31: VSS; break;
    //case 32: VDD; break;
    case 33: TRISBbits.RB0=mode; break;
    case 34: TRISBbits.RB1=mode; break;
    case 35: TRISBbits.RB2=mode; break;
    case 36: TRISBbits.RB3=mode; break;
    case 37: TRISBbits.RB4=mode; break;
    case 38: TRISBbits.RB5=mode; break;
    case 39: TRISBbits.RB6=mode; break;
    case 40: TRISBbits.RB7=mode; break;
    default: break;
  }
}

void digitalWrite(uint8_t pin,uint8_t mode)
{
  switch(pin)
  {
    //case 1: LATEbits.LATE3=mode; break;
    case 2: LATAbits.LATA0=mode; break;
    case 3: LATAbits.LATA1=mode; break;
    case 4: LATAbits.LATA2=mode; break;
    case 5: LATAbits.LATA3=mode; break;
    case 6: LATAbits.LATA4=mode; break;
    case 7: LATAbits.LATA5=mode; break;
    case 8: LATEbits.LATE0=mode; break;
    case 9: LATEbits.LATE1=mode; break;
    case 10: LATEbits.LATE2=mode; break;
    //case 11: VDD; break;
    //case 12: VSS; break;
    case 13: LATAbits.LATA7=mode; break;
    case 14: LATAbits.LATA6=mode; break;
    case 15: LATCbits.LATC0=mode; break;
    case 16: LATCbits.LATC1=mode; break;
    case 17: LATCbits.LATC2=mode; break;
    case 18: LATCbits.LATC3=mode; break;
    case 19: LATDbits.LATD0=mode; break;
    case 20: LATDbits.LATD1=mode; break;
    case 21: LATDbits.LATD2=mode; break;
    case 22: LATDbits.LATD3=mode; break;
    case 23: LATCbits.LATC4=mode; break;
    case 24: LATCbits.LATC5=mode; break;
    case 25: LATCbits.LATC6=mode; break;
    case 26: LATCbits.LATC7=mode; break;
    case 27: LATDbits.LATD4=mode; break;
    case 28: LATDbits.LATD5=mode; break;
    case 29: LATDbits.LATD6=mode; break;
    case 30: LATDbits.LATD7=mode; break;
    //case 31: VSS; break;
    //case 32: VDD; break;
    case 33: LATBbits.LATB0=mode; break;
    case 34: LATBbits.LATB1=mode; break;
    case 35: LATBbits.LATB2=mode; break;
    case 36: LATBbits.LATB3=mode; break;
    case 37: LATBbits.LATB4=mode; break;
    case 38: LATBbits.LATB5=mode; break;
    case 39: LATBbits.LATB6=mode; break;
    case 40: LATBbits.LATB7=mode; break;
    default: break;
  }
}


uint8_t digitalRead(uint8_t pin)
{
  uint8_t ret =0;  
  
  switch(pin)
  {
    case 1: ret= PORTEbits.RE3; break;
    case 2: ret= PORTAbits.RA0; break;
    case 3: ret= PORTAbits.RA1; break;
    case 4: ret= PORTAbits.RA2; break;
    case 5: ret= PORTAbits.RA3; break;
    case 6: ret= PORTAbits.RA4; break;
    case 7: ret= PORTAbits.RA5; break;
    case 8: ret= PORTEbits.RE0; break;
    case 9: ret= PORTEbits.RE1; break;
    case 10: ret= PORTEbits.RE2; break;
    //case 11: VDD; break;
    //case 12: VSS; break;
    case 13: ret= PORTAbits.RA7; break;
    case 14: ret= PORTAbits.RA6; break;
    case 15: ret= PORTCbits.RC0; break;
    case 16: ret= PORTCbits.RC1; break;
    case 17: ret= PORTCbits.RC2; break;
    case 18: ret= PORTCbits.RC3; break;
    case 19: ret= PORTDbits.RD0; break;
    case 20: ret= PORTDbits.RD1; break;
    case 21: ret= PORTDbits.RD2; break;
    case 22: ret= PORTDbits.RD3; break;
    case 23: ret= PORTCbits.RC4; break;
    case 24: ret= PORTCbits.RC5; break;
    case 25: ret= PORTCbits.RC6; break;
    case 26: ret= PORTCbits.RC7; break;
    case 27: ret= PORTDbits.RD4; break;
    case 28: ret= PORTDbits.RD5; break;
    case 29: ret= PORTDbits.RD6; break;
    case 30: ret= PORTDbits.RD7; break;
    //case 31: VSS; break;
    //case 32: VDD; break;
    case 33: ret= PORTBbits.RB0; break;
    case 34: ret= PORTBbits.RB1; break;
    case 35: ret= PORTBbits.RB2; break;
    case 36: ret= PORTBbits.RB3; break;
    case 37: ret= PORTBbits.RB4; break;
    case 38: ret= PORTBbits.RB5; break;
    case 39: ret= PORTBbits.RB6; break;
    case 40: ret= PORTBbits.RB7; break;
    default: break;
  }
  
  return ret;  
}

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
//RF_MISO 
    TRISCbits.TRISC4=1; 
//RF_CLK  
    TRISCbits.TRISC3=0;
//RF_MOSI 
    TRISCbits.TRISC5=0;
    
    SSPCON1bits.SSPEN=0;
    SSPSTATbits.CKE=1;
    SSPCON1bits.CKP=0;
    SSPSTATbits.SMP=0;//0
    SSPCON1bits.SSPM=1;// FOSC/16
    SSPCON1bits.SSPEN=1;
}

uint8_t SPI_transfer(uint8_t data)
{
    SSPSTATbits.BF = 0;
    SSPBUF = data;  // Put value into SPI buffer
    while (!SSPSTATbits.BF);         // Wait for the transfer to finish
    return SSPBUF;
}
        