/*
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "nRF24L01.h"
#include "RF24_config.h"
#include "RF24.h"
#include <stdio.h>

/****************************************************************************/

void RF24::csn(bool mode)
{
    #if defined(RF24_TINY)
    if (ce_pin != csn_pin) {
        digitalWrite(csn_pin, mode);
    }
    else {
        if (mode == HIGH) {
            PORTB |= (1<<PINB2);  	                       // SCK->CSN HIGH
            delayMicroseconds(RF24_CSN_SETTLE_HIGH_DELAY); // allow csn to settle.
        }
        else {
            PORTB &= ~(1<<PINB2);	                      // SCK->CSN LOW
            delayMicroseconds(RF24_CSN_SETTLE_LOW_DELAY); // allow csn to settle
        }
    }
    // Return, CSN toggle complete
    return;

    #elif defined (ARDUINO) && !defined(RF24_SPI_TRANSACTIONS)
    // Minimum ideal SPI bus speed is 2x data rate
    // If we assume 2Mbs data rate and 16Mhz clock, a
    // divider of 4 is the minimum we want.
    // CLK:BUS 8Mhz:2Mhz, 16Mhz:4Mhz, or 20Mhz:5Mhz

        #if !defined(SOFTSPI)
        // applies to SPI_UART and inherent hardware SPI
            #if defined (RF24_SPI_PTR)
    _spi->setBitOrder(MSBFIRST);
    _spi->setDataMode(SPI_MODE0);

                #if !defined(F_CPU) || F_CPU < 20000000
    _spi->setClockDivider(SPI_CLOCK_DIV2);
                #elif F_CPU < 40000000
    _spi->setClockDivider(SPI_CLOCK_DIV4);
                #elif F_CPU < 80000000
    _spi->setClockDivider(SPI_CLOCK_DIV8);
                #elif F_CPU < 160000000
    _spi->setClockDivider(SPI_CLOCK_DIV16);
                #elif F_CPU < 320000000
    _spi->setClockDivider(SPI_CLOCK_DIV32);
                #elif F_CPU < 640000000
    _spi->setClockDivider(SPI_CLOCK_DIV64);
                #elif F_CPU < 1280000000
    _spi->setClockDivider(SPI_CLOCK_DIV128);
                #else // F_CPU >= 1280000000
                    #error "Unsupported CPU frequency. Please set correct SPI divider."
                #endif // F_CPU to SPI_CLOCK_DIV translation

            #else // !defined(RF24_SPI_PTR)
    _SPI.setBitOrder(MSBFIRST);
    _SPI.setDataMode(SPI_MODE0);

                #if !defined(F_CPU) || F_CPU < 20000000
    _SPI.setClockDivider(SPI_CLOCK_DIV2);
                #elif F_CPU < 40000000
    _SPI.setClockDivider(SPI_CLOCK_DIV4);
                #elif F_CPU < 80000000
    _SPI.setClockDivider(SPI_CLOCK_DIV8);
                #elif F_CPU < 160000000
    _SPI.setClockDivider(SPI_CLOCK_DIV16);
                #elif F_CPU < 320000000
    _SPI.setClockDivider(SPI_CLOCK_DIV32);
                #elif F_CPU < 640000000
    _SPI.setClockDivider(SPI_CLOCK_DIV64);
                #elif F_CPU < 1280000000
    _SPI.setClockDivider(SPI_CLOCK_DIV128);
                #else // F_CPU >= 1280000000
                    #error "Unsupported CPU frequency. Please set correct SPI divider."
                #endif // F_CPU to SPI_CLOCK_DIV translation
            #endif // !defined(RF24_SPI_PTR)
        #endif // !defined(SOFTSPI)

    #elif defined (RF24_RPi)
    if(!mode)
        _SPI.chipSelect(csn_pin);
    #endif // defined(RF24_RPi)

    #if !defined(RF24_LINUX)
    digitalWrite(csn_pin, mode);
    delayMicroseconds(csDelay);
    #else
    static_cast<void>(mode); // ignore -Wunused-parameter
    #endif // !defined(RF24_LINUX)
}

/****************************************************************************/

void RF24::ce(bool level)
{
    //Allow for 3-pin use on ATTiny
    if (ce_pin != csn_pin) {
        digitalWrite(ce_pin, level);
    }
}

/****************************************************************************/

inline void RF24::beginTransaction()
{
    #if defined (RF24_SPI_TRANSACTIONS)
        #if defined (RF24_SPI_PTR)
            #if defined (RF24_RP2)
    _spi->beginTransaction(spi_speed);
            #else // ! defined (RF24_RP2)
    _spi->beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
            #endif // ! defined (RF24_RP2)
        #else // !defined(RF24_SPI_PTR)
    _SPI.beginTransaction(SPISettings(spi_speed, MSBFIRST, SPI_MODE0));
        #endif // !defined(RF24_SPI_PTR)
    #endif // defined (RF24_SPI_TRANSACTIONS)
    csn(LOW);
}

/****************************************************************************/

inline void RF24::endTransaction()
{
    csn(HIGH);
    #if defined (RF24_SPI_TRANSACTIONS)
        #if defined (RF24_SPI_PTR)
    _spi->endTransaction();
        #else // !defined(RF24_SPI_PTR)
    _SPI.endTransaction();
        #endif // !defined(RF24_SPI_PTR)
    #endif // defined (RF24_SPI_TRANSACTIONS)
}

/****************************************************************************/

void RF24::read_register(uint8_t reg, uint8_t* buf, uint8_t len)
{
    #if defined (RF24_LINUX) || defined (RF24_RP2)
    beginTransaction(); //configures the spi settings for RPi, locks mutex and setting csn low
    uint8_t * prx = spi_rxbuff;
    uint8_t * ptx = spi_txbuff;
    uint8_t size = static_cast<uint8_t>(len + 1); // Add register value to transmit buffer

    *ptx++ = (R_REGISTER | reg);

    while (len--){ *ptx++ = RF24_NOP; } // Dummy operation, just for reading

        #if defined (RF24_RP2)
    _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, size);
        #else // !defined (RF24_RP2)
    _SPI.transfernb(reinterpret_cast<char *>(spi_txbuff), reinterpret_cast<char *>(spi_rxbuff), size);
        #endif // !defined (RF24_RP2)

    status = *prx++; // status is 1st byte of receive buffer

    // decrement before to skip status byte
    while (--size) { *buf++ = *prx++; }

    endTransaction(); // unlocks mutex and setting csn high

    #else // !defined(RF24_LINUX) && !defined(RF24_RP2)

    beginTransaction();
        #if defined (RF24_SPI_PTR)
    status = _spi->transfer(R_REGISTER | reg);
    while (len--) { *buf++ = _spi->transfer(0xFF); }

        #else // !defined(RF24_SPI_PTR)
    status = _SPI.transfer(R_REGISTER | reg);
    while (len--) { *buf++ = _SPI.transfer(0xFF); }

        #endif // !defined(RF24_SPI_PTR)
    endTransaction();
    #endif // !defined(RF24_LINUX) && !defined(RF24_RP2)
}

/****************************************************************************/

uint8_t RF24::read_register(uint8_t reg)
{
    uint8_t result;

    #if defined (RF24_LINUX) || defined (RF24_RP2)
    beginTransaction();

    uint8_t * prx = spi_rxbuff;
    uint8_t * ptx = spi_txbuff;
    *ptx++ = (R_REGISTER | reg);
    *ptx++ = RF24_NOP ; // Dummy operation, just for reading

        #if defined (RF24_RP2)
    _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, 2);
        #else // !defined(RF24_RP2)
    _SPI.transfernb(reinterpret_cast<char *>(spi_txbuff), reinterpret_cast<char *>(spi_rxbuff), 2);
        #endif // !defined(RF24_RP2)

    status = *prx;     // status is 1st byte of receive buffer
    result = *++prx;   // result is 2nd byte of receive buffer

    endTransaction();
    #else // !defined(RF24_LINUX) && !defined(RF24_RP2)

    beginTransaction();
        #if defined (RF24_SPI_PTR)
    status = _spi->transfer(R_REGISTER | reg);
    result = _spi->transfer(0xff);

        #else // !defined(RF24_SPI_PTR)
    status = _SPI.transfer(R_REGISTER | reg);
    result = _SPI.transfer(0xff);

        #endif // !defined(RF24_SPI_PTR)
    endTransaction();
    #endif // !defined(RF24_LINUX) && !defined(RF24_RP2)

    return result;
}

/****************************************************************************/

void RF24::write_register(uint8_t reg, const uint8_t* buf, uint8_t len)
{
    #if defined (RF24_LINUX) || defined (RF24_RP2)
    beginTransaction();
    uint8_t * prx = spi_rxbuff;
    uint8_t * ptx = spi_txbuff;
    uint8_t size = static_cast<uint8_t>(len + 1); // Add register value to transmit buffer

    *ptx++ = (W_REGISTER | (REGISTER_MASK & reg));
    while (len--) { *ptx++ = *buf++; }

        #if defined (RF24_RP2)
    _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, size);
        #else // !defined(RF24_RP2)
    _SPI.transfernb(reinterpret_cast<char *>(spi_txbuff), reinterpret_cast<char *>(spi_rxbuff), size);
        #endif // !defined(RF24_RP2)

    status = *prx; // status is 1st byte of receive buffer
    endTransaction();
    #else // !defined(RF24_LINUX) && !defined(RF24_RP2)

    beginTransaction();
        #if defined (RF24_SPI_PTR)
    status = _spi->transfer(W_REGISTER | reg);
    while (len--) { _spi->transfer(*buf++); }

        #else // !defined(RF24_SPI_PTR)
    status = _SPI.transfer(W_REGISTER | reg);
    while (len--) { _SPI.transfer(*buf++); }

        #endif // !defined(RF24_SPI_PTR)
    endTransaction();
    #endif // !defined(RF24_LINUX) && !defined(RF24_RP2)
}

/****************************************************************************/

void RF24::write_register(uint8_t reg, uint8_t value, bool is_cmd_only)
{
    if (is_cmd_only) {
        if (reg != RF24_NOP) { // don't print the get_status() operation
            IF_SERIAL_DEBUG(printf_P(PSTR("write_register(%02x)\r\n"), reg));
        }
        beginTransaction();
        #if defined (RF24_LINUX)
        status = _SPI.transfer(W_REGISTER | reg);
        #else // !defined(RF24_LINUX) || defined (RF24_RP2)
            #if defined (RF24_SPI_PTR)
        status = _spi->transfer(W_REGISTER | reg);
            #else // !defined (RF24_SPI_PTR)
        status = _SPI.transfer(W_REGISTER | reg);
            #endif // !defined (RF24_SPI_PTR)
        #endif // !defined(RF24_LINUX) || defined(RF24_RP2)
        endTransaction();
    }
    else {
        IF_SERIAL_DEBUG(printf_P(PSTR("write_register(%02x,%02x)\r\n"), reg, value));
        #if defined (RF24_LINUX) || defined (RF24_RP2)
        beginTransaction();
        uint8_t * prx = spi_rxbuff;
        uint8_t * ptx = spi_txbuff;
        *ptx++ = (W_REGISTER | reg);
        *ptx = value;

            #if defined (RF24_RP2)
        _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, 2);
            #else // !defined(RF24_RP2)
        _SPI.transfernb(reinterpret_cast<char *>(spi_txbuff), reinterpret_cast<char *>(spi_rxbuff), 2);
            #endif // !defined(RF24_RP2)

        status = *prx++; // status is 1st byte of receive buffer
        endTransaction();
        #else // !defined(RF24_LINUX) && !defined(RF24_RP2)

        beginTransaction();
            #if defined (RF24_SPI_PTR)
        status = _spi->transfer(W_REGISTER | reg);
        _spi->transfer(value);
            #else // !defined(RF24_SPI_PTR)
        status = _SPI.transfer(W_REGISTER | reg);
        _SPI.transfer(value);
            #endif // !defined(RF24_SPI_PTR)
        endTransaction();
        #endif // !defined(RF24_LINUX) && !defined(RF24_RP2)
    }
}

