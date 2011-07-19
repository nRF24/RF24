/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include <WProgram.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

#undef SERIAL_DEBUG
#ifdef SERIAL_DEBUG
#define IF_SERIAL_DEBUG(x) (x)
#else
#define IF_SERIAL_DEBUG(x)
#endif

// Avoid spurious warnings
#undef PROGMEM 
#define PROGMEM __attribute__(( section(".progmem.data") )) 
#undef PSTR 
#define PSTR(s) (__extension__({static prog_char __c[] PROGMEM = (s); &__c[0];}))

/******************************************************************/

void RF24::csn(int mode)
{
  digitalWrite(csn_pin,mode);
}

/******************************************************************/

void RF24::ce(int level)
{
  digitalWrite(ce_pin,level);
}

/******************************************************************/

void RF24::configSPIBus(void)
{
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV2); 
}

/******************************************************************/

uint8_t RF24::read_register(uint8_t reg, uint8_t* buf, uint8_t len)
{
  uint8_t status;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- )
    *buf++ = SPI.transfer(0xff);

  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::read_register(uint8_t reg)
{
  csn(LOW);
  configSPIBus() ;
  SPI.transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
  uint8_t result = SPI.transfer(0xff);

  csn(HIGH);
  return result;
}

/******************************************************************/

