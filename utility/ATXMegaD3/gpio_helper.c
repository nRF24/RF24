/*
 * gpio_helper.c
 *
 * Created: 22/1/2016 15:28:48
 *  Author: akatran
 */

#include "gpio_helper.h"

/**
 * Get the port corresponding in port_num. Default is PORTC.
 */
PORT_t* GPIO_getPort(int pin_num, uint8_t* pin_bm)
//PORT_t * GPIO_getPort(int port_num)
{
    PORT_t* port = &PORTC;
    if ((pin_num >= XMEGA_PORTA_PIN0) && (pin_num <= XMEGA_PORTA_PIN7)) {
        port = &PORTA;
        *pin_bm = (1 << pin_num);
    }
    else if ((pin_num >= XMEGA_PORTB_PIN0) && (pin_num <= XMEGA_PORTB_PIN7)) {
        port = &PORTB;
        *pin_bm = (1 << (pin_num - 8));
    }
    else if ((pin_num >= XMEGA_PORTC_PIN0) && (pin_num <= XMEGA_PORTC_PIN7)) {
        port = &PORTC;
        *pin_bm = (1 << (pin_num - 16));
    }
    else if ((pin_num >= XMEGA_PORTD_PIN0) && (pin_num <= XMEGA_PORTD_PIN7)) {
        port = &PORTD;
        *pin_bm = (1 << (pin_num - 24));
    }
    else if ((pin_num >= XMEGA_PORTE_PIN0) && (pin_num <= XMEGA_PORTE_PIN7)) {
        port = &PORTE;
        *pin_bm = (1 << (pin_num - 32));
    }
    else if ((pin_num >= XMEGA_PORTF_PIN0) && (pin_num <= XMEGA_PORTF_PIN7)) {
        port = &PORTF;
        *pin_bm = (1 << (pin_num - 40));
    }

    return port;
}