/****************************************************************************/

void RF24::write_payload(const void* buf, uint8_t data_len, const uint8_t writeType)
{
    const uint8_t* current = reinterpret_cast<const uint8_t*>(buf);

    uint8_t blank_len = !data_len ? 1 : 0;
    if (!dynamic_payloads_enabled) {
        data_len = rf24_min(data_len, payload_size);
        blank_len = static_cast<uint8_t>(payload_size - data_len);
    }
    else {
        data_len = rf24_min(data_len, static_cast<uint8_t>(32));
    }

    //printf("[Writing %u bytes %u blanks]",data_len,blank_len);
    IF_SERIAL_DEBUG(printf("[Writing %u bytes %u blanks]\n", data_len, blank_len); );

    #if defined (RF24_LINUX) || defined (RF24_RP2)
    beginTransaction();
    uint8_t * prx = spi_rxbuff;
    uint8_t * ptx = spi_txbuff;
    uint8_t size;
    size = static_cast<uint8_t>(data_len + blank_len + 1); // Add register value to transmit buffer

    *ptx++ =  writeType;
    while (data_len--) { *ptx++ =  *current++; }
    while (blank_len--) { *ptx++ =  0; }

        #if defined (RF24_RP2)
    _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, size);
        #else // !defined(RF24_RP2)
    _SPI.transfernb(reinterpret_cast<char *>(spi_txbuff), reinterpret_cast<char *>(spi_rxbuff), size);
        #endif // !defined(RF24_RP2)

    status = *prx; // status is 1st byte of receive buffer
    endTransaction();

    #else // !defined(RF24_LINUX) && !defined(RF24_RP2)

    beginTransaction();
        #if defined (RF24_SPI_PTR)
    status = _spi->transfer(writeType);
    while (data_len--) { _spi->transfer(*current++); }
    while (blank_len--) { _spi->transfer(0); }

        #else // !defined(RF24_SPI_PTR)
    status = _SPI.transfer(writeType);
    while (data_len--) { _SPI.transfer(*current++); }

    while (blank_len--) { _SPI.transfer(0); }

        #endif // !defined(RF24_SPI_PTR)
    endTransaction();
    #endif // !defined(RF24_LINUX) && !defined(RF24_RP2)
}

/****************************************************************************/

void RF24::read_payload(void* buf, uint8_t data_len)
{
    uint8_t* current = reinterpret_cast<uint8_t*>(buf);

    uint8_t blank_len = 0;
    if (!dynamic_payloads_enabled) {
        data_len = rf24_min(data_len, payload_size);
        blank_len = static_cast<uint8_t>(payload_size - data_len);
    }
    else {
        data_len = rf24_min(data_len, static_cast<uint8_t>(32));
    }

    //printf("[Reading %u bytes %u blanks]",data_len,blank_len);

    IF_SERIAL_DEBUG(printf("[Reading %u bytes %u blanks]\n", data_len, blank_len); );

    #if defined (RF24_LINUX) || defined (RF24_RP2)
    beginTransaction();
    uint8_t * prx = spi_rxbuff;
    uint8_t * ptx = spi_txbuff;
    uint8_t size;
    size = static_cast<uint8_t>(data_len + blank_len + 1); // Add register value to transmit buffer

    *ptx++ =  R_RX_PAYLOAD;
    while(--size) { *ptx++ = RF24_NOP; }

    size = static_cast<uint8_t>(data_len + blank_len + 1); // Size has been lost during while, re affect

        #if defined (RF24_RP2)
    _spi->transfernb((const uint8_t*)spi_txbuff, spi_rxbuff, size);
        #else // !defined(RF24_RP2)
    _SPI.transfernb(reinterpret_cast<char *>(spi_txbuff), reinterpret_cast<char *>(spi_rxbuff), size);
        #endif // !defined(RF24_RP2)

    status = *prx++; // 1st byte is status

    if (data_len > 0) {
        // Decrement before to skip 1st status byte
        while (--data_len) { *current++ = *prx++; }

        *current = *prx;
    }
    endTransaction();
    #else // !defined(RF24_LINUX) && !defined(RF24_RP2)

    beginTransaction();
        #if defined (RF24_SPI_PTR)
    status = _spi->transfer(R_RX_PAYLOAD);
    while (data_len--) { *current++ = _spi->transfer(0xFF); }

    while (blank_len--) { _spi->transfer(0xFF); }

        #else // !defined(RF24_SPI_PTR)
    status = _SPI.transfer(R_RX_PAYLOAD);
    while (data_len--) { *current++ = _SPI.transfer(0xFF); }
    while (blank_len--) { _SPI.transfer(0xff); }

        #endif // !defined(RF24_SPI_PTR)
    endTransaction();

    #endif // !defined(RF24_LINUX) && !defined(RF24_RP2)
}

/****************************************************************************/

uint8_t RF24::flush_rx(void)
{
    write_register(FLUSH_RX, RF24_NOP, true);
    return status;
}

/****************************************************************************/

uint8_t RF24::flush_tx(void)
{
    write_register(FLUSH_TX, RF24_NOP, true);
    return status;
}

/****************************************************************************/

uint8_t RF24::get_status(void)
{
    write_register(RF24_NOP, RF24_NOP, true);
    return status;
}

/****************************************************************************/
#if !defined(MINIMAL)

void RF24::print_status(uint8_t _status)
{
    printf_P(PSTR("STATUS\t\t= 0x%02x RX_DR=%x TX_DS=%x MAX_RT=%x RX_P_NO=%x TX_FULL=%x\r\n"), _status, (_status & _BV(RX_DR)) ? 1 : 0,
            (_status & _BV(TX_DS)) ? 1 : 0, (_status & _BV(MAX_RT)) ? 1 : 0, ((_status >> RX_P_NO) & 0x07), (_status & _BV(TX_FULL)) ? 1 : 0);
}

/****************************************************************************/

void RF24::print_observe_tx(uint8_t value)
{
    printf_P(PSTR("OBSERVE_TX=%02x: POLS_CNT=%x ARC_CNT=%x\r\n"), value, (value >> PLOS_CNT) & 0x0F, (value >> ARC_CNT) & 0x0F);
}

/****************************************************************************/

void RF24::print_byte_register(const char* name, uint8_t reg, uint8_t qty)
{
    //char extra_tab = strlen_P(name) < 8 ? '\t' : 0;
    //printf_P(PSTR(PRIPSTR"\t%c ="),name,extra_tab);
    #if defined(RF24_LINUX)
    printf("%s\t=", name);
    #else // !defined(RF24_LINUX)
    printf_P(PSTR(PRIPSTR"\t="),name);
    #endif // !defined(RF24_LINUX)
    while (qty--) {
        printf_P(PSTR(" 0x%02x"), read_register(reg++));
    }
    printf_P(PSTR("\r\n"));
}

/****************************************************************************/

void RF24::sprintf_byte_register(char *out_buffer, uint8_t reg, uint8_t qty)
{
    uint8_t i = 0;
    char sprintf_buffer[4] = {'\0'};
    while (qty--) {
        sprintf_P(sprintf_buffer, PSTR("%02x"), read_register(reg++));
        out_buffer[i+0] = sprintf_buffer[0];
        out_buffer[i+1] = sprintf_buffer[1];
        i=i+2;
    }
}

/****************************************************************************/

void RF24::arrayify_byte_register(uint8_t *out_array, uint8_t reg, uint8_t qty)
{
    uint8_t i = 0;
    while (qty--)
    {
        out_array[i] = read_register(reg++);
        i = i + 1;
    }
}

/****************************************************************************/

void RF24::print_address_register(const char* name, uint8_t reg, uint8_t qty)
{

    #if defined(RF24_LINUX)
    printf("%s\t=", name);
    #else // !defined(RF24_LINUX)
    printf_P(PSTR(PRIPSTR"\t="), name);
    #endif // !defined(RF24_LINUX)
    uint8_t *buffer = new uint8_t[addr_width];
    while (qty--) {
        read_register(reg++ & REGISTER_MASK, buffer, addr_width);

        printf_P(PSTR(" 0x"));
        uint8_t* bufptr = buffer + addr_width;
        while (--bufptr >= buffer) {
            printf_P(PSTR("%02x"), *bufptr);
        }
    }
    delete[] buffer;
    printf_P(PSTR("\r\n"));
}

/****************************************************************************/

void RF24::sprintf_address_register(char *out_buffer, uint8_t reg, uint8_t qty)
{
    uint8_t i = 0;
    char sprintf_buffer[4] = {'\0'};
    uint8_t *read_buffer = new uint8_t[addr_width];
    while (qty--) {
        read_register(reg++ & REGISTER_MASK, read_buffer, addr_width);

        uint8_t* bufptr = read_buffer + addr_width;
        while (--bufptr >= read_buffer) {
            sprintf_P(sprintf_buffer, PSTR("%02x"), *bufptr);
            out_buffer[i] = sprintf_buffer[0];
            out_buffer[i + 1] = sprintf_buffer[1];
            i=i+2;
        }
    }
    delete[] read_buffer;
}

/****************************************************************************/

void RF24::arrayify_address_register(uint8_t *out_array, uint8_t reg, uint8_t qty)
{
    uint8_t *read_buffer = new uint8_t[addr_width];
    while (qty--)
    {
        uint8_t i = 0;
        read_register(reg++ & REGISTER_MASK, read_buffer, addr_width);

        uint8_t *bufptr = read_buffer + addr_width;
        while (--bufptr >= read_buffer)
        {
            out_array[i] = *bufptr;
            i = i + 1;
        }
    }
    delete[] read_buffer;
}

#endif // !defined(MINIMAL)

/****************************************************************************/

RF24::RF24(uint16_t _cepin, uint16_t _cspin, uint32_t _spi_speed)
        :ce_pin(_cepin), csn_pin(_cspin), spi_speed(_spi_speed), payload_size(32), _is_p_variant(false), _is_p0_rx(false), addr_width(5), dynamic_payloads_enabled(true),
         csDelay(5)
{
    _init_obj();
}

/****************************************************************************/

RF24::RF24(uint32_t _spi_speed)
        :ce_pin(0xFFFF), csn_pin(0xFFFF), spi_speed(_spi_speed), payload_size(32), _is_p_variant(false), _is_p0_rx(false), addr_width(5), dynamic_payloads_enabled(true),
         csDelay(5)
{
    _init_obj();
}

/****************************************************************************/

void RF24::_init_obj()
{
    // Use a pointer on the Arduino platform

    #if defined (RF24_SPI_PTR) && !defined (RF24_RP2)
    _spi = &SPI;
    #endif // defined (RF24_SPI_PTR)

    pipe0_reading_address[0] = 0;
    if(spi_speed <= 35000){ //Handle old BCM2835 speed constants, default to RF24_SPI_SPEED
        spi_speed = RF24_SPI_SPEED;
    }
}

/****************************************************************************/

void RF24::setChannel(uint8_t channel)
{
    const uint8_t max_channel = 125;
    write_register(RF_CH, rf24_min(channel, max_channel));
}

uint8_t RF24::getChannel()
{
    return read_register(RF_CH);
}

/****************************************************************************/

void RF24::setPayloadSize(uint8_t size)
{
    // payload size must be in range [1, 32]
    payload_size = static_cast<uint8_t>(rf24_max(1, rf24_min(32, size)));

    // write static payload size setting for all pipes
    for (uint8_t i = 0; i < 6; ++i)
        write_register(static_cast<uint8_t>(RX_PW_P0 + i), payload_size);
}

/****************************************************************************/

uint8_t RF24::getPayloadSize(void)
{
    return payload_size;
}

/****************************************************************************/

#if !defined(MINIMAL)

