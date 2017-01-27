/*
 Copyright (c) 2016 Luis Claudio Gamboa Lopes <lcgamboa@yahoo.com>
 Copyright (C) 2011 J. Coliz <maniacbug@ymail.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#include "nRF24L01.h"
#include "RF24_config.h"
#include "RF24.h"

//for XC8 compatibility
#define ADDR_WIDTH 5

/****************************************************************************/

//global object
static RF24_ rf;

#if !defined(__XC8) && !defined(__SDCC)
void RF24_csn_d( uint8_t mode)
{

#if defined (RF24_TINY)
	if (ce_pin != csn_pin) {
		digitalWrite(csn_pin,mode);
	} 
	else {
		if (mode == HIGH) {
			PORTB |= (1<<PINB2);  	// SCK->CSN HIGH
			delayMicroseconds(100); // allow csn to settle.
		} 
		else {
			PORTB &= ~(1<<PINB2);	// SCK->CSN LOW
			delayMicroseconds(11);  // allow csn to settle
		}
	}
	// Return, CSN toggle complete
	return;
	
#elif defined(ARDUINO) && !defined (RF24_SPI_TRANSACTIONS)
	// Minimum ideal SPI bus speed is 2x data rate
	// If we assume 2Mbs data rate and 16Mhz clock, a
	// divider of 4 is the minimum we want.
	// CLK:BUS 8Mhz:2Mhz, 16Mhz:4Mhz, or 20Mhz:5Mhz
	
      #if !defined (SOFTSPI)	
		SPI_setBitOrder(MSBFIRST);
		SPI_setDataMode(SPI_MODE0);
		SPI_setClockDivider(SPI_CLOCK_DIV2);
      #endif
#elif defined (RF24_RPi)
      if(!mode)
	    SPI_chipSelect(rf.csn_pin);
#endif

#if !defined (RF24_LINUX)
    digitalWrite(rf.csn_pin,mode);
	delayMicroseconds(rf.csDelay);
#endif

}

/****************************************************************************/


void RF24_ce_d(uint8_t level)
{
  //Allow for 3-pin use on ATTiny
  if (rf.ce_pin != rf.csn_pin) digitalWrite(rf.ce_pin,level);
 
}

/****************************************************************************/

  void RF24_beginTransaction(void ) {
    #if defined (RF24_SPI_TRANSACTIONS)
    SPI_beginTransaction(*SPI_Settings(&(rf.spi),RF24_SPI_SPEED, MSBFIRST, SPI_MODE0));
	#endif
    RF24_csn_d(LOW);
  }

/****************************************************************************/

  void RF24_endTransaction(void) {
    RF24_csn_d(HIGH);
	#if defined (RF24_SPI_TRANSACTIONS)
    SPI_endTransaction();
	#endif
  }

 #endif //__XC8
/****************************************************************************/

uint8_t RF24_read_register_m_d(uint8_t reg, uint8_t* buf, uint8_t len)
{
  uint8_t status;

  #if defined (RF24_LINUX)
  RF24_beginTransaction(); //configures the spi settings for RPi, locks mutex and setting csn low
  uint8_t * prx = rf.spi_rxbuff;
  uint8_t * ptx = rf.spi_txbuff;
  uint8_t size = len + 1; // Add register value to transmit buffer

  *ptx++ = ( R_REGISTER | ( REGISTER_MASK & reg ) );

  while (len--){ *ptx++ = NOP_; } // Dummy operation, just for reading
  
  SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, size);
  
  status = *prx++; // status is 1st byte of receive buffer

  // decrement before to skip status byte
  while ( --size ){ *buf++ = *prx++; } 
  RF24_endTransaction(); //unlocks mutex and setting csn high

#else

  RF24_beginTransaction();
  status = SPI_transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- ){
    *buf++ = SPI_transfer(0xff);
  }
  RF24_endTransaction();

#endif

  return status;
}

/****************************************************************************/

uint8_t RF24_read_register_d(uint8_t reg)
{
  uint8_t result;
  
  #if defined (RF24_LINUX)
	
  RF24_beginTransaction();
  
  uint8_t * prx = rf.spi_rxbuff;
  uint8_t * ptx = rf.spi_txbuff;	
  *ptx++ = ( R_REGISTER | ( REGISTER_MASK & reg ) );
  *ptx++ = NOP_ ; // Dummy operation, just for reading
  
  SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, 2);
  result = *++prx;   // result is 2nd byte of receive buffer
  
  RF24_endTransaction();
  #else

  RF24_beginTransaction();
  SPI_transfer( R_REGISTER | ( REGISTER_MASK & reg ) );
  result = SPI_transfer(0xff);
  RF24_endTransaction();

  #endif

  return result;
}

/****************************************************************************/

uint8_t RF24_write_register_c_d(uint8_t reg, const uint8_t* buf, uint8_t len)
{
  uint8_t status;

  #if defined (RF24_LINUX) 
  RF24_beginTransaction();
  uint8_t * prx = rf.spi_rxbuff;
  uint8_t * ptx = rf.spi_txbuff;
  uint8_t size = len + 1; // Add register value to transmit buffer

  *ptx++ = ( W_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- )
    *ptx++ = *buf++;
  
  SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, size);
  status = *prx; // status is 1st byte of receive buffer
  RF24_endTransaction();
  #else

  RF24_beginTransaction();
  status = SPI_transfer( W_REGISTER | ( REGISTER_MASK & reg ) );
  while ( len-- )
    SPI_transfer(*buf++);
  RF24_endTransaction();

  #endif

  return status;
}

/****************************************************************************/

uint8_t RF24_write_register_d(uint8_t reg, uint8_t value)
{
  uint8_t status;

  IF_SERIAL_DEBUG(printf_P(PSTR("RF24_write_register_d(%02x,%02x)\r\n"),reg,value));

  #if defined (RF24_LINUX)
    RF24_beginTransaction();
	uint8_t * prx = rf.spi_rxbuff;
	uint8_t * ptx = rf.spi_txbuff;
	*ptx++ = ( W_REGISTER | ( REGISTER_MASK & reg ) );
	*ptx = value ;	
  	
	SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, 2);
	status = *prx++; // status is 1st byte of receive buffer
	RF24_endTransaction();
  #else

  RF24_beginTransaction();
  status = SPI_transfer( W_REGISTER | ( REGISTER_MASK & reg ) );
  SPI_transfer(value);
  RF24_endTransaction();

  #endif

  return status;
}

/****************************************************************************/

