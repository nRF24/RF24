/*
 Copyright (C) 2023 R. Krauthann <krauthann1@googlemail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Multiple Radio example using an additional spi bus.
 *
 * Example on how to connect multiple radios to different SPI busses on the
 * raspberry pi pico.
 *
 * Inspired by the previous documentation on how to customize SPI Pins.
 * See https://nrf24.github.io/RF24/md_docs_pico_sdk.html#autotoc_md53
 */

#include <RF24.h>

// one spi interface is already created by the rp2 utility of RF24, but we need
// one extra since we do not connect them on the same bus
// note that it is possible to do so, but you will need individual CE and CSN pins
SPI _spi1;

RF24 radio0(8, 5); // pin numbers connected to the radio's CE and CSN pins (respectively)
RF24 radio1(14, 13); 


int main()
{
    stdio_init_all();

    // check the pico SDK pins for spi0 and spi1
    spi.begin(spi0, 6, 7, 4); // spi0 or spi1 bus, SCK, TX, RX
    while (!radio0.begin(&spi)) {
        printf("Radio0 hardware is not responding!\n");
        sleep_ms(1000);
    }
    printf("Radio0 initalized!\n");

    _spi1.begin(spi1, 10, 11, 12);
    while (!radio1.begin(&_spi1)) {
        printf("Radio1 hardware is not responding!\n");
        sleep_ms(1000);
    }
    printf("Radio1 initalized!\n");

    // continue with program as normal ...
    while(true){
        // do stuff
        sleep_ms(1000);
    }
}