static const PROGMEM char rf24_datarate_e_str_0[] = "= 1 MBPS";
static const PROGMEM char rf24_datarate_e_str_1[] = "= 2 MBPS";
static const PROGMEM char rf24_datarate_e_str_2[] = "= 250 KBPS";
static const PROGMEM char * const rf24_datarate_e_str_P[] = {
  rf24_datarate_e_str_0,
  rf24_datarate_e_str_1,
  rf24_datarate_e_str_2,
};
static const PROGMEM char rf24_model_e_str_0[] = "nRF24L01";
static const PROGMEM char rf24_model_e_str_1[] = "nRF24L01+";
static const PROGMEM char * const rf24_model_e_str_P[] = {
  rf24_model_e_str_0,
  rf24_model_e_str_1,
};
static const PROGMEM char rf24_crclength_e_str_0[] = "= Disabled";
static const PROGMEM char rf24_crclength_e_str_1[] = "= 8 bits";
static const PROGMEM char rf24_crclength_e_str_2[] = "= 16 bits" ;
static const PROGMEM char * const rf24_crclength_e_str_P[] = {
  rf24_crclength_e_str_0,
  rf24_crclength_e_str_1,
  rf24_crclength_e_str_2,
};
static const PROGMEM char rf24_pa_dbm_e_str_0[] = "= PA_MIN";
static const PROGMEM char rf24_pa_dbm_e_str_1[] = "= PA_LOW";
static const PROGMEM char rf24_pa_dbm_e_str_2[] = "= PA_HIGH";
static const PROGMEM char rf24_pa_dbm_e_str_3[] = "= PA_MAX";
static const PROGMEM char * const rf24_pa_dbm_e_str_P[] = {
  rf24_pa_dbm_e_str_0,
  rf24_pa_dbm_e_str_1,
  rf24_pa_dbm_e_str_2,
  rf24_pa_dbm_e_str_3,
};

    #if defined(RF24_LINUX)
static const char rf24_csn_e_str_0[] = "CE0 (PI Hardware Driven)";
static const char rf24_csn_e_str_1[] = "CE1 (PI Hardware Driven)";
static const char rf24_csn_e_str_2[] = "CE2 (PI Hardware Driven)";
static const char rf24_csn_e_str_3[] = "Custom GPIO Software Driven";
static const char * const rf24_csn_e_str_P[] = {
  rf24_csn_e_str_0,
  rf24_csn_e_str_1,
  rf24_csn_e_str_2,
  rf24_csn_e_str_3,
};
    #endif // defined(RF24_LINUX)

static const PROGMEM char rf24_feature_e_str_on[] = "= Enabled";
static const PROGMEM char rf24_feature_e_str_allowed[] = "= Allowed";
static const PROGMEM char rf24_feature_e_str_open[] = " open ";
static const PROGMEM char rf24_feature_e_str_closed[] = "closed";
static const PROGMEM char * const rf24_feature_e_str_P[] = {
    rf24_crclength_e_str_0,
    rf24_feature_e_str_on,
    rf24_feature_e_str_allowed,
    rf24_feature_e_str_closed,
    rf24_feature_e_str_open
};

void RF24::printDetails(void)
{

    #if defined(RF24_LINUX)
    printf("================ SPI Configuration ================\n" );
    uint8_t bus_ce = static_cast<uint8_t>(csn_pin % 10);
    uint8_t bus_numb = static_cast<uint8_t>((csn_pin - bus_ce) / 10);
    printf("CSN Pin\t\t= /dev/spidev%d.%d\n", bus_numb, bus_ce);
    printf("CE Pin\t\t= Custom GPIO%d\n", ce_pin);
    #endif
    printf_P(PSTR("SPI Speedz\t= %d Mhz\n"), static_cast<uint8_t>(spi_speed / 1000000)); //Print the SPI speed on non-Linux devices
    #if defined(RF24_LINUX)
    printf("================ NRF Configuration ================\n");
    #endif // defined(RF24_LINUX)

    print_status(get_status());

    print_address_register(PSTR("RX_ADDR_P0-1"), RX_ADDR_P0, 2);
    print_byte_register(PSTR("RX_ADDR_P2-5"), RX_ADDR_P2, 4);
    print_address_register(PSTR("TX_ADDR\t"), TX_ADDR);

    print_byte_register(PSTR("RX_PW_P0-6"), RX_PW_P0, 6);
    print_byte_register(PSTR("EN_AA\t"), EN_AA);
    print_byte_register(PSTR("EN_RXADDR"), EN_RXADDR);
    print_byte_register(PSTR("RF_CH\t"), RF_CH);
    print_byte_register(PSTR("RF_SETUP"), RF_SETUP);
    print_byte_register(PSTR("CONFIG\t"), NRF_CONFIG);
    print_byte_register(PSTR("DYNPD/FEATURE"), DYNPD, 2);

    printf_P(PSTR("Data Rate\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_datarate_e_str_P[getDataRate()])));
    printf_P(PSTR("Model\t\t= "
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_model_e_str_P[isPVariant()])));
    printf_P(PSTR("CRC Length\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_crclength_e_str_P[getCRCLength()])));
    printf_P(PSTR("PA Power\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_pa_dbm_e_str_P[getPALevel()])));
    printf_P(PSTR("ARC\t\t= %d\r\n"), getARC());
}

void RF24::printPrettyDetails(void) {

    #if defined(RF24_LINUX)
    printf("================ SPI Configuration ================\n");
    uint8_t bus_ce = static_cast<uint8_t>(csn_pin % 10);
    uint8_t bus_numb = static_cast<uint8_t>((csn_pin - bus_ce) / 10);
    printf("CSN Pin\t\t\t= /dev/spidev%d.%d\n", bus_numb, bus_ce);
    printf("CE Pin\t\t\t= Custom GPIO%d\n", ce_pin);
    #endif
    printf_P(PSTR("SPI Frequency\t\t= %d Mhz\n"), static_cast<uint8_t>(spi_speed / 1000000)); //Print the SPI speed on non-Linux devices
    #if defined(RF24_LINUX)
    printf("================ NRF Configuration ================\n");
    #endif // defined(RF24_LINUX)

    uint8_t channel = getChannel();
    uint16_t frequency = static_cast<uint16_t>(channel + 2400);
    printf_P(PSTR("Channel\t\t\t= %u (~ %u MHz)\r\n"), channel, frequency);

    printf_P(PSTR("RF Data Rate\t\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_datarate_e_str_P[getDataRate()])));
    printf_P(PSTR("RF Power Amplifier\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_pa_dbm_e_str_P[getPALevel()])));
    printf_P(PSTR("RF Low Noise Amplifier\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_feature_e_str_P[(read_register(RF_SETUP) & 1) * 1])));
    printf_P(PSTR("CRC Length\t\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_crclength_e_str_P[getCRCLength()])));
    printf_P(PSTR("Address Length\t\t= %d bytes\r\n"), (read_register(SETUP_AW) & 3) + 2);
    printf_P(PSTR("Static Payload Length\t= %d bytes\r\n"), getPayloadSize());

    uint8_t setupRetry = read_register(SETUP_RETR);
    printf_P(PSTR("Auto Retry Delay\t= %d microseconds\r\n"), (setupRetry >> ARD) * 250 + 250);
    printf_P(PSTR("Auto Retry Attempts\t= %d maximum\r\n"), setupRetry & 0x0F);

    uint8_t observeTx = read_register(OBSERVE_TX);
    printf_P(PSTR("Packets lost on\n    current channel\t= %d\r\n"), observeTx >> 4);
    printf_P(PSTR("Retry attempts made for\n    last transmission\t= %d\r\n"), observeTx & 0x0F);

    uint8_t features = read_register(FEATURE);
    printf_P(PSTR("Multicast\t\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(features & _BV(EN_DYN_ACK)) * 2])));
    printf_P(PSTR("Custom ACK Payload\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(features & _BV(EN_ACK_PAY)) * 1])));

    uint8_t dynPl = read_register(DYNPD);
    printf_P(PSTR("Dynamic Payloads\t"
    PRIPSTR
    "\r\n"), (char *)(pgm_read_ptr(&rf24_feature_e_str_P[(dynPl && (features &_BV(EN_DPL))) * 1])));

    uint8_t autoAck = read_register(EN_AA);
    if (autoAck == 0x3F || autoAck == 0) {
        // all pipes have the same configuration about auto-ack feature
        printf_P(PSTR("Auto Acknowledgment\t"
        PRIPSTR
        "\r\n"), (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(autoAck) * 1])));
    } else {
        // representation per pipe
        printf_P(PSTR("Auto Acknowledgment\t= 0b%c%c%c%c%c%c\r\n"),
                 static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P5)) + 48),
                 static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P4)) + 48),
                 static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P3)) + 48),
                 static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P2)) + 48),
                 static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P1)) + 48),
                 static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P0)) + 48));
    }

    config_reg = read_register(NRF_CONFIG);
    printf_P(PSTR("Primary Mode\t\t= %cX\r\n"), config_reg & _BV(PRIM_RX) ? 'R' : 'T');
    print_address_register(PSTR("TX address\t"), TX_ADDR);

    uint8_t openPipes = read_register(EN_RXADDR);
    for (uint8_t i = 0; i < 6; ++i) {
        bool isOpen = openPipes & _BV(i);
        printf_P(PSTR("pipe %u ("
        PRIPSTR
        ") bound"), i, (char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen + 3])));
        if (i < 2) {
            print_address_register(PSTR(""), static_cast<uint8_t>(RX_ADDR_P0 + i));
        }
        else {
            print_byte_register(PSTR(""), static_cast<uint8_t>(RX_ADDR_P0 + i));
        }
    }
}

/****************************************************************************/

void RF24::sprintfPrettyDetails(char *debugging_information)
{
    const char *format_string = PSTR("================ SPI Configuration ================\n"
                                     "CSN Pin\t\t\t= %d\n"
                                     "CE Pin\t\t\t= %d\n"
                                     "SPI Frequency\t\t= %d Mhz\n"
                                     "================ NRF Configuration ================\n"
                                     "Channel\t\t\t= %u (~ %u MHz)\n"
                                     "RF Data Rate\t\t"
                                     PRIPSTR
                                     "\n"
                                     "RF Power Amplifier\t"
                                     PRIPSTR
                                     "\n"
                                     "RF Low Noise Amplifier\t"
                                     PRIPSTR
                                     "\n"
                                     "CRC Length\t\t"
                                     PRIPSTR
                                     "\n"
                                     "Address Length\t\t= %d bytes\n"
                                     "Static Payload Length\t= %d bytes\n"
                                     "Auto Retry Delay\t= %d microseconds\n"
                                     "Auto Retry Attempts\t= %d maximum\n"
                                     "Packets lost on\n    current channel\t= %d\r\n"
                                     "Retry attempts made for\n    last transmission\t= %d\r\n"
                                     "Multicast\t\t"
                                     PRIPSTR
                                     "\n"
                                     "Custom ACK Payload\t"
                                     PRIPSTR
                                     "\n"
                                     "Dynamic Payloads\t"
                                     PRIPSTR
                                     "\n"
                                     "Auto Acknowledgment\t"
                                     PRIPSTR
                                     "\n"
                                     "Primary Mode\t\t= %cX\n"
                                     "TX address\t\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 0 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 1 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 2 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 3 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 4 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 5 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                    );

    char tx_address_char_array[16] = {'\0'};
    sprintf_address_register(tx_address_char_array, TX_ADDR);

    char pipe_address_char_2d_array[6][16] = {'\0'};
    char pipe_address_char_array[16] = {'\0'};
    bool isOpen_array[6] = {false};

    uint8_t openPipes = read_register(EN_RXADDR);
    for (uint8_t i = 0; i < 6; ++i) {
        bool isOpen = openPipes & _BV(i);
        isOpen_array[i] = isOpen;
        if (i < 2) {
            sprintf_address_register(pipe_address_char_array, static_cast<uint8_t>(RX_ADDR_P0 + i));
            for (uint8_t j = 0; j < 16; j++) {
                pipe_address_char_2d_array[i][j] = pipe_address_char_array[j];
            }
            for (uint8_t j = 0; j < 16; j++) {
                pipe_address_char_array[j] = '\0';
            }
        }
        else {
            sprintf_byte_register(pipe_address_char_array, static_cast<uint8_t>(RX_ADDR_P0 + i));
            for (uint8_t j = 0; j < 16; j++) {
                pipe_address_char_2d_array[i][j] = pipe_address_char_array[j];
            }
            for (uint8_t j = 0; j < 16; j++) {
                pipe_address_char_array[j] = '\0';
            }
        }
    }

    char autoack_status_char_array[11] = {'\0'};
    uint8_t autoAck = read_register(EN_AA);
    if (autoAck == 0x3F || autoAck == 0) {
        // all pipes have the same configuration about auto-ack feature
        sprintf_P(autoack_status_char_array,
                  PSTR(""
                       PRIPSTR
                       ""),
                  (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(autoAck) * 1]))
                );
    }
    else {
        // representation per pipe
        sprintf_P(autoack_status_char_array,
                  PSTR("= 0b%c%c%c%c%c%c"),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P5)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P4)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P3)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P2)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P1)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P0)) + 48)
                 );
    }

    sprintf_P(debugging_information,
              format_string,
              csn_pin,
              ce_pin,
              static_cast<uint8_t>(spi_speed / 1000000),
              getChannel(),
              static_cast<uint16_t>(getChannel() + 2400),
              (char *)(pgm_read_ptr(&rf24_datarate_e_str_P[getDataRate()])),
              (char *)(pgm_read_ptr(&rf24_pa_dbm_e_str_P[getPALevel()])),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[(read_register(RF_SETUP) & 1) * 1])),
              (char *)(pgm_read_ptr(&rf24_crclength_e_str_P[getCRCLength()])),
              ((read_register(SETUP_AW) & 3) + 2),
              getPayloadSize(),
              ((read_register(SETUP_RETR) >> ARD) * 250 + 250),
              (read_register(SETUP_RETR) & 0x0F),
              (read_register(OBSERVE_TX) >> 4),
              (read_register(OBSERVE_TX) & 0x0F),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK)) * 2])),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY)) * 1])),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[(read_register(DYNPD) && (read_register(FEATURE) &_BV(EN_DPL))) * 1])),
              (autoack_status_char_array),
              (read_register(NRF_CONFIG) & _BV(PRIM_RX) ? 'R' : 'T'),
              (tx_address_char_array),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[0] + 3]))),
              (pipe_address_char_2d_array[0]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[1] + 3]))),
              (pipe_address_char_2d_array[1]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[2] + 3]))),
              (pipe_address_char_2d_array[2]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[3] + 3]))),
              (pipe_address_char_2d_array[3]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[4] + 3]))),
              (pipe_address_char_2d_array[4]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[5] + 3]))),
              (pipe_address_char_2d_array[5])
             );
}