uint8_t RF24::write_register(uint8_t reg, const uint8_t* buf, uint8_t len)
{
  uint8_t status;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( W_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- )
    SPI.transfer(*buf++);

  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::write_register(uint8_t reg, uint8_t value)
{
  uint8_t status;

  IF_SERIAL_DEBUG(printf_P(PSTR("write_register(%02x,%02x)\n\r"),reg,value));

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( W_REGISTER | ( REGISTER_MASK & reg ) );
  SPI.transfer(value);
  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::write_payload(const void* buf, uint8_t len)
{
  uint8_t status;

  const uint8_t* current = (const uint8_t*)buf;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( W_TX_PAYLOAD );
  uint8_t data_len = min(len,payload_size);
  uint8_t blank_len = payload_size - data_len;
  while ( data_len-- )
    SPI.transfer(*current++);
  while ( blank_len-- )
    SPI.transfer(0);

  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::read_payload(void* buf, uint8_t len) 
{
  uint8_t status;
  uint8_t* current = (uint8_t*)buf;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( R_RX_PAYLOAD );
  uint8_t data_len = min(len,payload_size);
  uint8_t blank_len = payload_size - data_len;
  while ( data_len-- )
    *current++ = SPI.transfer(0xff);
  while ( blank_len-- )
    SPI.transfer(0xff);
  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::flush_rx(void)
{
  uint8_t status;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( FLUSH_RX );  
  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::flush_tx(void)
{
  uint8_t status;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( FLUSH_TX );  
  csn(HIGH);

  return status;
}

/******************************************************************/

uint8_t RF24::get_status(void)
{
  uint8_t status;

  csn(LOW);
  configSPIBus() ;
  status = SPI.transfer( NOP );
  csn(HIGH);

  return status;
}

/******************************************************************/

void RF24::print_status(uint8_t status)
{
  printf_P(PSTR("STATUS=%02x: RX_DR=%x TX_DS=%x MAX_RT=%x RX_P_NO=%x TX_FULL=%x\n\r"),
  status,
  (status & _BV(RX_DR))?1:0,
  (status & _BV(TX_DS))?1:0,
  (status & _BV(MAX_RT))?1:0,
  ((status >> RX_P_NO) & B111),
  (status & _BV(TX_FULL))?1:0
    );
}

/******************************************************************/

void RF24::print_observe_tx(uint8_t value)
{
  printf_P(PSTR("OBSERVE_TX=%02x: POLS_CNT=%x ARC_CNT=%x\n\r"),
  value,
  (value >> PLOS_CNT) & B1111,
  (value >> ARC_CNT) & B1111
    );
}

/******************************************************************/

RF24::RF24(uint8_t _cepin, uint8_t _cspin): 
    ce_pin(_cepin), csn_pin(_cspin), wide_band(true), p_variant(false),
    payload_size(32), ack_payload_available(false)
{
}

/******************************************************************/

void RF24::setChannel(uint8_t channel)
{
    if( wide_band ) {
	write_register(RF_CH,min(channel,127));
    } else {
	write_register(RF_CH,min(channel,127));
    }
}

/******************************************************************/

void RF24::setPayloadSize(uint8_t size)
{
  payload_size = min(size,32);
}

/******************************************************************/

uint8_t RF24::getPayloadSize(void) 
{
  return payload_size;
}

/******************************************************************/

void RF24::printDetails(void)
{
  uint8_t buffer[5];
  uint8_t status = read_register(RX_ADDR_P0,buffer,5);
  print_status(status);
  printf_P(PSTR("RX_ADDR_P0 = 0x"));
  uint8_t *bufptr = buffer + 5;
  while( bufptr-- > buffer )
    printf_P(PSTR("%02x"),*bufptr);
  printf_P(PSTR("\n\r"));

  status = read_register(RX_ADDR_P1,buffer,5);
  printf_P(PSTR("RX_ADDR_P1 = 0x"));
  bufptr = buffer + 5;
  while( bufptr-- > buffer )
    printf_P(PSTR("%02x"),*bufptr);
  printf_P(PSTR("\n\r"));

  status = read_register(RX_ADDR_P2,buffer,1);
  printf_P(PSTR("RX_ADDR_P2 = 0x%02x"),*buffer);
  printf_P(PSTR("\n\r"));

  status = read_register(RX_ADDR_P3,buffer,1);
  printf_P(PSTR("RX_ADDR_P3 = 0x%02x"),*buffer);
  printf_P(PSTR("\n\r"));

  status = read_register(RX_ADDR_P4,buffer,1);
  printf_P(PSTR("RX_ADDR_P4 = 0x%02x"),*buffer);
  printf_P(PSTR("\n\r"));

  status = read_register(RX_ADDR_P5,buffer,1);
  printf_P(PSTR("RX_ADDR_P5 = 0x%02x"),*buffer);
  printf_P(PSTR("\n\r"));

  status = read_register(TX_ADDR,buffer,5);
  printf_P(PSTR("TX_ADDR = 0x"));
  bufptr = buffer + 5;
  while( bufptr-- > buffer )
    printf_P(PSTR("%02x"),*bufptr);
  printf_P(PSTR("\n\r"));
  
  status = read_register(RX_PW_P0,buffer,1);
  printf_P(PSTR("RX_PW_P0 = 0x%02x\n\r"),*buffer);

  status = read_register(RX_PW_P1,buffer,1);
  printf_P(PSTR("RX_PW_P1 = 0x%02x\n\r"),*buffer);

  read_register(EN_AA,buffer,1);
  printf_P(PSTR("EN_AA = 0x%02x\n\r"),*buffer);

  read_register(EN_RXADDR,buffer,1);
  printf_P(PSTR("EN_RXADDR = 0x%02x\n\r"),*buffer);

  read_register(RF_CH,buffer,1);
  printf_P(PSTR("RF_CH = 0x%02x\n\r"),*buffer);  

  read_register(RF_SETUP,buffer,1);
  printf_P(PSTR("RF_SETUP = 0x%02x (data rate: %d)\n\r"),*buffer,getDataRate());  
  printf_P(PSTR("Hardware; isPVariant: %d\n\r"),isPVariant());

  read_register(CONFIG,buffer,1);
  printf_P(PSTR("CONFIG = 0x%02x (CRC enable: %d; CRC16: %d)\n\r"),
	   *buffer,(*buffer)&_BV(EN_CRC)?1:0,
	   (*buffer)&_BV(CRCO)?1:0);  
}

/******************************************************************/

void RF24::begin(void)
{
  // Initialize pins
  pinMode(ce_pin,OUTPUT);
  pinMode(csn_pin,OUTPUT);

  // Initialize SPI bus
  // Minimum ideal SPI bus speed is 2x data rate
  // If we assume 2Mbs data rate and 16Mhz clock, a
  // divider of 4 is the minimum we want.
  // CLK:BUS 8Mhz:2Mhz, 16Mhz:4Mhz, or 20Mhz:5Mhz
  // We'll use a divider of 2 which will work up to
  // MCU speeds of 20Mhz.
  // CLK:BUS 8Mhz:4Mhz, 16Mhz:8Mhz, or 20Mhz:10Mhz (max)
  configSPIBus() ;
  SPI.begin();

  ce(LOW);
  csn(HIGH);

  // Must allow the radio time to settle else configuration bits will not necessarily stick.
  // This is actually only required following power up but some settling time also appears to
  // be required after resets too. For full coverage, we'll always assume the worst.
  // Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
  // Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
  // WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
  delay( 5 ) ;

  // Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
  // WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
  // sizes must never be used. See documentation for a more complete explanation.
  write_register(SETUP_RETR,(B0100 << ARD) | (B1111 << ARC));

  // Restore our default PA level
  setPALevel( RF24_PA_MAX ) ;

  // Determine if this is a p or non-p RF24 module and then
  // reset our data rate back to default value. This works
  // because a non-P variant won't allow the data rate to
  // be set to 250Kbps.
  if( setDataRate( RF24_250KBPS ) ) {
      p_variant = true ;
  }
  setDataRate( RF24_2MBPS ) ;

  // Initialize CRC and request 2-byte (16bit) CRC
  setCRCLength( RF24_CRC_16 ) ;

  // Reset current status
  // Notice reset and flush is the last thing we do
  write_register(STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
 
  // Flush buffers
  flush_rx();
  flush_tx();
}

/******************************************************************/

void RF24::startListening(void)
{
  write_register(CONFIG, read_register(CONFIG) | _BV(PWR_UP) | _BV(PRIM_RX));
  write_register(STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
  
  // Restore the pipe0 adddress
  write_register(RX_ADDR_P0, reinterpret_cast<const uint8_t*>(&pipe0_reading_address), 5);

  // Flush buffers
  flush_rx();

  // Go!  
  ce(HIGH);

  // wait for the radio to come up (130us actually only needed)
  delayMicroseconds(130);
}

/******************************************************************/

void RF24::stopListening(void)
{
  ce(LOW);
}

/******************************************************************/

void RF24::powerDown(void)
{
  write_register(CONFIG,read_register(CONFIG) & ~_BV(PWR_UP));
}

/******************************************************************/

void RF24::powerUp(void)
{
  write_register(CONFIG,read_register(CONFIG) | _BV(PWR_UP));
}

/******************************************************************/

boolean RF24::write( const void* buf, uint8_t len )
{
  boolean result = false;

  // Transmitter power-up
  write_register(CONFIG, ( read_register(CONFIG) | _BV(PWR_UP) ) & ~_BV(PRIM_RX) );
  delay(2);

  // Send the payload
  write_payload( buf, len );

  // Allons!
  ce(HIGH);

  // IN the end, the send should be blocking.  It comes back in 60ms worst case, or much faster
  // if I tighted up the retry logic.  (Default settings will be 1500us.
  // Monitor the send
  uint8_t observe_tx;
  uint8_t status;
  uint8_t retries = 255;
  do
  {
    status = read_register(OBSERVE_TX,&observe_tx,1);
    IF_SERIAL_DEBUG(Serial.print(status,HEX));
    IF_SERIAL_DEBUG(Serial.print(observe_tx,HEX));
    if ( ! retries-- )
    {
      IF_SERIAL_DEBUG(printf("ABORTED: too many retries\n\r"));
      break;
    }
  }
  while( ! ( status & ( _BV(TX_DS) | _BV(MAX_RT) ) ) );

  if ( status & _BV(TX_DS) )
    result = true;
  
  IF_SERIAL_DEBUG(Serial.print(result?"...OK.":"...Failed"));
  
  ack_payload_available = ( status & _BV(RX_DR) );
  if ( ack_payload_available )
  {
    write_register(STATUS,_BV(RX_DR) );
    ack_payload_length = read_payload_length();
    IF_SERIAL_DEBUG(Serial.print("[AckPacket]/"));
    IF_SERIAL_DEBUG(Serial.println(ack_payload_length,DEC));
  }

  // Yay, we are done.
  ce(LOW);

  // Power down
  write_register(CONFIG,read_register(CONFIG) & ~_BV(PWR_UP));

  // Reset current status
  write_register(STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Flush buffers
  flush_tx();  

  return result;
}

/******************************************************************/

uint8_t RF24::read_payload_length(void)
{
  uint8_t result = 0;

  csn(LOW);
  configSPIBus() ;
  SPI.transfer( R_RX_PL_WID );
  result = SPI.transfer(0xff);
  csn(HIGH);

  return result;
}

/******************************************************************/

boolean RF24::available(void)
{
  return available(NULL);
}

/******************************************************************/

boolean RF24::available(uint8_t* pipe_num)
{
  uint8_t status = get_status();
  IF_SERIAL_DEBUG(print_status(status));
  boolean result = ( status & _BV(RX_DR) );

  if (result)
  {
    // If the caller wants the pipe number, include that
    if ( pipe_num )
      *pipe_num = ( status >> RX_P_NO ) & B111;

    // Clear the status bit

    // ??? Should this REALLY be cleared now?  Or wait until we
    // actually READ the payload?

    write_register(STATUS,_BV(RX_DR) );

    // Handle ack payload receipt
    if ( status & _BV(TX_DS) )
    {
      write_register(STATUS,_BV(TX_DS));
    }
  }

  return result;
}

/******************************************************************/

boolean RF24::read( void* buf, uint8_t len ) 
{
  // was this the last of the data available?
  boolean result = false;

  // Fetch the payload
  read_payload( buf, len );

  uint8_t fifo_status;
  read_register(FIFO_STATUS,&fifo_status,1);
  if ( fifo_status & _BV(RX_EMPTY) )
    result = true;

  return result;
}

/******************************************************************/

void RF24::openWritingPipe(uint64_t value)
{
  // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
  // expects it LSB first too, so we're good.  
  
  write_register(RX_ADDR_P0, reinterpret_cast<uint8_t*>(&value), 5);
  write_register(TX_ADDR, reinterpret_cast<uint8_t*>(&value), 5);  
  write_register(RX_PW_P0,min(payload_size,32));
}

/******************************************************************/

void RF24::openReadingPipe(uint8_t child, uint64_t address)
{
  const uint8_t child_pipe[] = { 
    RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2, RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5   };
  const uint8_t child_payload_size[] = { 
    RX_PW_P0, RX_PW_P1, RX_PW_P2, RX_PW_P3, RX_PW_P4, RX_PW_P5   };
  const uint8_t child_pipe_enable[] = { 
    ERX_P0, ERX_P1, ERX_P2, ERX_P3, ERX_P4, ERX_P5 };

  // If this is pipe 0, cache the address.  This is needed because
  // openWritingPipe() will overwrite the pipe 0 address, so
  // startListening() will have to restore it.
  if (child == 0)
    pipe0_reading_address = address;

  if (child < 6)
  {
    // For pipes 2-5, only write the LSB
    if ( child < 2 )
      write_register(child_pipe[child], reinterpret_cast<const uint8_t*>(&address), 5);    
    else  
      write_register(child_pipe[child], reinterpret_cast<const uint8_t*>(&address), 1);    
    
    write_register(child_payload_size[child],payload_size);  

    // Note this is kind of an inefficient way to set up these enable bits, but I thought it made
    // the calling code more simple
    uint8_t en_rx;
    read_register(EN_RXADDR,&en_rx,1);
    en_rx |= _BV(child_pipe_enable[child]);
    write_register(EN_RXADDR,en_rx);
  }
}

/******************************************************************/
  
void RF24::toggle_features(void)
{
  csn(LOW);
  configSPIBus() ;
  SPI.transfer( ACTIVATE );
  SPI.transfer( 0x73 );
  csn(HIGH);
}

/******************************************************************/

void RF24::enableAckPayload(void)
{
  //
  // enable ack payload and dynamic payload features
  //

  write_register(FEATURE,read_register(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL) );

  // If it didn't work, the features are not enabled
  if ( ! read_register(FEATURE) )
  {
    // So enable them and try again
    toggle_features();
    write_register(FEATURE,read_register(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL) );
  }

  IF_SERIAL_DEBUG(printf("FEATURE=%i\n\r",read_register(FEATURE)));

  //
  // Enable dynamic payload on pipe 0
  //

  write_register(DYNPD,read_register(DYNPD) | _BV(DPL_P1) | _BV(DPL_P0));
}

/******************************************************************/

void RF24::writeAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
  const uint8_t* current = (const uint8_t*)buf;

  csn(LOW);
  configSPIBus() ;
  SPI.transfer( W_ACK_PAYLOAD | ( pipe & B111 ) );
  uint8_t data_len = min(len,32);
  while ( data_len-- )
    SPI.transfer(*current++);

  csn(HIGH);
}

/******************************************************************/

boolean RF24::isAckPayloadAvailable(void)
{
  boolean result = ack_payload_available;
  ack_payload_available = false;
  return result;
}

/******************************************************************/

boolean RF24::isPVariant(void) {
    return p_variant ;
}

/******************************************************************/

void RF24::setAutoAck(bool enable)
{
  if ( enable )
    write_register(EN_AA, B111111);
  else
    write_register(EN_AA, 0);
}

/******************************************************************/

void RF24::setAutoAck( uint8_t pipe, bool enable )
{
    uint8_t en_aa = read_register( EN_AA ) ;
    if( enable ) {
	en_aa |= _BV(pipe) ;
    } else {
	en_aa &= ~_BV(pipe) ;
    }
    write_register( EN_AA, en_aa ) ;
}

/******************************************************************/

boolean RF24::testCarrier(void)
{
  return ( read_register(CD) & 1 );
}

/******************************************************************/

boolean RF24::testRPD(void)
{
  return ( read_register(RPD) & 1 ) ;
}

/******************************************************************/

void RF24::setPALevel(rf24_pa_dbm_e level)
{
  uint8_t setup = read_register(RF_SETUP) ;
  setup &= ~(_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;

  switch( level )
  {
  case RF24_PA_MAX:
      setup |= (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;
      break ;

  case RF24_PA_HIGH:
      setup |= _BV(RF_PWR_HIGH) ;
      break ;

  case RF24_PA_LOW:
      setup |= _BV(RF_PWR_LOW) ;
      break ;

  case RF24_PA_MIN:
      break ;

  case RF24_PA_ERROR:
      // On error, go to maximum PA
      setup |= (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;
      break ;
  }

  write_register( RF_SETUP, setup ) ;
}

/******************************************************************/

rf24_pa_dbm_e RF24::getPALevel(void)
{
  rf24_pa_dbm_e result = RF24_PA_ERROR ;
  uint8_t power = read_register(RF_SETUP) & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)) ;

  switch( power )
  {
  case (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH)):
      result = RF24_PA_MAX ;
      break ;

  case _BV(RF_PWR_HIGH):
      result = RF24_PA_HIGH ;
      break ;

  case _BV(RF_PWR_LOW):
      result = RF24_PA_LOW ;
      break ;

  default:
      result = RF24_PA_MIN ;
      break ;
  }

  return result ;
}

/******************************************************************/

boolean RF24::setDataRate(rf24_datarate_e speed)
{
  uint8_t setup = read_register(RF_SETUP) ;

  // HIGH and LOW '00' is 1Mbs - our default
  wide_band = false ;
  setup &= ~(_BV(RF_DR_LOW) | _BV(RF_DR_HIGH)) ;
  if( speed == RF24_250KBPS )
  {
      // Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0
      // Making it '10'.
      wide_band = false ;
      setup |= _BV( RF_DR_LOW ) ;
  }
  else
  {
      // Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
      // Making it '01'
      if ( speed == RF24_2MBPS )
      {
  	  wide_band = true ;
  	  setup |= _BV(RF_DR_HIGH);
      } else {
	  // 1Mbs
	  wide_band = false ;
      }
  }
  write_register(RF_SETUP,setup);

  // Verify our result
  setup = read_register(RF_SETUP) ;
  if( setup == setup ) {
      return true ;
  }

  wide_band = false ;
  return false ;
}

/******************************************************************/

rf24_datarate_e RF24::getDataRate( void ) {
  rf24_datarate_e result ;
  uint8_t setup = read_register(RF_SETUP) ;

  // Order matters in our case below
  switch( setup & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH)) ) {
  case _BV(RF_DR_LOW):
      // '10' = 250KBPS
      result = RF24_250KBPS ;
      break ;

  case _BV(RF_DR_HIGH):
      // '01' = 2MBPS
      result = RF24_2MBPS ;
      break ;

  default:
      // '00' = 1MBPS
      result = RF24_1MBPS ;
      break ;
  }

  return result ;
}

/******************************************************************/

void RF24::setCRCLength(rf24_crclength_e length)
{
  uint8_t config = read_register(CONFIG) & ~_BV(CRCO) ;

  // Always make sure CRC hardware validation is actually on
  config |= _BV(EN_CRC) ;

  // Now config 8 or 16 bit CRCs - only 16bit need be turned on
  // 8b is the default.
  if( length == RF24_CRC_16 ) {
      config |= _BV( CRCO ) ;
  }

  write_register( CONFIG, config ) ;
}

/******************************************************************/

void RF24::disableCRC( void )
{
  uint8_t disable = read_register(CONFIG) & ~_BV(EN_CRC) ;
  write_register( CONFIG, disable ) ;
}
// vim:ai:cin:sts=2 sw=2 ft=cpp

