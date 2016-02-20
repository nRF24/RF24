/*
 * compatibility.c
 *
 * Created: 19/1/2016 15:31:35
 *  Author: akatran
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

volatile uint32_t _millis;
//volatile uint32_t _secsCounter;

void __msleep(int milisec)
{
	while(milisec-- >0)
	{
		_delay_ms(1);
	}
}

void __usleep(int usec)
{
	while(usec-- >0)
	{
		_delay_us(1);
	}
}


void __start_timer()
{
	
	// Timer details : Clock is 32MHz, Timer resolution is 8bit, Prescaler is 256, Period is 124, Real Time is 0.001s

	/* Set the timer to run at the fastest rate. */
	TCC0.CTRLA = TC_CLKSEL_DIV256_gc;

	/* Configure the timer for normal counting. */
	TCC0.CTRLB = TC_WGMODE_NORMAL_gc;

	/* At 2 MHz, one tick is 0.5 us.  Set period to 8 us. */
	TCC0.PER = 124;
	//TCC0.PER = 2;

	/* Configure timer to generate an interrupt on overflow. */
	TCC0.INTCTRLA = TC_OVFINTLVL_HI_gc;

	/* Enable this interrupt level. */
	PMIC.CTRL = PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm;
	
	_millis=0;
}

long __millis()
{
	return _millis;
}

void update_milisec()
{
	_millis++;
	//_secsCounter++;
	//if (_secsCounter>=1000)
	//{	
		//_secsCounter =0;
		//PORTF.OUTTGL = 128;
	//}
}