/****************************************************************************/

void RF24::encodeRadioDetails(uint8_t *encoded_details)
{
    /*
     * This was made with maintainability/customisability in mind, items can be added/removed to/from
     * the output bit array `encoded_details` in any order using encode_bit_manipulation_methods, then changing
     * decodeRadioDetails to suit your use case.  It should work even if the variables used as the bit array
     * `encoded_details` are noncontiguously allocated.
     */
    uint16_t bit_index = 0;                         // bitwise index of encoded_details
    uint8_t encoded_details_index = 0;              // encoded_details array index
    bool temp_bool = false;                         // arithmetic performed on this before passing as argument to bit manipulation method
    uint8_t temp_8_bit = 0;                         // arithmetic performed on this before passing as argument to bit manipulation method    
    uint8_t forty_bit_register_array[5] = {0};      // 40 bit register array    
    uint8_t eight_bit_register_array[2] = {0};      // 8 bit register array
    /*
     * encodeRadioDetails() BitManip use primer
     *
     * We use two methods in BitManip to put bits into the array encoded_details:
     *
     * packValue(source, number_of_bits, encoded_details, &encoded_details_index, &bit_index);
     * and
     * packBool(source, encoded_details, &encoded_details_index, &bit_index);
     *
     * The first method puts nonboolean values into the bit array, there is no overflow checking.
     * Ensure proper buffer size by adding up the amount of bits you plan on sending and dividing by
     * the width of an unsigned byte (eight, 8), and double check that your encoded_details array can
     * accomodate that.
     * The major difference between the two methods is that since boolean are always represented by
     * a single bit in the array encoded_details we do not need to tell the method packBool()
     * how many bits to put into the array encoded_details, it defaults to one.
     */

    // 1 csn_pin
    BitManip::packValue(csn_pin, 16, encoded_details, &encoded_details_index, &bit_index);
    // 2 ce_pin
    BitManip::packValue(ce_pin, 16, encoded_details, &encoded_details_index, &bit_index);
    // 3 spi_speed
    temp_8_bit = static_cast<uint8_t>(spi_speed / 1000000UL);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 4 getChannel()
    BitManip::packValue(getChannel(), 8, encoded_details, &encoded_details_index, &bit_index);
    // 5 getDataRate()
    BitManip::packValue(getDataRate(), 8, encoded_details, &encoded_details_index, &bit_index);
    // 6 getPALevel()
    BitManip::packValue(getPALevel(), 8, encoded_details, &encoded_details_index, &bit_index);
    // 7 ((read_register(RF_SETUP) & 1) * 1)
    temp_8_bit = ((read_register(RF_SETUP) & 1) * 1);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 8 getCRCLength()
    BitManip::packValue(getCRCLength(), 8, encoded_details, &encoded_details_index, &bit_index);
    // 9 ((read_register(SETUP_AW) & 3) + 2)
    temp_8_bit = ((read_register(SETUP_AW) & 3) + 2);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 10 getPayloadSize()
    BitManip::packValue(getPayloadSize(), 8, encoded_details, &encoded_details_index, &bit_index);
    // 11 (read_register(SETUP_RETR) >> ARD)
    temp_8_bit = (read_register(SETUP_RETR) >> ARD);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 12 (read_register(SETUP_RETR) & 0x0F)
    temp_8_bit = (read_register(SETUP_RETR) & 0x0F);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 13 (read_register(OBSERVE_TX) >> 4)
    temp_8_bit = (read_register(OBSERVE_TX) >> 4);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 14 (read_register(OBSERVE_TX) & 0x0F)
    temp_8_bit = (read_register(OBSERVE_TX) & 0x0F);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 15 static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK))
    temp_bool = static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK));
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 16 static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY))
    temp_bool = static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY));
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 17 ((read_register(DYNPD) && (read_register(FEATURE) &_BV(EN_DPL))) * 1)
    temp_8_bit = ((read_register(DYNPD) && (read_register(FEATURE) & _BV(EN_DPL))) * 1);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);
    // 18 (static_cast<bool>(temp_8_bit & _BV(ENAA_P5)) + 48)
    temp_8_bit = read_register(EN_AA);
    temp_bool = (static_cast<bool>(temp_8_bit & _BV(ENAA_P5)) + 48);
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 19 (static_cast<bool>(temp_8_bit & _BV(ENAA_P4)) + 48)
    temp_bool = (static_cast<bool>(temp_8_bit & _BV(ENAA_P4)) + 48);
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 20 (static_cast<bool>(temp_8_bit & _BV(ENAA_P3)) + 48)
    temp_bool = (static_cast<bool>(temp_8_bit & _BV(ENAA_P3)) + 48);
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 21 (static_cast<bool>(temp_8_bit & _BV(ENAA_P2)) + 48)
    temp_bool = (static_cast<bool>(temp_8_bit & _BV(ENAA_P2)) + 48);
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 22 (static_cast<bool>(temp_8_bit & _BV(ENAA_P1)) + 48)
    temp_bool = (static_cast<bool>(temp_8_bit & _BV(ENAA_P1)) + 48);
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 23 (static_cast<bool>(temp_8_bit & _BV(ENAA_P0)) + 48)
    temp_bool = (static_cast<bool>(temp_8_bit & _BV(ENAA_P0)) + 48);
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);
    // 24 (read_register(NRF_CONFIG) & _BV(PRIM_RX))
    temp_bool = (read_register(NRF_CONFIG) & _BV(PRIM_RX));
    BitManip::packBool(temp_bool, encoded_details, &encoded_details_index, &bit_index);

    // TX_ADDR
    arrayify_address_register(forty_bit_register_array, TX_ADDR);
    // 25 forty_bit_register_array[0]
    BitManip::packValue(forty_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);
    // 26 forty_bit_register_array[1]
    BitManip::packValue(forty_bit_register_array[1], 8, encoded_details, &encoded_details_index, &bit_index);
    // 27 forty_bit_register_array[2]
    BitManip::packValue(forty_bit_register_array[2], 8, encoded_details, &encoded_details_index, &bit_index);
    // 28 forty_bit_register_array[3]
    BitManip::packValue(forty_bit_register_array[3], 8, encoded_details, &encoded_details_index, &bit_index);
    // 29 forty_bit_register_array[4]
    BitManip::packValue(forty_bit_register_array[4], 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 0 40 bit address register (static_cast<uint8_t>(RX_ADDR_P0 + 0))
    temp_8_bit = (static_cast<uint8_t>(RX_ADDR_P0 + 0));
    arrayify_address_register(forty_bit_register_array, temp_8_bit);
    // 30 forty_bit_register_array[0]
    BitManip::packValue(forty_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);
    // 31 forty_bit_register_array[1]
    BitManip::packValue(forty_bit_register_array[1], 8, encoded_details, &encoded_details_index, &bit_index);
    // 32 forty_bit_register_array[2]
    BitManip::packValue(forty_bit_register_array[2], 8, encoded_details, &encoded_details_index, &bit_index);
    // 33 forty_bit_register_array[3]
    BitManip::packValue(forty_bit_register_array[3], 8, encoded_details, &encoded_details_index, &bit_index);
    // 34 forty_bit_register_array[4]
    BitManip::packValue(forty_bit_register_array[4], 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 1 40 bit address register (static_cast<uint8_t>(RX_ADDR_P0 + 1))
    temp_8_bit = (static_cast<uint8_t>(RX_ADDR_P0 + 1));
    arrayify_address_register(forty_bit_register_array, temp_8_bit);
    // 35 forty_bit_register_array[0]
    BitManip::packValue(forty_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);
    // 36 forty_bit_register_array[1]
    BitManip::packValue(forty_bit_register_array[1], 8, encoded_details, &encoded_details_index, &bit_index);
    // 37 forty_bit_register_array[2]
    BitManip::packValue(forty_bit_register_array[2], 8, encoded_details, &encoded_details_index, &bit_index);
    // 38 forty_bit_register_array[3]
    BitManip::packValue(forty_bit_register_array[3], 8, encoded_details, &encoded_details_index, &bit_index);
    // 39 forty_bit_register_array[4]
    BitManip::packValue(forty_bit_register_array[4], 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 2 8 bit address register (static_cast<uint8_t>(RX_ADDR_P0 + 2)
    temp_8_bit = (static_cast<uint8_t>(RX_ADDR_P0 + 2));
    arrayify_byte_register(eight_bit_register_array, temp_8_bit);
    // 40 eight_bit_register_array[0]
    BitManip::packValue(eight_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 3 8 bit address register (static_cast<uint8_t>(RX_ADDR_P0 + 3)
    temp_8_bit = (static_cast<uint8_t>(RX_ADDR_P0 + 3));
    arrayify_byte_register(eight_bit_register_array, temp_8_bit);
    // 41 eight_bit_register_array[0]
    BitManip::packValue(eight_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 4 8 bit address register (static_cast<uint8_t>(RX_ADDR_P0 + 4)
    temp_8_bit = (static_cast<uint8_t>(RX_ADDR_P0 + 4));
    arrayify_byte_register(eight_bit_register_array, temp_8_bit);
    // 42 eight_bit_register_array[0]
    BitManip::packValue(eight_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 4 8 bit address register (static_cast<uint8_t>(RX_ADDR_P0 + 5)
    temp_8_bit = (static_cast<uint8_t>(RX_ADDR_P0 + 5));
    arrayify_byte_register(eight_bit_register_array, temp_8_bit);
    // 43 eight_bit_register_array[0]
    BitManip::packValue(eight_bit_register_array[0], 8, encoded_details, &encoded_details_index, &bit_index);

    // 44 read_register(EN_RXADDR)
    temp_8_bit = read_register(EN_RXADDR);
    BitManip::packValue(temp_8_bit, 8, encoded_details, &encoded_details_index, &bit_index);

    /*
     * Divide your total bits by 8 and round up to determine the amount of uint8_t array members you need to pass to this function
     * default is 40 uint8_t
     */
}

/****************************************************************************/

void RF24::decodeRadioDetails(char *debugging_information, uint8_t *encoded_details)
{
    uint16_t bit_index = 0;
    uint8_t encoded_details_index = 0;

    /*
     * encoded_details packing order
     *
     * 1 csn_pin
     * 2 ce_pin
     * 3 spi_speed
     * 4 getChannel()
     * 5 getDataRate()
     * 6 getPALevel()
     * 7 ((read_register(RF_SETUP) & 1) * 1)
     * 8 getCRCLength()
     * 9 ((read_register(SETUP_AW) & 3) + 2)
     * 10 getPayloadSize()
     * 11 (read_register(SETUP_RETR) >> ARD)
     * 12 (read_register(SETUP_RETR) & 0x0F)
     * 13 (read_register(OBSERVE_TX) >> 4)
     * 14 (read_register(OBSERVE_TX) & 0x0F)
     * 15 static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK))
     * 16 static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY))
     * 17 ((read_register(DYNPD) && (read_register(FEATURE) &_BV(EN_DPL))) * 1)
     * 18 (static_cast<bool>(temp_8_bit & _BV(ENAA_P5)) + 48)
     * 19 (static_cast<bool>(temp_8_bit & _BV(ENAA_P4)) + 48)
     * 20 (static_cast<bool>(temp_8_bit & _BV(ENAA_P3)) + 48)
     * 21 (static_cast<bool>(temp_8_bit & _BV(ENAA_P2)) + 48)
     * 22 (static_cast<bool>(temp_8_bit & _BV(ENAA_P1)) + 48)
     * 23 (static_cast<bool>(temp_8_bit & _BV(ENAA_P0)) + 48)
     * 24 (read_register(NRF_CONFIG) & _BV(PRIM_RX))
     * // TX_ADDR
     * 25 forty_bit_register_array[0]
     * 26 forty_bit_register_array[1]
     * 27 forty_bit_register_array[2]
     * 28 forty_bit_register_array[3]
     * 29 forty_bit_register_array[4]
     * // pipe 0 address
     * 30 forty_bit_register_array[0]
     * 31 forty_bit_register_array[1]
     * 32 forty_bit_register_array[2]
     * 33 forty_bit_register_array[3]
     * 34 forty_bit_register_array[4]
     * // pipe 1 address
     * 35 forty_bit_register_array[0]
     * 36 forty_bit_register_array[1]
     * 37 forty_bit_register_array[2]
     * 38 forty_bit_register_array[3]
     * 39 forty_bit_register_array[4]
     * // pipes 2-5 addresses
     * 40 eight_bit_register_array[0]
     * 41 eight_bit_register_array[0]
     * 42 eight_bit_register_array[0]
     * 43 eight_bit_register_array[0]
     * 44 read_register(EN_RXADDR)
     */

    /*
     * decodeRadioDetails() BitManip use primer
     *
     * We use two methods in BitManip to get bits from the array encoded_details:
     *
     * getBits(source, number_of_bits, encoded_details, &encoded_details_index, &bit_index);
     * and
     * unpackBool(source, encoded_details, &encoded_details_index, &bit_index);
     *
     * The first method gets nonboolean values from the bit array, there is no overflow checking.
     *
     * The major difference between the two methods is that since boolean are always represented by
     * a single bit in the array encoded_details we do not need to tell the method unpackBool()
     * how many bits to get from the array encoded_details.
     */

    // csn_pin
    uint16_t one = 0;
    BitManip::getBits(&one, 16, encoded_details, &encoded_details_index, &bit_index);

    // ce_pin
    uint16_t two = 0;
    BitManip::getBits(&two, 16, encoded_details, &encoded_details_index, &bit_index);

    // static_cast<uint8_t>(spi_speed / 1000000)
    uint8_t three = 0;
    BitManip::getBits(&three, 8, encoded_details, &encoded_details_index, &bit_index);

    // getChannel()
    uint8_t four = 0;
    BitManip::getBits(&four, 8, encoded_details, &encoded_details_index, &bit_index);

    // static_cast<uint16_t>(getChannel() + 2400)
    uint16_t temp = four;
    uint16_t five = static_cast<uint16_t>(temp + 2400UL);

    // getDataRate()
    uint8_t six = 0;
    BitManip::getBits(&six, 8, encoded_details, &encoded_details_index, &bit_index);

    // getPALevel()
    uint8_t seven = 0;
    BitManip::getBits(&seven, 8, encoded_details, &encoded_details_index, &bit_index);

    //(read_register(RF_SETUP) & 1) * 1)
    uint8_t eight = 0;
    BitManip::getBits(&eight, 8, encoded_details, &encoded_details_index, &bit_index);

    // getCRCLength()
    uint8_t nine = 0;
    BitManip::getBits(&nine, 8, encoded_details, &encoded_details_index, &bit_index);

    //((read_register(SETUP_AW) & 3) + 2)
    uint8_t ten = 0;
    BitManip::getBits(&ten, 8, encoded_details, &encoded_details_index, &bit_index);

    // getPayloadSize()
    uint8_t eleven = 0;
    BitManip::getBits(&eleven, 8, encoded_details, &encoded_details_index, &bit_index);

    //((read_register(SETUP_RETR) >> ARD) * 250 + 250) STORED AS 8 bits!
    uint16_t twelve = 0;
    BitManip::getBits(&twelve, 8, encoded_details, &encoded_details_index, &bit_index);
    twelve = twelve * 250UL + 250UL;

    //(read_register(SETUP_RETR) & 0x0F)
    uint8_t thirteen = 0;
    BitManip::getBits(&thirteen, 8, encoded_details, &encoded_details_index, &bit_index);

    //(read_register(OBSERVE_TX) >> 4)
    uint8_t fourteen = 0;
    BitManip::getBits(&fourteen, 8, encoded_details, &encoded_details_index, &bit_index);

    //(read_register(OBSERVE_TX) & 0x0F)
    uint8_t fifteen = 0;
    BitManip::getBits(&fifteen, 8, encoded_details, &encoded_details_index, &bit_index);

    //(static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK)) * 2)
    bool sixteen = 0;
    BitManip::unpackBool(&sixteen, encoded_details, &encoded_details_index, &bit_index);

    //(static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY)) * 1)
    bool seventeen = 0;
    BitManip::unpackBool(&seventeen, encoded_details, &encoded_details_index, &bit_index);

    //((read_register(DYNPD) && (read_register(FEATURE) &_BV(EN_DPL))) * 1)
    uint8_t eighteen = 0;
    BitManip::getBits(&eighteen, 8, encoded_details, &encoded_details_index, &bit_index);

    // auto-ack status
    //(static_cast<bool>(autoAck & _BV(ENAA_P5)) + 48)
    bool nineteen = 0;
    BitManip::unpackBool(&nineteen, encoded_details, &encoded_details_index, &bit_index);
    //(static_cast<bool>(autoAck & _BV(ENAA_P4)) + 48)
    bool twenty = 0;
    BitManip::unpackBool(&twenty, encoded_details, &encoded_details_index, &bit_index);
    //(static_cast<bool>(autoAck & _BV(ENAA_P3)) + 48)
    bool twentyone = 0;
    BitManip::unpackBool(&twentyone, encoded_details, &encoded_details_index, &bit_index);
    //(static_cast<bool>(autoAck & _BV(ENAA_P2)) + 48)
    bool twentytwo = 0;
    BitManip::unpackBool(&twentytwo, encoded_details, &encoded_details_index, &bit_index);
    //(static_cast<bool>(autoAck & _BV(ENAA_P1)) + 48)
    bool twentythree = 0;
    BitManip::unpackBool(&twentythree, encoded_details, &encoded_details_index, &bit_index);
    //(static_cast<bool>(autoAck & _BV(ENAA_P0)) + 48)
    bool twentyfour = 0;
    BitManip::unpackBool(&twentyfour, encoded_details, &encoded_details_index, &bit_index);

    //(read_register(NRF_CONFIG) & _BV(PRIM_RX))
    bool twentyfive = 0;
    BitManip::unpackBool(&twentyfive, encoded_details, &encoded_details_index, &bit_index);

    // TX_ADDR
    uint8_t twentysix = 0;
    BitManip::getBits(&twentysix, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t twentyseven = 0;
    BitManip::getBits(&twentyseven, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t twentyeight = 0;
    BitManip::getBits(&twentyeight, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t twentynine = 0;
    BitManip::getBits(&twentynine, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirty = 0;
    BitManip::getBits(&thirty, 8, encoded_details, &encoded_details_index, &bit_index);

    // pipe 0
    uint8_t thirtyone = 0;
    BitManip::getBits(&thirtyone, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtytwo = 0;
    BitManip::getBits(&thirtytwo, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtythree = 0;
    BitManip::getBits(&thirtythree, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtyfour = 0;
    BitManip::getBits(&thirtyfour, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtyfive = 0;
    BitManip::getBits(&thirtyfive, 8, encoded_details, &encoded_details_index, &bit_index);
    // pipe 1
    uint8_t thirtysix = 0;
    BitManip::getBits(&thirtysix, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtyseven = 0;
    BitManip::getBits(&thirtyseven, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtyeight = 0;
    BitManip::getBits(&thirtyeight, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t thirtynine = 0;
    BitManip::getBits(&thirtynine, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t fourty = 0;
    BitManip::getBits(&fourty, 8, encoded_details, &encoded_details_index, &bit_index);
    // pipes 3-5 8-bit registers
    uint8_t fourtyone = 0;
    BitManip::getBits(&fourtyone, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t fourtytwo = 0;
    BitManip::getBits(&fourtytwo, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t fourtythree = 0;
    BitManip::getBits(&fourtythree, 8, encoded_details, &encoded_details_index, &bit_index);
    uint8_t fourtyfour = 0;
    BitManip::getBits(&fourtyfour, 8, encoded_details, &encoded_details_index, &bit_index);

    // open pipes
    uint8_t fourtyfive = 0;
    BitManip::getBits(&fourtyfive, 8, encoded_details, &encoded_details_index, &bit_index);

    // output debugging_information
    const char *format_string = PSTR("================ SPI Configuration ================\n"
                                     "CSN Pin\t\t\t= %d\n"
                                     "CE Pin\t\t\t= %d\n"
                                     "SPI Frequency\t\t= %d Mhz\n"
                                     "================ NRF Configuration ================\n"
                                     "Channel\t\t\t= %u (~ %u MHz)\n"
                                     "RF Data Rate\t\t"
                                     PRIPSTR
                                     "\n"
                                     "RF Power Amplifier\t"
                                     PRIPSTR
                                     "\n"
                                     "RF Low Noise Amplifier\t"
                                     PRIPSTR
                                     "\n"
                                     "CRC Length\t\t"
                                     PRIPSTR
                                     "\n"
                                     "Address Length\t\t= %d bytes\n"
                                     "Static Payload Length\t= %d bytes\n"
                                     "Auto Retry Delay\t= %d microseconds\n"
                                     "Auto Retry Attempts\t= %d maximum\n"
                                     "Packets lost on\n    current channel\t= %d\r\n"
                                     "Retry attempts made for\n    last transmission\t= %d\r\n"
                                     "Multicast\t\t"
                                     PRIPSTR
                                     "\n"
                                     "Custom ACK Payload\t"
                                     PRIPSTR
                                     "\n"
                                     "Dynamic Payloads\t"
                                     PRIPSTR
                                     "\n"
                                     "Auto Acknowledgment\t"
                                     PRIPSTR
                                     "\n"
                                     "Primary Mode\t\t= %cX\n"
                                     "TX address\t\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 0 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 1 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 2 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 3 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 4 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                     "\n"
                                     "pipe 5 ("
                                     PRIPSTR
                                     ") bound\t= 0x"
                                     PRIPSTR
                                    );

    char tx_address_char_array[16] = {'\0'};
    sprintf_P(tx_address_char_array,
              PSTR("%02x%02x%02x%02x%02x"),
              twentysix,
              twentyseven,
              twentyeight,
              twentynine,
              thirty);

    char pipe_address_char_2d_array[6][16] = {'\0'};

    bool isOpen_array[6] = {false};

    sprintf_P(pipe_address_char_2d_array[0],
              PSTR("%02x%02x%02x%02x%02x"),
              thirtyone,
              thirtytwo,
              thirtythree,
              thirtyfour,
              thirtyfive);
    sprintf_P(pipe_address_char_2d_array[1],
              PSTR("%02x%02x%02x%02x%02x"),
              thirtysix,
              thirtyseven,
              thirtyeight,
              thirtynine,
              fourty);

    sprintf_P(pipe_address_char_2d_array[2],
              PSTR("%02x"),
              fourtyone);
    sprintf_P(pipe_address_char_2d_array[3],
              PSTR("%02x"),
              fourtytwo);
    sprintf_P(pipe_address_char_2d_array[4],
              PSTR("%02x"),
              fourtythree);
    sprintf_P(pipe_address_char_2d_array[5],
              PSTR("%02x"),
              fourtyfour);

    uint8_t openPipes = fourtyfive;
    for (uint8_t i = 0; i < 6; ++i)
    {
        bool isOpen = openPipes & _BV(i);
        isOpen_array[i] = isOpen;
    }

    uint8_t autoAck = 0;
    if (nineteen == true)
    {
        BitManip::SetBit(&autoAck, 0);
    }
    if (twenty == true)
    {
        BitManip::SetBit(&autoAck, 1);
    }
    if (twentyone == true)
    {
        BitManip::SetBit(&autoAck, 2);
    }
    if (twentytwo == true)
    {
        BitManip::SetBit(&autoAck, 3);
    }
    if (twentythree == true)
    {
        BitManip::SetBit(&autoAck, 4);
    }
    if (twentyfour == true)
    {
        BitManip::SetBit(&autoAck, 5);
    }

    char autoack_status_char_array[11] = {'\0'};
    if (autoAck == 0x3F || autoAck == 0)
    {
        // all pipes have the same configuration about auto-ack feature
        sprintf_P(autoack_status_char_array,
                  PSTR("" PRIPSTR
                       ""),
                  (char *)(pgm_read_ptr(&rf24_feature_e_str_P[static_cast<bool>(autoAck) * 1])));
    }
    else
    {
        // representation per pipe
        sprintf_P(autoack_status_char_array,
                  PSTR("= 0b%c%c%c%c%c%c"),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P5)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P4)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P3)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P2)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P1)) + 48),
                  static_cast<char>(static_cast<bool>(autoAck & _BV(ENAA_P0)) + 48));
    }

    sprintf_P(debugging_information,
              format_string,
              one,
              two,
              three,
              four,
              five,
              (char *)(pgm_read_ptr(&rf24_datarate_e_str_P[six])),
              (char *)(pgm_read_ptr(&rf24_pa_dbm_e_str_P[seven])),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[eight])),
              (char *)(pgm_read_ptr(&rf24_crclength_e_str_P[nine])),
              ten,
              eleven,
              twelve,
              thirteen,
              fourteen,
              fifteen,
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[sixteen])),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[seventeen])),
              (char *)(pgm_read_ptr(&rf24_feature_e_str_P[eighteen])),
              (autoack_status_char_array),
              (twentyfive ? 'R' : 'T'),
              (tx_address_char_array),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[0] + 3]))),
              (pipe_address_char_2d_array[0]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[1] + 3]))),
              (pipe_address_char_2d_array[1]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[2] + 3]))),
              (pipe_address_char_2d_array[2]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[3] + 3]))),
              (pipe_address_char_2d_array[3]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[4] + 3]))),
              (pipe_address_char_2d_array[4]),
              ((char *)(pgm_read_ptr(&rf24_feature_e_str_P[isOpen_array[5] + 3]))),
              (pipe_address_char_2d_array[5]));
}
#endif // !defined(MINIMAL)

