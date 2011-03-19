/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

#ifndef __RF24_H__
#define __RF24_H__

#include <inttypes.h>

/**
 * Driver for nRF24L01 2.4GHz Wireless Transceiver
 *
 * See <a href="http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf">Datasheet</a>
 *
 * This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or
 * the SPI hardware will go into 'slave' mode.
 *
 * Design Goals: This library is designed to be...
 *   * Maximally compliant with the intended operation of the chip
 *   * Easy for beginners to use
 *   * Consumed with a public interface that's similiar to other Arduino standard libraries
 *   * Built against the standard SPI library. 
 */
 
class RF24
{
private:
  int ce_pin; /**< "Chip Enable" pin, activates the RX or TX role */
  int csn_pin; /**< SPI Chip select */
  int payload_size; /**< Fixed size of payloads */

protected:  
  /**
   * @name Low-level internal interface.
   * 
   *  Protected methods that address the chip directly.
   */
  /**@{*/

  /**
   * Set chip select pin
   *
   * @param mode HIGH to take this unit off the SPI bus, LOW to put it on
   */
  void csn(int mode) ;

  /**
   * Set chip enable
   *
   * @param mode HIGH to actively begin transmission or LOW to put in standby.  Please see data sheet
   * for a much more detailed description of this pin.
   */
  void ce(int mode);

  /**
   * Read a chunk of data in from a register
   *
   * @param reg Which register. Use constants from nRF24L01.h
   * @param buf Where to put the data
   * @param len How many bytes of data to transfer
   * @return Current value of status register
   */
  uint8_t read_register(uint8_t reg, uint8_t* buf, uint8_t len) ;

  /**
   * Write a chunk of data to a register
   *
   * @param reg Which register. Use constants from nRF24L01.h
   * @param buf Where to get the data
   * @param len How many bytes of data to transfer
   * @return Current value of status register
   */
  uint8_t write_register(uint8_t reg, const uint8_t* buf, uint8_t len);

  /**
   * Write a single byte to a register
   *
   * @param reg Which register. Use constants from nRF24L01.h
   * @param value The new value to write
   * @return Current value of status register
   */
  uint8_t write_register(uint8_t reg, uint8_t value);

  /**
   * Write the transmit payload
   *
   * The size of data written is the fixed payload size, see getPayloadSize()
   * 
   * @param buf Where to get the data
   * @return Current value of status register
   */
  uint8_t write_payload(const void* buf);

  /**
   * Read the receive payload
   *
   * The size of data read is the fixed payload size, see getPayloadSize()
   * 
   * @param buf Where to put the data
   * @return Current value of status register
   */
  uint8_t read_payload(void* buf) ;

  /**
   * Empty the receive buffer
   *
   * @return Current value of status register
   */
  uint8_t flush_rx(void);

  /**
   * Empty the transmit buffer
   *
   * @return Current value of status register
   */
  uint8_t flush_tx(void);

  /**
   * Retrieve the current status of the chip
   *
   * @return Current value of status register
   */
  uint8_t get_status(void) ;

  /**
   * Decode and print the given status to stdout
   *
   * @param status Status value to print
   *
   * @warning Does nothing if stdout is not defined.  See fdevopen in stdio.h
   */
  void print_status(uint8_t status) ;

  /**
   * Decode and print the given 'observe_tx' value to stdout
   *
   * @param value The observe_tx value to print
   *
   * @warning Does nothing if stdout is not defined.  See fdevopen in stdio.h
   */
  void print_observe_tx(uint8_t value) ;

  /**@}*/

public:
  /**
   * Constructor
   *
   * Creates a new instance of this driver.  Before using, you create an instance
   * and send in the unique pins that this chip is connected to.
   * 
   * @param _cepin The pin attached to Chip Enable on the RF module
   * @param _cspin The pin attached to Chip Select
   */
  RF24(int _cepin, int _cspin);

  /**
   * Begin operation of the chip
   *
   * Call this in setup(), before calling any other methods.
   */
  void begin(void);

  /**
   * Set RF communication channel
   * 
   * @param channel Which RF channel to communicate on, 0-127
   */
  void setChannel(int channel);

  /**
   * Set Payload Size
   * 
   * This implementation uses a pre-stablished fixed payload size for all
   * transmissions.
   *
   * @todo Implement variable-sized payloads feature
   * 
   * @param size The number of bytes in the payload
   */
  void setPayloadSize(uint8_t size);

  /**
   * Get Payload Size
   * 
   * @see setPayloadSize()
   *
   * @return The number of bytes in the payload
   */
   uint8_t getPayloadSize(void) ;

  /**
   * Print a giant block of debugging information to stdout
   *
   * @warning Does nothing if stdout is not defined.  See fdevopen in stdio.h
   */
  void print_details(void) ;

  /**
   * Start listening on the pipes opened for reading.  
   *
   * Be sure to open some pipes for reading first.  Do not call 'write'
   * while in this mode, without first calling 'stopListening'.
   */
  void startListening(void);

  /**
   * Stop listening for incoming messages
   *
   * Necessary to do this before writing.
   */
  void stopListening(void);

  /**
   * Write to the open writing pipe
   *
   * This blocks until the message is successfully acknowledged by
   * the receiver or the timeout/retransmit maxima are reached.  In
   * the current configuration, the max delay here is 60ms.
   *
   * The size of data written is the fixed payload size, see getPayloadSize()
   * 
   * @param buf Pointer to the data to be sent
   * @return True if the payload was delivered successfully false if not
   */
  boolean write( const void* buf );

  /**
   * Test whether there are bytes available to be read
   *
   * @return True if there is a payload available, false if none is
   */
  boolean available(void) ;

  /**
   * Read the payload
   *
   * Return the last payload received
   *
   * The size of data read is the fixed payload size, see getPayloadSize()
   * 
   * @todo Indicate which pipe it came from
   *
   * @note I specifically chose 'void*' as a data type to make it easier
   * for beginners to use.  No casting needed.
   *
   * @param buf Pointer to a buffer where the data should be written
   * @return True if the payload was delivered successfully false if not
   */
  boolean read( void* buf ) ;

  /**
   * Open a pipe for writing
   *
   * Only one pipe can be open at once, but you can change the pipe
   * you'll listen to.  Do not call this while actively listening.
   * Remember to stopListening() first.
   *
   * Addresses are 40-bit hex values, e.g.:
   *
   * @code
   *   openWritingPipe(0xF0F0F0F0F0);
   * @endcode
   *
   * @param address The 40-bit address of the pipe to open.  This can be
   * any value whatsoever, as long as you are the only one writing to it
   * and only one other radio is listening to it.  Coordinate these pipe
   * addresses amongst nodes on the network.
   */
  void openWritingPipe(uint64_t address);

  /**
   * Open a pipe for reading
   *
   * Up to 5 pipes can be open for reading at once.  Open all the
   * reading pipes, and then call startListening().
   *
   * @see openWritingPipe
   *
   * @warning all 5 reading pipes should share the first 32 bits.
   * Only the least significant byte should be unique, e.g.
   * 
   * @code
   *   openReadingPipe(0xF0F0F0F0AA);
   *   openReadingPipe(0xF0F0F0F066);
   * @endcode
   * 
   * @todo Enforce the restriction that all pipes must share the top 32 bits
   *
   * @param number Which pipe# to open, 1-5.
   * @param address The 40-bit address of the pipe to open.
   */
  void openReadingPipe(uint8_t number, uint64_t address);

}; 
#endif // __RF24_H__