uint8_t RF24_write_payload(const void* buf, uint8_t data_len, const uint8_t writeType)
{
  uint8_t status;
  const uint8_t* current = (const uint8_t*)(buf);
  uint8_t blank_len;
  
   data_len = rf24_min(data_len, rf.payload_size);
   blank_len = rf.dynamic_payloads_enabled ? 0 : rf.payload_size - data_len;
  
  //printf("[Writing %u bytes %u blanks]",data_len,blank_len);
  IF_SERIAL_DEBUG( printf("[Writing %u bytes %u blanks]\n",data_len,blank_len); );
  
 #if defined (RF24_LINUX)
	RF24_beginTransaction();
	uint8_t * prx = rf.spi_rxbuff;
	uint8_t * ptx = rf.spi_txbuff;
    uint8_t size;
	size = data_len + blank_len + 1 ; // Add register value to transmit buffer

	*ptx++ =  writeType;
    while ( data_len-- )
      *ptx++ =  *current++;
    while ( blank_len-- )
	  *ptx++ =  0;
	
	SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, size);
	status = *prx; // status is 1st byte of receive buffer
	RF24_endTransaction();

  #else

  RF24_beginTransaction();
  status = SPI_transfer( writeType );
  while ( data_len-- ) {
    SPI_transfer(*current++);
  }
  while ( blank_len-- ) {
    SPI_transfer(0);
  }  
  RF24_endTransaction();

  #endif

  return status;
}

/****************************************************************************/

uint8_t RF24_read_payload(void* buf, uint8_t data_len)
{
  uint8_t status;
  uint8_t* current = (uint8_t*)(buf);
  uint8_t blank_len;
  
  if(data_len > rf.payload_size) data_len = rf.payload_size;
  blank_len = rf.dynamic_payloads_enabled ? 0 : rf.payload_size - data_len;
  
  //printf("[Reading %u bytes %u blanks]",data_len,blank_len);

  IF_SERIAL_DEBUG( printf("[Reading %u bytes %u blanks]\n",data_len,blank_len); );
  
  #if defined (RF24_LINUX)
	RF24_beginTransaction();
	uint8_t * prx = rf.spi_rxbuff;
	uint8_t * ptx = rf.spi_txbuff;
    uint8_t size;
    size = data_len + blank_len + 1; // Add register value to transmit buffer

	*ptx++ =  R_RX_PAYLOAD;
	while(--size) 
		*ptx++ = NOP_;
		
	size = data_len + blank_len + 1; // Size has been lost during while, re affect
	
	SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, size);
	
	status = *prx++; // 1st byte is status	
    
    if (data_len > 0) {
      while ( --data_len ) // Decrement before to skip 1st status byte
          *current++ = *prx++;
		
      *current = *prx;
    }
	RF24_endTransaction();
  #else

  RF24_beginTransaction();
  status = SPI_transfer( R_RX_PAYLOAD );
  while ( data_len-- ) {
    *current++ = SPI_transfer(0xFF);
  }
  while ( blank_len-- ) {
    SPI_transfer(0xff);
  }
  RF24_endTransaction();

  #endif

  return status;
}
/****************************************************************************/

uint8_t RF24_spiTrans(uint8_t cmd){

  uint8_t status;
  
  RF24_beginTransaction();
  status = SPI_transfer( cmd );
  RF24_endTransaction();
  
  return status;
}


/****************************************************************************/

uint8_t RF24_flush_rx(void)
{
  return RF24_spiTrans( FLUSH_RX );
}

/****************************************************************************/

uint8_t RF24_flush_tx(void )
{
  return RF24_spiTrans( FLUSH_TX );
}

/****************************************************************************/

uint8_t RF24_get_status(void )
{
  return RF24_spiTrans( NOP_);
}

/****************************************************************************/
#if !defined (MINIMAL)
void RF24_print_status( uint8_t status)
{
  printf_P(PSTR("STATUS\t\t = 0x%02x RX_DR=%x TX_DS=%x MAX_RT=%x RX_P_NO=%x TX_FULL=%x\r\n"),
           status,
           (status & _BV(RX_DR))?1:0,
           (status & _BV(TX_DS))?1:0,
           (status & _BV(MAX_RT))?1:0,
           ((status >> RX_P_NO) & 0b111),
           (status & _BV(TX_FULL))?1:0
          );
}

/****************************************************************************/

void RF24_print_observe_tx( uint8_t value)
{
  printf_P(PSTR("OBSERVE_TX=%02x: POLS_CNT=%x ARC_CNT=%x\r\n"),
           value,
           (value >> PLOS_CNT) & 0b1111,
           (value >> ARC_CNT) & 0b1111
          );
}

/****************************************************************************/

void RF24_print_byte_register_d( const char* name, uint8_t reg, uint8_t qty)
{
  //char extra_tab = strlen_P(name) < 8 ? '\t' : 0;
  //printf_P(PSTR(PRIPSTR"\t%c ="),name,extra_tab);
  #if defined (RF24_LINUX)
    printf("%s\t =", name);
  #else
    printf_P(PSTR(PRIPSTR"\t ="),name);
  #endif
  while (qty--)
    printf_P(PSTR(" 0x%02x"),RF24_read_register_d(reg++));
  printf_P(PSTR("\r\n"));
}

/****************************************************************************/

void RF24_print_address_register_d( const char* name, uint8_t reg, uint8_t qty)
{

  #if defined (RF24_LINUX)
    printf("%s\t =",name);
  #else
    printf_P(PSTR(PRIPSTR"\t ="),name);
  #endif
  while (qty--)
  {
    uint8_t* bufptr;
    
#if defined(__XC8) || defined (__SDCC)
    uint8_t buffer[ADDR_WIDTH];
    #else
    uint8_t buffer[rf.addr_width];
    #endif
    RF24_read_register_m_d(reg++,buffer,sizeof buffer);

    printf_P(PSTR(" 0x"));
    bufptr = buffer + sizeof buffer;
    while( --bufptr >= buffer )
      printf_P(PSTR("%02x"),*bufptr);
  }

  printf_P(PSTR("\r\n"));
}
#endif
/****************************************************************************/