/****************************************************************************/
#if defined (RF24_SPI_PTR) || defined (DOXYGEN_FORCED)
// does not apply to RF24_LINUX

bool RF24::begin(_SPI* spiBus)
{
    _spi = spiBus;
    return _init_pins() && _init_radio();
}

/****************************************************************************/

bool RF24::begin(_SPI* spiBus, uint16_t _cepin, uint16_t _cspin)
{
    ce_pin = _cepin;
    csn_pin = _cspin;
    return begin(spiBus);
}

#endif // defined (RF24_SPI_PTR) || defined (DOXYGEN_FORCED)

/****************************************************************************/

bool RF24::begin(uint16_t _cepin, uint16_t _cspin)
{
    ce_pin = _cepin;
    csn_pin = _cspin;
    return begin();
}

/****************************************************************************/

bool RF24::begin(void)
{
    #if defined (RF24_LINUX)
        #if defined (RF24_RPi)
    switch(csn_pin) {                 // Ensure valid hardware CS pin
        case 0: break;
        case 1: break;
        // Allow BCM2835 enums for RPi
        case 8: csn_pin = 0; break;
        case 7: csn_pin = 1; break;
        case 18: csn_pin = 10; break; // to make it work on SPI1
        case 17: csn_pin = 11; break;
        case 16: csn_pin = 12; break;
        default: csn_pin = 0; break;
    }
        #endif // RF24_RPi

    _SPI.begin(csn_pin, spi_speed);

    #elif defined (XMEGA_D3)
    _spi->begin(csn_pin);

    #elif defined (RF24_RP2)
    _spi->begin(PICO_DEFAULT_SPI ? spi1 : spi0);

    #else // using an Arduino platform || defined (LITTLEWIRE)

        #if defined (RF24_SPI_PTR)
    _spi->begin();
        #else  // !defined(RF24_SPI_PTR)
    _SPI.begin();
        #endif // !defined(RF24_SPI_PTR)

    #endif // !defined(XMEGA_D3) && !defined(RF24_LINUX)

    return _init_pins() && _init_radio();
}

