/* ########################################################################

   PICsim - PIC simulator http://sourceforge.net/projects/picsim/

   ########################################################################

   Copyright (c) : 2014-2016  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include "xc8_config.h"

#include <stdio.h>
#include <stdlib.h>

void Serial_begin_(unsigned char baud)
{
    TRISCbits.TRISC6=1;
    TRISCbits.TRISC7=1;
    
    //          BRG16=0         BRG16=1
    //BRGH=0 FOSC/[64(n+1)]    FOSC/[16(n+1)]
    //BRGH=1 FOSC/[16(n+1)]    FOSC/[4(n+1)]
 
    SPBRG = baud; //baud rate de 115200 - 32MHz
    //SPBRGH=(0xFF00 & baud)>>8; 
    //BAUDCONbits.BRG16=1; //16 bits baud rate
    
	  //Serial configuration
    //TXSTAbits.TX9=0;    //transmissao em 8 bits
    //TXSTAbits.SYNC=0;  //modo assincrono
    //TXSTAbits.BRGH=1;  //high baud rate
    //TXSTAbits.TXEN=1;  //habilita transmissao
    //CSRC TX9 TXEN SYNC SENDB BRGH TRMT TX9D
    TXSTA = 0b00100100; 
    //RCSTAbits.RX9=0;   //recepcao em 8 bits
    //RCSTAbits.CREN=1;  //recepcao continua
    //RCSTAbits.SPEN=1;  //habilita porta serial - rx
    //SPEN RX9 SREN CREN ADDEN FERR OERR RX9D
    RCSTA = 0b10010000;
}



void Serial_tx(const unsigned char val)
{
  TXREG=val;
  while(!TXSTAbits.TRMT);
}

void Serial_print(const char* val)
{
  unsigned int i=0;
  
  while(val[i])
  {
    Serial_tx(val[i]);
    i++; 
  }
}

void Serial_println(const char* val)
{
   Serial_print(val);
   Serial_print("\r\n");
}

unsigned char Serial_rx(unsigned int timeout)
{
  unsigned int to=0;

  if(RCSTAbits.FERR || RCSTAbits.OERR)//trata erro
  {
      RCSTAbits.CREN=0;
      RCSTAbits.CREN=1;
  }

  while(((to < timeout)||(!timeout))&&(!PIR1bits.RCIF))
  {
    delay(20);
    to+=20; 
  }
  if(PIR1bits.RCIF)
    return RCREG;
  else
    return 0xA5;
}


char buff[10];//for itoa

const char * itoa_(uint32_t val)
{
#ifdef __XC8
    ultoa(buff,val,10);
#else
    ultoa(val,buff,10);
#endif    
  return buff;
}