#if defined(__XC8) || defined(__SDCC)   
void RF24_init(void)
{
#else
void RF24_init( uint8_t _cepin, uint8_t _cspin)
{
 
  rf.ce_pin=_cepin;
  rf.csn_pin=_cspin;
#endif  
  rf.p_variant=0;
  rf.payload_size=32;
  rf.dynamic_payloads_enabled=0;
  rf.addr_width=ADDR_WIDTH;
  rf.csDelay=5;
  rf.pipe0_reading_address[0]=0;
}

/****************************************************************************/

#if defined (RF24_LINUX) && !defined (MRAA)//RPi constructor
void RF24_init2( uint8_t _cepin, uint8_t _cspin, uint32_t _spi_speed)
{
  rf.ce_pin=_cepin;
  rf.csn_pin=_cspin;
  rf.spi_speed=_spi_speed;
  rf.p_variant=0;
  rf.payload_size=32;
  rf.dynamic_payloads_enabled=0;
  rf.addr_width=ADDR_WIDTH;
  rf.csDelay=5;
  rf.pipe0_reading_address[0]=0;
}
#endif

/****************************************************************************/

void RF24_setChannel( uint8_t channel)
{
  const uint8_t max_channel = 125;
  RF24_write_register_d(RF_CH,rf24_min(channel,max_channel));
}

uint8_t RF24_getChannel(void)
{
  
  return RF24_read_register_d(RF_CH);
}
/****************************************************************************/

void RF24_setPayloadSize(uint8_t size)
{
  rf.payload_size = rf24_min(size,32);
}

/****************************************************************************/

uint8_t RF24_getPayloadSize(void)
{
  return rf.payload_size;
}

/****************************************************************************/

#if !defined (MINIMAL)

static const char rf24_datarate_e_str_0[] PROGMEM = "1MBPS";
static const char rf24_datarate_e_str_1[] PROGMEM = "2MBPS";
static const char rf24_datarate_e_str_2[] PROGMEM = "250KBPS";
static const char * const rf24_datarate_e_str_P[] PROGMEM = {
  rf24_datarate_e_str_0,
  rf24_datarate_e_str_1,
  rf24_datarate_e_str_2,
};
static const char rf24_model_e_str_0[] PROGMEM = "nRF24L01";
static const char rf24_model_e_str_1[] PROGMEM = "nRF24L01+";
static const char * const rf24_model_e_str_P[] PROGMEM = {
  rf24_model_e_str_0,
  rf24_model_e_str_1,
};
static const char rf24_crclength_e_str_0[] PROGMEM = "Disabled";
static const char rf24_crclength_e_str_1[] PROGMEM = "8 bits";
static const char rf24_crclength_e_str_2[] PROGMEM = "16 bits" ;
static const char * const rf24_crclength_e_str_P[] PROGMEM = {
  rf24_crclength_e_str_0,
  rf24_crclength_e_str_1,
  rf24_crclength_e_str_2,
};
static const char rf24_pa_dbm_e_str_0[] PROGMEM = "PA_MIN";
static const char rf24_pa_dbm_e_str_1[] PROGMEM = "PA_LOW";
static const char rf24_pa_dbm_e_str_2[] PROGMEM = "PA_HIGH";
static const char rf24_pa_dbm_e_str_3[] PROGMEM = "PA_MAX";
static const char * const rf24_pa_dbm_e_str_P[] PROGMEM = {
  rf24_pa_dbm_e_str_0,
  rf24_pa_dbm_e_str_1,
  rf24_pa_dbm_e_str_2,
  rf24_pa_dbm_e_str_3,
};

#if defined (RF24_LINUX)
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
#endif

void RF24_printDetails(void)
{

#if defined (RF24_RPi)
  printf("================ SPI Configuration ================\n" );
  if (rf.csn_pin < BCM2835_SPI_CS_NONE ){
    printf("CSN Pin  \t = %s\n",rf24_csn_e_str_P[rf.csn_pin]);
  }else{
    printf("CSN Pin  \t = Custom GPIO%d%s\n", rf.csn_pin,
    rf.csn_pin==RPI_V2_GPIO_P1_26 ? " (CE1) Software Driven" : "" );
  }
  printf("CE Pin  \t = Custom GPIO%d\n", rf.ce_pin );
  printf("Clock Speed\t = " );
	switch (rf.spi_speed)
	{
		case BCM2835_SPI_SPEED_64MHZ : printf("64 Mhz");	break ;
		case BCM2835_SPI_SPEED_32MHZ : printf("32 Mhz");	break ;
		case BCM2835_SPI_SPEED_16MHZ : printf("16 Mhz");	break ;
		case BCM2835_SPI_SPEED_8MHZ  : printf("8 Mhz");	break ;
		case BCM2835_SPI_SPEED_4MHZ  : printf("4 Mhz");	break ;
		case BCM2835_SPI_SPEED_2MHZ  : printf("2 Mhz");	break ;
		case BCM2835_SPI_SPEED_1MHZ  : printf("1 Mhz");	break ;
		case BCM2835_SPI_SPEED_512KHZ: printf("512 KHz");	break ;
		case BCM2835_SPI_SPEED_256KHZ: printf("256 KHz");	break ;
		case BCM2835_SPI_SPEED_128KHZ: printf("128 KHz");	break ;
		case BCM2835_SPI_SPEED_64KHZ : printf("64 KHz");	break ;
		case BCM2835_SPI_SPEED_32KHZ : printf("32 KHz");	break ;
		case BCM2835_SPI_SPEED_16KHZ : printf("16 KHz");	break ;
		case BCM2835_SPI_SPEED_8KHZ  : printf("8 KHz");	break ;
		default : printf("8 Mhz");	break ;
	}
	printf("\n================ NRF Configuration ================\n");
 
#endif //Linux

  RF24_print_status(RF24_get_status());

  RF24_print_address_register_d(PSTR("RX_ADDR_P0-1"),RX_ADDR_P0,2);
  RF24_print_byte_register_d(PSTR("RX_ADDR_P2-5"),RX_ADDR_P2,4);
  RF24_print_address_register_d(PSTR("TX_ADDR\t"),TX_ADDR,1);

  RF24_print_byte_register_d(PSTR("RX_PW_P0-6"),RX_PW_P0,6);
  RF24_print_byte_register_d(PSTR("EN_AA\t"),EN_AA,1);
  RF24_print_byte_register_d(PSTR("EN_RXADDR"),EN_RXADDR,1);
  RF24_print_byte_register_d(PSTR("RF_CH\t"),RF_CH,1);
  RF24_print_byte_register_d(PSTR("RF_SETUP"),RF_SETUP,1);
  RF24_print_byte_register_d(PSTR("CONFIG\t"),NRF_CONFIG,1);
  RF24_print_byte_register_d(PSTR("DYNPD/FEATURE"),DYNPD,2);

  printf_P(PSTR("Data Rate\t = " PRIPSTR "\r\n"),pgm_read_word(&rf24_datarate_e_str_P[RF24_getDataRate()]));
  printf_P(PSTR("Model\t\t = " PRIPSTR "\r\n"),pgm_read_word(&rf24_model_e_str_P[RF24_isPVariant()]));
  printf_P(PSTR("CRC Length\t = " PRIPSTR "\r\n"),pgm_read_word(&rf24_crclength_e_str_P[RF24_getCRCLength()]));
  printf_P(PSTR("PA Power\t = " PRIPSTR "\r\n"),  pgm_read_word(&rf24_pa_dbm_e_str_P[RF24_getPALevel()]));

}

#endif
/****************************************************************************/

uint8_t RF24_begin(void )
{

  uint8_t setup=0;

  #if defined (RF24_LINUX)

	#if defined (MRAA)
	  GPIO();	
	  gpio.begin(ce_pin,csn_pin);	
	#endif
	
    #ifdef RF24_RPi
	  switch(rf.csn_pin){     //Ensure valid hardware CS pin
	    case 0: break;
	    case 1: break;
	    // Allow BCM2835 enums for RPi
	    case 8: rf.csn_pin = 0; break;
	    case 7: rf.csn_pin = 1; break;
	    default: rf.csn_pin = 0; break;
	  }
    #endif
	
    SPI_begin(rf.csn_pin);

	pinMode(rf.ce_pin,OUTPUT);
	RF24_ce_d(LOW);    

	delay(100);
  
  #elif defined(LITTLEWIRE)
    pinMode(csn_pin,OUTPUT);
    SPI_begin();
    RF24_csn_d(HIGH);
  #elif defined(XMEGA_D3)
	if (ce_pin != csn_pin) pinMode(ce_pin,OUTPUT);
	SPI_begin(csn_pin);
	RF24_ce_d(LOW);
	RF24_csn_d(HIGH);
	delay(200);
  #else
    // Initialize pins
#if  defined(__XC8) || defined(__SDCC)
    ce_pin_t=OUTPUT;
    csn_pin_t=OUTPUT;
#else    
    if (rf.ce_pin != rf.csn_pin) pinMode(rf.ce_pin,OUTPUT);  
  
    #if ! defined(LITTLEWIRE)
      if (rf.ce_pin != rf.csn_pin)
    #endif
        pinMode(rf.csn_pin,OUTPUT);
#endif    
    SPI_begin();
    RF24_ce_d(LOW);
  	RF24_csn_d(HIGH);
  	#if defined (__ARDUINO_X86__)
		delay(100);
  	#endif
  #endif //Linux

  // Must allow the radio time to settle else configuration bits will not necessarily stick.
  // This is actually only required following power up but some settling time also appears to
  // be required after resets too. For full coverage, we'll always assume the worst.
  // Enabling 16b CRC is by far the most obvious case if the wrong timing is used - or skipped.
  // Technically we require 4.5ms + 14us as a worst case. We'll just call it 5ms for good measure.
  // WARNING: Delay is based on P-variant whereby non-P *may* require different timing.
  delay( 5 ) ;

  // Reset NRF_CONFIG and enable 16-bit CRC.
  RF24_write_register_d( NRF_CONFIG, 0b00001100 ) ;

  // Set 1500uS (minimum for 32B payload in ESB@250KBPS) timeouts, to make testing a little easier
  // WARNING: If this is ever lowered, either 250KBS mode with AA is broken or maximum packet
  // sizes must never be used. See documentation for a more complete explanation.
  RF24_setRetries(5,15);

  // Reset value is MAX
  //setPALevel( RF24_PA_MAX ) ;

  // check for connected module and if this is a p nRF24l01 variant
  //
  if( RF24_setDataRate( RF24_250KBPS ) )
  {
    rf.p_variant = 1 ;
  }
  setup = RF24_read_register_d(RF_SETUP);
  /*if( setup == 0b00001110 )     // register default for nRF24L01P
  {
    p_variant = true ;
  }*/
  
  // Then set the data rate to the slowest (and most reliable) speed supported by all
  // hardware.
  RF24_setDataRate( RF24_1MBPS ) ;

  // Initialize CRC and request 2-byte (16bit) CRC
  //setCRCLength( RF24_CRC_16 ) ;

  // Disable dynamic payloads, to match dynamic_payloads_enabled setting - Reset value is 0
  RF24_toggle_features_d();
  RF24_write_register_d(FEATURE,0 );
  RF24_write_register_d(DYNPD,0);

  // Reset current status
  // Notice reset and flush is the last thing we do
  RF24_write_register_d(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Set up default configuration.  Callers can always change it later.
  // This channel should be universally safe and not bleed over into adjacent
  // spectrum.
  RF24_setChannel(76);

  // Flush buffers
  RF24_flush_rx();
  RF24_flush_tx();

  RF24_powerUp(); //Power up by default when begin() is called

  // Enable PTX, do not write CE high so radio will remain in standby I mode ( 130us max to transition to RX or TX instead of 1500us from powerUp )
  // PTX should use only 22uA of power
  RF24_write_register_d(NRF_CONFIG, ( RF24_read_register_d(NRF_CONFIG) ) & ~_BV(PRIM_RX) );

  // if setup is 0 or ff then there was no response from module
  return ( setup != 0 && setup != 0xff );
}

/****************************************************************************/

void RF24_startListening(void)
{
 #if !defined (RF24_TINY) && ! defined(LITTLEWIRE)
  RF24_powerUp();
 #endif
  RF24_write_register_d(NRF_CONFIG, RF24_read_register_d(NRF_CONFIG) | _BV(PRIM_RX));
  RF24_write_register_d(NRF_STATUS, _BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );
  RF24_ce_d(HIGH);
  // Restore the pipe0 adddress, if exists
  if (rf.pipe0_reading_address[0] > 0){
    RF24_write_register_c_d(RX_ADDR_P0, rf.pipe0_reading_address, rf.addr_width);	
  }else{
	RF24_closeReadingPipe(0);
  }

  // Flush buffers
  //RF24_flush_rx();;
  if(RF24_read_register_d(FEATURE) & _BV(EN_ACK_PAY)){
	RF24_flush_tx();
  }

  // Go!
  //delayMicroseconds(100);
}

/****************************************************************************/
static const uint8_t child_pipe_enable[] PROGMEM =
{
  ERX_P0, ERX_P1, ERX_P2, ERX_P3, ERX_P4, ERX_P5
};

void RF24_stopListening(void)
{  
  RF24_ce_d(LOW);

  delayMicroseconds(rf.txDelay);
  
  if(RF24_read_register_d(FEATURE) & _BV(EN_ACK_PAY)){
    delayMicroseconds(rf.txDelay); //200
	RF24_flush_tx();
  }
  //RF24_flush_rx();;
  RF24_write_register_d(NRF_CONFIG, ( RF24_read_register_d(NRF_CONFIG) ) & ~_BV(PRIM_RX) );
 
  #if defined (RF24_TINY) || defined (LITTLEWIRE)
  // for 3 pins solution TX mode is only left with additonal powerDown/powerUp cycle
  if (rf.ce_pin == rf.csn_pin) {
    RF24_powerDown();
	RF24_powerUp();
  }
  #endif
  RF24_write_register_d(EN_RXADDR,RF24_read_register_d(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[0]))); // Enable RX on pipe0
  
  //delayMicroseconds(100);

}

/****************************************************************************/

void RF24_powerDown(void)
{
  RF24_ce_d(LOW); // Guarantee CE is low on powerDown
  RF24_write_register_d(NRF_CONFIG,RF24_read_register_d(NRF_CONFIG) & ~_BV(PWR_UP));
}

/****************************************************************************/

//Power up now. Radio will not power down unless instructed by MCU for config changes etc.
void RF24_powerUp(void)
{
   uint8_t cfg = RF24_read_register_d(NRF_CONFIG);

   // if not powered up then power up and wait for the radio to initialize
   if (!(cfg & _BV(PWR_UP))){
      RF24_write_register_d(NRF_CONFIG, cfg | _BV(PWR_UP));

      // For nRF24L01+ to go from power down mode to TX or RX mode it must first pass through stand-by mode.
	  // There must be a delay of Tpd2stby (see Table 16.) after the nRF24L01+ leaves power down mode before
	  // the CEis set high. - Tpd2stby can be up to 5ms per the 1.0 datasheet
      delay(5);
   }
}

/******************************************************************/
#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
void RF24_errNotify(void){
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
uint8_t RF24_write_m( const void* buf, uint8_t len, const uint8_t multicast )
{
    uint8_t status;
    
	//Start Writing
	RF24_startFastWrite(buf,len,multicast,1);

	//Wait until complete or failed
	#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
		uint32_t timer = millis();
	#endif 
	
	while( ! ( RF24_get_status()  & ( _BV(TX_DS) | _BV(MAX_RT) ))) { 
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if(millis() - timer > 95){			
				RF24_errNotify();
				#if defined (FAILURE_HANDLING)
				  return 0;		
				#else
				  delay(100);
				#endif
			}
		#endif
	}
    
	RF24_ce_d(LOW);

	status = RF24_write_register_d(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  //Max retries exceeded
  if( status & _BV(MAX_RT)){
  	RF24_flush_tx(); //Only going to be 1 packet int the FIFO at a time using this method, so just flush
  	return 0;
  }
	//TX OK 1 or 0
  return 1;
}

uint8_t RF24_write(const void* buf, uint8_t len ){
	return RF24_write_m(buf,len,0);
}
/****************************************************************************/

//For general use, the interrupt flags are not important to clear
uint8_t RF24_writeBlocking(const void* buf, uint8_t len, uint32_t timeout )
{
	//Block until the FIFO is NOT full.
	//Keep track of the MAX retries and set auto-retry if seeing failures
	//This way the FIFO will fill up and allow blocking until packets go through
	//The radio will auto-clear everything in the FIFO as long as CE remains high

	uint32_t timer = millis();							  //Get the time that the payload transmission started

	while( ( RF24_get_status()  & ( _BV(TX_FULL) ))) {		  //Blocking only if FIFO is full. This will loop and block until TX is successful or timeout

		if( RF24_get_status() & _BV(MAX_RT)){					  //If MAX Retries have been reached
			RF24_reUseTX();										  //Set re-transmit and clear the MAX_RT interrupt flag
			if(millis() - timer > timeout){ return 0; }		  //If this payload has exceeded the user-defined timeout, exit and return 0
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if(millis() - timer > (timeout+95) ){			
				RF24_errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;			
                #endif				
			}
		#endif

  	}

  	//Start Writing
	RF24_startFastWrite(buf,len,0,1);								  //Write the payload if a buffer is clear

	return 1;												  //Return 1 to indicate successful transmission
}

/****************************************************************************/

void RF24_reUseTX(void){
		RF24_write_register_d(NRF_STATUS,_BV(MAX_RT) );			  //Clear max retry flag
		RF24_spiTrans(REUSE_TX_PL );
		RF24_ce_d(LOW);										  //Re-Transfer packet
		RF24_ce_d(HIGH);
}

/****************************************************************************/

uint8_t RF24_writeFast_m( const void* buf, uint8_t len, const uint8_t multicast )
{
	//Block until the FIFO is NOT full.
	//Keep track of the MAX retries and set auto-retry if seeing failures
	//Return 0 so the user can control the retrys and set a timer or failure counter if required
	//The radio will auto-clear everything in the FIFO as long as CE remains high

	#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
		uint32_t timer = millis();
	#endif
	
	while( ( RF24_get_status()  & ( _BV(TX_FULL) ))) {			  //Blocking only if FIFO is full. This will loop and block until TX is successful or fail

		if( RF24_get_status() & _BV(MAX_RT)){
			//reUseTX();										  //Set re-transmit
			RF24_write_register_d(NRF_STATUS,_BV(MAX_RT) );			  //Clear max retry flag
			return 0;										  //Return 0. The previous payload has been retransmitted
															  //From the user perspective, if you get a 0, just keep trying to send the same payload
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if(millis() - timer > 95 ){			
				RF24_errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;							
				#endif
			}
		#endif
  	}
		     //Start Writing
	RF24_startFastWrite(buf,len,multicast,1);

	return 1;
}

uint8_t RF24_writeFast(const void* buf, uint8_t len ){
	return RF24_writeFast_m(buf,len,0);
}

/****************************************************************************/

//Per the documentation, we want to set PTX Mode when not listening. Then all we do is write data and set CE high
//In this mode, if we can keep the FIFO buffers loaded, packets will transmit immediately (no 130us delay)
//Otherwise we enter Standby-II mode, which is still faster than standby mode
//Also, we remove the need to keep writing the config register over and over and delaying for 150 us each time if sending a stream of data

void RF24_startFastWrite(const void* buf, uint8_t len, const uint8_t multicast, uint8_t startTx){ //TMRh20

	//write_payload( buf,len);
	RF24_write_payload( buf, len,multicast ? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD ) ;
	if(startTx){
		RF24_ce_d(HIGH);
	}

}

/****************************************************************************/

//Added the original startWrite back in so users can still use interrupts, ack payloads, etc
//Allows the library to pass all tests
void RF24_startWrite(const void* buf, uint8_t len, const uint8_t multicast ){

  // Send the payload

  //write_payload( buf, len );
  RF24_write_payload( buf, len,multicast? W_TX_PAYLOAD_NO_ACK : W_TX_PAYLOAD ) ;
  RF24_ce_d(HIGH);
  #if defined(CORE_TEENSY) || !defined(ARDUINO) || defined (RF24_SPIDEV) || defined (RF24_DUE)
	delayMicroseconds(10);
  #endif
  RF24_ce_d(LOW);


}

/****************************************************************************/

uint8_t RF24_rxFifoFull(void){
	return RF24_read_register_d(FIFO_STATUS) & _BV(RX_FULL);
}
/****************************************************************************/

uint8_t RF24_txStandBy(void){

    #if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
		uint32_t timeout = millis();
	#endif
	while( ! (RF24_read_register_d(FIFO_STATUS) & _BV(TX_EMPTY)) ){
		if( RF24_get_status() & _BV(MAX_RT)){
			RF24_write_register_d(NRF_STATUS,_BV(MAX_RT) );
			RF24_ce_d(LOW);
			RF24_flush_tx();;    //Non blocking, flush the data
			return 0;
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if( millis() - timeout > 95){
				RF24_errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;	
				#endif
			}
		#endif
	}

	RF24_ce_d(LOW);			   //Set STANDBY-I mode
	return 1;
}

/****************************************************************************/

uint8_t RF24_txStandBy_t(uint32_t timeout, uint8_t startTx){
    uint32_t start;
    
    if(startTx){
	  RF24_stopListening();
	  RF24_ce_d(HIGH);
	}
	
    start = millis();

	while( ! (RF24_read_register_d(FIFO_STATUS) & _BV(TX_EMPTY)) ){
		if( RF24_get_status() & _BV(MAX_RT)){
			RF24_write_register_d(NRF_STATUS,_BV(MAX_RT) );
				RF24_ce_d(LOW);										  //Set re-transmit
				RF24_ce_d(HIGH);
				if(millis() - start >= timeout){
					RF24_ce_d(LOW); RF24_flush_tx();; return 0;
				}
		}
		#if defined (FAILURE_HANDLING) || defined (RF24_LINUX)
			if( millis() - start > (timeout+95)){
				RF24_errNotify();
				#if defined (FAILURE_HANDLING)
				return 0;	
				#endif
			}
		#endif
	}

	
	RF24_ce_d(LOW);				   //Set STANDBY-I mode
	return 1;

}

/****************************************************************************/

void RF24_maskIRQ(uint8_t tx, uint8_t fail, uint8_t rx){

	uint8_t config = RF24_read_register_d(NRF_CONFIG);
	/* clear the interrupt flags */
	config &= ~(1 << MASK_MAX_RT | 1 << MASK_TX_DS | 1 << MASK_RX_DR);
	/* set the specified interrupt flags */
	config |= fail << MASK_MAX_RT | tx << MASK_TX_DS | rx << MASK_RX_DR;
	RF24_write_register_d(NRF_CONFIG, config);
}

/****************************************************************************/

uint8_t RF24_getDynamicPayloadSize(void)
{
  uint8_t result = 0;

  #if defined (RF24_LINUX)  
  rf.spi_txbuff[0] = R_RX_PL_WID;
  rf.spi_rxbuff[1] = 0xff;
  RF24_beginTransaction();
  SPI_transfernb( (char *) rf.spi_txbuff, (char *) rf.spi_rxbuff, 2);
  result = rf.spi_rxbuff[1];  
  RF24_endTransaction();
  #else
  RF24_beginTransaction();
  SPI_transfer( R_RX_PL_WID );
  result = SPI_transfer(0xff);
  RF24_endTransaction();
  #endif

  if(result > 32) { RF24_flush_rx();; delay(2); return 0; }
  return result;
}

/****************************************************************************/

uint8_t RF24_available(void)
{
  return RF24_available_p(NULL);
}

/****************************************************************************/

uint8_t RF24_available_p(uint8_t* pipe_num)
{
  if (!( RF24_read_register_d(FIFO_STATUS) & _BV(RX_EMPTY) )){

    // If the caller wants the pipe number, include that
    if ( pipe_num ){
	  uint8_t status = RF24_get_status();
      *pipe_num = ( status >> RX_P_NO ) & 0b111;
  	}
  	return 1;
  }


  return 0;


}

/****************************************************************************/

void RF24_read(void* buf, uint8_t len ){

  // Fetch the payload
  RF24_read_payload( buf, len );

  //Clear the two possible interrupt flags with one command
  RF24_write_register_d(NRF_STATUS,_BV(RX_DR) | _BV(MAX_RT) | _BV(TX_DS) );

}

/****************************************************************************/

void RF24_whatHappened( uint8_t * tx_ok,uint8_t * tx_fail,uint8_t * rx_ready)
{
  // Read the status & reset the status in one easy call
  // Or is that such a good idea?
  uint8_t status = RF24_write_register_d(NRF_STATUS,_BV(RX_DR) | _BV(TX_DS) | _BV(MAX_RT) );

  // Report to the user what happened
  *tx_ok = status & _BV(TX_DS);
  *tx_fail = status & _BV(MAX_RT);
  *rx_ready = status & _BV(RX_DR);
}

/****************************************************************************/

void RF24_openWritingPipe_d(const raddr_t*  value_)
{
  uint8_t i;
  raddr_t value[5];
  for(i=0;i<5;i++)
  {
    value[i]=value_[4-i];
  }
  
  RF24_write_register_c_d(RX_ADDR_P0, ((uint8_t*)(value)), rf.addr_width);
  RF24_write_register_c_d(TX_ADDR, ((uint8_t*)(value)), rf.addr_width);
  
  
  //const uint8_t max_payload_size = 32;
  //RF24_write_register_d(RX_PW_P0,rf24_min(payload_size,max_payload_size));
  RF24_write_register_d(RX_PW_P0,rf.payload_size);
}

/****************************************************************************/
void RF24_openWritingPipe(const uint8_t *address)
{
  // Note that AVR 8-bit uC's store this LSB first, and the NRF24L01(+)
  // expects it LSB first too, so we're good.

  RF24_write_register_c_d(RX_ADDR_P0,address, rf.addr_width);
  RF24_write_register_c_d(TX_ADDR, address, rf.addr_width);

  //const uint8_t max_payload_size = 32;
  //RF24_write_register_d(RX_PW_P0,rf24_min(payload_size,max_payload_size));
  RF24_write_register_d(RX_PW_P0,rf.payload_size);
}

/****************************************************************************/
static const uint8_t child_pipe[] PROGMEM =
{
  RX_ADDR_P0, RX_ADDR_P1, RX_ADDR_P2, RX_ADDR_P3, RX_ADDR_P4, RX_ADDR_P5
};
static const uint8_t child_payload_size[] PROGMEM =
{
  RX_PW_P0, RX_PW_P1, RX_PW_P2, RX_PW_P3, RX_PW_P4, RX_PW_P5
};


void RF24_openReadingPipe_d(uint8_t child, const raddr_t* address_)
{
  uint8_t i;
  raddr_t address[5];
  for(i=0;i<5;i++)
  {
    address[i]=address_[4-i];
  }
  // If this is pipe 0, cache the address.  This is needed because
  // openWritingPipe() will overwrite the pipe 0 address, so
  // startListening() will have to restore it.
  if (child == 0){
    memcpy(rf.pipe0_reading_address,address,rf.addr_width);
  }

  if (child <= 6)
  {
    // For pipes 2-5, only write the LSB
    if ( child < 2 )
      RF24_write_register_c_d(pgm_read_byte(&child_pipe[child]), (const uint8_t*)(address), rf.addr_width);
    else
      RF24_write_register_c_d(pgm_read_byte(&child_pipe[child]), (const uint8_t*)(address), 1);

    RF24_write_register_d(pgm_read_byte(&child_payload_size[child]),rf.payload_size);

    // Note it would be more efficient to set all of the bits for all open
    // pipes at once.  However, I thought it would make the calling code
    // more simple to do it this way.
    RF24_write_register_d(EN_RXADDR,RF24_read_register_d(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[child])));
  }
}

/****************************************************************************/
void RF24_setAddressWidth(uint8_t a_width){

	if(a_width -= 2){
		RF24_write_register_d(SETUP_AW,a_width%4);
		rf.addr_width = (a_width%4) + 2;
	}

}

/****************************************************************************/

void RF24_openReadingPipe(uint8_t child, const uint8_t *address)
{
  // If this is pipe 0, cache the address.  This is needed because
  // openWritingPipe() will overwrite the pipe 0 address, so
  // startListening() will have to restore it.
  if (child == 0){
    memcpy(rf.pipe0_reading_address,address,rf.addr_width);
  }
  if (child <= 6)
  {
    // For pipes 2-5, only write the LSB
    if ( child < 2 ){
      RF24_write_register_c_d(pgm_read_byte(&child_pipe[child]), address, rf.addr_width);
    }else{
      RF24_write_register_c_d(pgm_read_byte(&child_pipe[child]), address, 1);
	}
    RF24_write_register_d(pgm_read_byte(&child_payload_size[child]),rf.payload_size);

    // Note it would be more efficient to set all of the bits for all open
    // pipes at once.  However, I thought it would make the calling code
    // more simple to do it this way.
    RF24_write_register_d(EN_RXADDR,RF24_read_register_d(EN_RXADDR) | _BV(pgm_read_byte(&child_pipe_enable[child])));

  }
}

/****************************************************************************/

void RF24_closeReadingPipe(uint8_t pipe )
{
  RF24_write_register_d(EN_RXADDR,RF24_read_register_d(EN_RXADDR) & ~_BV(pgm_read_byte(&child_pipe_enable[pipe])));
}

/****************************************************************************/

void RF24_toggle_features_d(void)
{
    RF24_beginTransaction();
	SPI_transfer( ACTIVATE );
    SPI_transfer( 0x73 );
	RF24_endTransaction();
}

/****************************************************************************/

void RF24_enableDynamicPayloads(void)
{
  // Enable dynamic payload throughout the system

    //toggle_features();
    RF24_write_register_d(FEATURE,RF24_read_register_d(FEATURE) | _BV(EN_DPL) );


  IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n",RF24_read_register_d(FEATURE)));

  // Enable dynamic payload on all pipes
  //
  // Not sure the use case of only having dynamic payload on certain
  // pipes, so the library does not support it.
  RF24_write_register_d(DYNPD,RF24_read_register_d(DYNPD) | _BV(DPL_P5) | _BV(DPL_P4) | _BV(DPL_P3) | _BV(DPL_P2) | _BV(DPL_P1) | _BV(DPL_P0));

  rf.dynamic_payloads_enabled = 1;
}

/****************************************************************************/

void RF24_enableAckPayload(void)
{
  //
  // enable ack payload and dynamic payload features
  //

    //toggle_features();
    RF24_write_register_d(FEATURE,RF24_read_register_d(FEATURE) | _BV(EN_ACK_PAY) | _BV(EN_DPL) );

  IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n",RF24_read_register_d(FEATURE)));

  //
  // Enable dynamic payload on pipes 0 & 1
  //

  RF24_write_register_d(DYNPD,RF24_read_register_d(DYNPD) | _BV(DPL_P1) | _BV(DPL_P0));
  rf.dynamic_payloads_enabled = 1;
}

/****************************************************************************/

void RF24_enableDynamicAck(void){
  //
  // enable dynamic ack features
  //
    //toggle_features();
    RF24_write_register_d(FEATURE,RF24_read_register_d(FEATURE) | _BV(EN_DYN_ACK) );

  IF_SERIAL_DEBUG(printf("FEATURE=%i\r\n",RF24_read_register_d(FEATURE)));


}

/****************************************************************************/

void RF24_writeAckPayload(uint8_t pipe, const void* buf, uint8_t len)
{
  const uint8_t* current = (const uint8_t*)(buf);

  uint8_t data_len = rf24_min(len,32);

  #if defined (RF24_LINUX)
    RF24_beginTransaction();
    uint8_t * ptx = rf.spi_txbuff;
    uint8_t size = data_len + 1 ; // Add register value to transmit buffer
	*ptx++ =  W_ACK_PAYLOAD | ( pipe & 0b111 );
    while ( data_len-- ){
      *ptx++ =  *current++;
    }
	
    SPI_transfern( (char *) rf.spi_txbuff, size);
	RF24_endTransaction();
  #else
  RF24_beginTransaction();
  SPI_transfer(W_ACK_PAYLOAD | ( pipe & 0b111 ) );

  while ( data_len-- )
    SPI_transfer(*current++);
  RF24_endTransaction();
  	
  #endif  

}

/****************************************************************************/

uint8_t RF24_isAckPayloadAvailable(void)
{
  return ! (RF24_read_register_d(FIFO_STATUS) & _BV(RX_EMPTY));
}

/****************************************************************************/

uint8_t RF24_isPVariant(void)
{
  return rf.p_variant ;
}

/****************************************************************************/

void RF24_setAutoAck( uint8_t enable)
{
  if ( enable )
    RF24_write_register_d(EN_AA, 0b111111);
  else
    RF24_write_register_d(EN_AA, 0);
}

/****************************************************************************/

void RF24_setAutoAck_p( uint8_t pipe, uint8_t enable )
{
  if ( pipe <= 6 )
  {
    uint8_t en_aa = RF24_read_register_d( EN_AA ) ;
    if( enable )
    {
      en_aa |= _BV(pipe) ;
    }
    else
    {
      en_aa &= ~_BV(pipe) ;
    }
    RF24_write_register_d( EN_AA, en_aa ) ;
  }
}

/****************************************************************************/

uint8_t RF24_testCarrier(void)
{
  return ( RF24_read_register_d(CD) & 1 );
}

/****************************************************************************/

uint8_t RF24_testRPD(void)
{
  return ( RF24_read_register_d(RPD) & 1 ) ;
}

/****************************************************************************/
  
uint8_t RF24_isValid(void) 
{ 
#if defined (__XC8) || defined(__SDCC)
  return 1;
#else    
  return rf.ce_pin != 0xff && rf.csn_pin != 0xff; 
#endif
}

/****************************************************************************/

void RF24_setPALevel(uint8_t level)
{

  uint8_t setup = RF24_read_register_d(RF_SETUP) & 0b11111000;

  if(level > 3){  						// If invalid level, go to max PA
	  level = (RF24_PA_MAX << 1) + 1;		// +1 to support the SI24R1 chip extra bit
  }else{
	  level = (level << 1) + 1;	 		// Else set level as requested
  }


  RF24_write_register_d( RF_SETUP, setup |= level ) ;	// Write it to the chip
}

/****************************************************************************/

uint8_t RF24_getPALevel(void)
{

  return (RF24_read_register_d(RF_SETUP) & (_BV(RF_PWR_LOW) | _BV(RF_PWR_HIGH))) >> 1 ;
}

/****************************************************************************/

uint8_t RF24_setDataRate(rf24_datarate_e speed)
{
  uint8_t result = 0;
  uint8_t setup = RF24_read_register_d(RF_SETUP) ;

  // HIGH and LOW '00' is 1Mbs - our default
  setup &= ~(_BV(RF_DR_LOW) | _BV(RF_DR_HIGH)) ;
  
  #if defined(__arm__) || defined (RF24_LINUX) || defined (__ARDUINO_X86__)
    rf.txDelay=250;
  #else //16Mhz Arduino
    rf.txDelay=85;
  #endif
  if( speed == RF24_250KBPS )
  {
    // Must set the RF_DR_LOW to 1; RF_DR_HIGH (used to be RF_DR) is already 0
    // Making it '10'.
    setup |= _BV( RF_DR_LOW ) ;
  #if defined(__arm__) || defined (RF24_LINUX) || defined (__ARDUINO_X86__)
    rf.txDelay=450;
  #else //16Mhz Arduino
	rf.txDelay=155;
  #endif
  }
  else
  {
    // Set 2Mbs, RF_DR (RF_DR_HIGH) is set 1
    // Making it '01'
    if ( speed == RF24_2MBPS )
    {
      setup |= _BV(RF_DR_HIGH);
      #if defined(__arm__) || defined (RF24_LINUX) || defined (__ARDUINO_X86__)
      rf.txDelay=190;
      #else //16Mhz Arduino	  
	  rf.txDelay=65;
	  #endif
    }
  }
  RF24_write_register_d(RF_SETUP,setup);

  // Verify our result
  if ( RF24_read_register_d(RF_SETUP) == setup )
  {
    result = 1;
  }
  return result;
}

/****************************************************************************/

rf24_datarate_e RF24_getDataRate(void )
{
  rf24_datarate_e result ;
  uint8_t dr = RF24_read_register_d(RF_SETUP) & (_BV(RF_DR_LOW) | _BV(RF_DR_HIGH));

  // switch uses RAM (evil!)
  // Order matters in our case below
  if ( dr == _BV(RF_DR_LOW) )
  {
    // '10' = 250KBPS
    result = RF24_250KBPS ;
  }
  else if ( dr == _BV(RF_DR_HIGH) )
  {
    // '01' = 2MBPS
    result = RF24_2MBPS ;
  }
  else
  {
    // '00' = 1MBPS
    result = RF24_1MBPS ;
  }
  return result ;
}

/****************************************************************************/

void RF24_setCRCLength(rf24_crclength_e length)
{
  uint8_t config = RF24_read_register_d(NRF_CONFIG) & ~( _BV(CRCO) | _BV(EN_CRC)) ;

  // switch uses RAM (evil!)
  if ( length == RF24_CRC_DISABLED )
  {
    // Do nothing, we turned it off above.
  }
  else if ( length == RF24_CRC_8 )
  {
    config |= _BV(EN_CRC);
  }
  else
  {
    config |= _BV(EN_CRC);
    config |= _BV( CRCO );
  }
  RF24_write_register_d( NRF_CONFIG, config ) ;
}

/****************************************************************************/

rf24_crclength_e RF24_getCRCLength(void)
{
  rf24_crclength_e result = RF24_CRC_DISABLED;
  
  uint8_t config = RF24_read_register_d(NRF_CONFIG) & ( _BV(CRCO) | _BV(EN_CRC)) ;
  uint8_t AA = RF24_read_register_d(EN_AA);
  
  if ( config & _BV(EN_CRC ) || AA)
  {
    if ( config & _BV(CRCO) )
      result = RF24_CRC_16;
    else
      result = RF24_CRC_8;
  }

  return result;
}

/****************************************************************************/

void RF24_disableCRC(void)
{
  uint8_t disable = RF24_read_register_d(NRF_CONFIG) & ~_BV(EN_CRC) ;
  RF24_write_register_d( NRF_CONFIG, disable ) ;
}

/****************************************************************************/
void RF24_setRetries( uint8_t delay, uint8_t count)
{
 RF24_write_register_d(SETUP_RETR,(delay&0xf)<<ARD | (count&0xf)<<ARC);
}


//ATTiny support code pulled in from https://github.com/jscrane/RF24

#if defined(__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
// see http://gammon.com.au/spi
#	define DI   0  // D0, pin 5  Data In
#	define DO   1  // D1, pin 6  Data Out (this is *not* MOSI)
#	define USCK 2  // D2, pin 7  Universal Serial Interface clock
#	define SS   3  // D3, pin 2  Slave Select
#elif defined(__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
// these depend on the core used (check pins_arduino.h)
// this is for jeelabs' one (based on google-code core)
#	define DI   4   // PA6
#	define DO   5   // PA5
#	define USCK 6   // PA4
#	define SS   3   // PA7
#elif defined(__AVR_ATtiny2313__) || defined(__AVR_ATtiny4313__)
// these depend on the core used (check pins_arduino.h)
// tested with google-code core
#	define DI   14  // PB5
#	define DO   15  // PB6
#	define USCK 16  // PB7
#	define SS   13  // PB4
#elif defined(__AVR_ATtiny861__)
// these depend on the core used (check pins_arduino.h)
// tested with google-code core
#    define DI   9   // PB0
#    define DO   8   // PB1
#    define USCK 7   // PB2
#    define SS   6   // PB3
#endif

#if defined(RF24_TINY)

void SPIClass::begin() {

  pinMode(USCK, OUTPUT);
  pinMode(DO, OUTPUT);
  pinMode(DI, INPUT);
  USICR = _BV(USIWM0);

}

byte SPIClass::transfer(byte b) {

  USIDR = b;
  USISR = _BV(USIOIF);
  do
    USICR = _BV(USIWM0) | _BV(USICS1) | _BV(USICLK) | _BV(USITC);
  while ((USISR & _BV(USIOIF)) == 0);
  return USIDR;

}

void SPIClass::end() {}
void SPIClass::setDataMode(uint8_t mode){}
void SPIClass::setBitOrder(uint8_t bitOrder){}
void SPIClass::setClockDivider(uint8_t rate){}


#endif