/****************************************************************************/

bool RF24::_init_pins()
{
    if (!isValid()) {
        // didn't specify the CSN & CE pins to c'tor nor begin()
        return false;
    }

    #if defined (RF24_LINUX)

        #if defined (MRAA)
    GPIO();
    gpio.begin(ce_pin, csn_pin);
        #endif

    pinMode(ce_pin, OUTPUT);
    ce(LOW);
    delay(100);

    #elif defined (LITTLEWIRE)
    pinMode(csn_pin, OUTPUT);
    csn(HIGH);

    #elif defined (XMEGA_D3)
    if (ce_pin != csn_pin) {
        pinMode(ce_pin, OUTPUT);
    };
    ce(LOW);
    csn(HIGH);
    delay(200);

    #else // using an Arduino platform

    // Initialize pins
    if (ce_pin != csn_pin) {
        pinMode(ce_pin, OUTPUT);
        pinMode(csn_pin, OUTPUT);
    }

    ce(LOW);
    csn(HIGH);

        #if defined (__ARDUINO_X86__)
    delay(100);
        #endif
    #endif // !defined(XMEGA_D3) && !defined(LITTLEWIRE) && !defined(RF24_LINUX)

    return true; // assuming pins are connected properly
}

/****************************************************************************/

bool RF24::_init_radio()
{
    // Must allow the radio time to settle else configuration bits will not necessarily stick.
    // This is actually only required following power up but some settling time also appears to
    // be required after resets too. For full coverage, we'll always assume the worst.
    // Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
    // Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
    // WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
    delay(5);

    // Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
    // WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
    // sizes must never be used. See datasheet for a more complete explanation.
    setRetries(5, 15);

    // Then set the data rate to the slowest (and most reliable) speed supported by all
    // hardware. Since this value occupies the same register as the PA level value, set
    // the PA level to MAX
    setRadiation(RF24_PA_MAX, RF24_1MBPS); // LNA enabled by default

    // detect if is a plus variant & use old toggle features command accordingly
    uint8_t before_toggle = read_register(FEATURE);
    toggle_features();
    uint8_t after_toggle = read_register(FEATURE);
    _is_p_variant = before_toggle == after_toggle;
    if (after_toggle){
        if (_is_p_variant){
            // module did not experience power-on-reset (#401)
            toggle_features();
        }
        // allow use of multicast parameter and dynamic payloads by default
        write_register(FEATURE, 0);
    }
    ack_payloads_enabled = false;     // ack payloads disabled by default
    write_register(DYNPD, 0);         // disable dynamic payloads by default (for all pipes)
    dynamic_payloads_enabled = false;
    write_register(EN_AA, 0x3F);      // enable auto-ack on all pipes
    write_register(EN_RXADDR, 3);     // only open RX pipes 0 & 1
    setPayloadSize(32);               // set static payload size to 32 (max) bytes by default
    setAddressWidth(5);               // set default address length to (max) 5 bytes

    // Set up default configuration.  Callers can always change it later.
    // This channel should be universally safe and not bleed over into adjacent
    // spectrum.
    setChannel(76);

    // Reset current status
    // Notice reset and flush is the last thing we do
    write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));


    // Flush buffers
    flush_rx();
    flush_tx();

    // Clear CONFIG register:
    //      Reflect all IRQ events on IRQ pin
    //      Enable PTX
    //      Power Up
    //      16-bit CRC (CRC required by auto-ack)
    // Do not write CE high so radio will remain in standby I mode
    // PTX should use only 22uA of power
    write_register(NRF_CONFIG, (_BV(EN_CRC) | _BV(CRCO)) );
    config_reg = read_register(NRF_CONFIG);

    powerUp();

    // if config is not set correctly then there was a bad response from module
    return config_reg == (_BV(EN_CRC) | _BV(CRCO) | _BV(PWR_UP)) ? true : false;
}

/****************************************************************************/

bool RF24::isChipConnected()
{
    return read_register(SETUP_AW) == (addr_width - static_cast<uint8_t>(2));
}

/****************************************************************************/

bool RF24::isValid()
{
    return ce_pin != 0xFFFF && csn_pin != 0xFFFF;
}

/****************************************************************************/

void RF24::startListening(void)
{
    #if !defined(RF24_TINY) && !defined(LITTLEWIRE)
    powerUp();
    #endif
    config_reg |= _BV(PRIM_RX);
    write_register(NRF_CONFIG, config_reg);
    write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));
    ce(HIGH);

    // Restore the pipe0 address, if exists
    if (_is_p0_rx) {
        write_register(RX_ADDR_P0, pipe0_reading_address, addr_width);
    } else {
        closeReadingPipe(0);
    }
}

/****************************************************************************/
static const PROGMEM uint8_t child_pipe_enable[] = {ERX_P0, ERX_P1, ERX_P2,
                                                    ERX_P3, ERX_P4, ERX_P5};

void RF24::stopListening(void)
{
    ce(LOW);

    //delayMicroseconds(100);
    delayMicroseconds(static_cast<int>(txDelay));
    if (ack_payloads_enabled){
        flush_tx();
    }

    config_reg = static_cast<uint8_t>(config_reg & ~_BV(PRIM_RX));
    write_register(NRF_CONFIG, config_reg);

    #if defined(RF24_TINY) || defined(LITTLEWIRE)
    // for 3 pins solution TX mode is only left with additonal powerDown/powerUp cycle
    if (ce_pin == csn_pin) {
      powerDown();
      powerUp();
    }
    #endif
    write_register(EN_RXADDR, static_cast<uint8_t>(read_register(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[0])))); // Enable RX on pipe0
}

/****************************************************************************/

void RF24::powerDown(void)
{
    ce(LOW); // Guarantee CE is low on powerDown
    config_reg = static_cast<uint8_t>(config_reg & ~_BV(PWR_UP));
    write_register(NRF_CONFIG, config_reg);
}

/****************************************************************************/

