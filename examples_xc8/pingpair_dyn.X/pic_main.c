

#include "xc8_config.h"
#include"config_pic.h"

void setup(void);
void loop(void);

#define _T1 65536l-(_XTAL_FREQ/4000l) //ciclos para 1 ms usando 50 instruções
#define _T1H  (_T1&0xFF00)>>8 
#define _T1L  (_T1&0x00FF) 

#ifdef __XC8
void interrupt isr(void)
#else
void isr(void) __shadowregs __interrupt 1
#endif
{
    if(PIR1bits.TMR1IF)
    {
        TMR1H=_T1H; 
        TMR1L=_T1L; //1000ms=1us*1*(65536-3036)
        mtime++;
        PIR1bits.TMR1IF=0;
    }
}


void main()
{
    mtime=0;
    //Configura TMR1

    //PIR1bits.TMR1IF=0;
    PIR1=0x00; 
    //INTCONbits.GIE = 1;
    //INTCONbits.PEIE=1;
    INTCON=0xC0;
    //PIE1bits.TMR1IE = 1;
    PIE1=0x01;
    TMR1H=_T1H; 
    TMR1L=_T1L; 
    //T1CONbits.TMR1CS=0;
    //T1CONbits.T1CKPS=0;
    //T1CONbits.TMR1ON=1;
    T1CON=0x01;
    
    setup();
    
            
    while(1)
    {
        loop();
    }

}