//Power up now. Radio will not power down unless instructed by MCU for config changes etc.
void RF24::powerUp(void)
{
    // if not powered up then power up and wait for the radio to initialize
    if (!(config_reg & _BV(PWR_UP))) {
        config_reg |= _BV(PWR_UP);
        write_register(NRF_CONFIG, config_reg);

        // For nRF24L01+ to go from power down mode to TX or RX mode it must first pass through stand-by mode.
        // There must be a delay of Tpd2stby (see Table 16.) after the nRF24L01+ leaves power down mode before
        // the CEis set high. - Tpd2stby can be up to 5ms per the 1.0 datasheet
        delayMicroseconds(RF24_POWERUP_DELAY);
    }
}

/******************************************************************/
#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)

void RF24::errNotify()
{
    #if defined (SERIAL_DEBUG) || defined (RF24_LINUX)
    printf_P(PSTR("RF24 HARDWARE FAIL: Radio not responding, verify pin connections, wiring, etc.\r\n"));
    #endif
    #if defined (FAILURE_HANDLING)
    failureDetected = 1;
    #else
    delay(5000);
    #endif
}

#endif
/******************************************************************/

//Similar to the previous write, clears the interrupt flags
bool RF24::write(const void* buf, uint8_t len, const bool multicast)
{
    //Start Writing
    startFastWrite(buf, len, multicast);

    //Wait until complete or failed
    #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
    uint32_t timer = millis();
    #endif // defined(FAILURE_HANDLING) || defined(RF24_LINUX)

    while (!(get_status() & (_BV(TX_DS) | _BV(MAX_RT)))) {
        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        if (millis() - timer > 95) {
            errNotify();
            #if defined(FAILURE_HANDLING)
            return 0;
            #else
            delay(100);
            #endif
        }
        #endif
    }

    ce(LOW);

    write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));

    //Max retries exceeded
    if (status & _BV(MAX_RT)) {
        flush_tx(); // Only going to be 1 packet in the FIFO at a time using this method, so just flush
        return 0;
    }
    //TX OK 1 or 0
    return 1;
}

bool RF24::write(const void* buf, uint8_t len)
{
    return write(buf, len, 0);
}
/****************************************************************************/

//For general use, the interrupt flags are not important to clear
bool RF24::writeBlocking(const void* buf, uint8_t len, uint32_t timeout)
{
    //Block until the FIFO is NOT full.
    //Keep track of the MAX retries and set auto-retry if seeing failures
    //This way the FIFO will fill up and allow blocking until packets go through
    //The radio will auto-clear everything in the FIFO as long as CE remains high

    uint32_t timer = millis();                               // Get the time that the payload transmission started

    while ((get_status() & (_BV(TX_FULL)))) {                // Blocking only if FIFO is full. This will loop and block until TX is successful or timeout

        if (status & _BV(MAX_RT)) {                          // If MAX Retries have been reached
            reUseTX();                                       // Set re-transmit and clear the MAX_RT interrupt flag
            if (millis() - timer > timeout) {
                return 0;                                    // If this payload has exceeded the user-defined timeout, exit and return 0
            }
        }
        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        if (millis() - timer > (timeout + 95)) {
            errNotify();
            #if defined(FAILURE_HANDLING)
            return 0;
            #endif
        }
        #endif

    }

    //Start Writing
    startFastWrite(buf, len, 0);                             // Write the payload if a buffer is clear

    return 1;                                                // Return 1 to indicate successful transmission
}

/****************************************************************************/

void RF24::reUseTX()
{
    write_register(NRF_STATUS, _BV(MAX_RT));  //Clear max retry flag
    write_register(REUSE_TX_PL, RF24_NOP, true);
    ce(LOW);                                  //Re-Transfer packet
    ce(HIGH);
}

/****************************************************************************/

bool RF24::writeFast(const void* buf, uint8_t len, const bool multicast)
{
    //Block until the FIFO is NOT full.
    //Keep track of the MAX retries and set auto-retry if seeing failures
    //Return 0 so the user can control the retrys and set a timer or failure counter if required
    //The radio will auto-clear everything in the FIFO as long as CE remains high

    #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
    uint32_t timer = millis();
    #endif

    //Blocking only if FIFO is full. This will loop and block until TX is successful or fail
    while ((get_status() & (_BV(TX_FULL)))) {
        if (status & _BV(MAX_RT)) {
            return 0;                                        //Return 0. The previous payload has not been retransmitted
            // From the user perspective, if you get a 0, just keep trying to send the same payload
        }
        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        if (millis() - timer > 95) {
            errNotify();
            #if defined(FAILURE_HANDLING)
            return 0;
            #endif // defined(FAILURE_HANDLING)
        }
        #endif
    }
    startFastWrite(buf, len, multicast);                     // Start Writing

    return 1;
}

bool RF24::writeFast(const void* buf, uint8_t len)
{
    return writeFast(buf, len, 0);
}

/****************************************************************************/

//Per the documentation, we want to set PTX Mode when not listening. Then all we do is write data and set CE high
//In this mode, if we can keep the FIFO buffers loaded, packets will transmit immediately (no 130us delay)
//Otherwise we enter Standby-II mode, which is still faster than standby mode
//Also, we remove the need to keep writing the config register over and over and delaying for 150 us each time if sending a stream of data

void RF24::startFastWrite(const void* buf, uint8_t len, const bool multicast, bool startTx)
{ //TMRh20

    write_payload(buf, len, multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD);
    if (startTx) {
        ce(HIGH);
    }
}

/****************************************************************************/

//Added the original startWrite back in so users can still use interrupts, ack payloads, etc
//Allows the library to pass all tests
bool RF24::startWrite(const void* buf, uint8_t len, const bool multicast)
{

    // Send the payload
    write_payload(buf, len, multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD);
    ce(HIGH);
    #if !defined(F_CPU) || F_CPU > 20000000
    delayMicroseconds(10);
    #endif
    ce(LOW);
    return !(status & _BV(TX_FULL));
}

/****************************************************************************/

bool RF24::rxFifoFull()
{
    return read_register(FIFO_STATUS) & _BV(RX_FULL);
}

/****************************************************************************/

bool RF24::txStandBy()
{

    #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
    uint32_t timeout = millis();
    #endif
    while (!(read_register(FIFO_STATUS) & _BV(TX_EMPTY))) {
        if (status & _BV(MAX_RT)) {
            write_register(NRF_STATUS, _BV(MAX_RT));
            ce(LOW);
            flush_tx();    //Non blocking, flush the data
            return 0;
        }
        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        if (millis() - timeout > 95) {
            errNotify();
            #if defined(FAILURE_HANDLING)
            return 0;
            #endif
        }
        #endif
    }

    ce(LOW);               //Set STANDBY-I mode
    return 1;
}

/****************************************************************************/

bool RF24::txStandBy(uint32_t timeout, bool startTx)
{

    if (startTx) {
        stopListening();
        ce(HIGH);
    }
    uint32_t start = millis();

    while (!(read_register(FIFO_STATUS) & _BV(TX_EMPTY))) {
        if (status & _BV(MAX_RT)) {
            write_register(NRF_STATUS, _BV(MAX_RT));
            ce(LOW); // Set re-transmit
            ce(HIGH);
            if (millis() - start >= timeout) {
                ce(LOW);
                flush_tx();
                return 0;
            }
        }
        #if defined(FAILURE_HANDLING) || defined(RF24_LINUX)
        if (millis() - start > (timeout + 95)) {
            errNotify();
            #if defined(FAILURE_HANDLING)
            return 0;
            #endif
        }
        #endif
    }

    ce(LOW);  //Set STANDBY-I mode
    return 1;

}

/****************************************************************************/

void RF24::maskIRQ(bool tx, bool fail, bool rx)
{
    /* clear the interrupt flags */
    config_reg = static_cast<uint8_t>(config_reg & ~(1 << MASK_MAX_RT | 1 << MASK_TX_DS | 1 << MASK_RX_DR));
    /* set the specified interrupt flags */
    config_reg = static_cast<uint8_t>(config_reg | fail << MASK_MAX_RT | tx << MASK_TX_DS | rx << MASK_RX_DR);
    write_register(NRF_CONFIG, config_reg);
}

/****************************************************************************/

uint8_t RF24::getDynamicPayloadSize(void)
{
    uint8_t result = read_register(R_RX_PL_WID);

    if (result > 32) {
        flush_rx();
        delay(2);
        return 0;
    }
    return result;
}

/****************************************************************************/

bool RF24::available(void)
{
    return available(NULL);
}

/****************************************************************************/

bool RF24::available(uint8_t* pipe_num)
{
    // get implied RX FIFO empty flag from status byte
    uint8_t pipe = (get_status() >> RX_P_NO) & 0x07;
    if (pipe > 5)
        return 0;

    // If the caller wants the pipe number, include that
    if (pipe_num)
        *pipe_num = pipe;

    return 1;
}

/****************************************************************************/

void RF24::read(void* buf, uint8_t len)
{

    // Fetch the payload
    read_payload(buf, len);

    //Clear the only applicable interrupt flags
    write_register(NRF_STATUS, _BV(RX_DR));

}

/****************************************************************************/

void RF24::whatHappened(bool& tx_ok, bool& tx_fail, bool& rx_ready)
{
    // Read the status & reset the status in one easy call
    // Or is that such a good idea?
    write_register(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT));

    // Report to the user what happened
    tx_ok = status & _BV(TX_DS);
    tx_fail = status & _BV(MAX_RT);
    rx_ready = status & _BV(RX_DR);
}

/****************************************************************************/

void RF24::openWritingPipe(uint64_t value)
{
    // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
    // expects it LSB first too, so we're good.

    write_register(RX_ADDR_P0, reinterpret_cast<uint8_t*>(&value), addr_width);
    write_register(TX_ADDR, reinterpret_cast<uint8_t*>(&value), addr_width);
}

/****************************************************************************/
void RF24::openWritingPipe(const uint8_t* address)
{
    // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
    // expects it LSB first too, so we're good.
    write_register(RX_ADDR_P0, address, addr_width);
    write_register(TX_ADDR, address, addr_width);
}

/****************************************************************************/
static const PROGMEM uint8_t child_pipe[] = {RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2,
                                             RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5};

void RF24::openReadingPipe(uint8_t child, uint64_t address)
{
    // If this is pipe 0, cache the address.  This is needed because
    // openWritingPipe() will overwrite the pipe 0 address, so
    // startListening() will have to restore it.
    if (child == 0) {
        memcpy(pipe0_reading_address, &address, addr_width);
        _is_p0_rx = true;
    }

    if (child <= 5) {
        // For pipes 2-5, only write the LSB
        if (child < 2) {
            write_register(pgm_read_byte(&child_pipe[child]), reinterpret_cast<const uint8_t*>(&address), addr_width);
        } else {
            write_register(pgm_read_byte(&child_pipe[child]), reinterpret_cast<const uint8_t*>(&address), 1);
        }

        // Note it would be more efficient to set all of the bits for all open
        // pipes at once.  However, I thought it would make the calling code
        // more simple to do it this way.
        write_register(EN_RXADDR, static_cast<uint8_t>(read_register(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[child]))));
    }
}

/****************************************************************************/

void RF24::setAddressWidth(uint8_t a_width)
{
    a_width = static_cast<uint8_t>(a_width - 2);
    if (a_width) {
        write_register(SETUP_AW, static_cast<uint8_t>(a_width % 4));
        addr_width = static_cast<uint8_t>((a_width % 4) + 2);
    } else {
        write_register(SETUP_AW, static_cast<uint8_t>(0));
        addr_width = static_cast<uint8_t>(2);
    }

}

/****************************************************************************/

void RF24::openReadingPipe(uint8_t child, const uint8_t* address)
{
    // If this is pipe 0, cache the address.  This is needed because
    // openWritingPipe() will overwrite the pipe 0 address, so
    // startListening() will have to restore it.
    if (child == 0) {
        memcpy(pipe0_reading_address, address, addr_width);
        _is_p0_rx = true;
    }
    if (child <= 5) {
        // For pipes 2-5, only write the LSB
        if (child < 2) {
            write_register(pgm_read_byte(&child_pipe[child]), address, addr_width);
        } else {
            write_register(pgm_read_byte(&child_pipe[child]), address, 1);
        }

        // Note it would be more efficient to set all of the bits for all open
        // pipes at once.  However, I thought it would make the calling code
        // more simple to do it this way.
        write_register(EN_RXADDR, static_cast<uint8_t>(read_register(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[child]))));

    }
}

/****************************************************************************/

void RF24::closeReadingPipe(uint8_t pipe)
{
    write_register(EN_RXADDR, static_cast<uint8_t>(read_register(EN_RXADDR) & ~_BV(pgm_read_byte(&child_pipe_enable[pipe]))));
    if (!pipe) {
        // keep track of pipe 0's RX state to avoid null vs 0 in addr cache
        _is_p0_rx = false;
    }
}

/****************************************************************************/

void RF24::toggle_features(void)
{
    beginTransaction();
    #if defined (RF24_SPI_PTR)
    status = _spi->transfer(ACTIVATE);
    _spi->transfer(0x73);
    #else
    status = _SPI.transfer(ACTIVATE);
    _SPI.transfer(0x73);
    #endif
    endTransaction();
}

/****************************************************************************/

void RF24::enableDynamicPayloads(void)
{
    // Enable dynamic payload throughout the system

    //toggle_features();
    write_register(FEATURE, read_register(FEATURE) | _BV(EN_DPL));

    IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n", read_register(FEATURE)));

    // Enable dynamic payload on all pipes
    //
    // Not sure the use case of only having dynamic payload on certain
    // pipes, so the library does not support it.
    write_register(DYNPD, read_register(DYNPD) | _BV(DPL_P5) | _BV(DPL_P4) | _BV(DPL_P3) | _BV(DPL_P2) | _BV(DPL_P1) | _BV(DPL_P0));

    dynamic_payloads_enabled = true;
}

/****************************************************************************/
void RF24::disableDynamicPayloads(void)
{
    // Disables dynamic payload throughout the system.  Also disables Ack Payloads

    //toggle_features();
    write_register(FEATURE, 0);

    IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n", read_register(FEATURE)));

    // Disable dynamic payload on all pipes
    //
    // Not sure the use case of only having dynamic payload on certain
    // pipes, so the library does not support it.
    write_register(DYNPD, 0);

    dynamic_payloads_enabled = false;
    ack_payloads_enabled = false;
}

/****************************************************************************/

void RF24::enableAckPayload(void)
{
    // enable ack payloads and dynamic payload features

    if (!ack_payloads_enabled){
        write_register(FEATURE, read_register(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL));

        IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n", read_register(FEATURE)));

        // Enable dynamic payload on pipes 0 & 1
        write_register(DYNPD, read_register(DYNPD) | _BV(DPL_P1) | _BV(DPL_P0));
        dynamic_payloads_enabled = true;
        ack_payloads_enabled = true;
    }
}

/****************************************************************************/

void RF24::disableAckPayload(void)
{
    // disable ack payloads (leave dynamic payload features as is)
    if (ack_payloads_enabled){
        write_register(FEATURE, static_cast<uint8_t>(read_register(FEATURE) | ~_BV(EN_ACK_PAY)));

        IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n", read_register(FEATURE)));

        ack_payloads_enabled = false;
    }
}

/****************************************************************************/

void RF24::enableDynamicAck(void)
{
    //
    // enable dynamic ack features
    //
    //toggle_features();
    write_register(FEATURE, read_register(FEATURE) | _BV(EN_DYN_ACK));

    IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n", read_register(FEATURE)));
}

/****************************************************************************/

bool RF24::writeAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
    if (ack_payloads_enabled){
        const uint8_t* current = reinterpret_cast<const uint8_t*>(buf);

        write_payload(current, len, W_ACK_PAYLOAD | (pipe & 0x07));
        return !(status & _BV(TX_FULL));
    }
    return 0;
}

/****************************************************************************/

bool RF24::isAckPayloadAvailable(void)
{
    return available(NULL);
}

/****************************************************************************/

bool RF24::isPVariant(void)
{
    return _is_p_variant;
}

/****************************************************************************/

void RF24::setAutoAck(bool enable)
{
    if (enable){
        write_register(EN_AA, 0x3F);
    }else{
        write_register(EN_AA, 0);
        // accomodate ACK payloads feature
        if (ack_payloads_enabled){
            disableAckPayload();
        }
    }
}

/****************************************************************************/

void RF24::setAutoAck(uint8_t pipe, bool enable)
{
    if (pipe < 6) {
        uint8_t en_aa = read_register(EN_AA);
        if (enable) {
            en_aa |= static_cast<uint8_t>(_BV(pipe));
        }else{
            en_aa = static_cast<uint8_t>(en_aa & ~_BV(pipe));
            if (ack_payloads_enabled && !pipe){
                disableAckPayload();
            }
        }
        write_register(EN_AA, en_aa);
    }
}

/****************************************************************************/

bool RF24::testCarrier(void)
{
    return (read_register(CD) & 1);
}

/****************************************************************************/

bool RF24::testRPD(void)
{
    return (read_register(RPD) & 1);
}

/****************************************************************************/

void RF24::setPALevel(uint8_t level, bool lnaEnable)
{
    uint8_t setup = read_register(RF_SETUP) & static_cast<uint8_t>(0xF8);
    setup |= _pa_level_reg_value(level, lnaEnable);
    write_register(RF_SETUP, setup);
}

/****************************************************************************/

uint8_t RF24::getPALevel(void)
{

    return (read_register(RF_SETUP) & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH))) >> 1;
}

/****************************************************************************/

uint8_t RF24::getARC(void)
{

    return read_register(OBSERVE_TX) & 0x0F;
}

/****************************************************************************/

bool RF24::setDataRate(rf24_datarate_e speed)
{
    bool result = false;
    uint8_t setup = read_register(RF_SETUP);

    // HIGH and LOW '00' is 1Mbs - our default
    setup = static_cast<uint8_t>(setup & ~(_BV(RF_DR_LOW) | _BV(RF_DR_HIGH)));
    setup |= _data_rate_reg_value(speed);

    write_register(RF_SETUP, setup);

    // Verify our result
    if (read_register(RF_SETUP) == setup) {
        result = true;
    }
    return result;
}

/****************************************************************************/

rf24_datarate_e RF24::getDataRate(void)
{
    rf24_datarate_e result;
    uint8_t dr = read_register(RF_SETUP) & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));

    // switch uses RAM (evil!)
    // Order matters in our case below
    if (dr == _BV(RF_DR_LOW)) {
        // '10' = 250KBPS
        result = RF24_250KBPS;
    } else if (dr == _BV(RF_DR_HIGH)) {
        // '01' = 2MBPS
        result = RF24_2MBPS;
    } else {
        // '00' = 1MBPS
        result = RF24_1MBPS;
    }
    return result;
}

/****************************************************************************/

void RF24::setCRCLength(rf24_crclength_e length)
{
    config_reg = static_cast<uint8_t>(config_reg & ~(_BV(CRCO) | _BV(EN_CRC)));

    // switch uses RAM (evil!)
    if (length == RF24_CRC_DISABLED) {
        // Do nothing, we turned it off above.
    } else if (length == RF24_CRC_8) {
        config_reg |= _BV(EN_CRC);
    } else {
        config_reg |= _BV(EN_CRC);
        config_reg |= _BV(CRCO);
    }
    write_register(NRF_CONFIG, config_reg);
}

/****************************************************************************/

rf24_crclength_e RF24::getCRCLength(void)
{
    rf24_crclength_e result = RF24_CRC_DISABLED;
    uint8_t AA = read_register(EN_AA);
    config_reg = read_register(NRF_CONFIG);

    if (config_reg & _BV(EN_CRC) || AA) {
        if (config_reg & _BV(CRCO)) {
            result = RF24_CRC_16;
        } else {
            result = RF24_CRC_8;
        }
    }

    return result;
}

/****************************************************************************/

void RF24::disableCRC(void)
{
    config_reg = static_cast<uint8_t>(config_reg & ~_BV(EN_CRC));
    write_register(NRF_CONFIG, config_reg);
}

/****************************************************************************/
void RF24::setRetries(uint8_t delay, uint8_t count)
{
    write_register(SETUP_RETR, static_cast<uint8_t>(rf24_min(15, delay) << ARD | rf24_min(15, count)));
}

/****************************************************************************/
void RF24::startConstCarrier(rf24_pa_dbm_e level, uint8_t channel)
{
    stopListening();
    write_register(RF_SETUP, read_register(RF_SETUP) | _BV(CONT_WAVE) | _BV(PLL_LOCK));
    if (isPVariant()){
        setAutoAck(0);
        setRetries(0, 0);
        uint8_t dummy_buf[32];
        for (uint8_t i = 0; i < 32; ++i)
            dummy_buf[i] = 0xFF;

        // use write_register() instead of openWritingPipe() to bypass
        // truncation of the address with the current RF24::addr_width value
        write_register(TX_ADDR, reinterpret_cast<uint8_t*>(&dummy_buf), 5);
        flush_tx();  // so we can write to top level

        // use write_register() instead of write_payload() to bypass
        // truncation of the payload with the current RF24::payload_size value
        write_register(W_TX_PAYLOAD, reinterpret_cast<const uint8_t*>(&dummy_buf), 32);

        disableCRC();
    }
    setPALevel(level);
    setChannel(channel);
    IF_SERIAL_DEBUG(printf_P(PSTR("RF_SETUP=%02x\r\n"), read_register(RF_SETUP)));
    ce(HIGH);
    if (isPVariant()){
        delay(1); // datasheet says 1 ms is ok in this instance
        ce(LOW);
        reUseTX();
    }
}

/****************************************************************************/

void RF24::stopConstCarrier()
{
    /*
     * A note from the datasheet:
     * Do not use REUSE_TX_PL together with CONT_WAVE=1. When both these
     * registers are set the chip does not react when setting CE low. If
     * however, both registers are set PWR_UP = 0 will turn TX mode off.
     */
    powerDown();  // per datasheet recommendation (just to be safe)
    write_register(RF_SETUP, static_cast<uint8_t>(read_register(RF_SETUP) & ~_BV(CONT_WAVE) & ~_BV(PLL_LOCK)));
    ce(LOW);
}

/****************************************************************************/

void RF24::toggleAllPipes(bool isEnabled)
{
    write_register(EN_RXADDR, static_cast<uint8_t>(isEnabled ? 0x3F : 0));
}

/****************************************************************************/

uint8_t RF24::_data_rate_reg_value(rf24_datarate_e speed)
{
    #if !defined(F_CPU) || F_CPU > 20000000
    txDelay = 280;
    #else //16Mhz Arduino
    txDelay=85;
    #endif
    if (speed == RF24_250KBPS) {
        #if !defined(F_CPU) || F_CPU > 20000000
        txDelay = 505;
        #else //16Mhz Arduino
        txDelay = 155;
        #endif
        // Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0
        // Making it '10'.
        return static_cast<uint8_t>(_BV(RF_DR_LOW));
    }
    else if (speed == RF24_2MBPS) {
        #if !defined(F_CPU) || F_CPU > 20000000
        txDelay = 240;
        #else // 16Mhz Arduino
        txDelay = 65;
        #endif
        // Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
        // Making it '01'
        return static_cast<uint8_t>(_BV(RF_DR_HIGH));
    }
    // HIGH and LOW '00' is 1Mbs - our default
    return static_cast<uint8_t>(0);

}

/****************************************************************************/

uint8_t RF24::_pa_level_reg_value(uint8_t level, bool lnaEnable)
{
    // If invalid level, go to max PA
    // Else set level as requested
    // + lnaEnable (1 or 0) to support the SI24R1 chip extra bit
    return static_cast<uint8_t>(((level > RF24_PA_MAX ? static_cast<uint8_t>(RF24_PA_MAX) : level) << 1) + lnaEnable);
}

/****************************************************************************/

void RF24::setRadiation(uint8_t level, rf24_datarate_e speed, bool lnaEnable)
{
    uint8_t setup = _data_rate_reg_value(speed);
    setup |= _pa_level_reg_value(level, lnaEnable);
    write_register(RF_SETUP, setup);
}