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
 */
 
class RF24
{
private:
  uint8_t ce_pin; /**< "Chip Enable" pin, activates the RX or TX role */
  uint8_t csn_pin; /**< SPI Chip select */
  uint8_t payload_size; /**< Fixed size of payloads */
  boolean ack_payload_available; /**< Whether there is an ack payload waiting */
  uint8_t ack_payload_length; /**< Dynamic size of pending ack payload. Note: not used. */
  uint64_t pipe0_reading_address; /**< Last address set on pipe 0 for reading. */

protected:  
  /**
   * @name Low-level internal interface.
   * 
   *  Protected methods that address the chip directly.  Regular users cannot
   *  ever call these.  They are documented for completeness and for developers who
   *  may want to extend this class.
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
   * Read single byte from a register
   *
   * @param reg Which register. Use constants from nRF24L01.h
   * @return Current value of register @p reg
   */
  uint8_t read_register(uint8_t reg);

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
   * @param len Number of bytes to be sent
   * @return Current value of status register
   */
  uint8_t write_payload(const void* buf, uint8_t len);

  /**
   * Read the receive payload
   *
   * The size of data read is the fixed payload size, see getPayloadSize()
   * 
   * @param buf Where to put the data
   * @param len Maximum number of bytes to read
   * @return Current value of status register
   */
  uint8_t read_payload(void* buf, uint8_t len) ;

  /**
   * Read the payload length
   *
   * For dynamic payloads, this pulls the size of the payload off
   * the chip
   *
   * @return Payload length of last-received dynamic payload
   */
  uint8_t read_payload_length(void);
  
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

  /**
   * Turn on or off the special features of the chip
   *
   * The chip has certain 'features' which are only available when the 'features'
   * are enabled.  See the datasheet for details.
   */
  void toggle_features(void);
  /**@}*/

public:
  /**
   * @name Primary public interface 
   * 
   *  These are the main methods you need to operate the chip 
   */
  /**@{*/

  /**
   * Constructor
   *
   * Creates a new instance of this driver.  Before using, you create an instance
   * and send in the unique pins that this chip is connected to.
   * 
   * @param _cepin The pin attached to Chip Enable on the RF module
   * @param _cspin The pin attached to Chip Select
   */
  RF24(uint8_t _cepin, uint8_t _cspin);

  /**
   * Begin operation of the chip
   *
   * Call this in setup(), before calling any other methods.
   */
  void begin(void);

  /**
   * Start listening on the pipes opened for reading.  
   *
   * Be sure to call openReadingPipe() first.  Do not call write() while
   * in this mode, without first calling stopListening().  Call
   * isAvailable() to check for incoming traffic, and read() to get it. 
   */
  void startListening(void);

  /**
   * Stop listening for incoming messages
   *
   * Do this before calling write(). 
   */
  void stopListening(void);

  /**
   * Write to the open writing pipe
   *
   * Be sure to call openWritingPipe() first to set the destination
   * of where to write to.
   *
   * This blocks until the message is successfully acknowledged by
   * the receiver or the timeout/retransmit maxima are reached.  In
   * the current configuration, the max delay here is 60ms.
   *
   * The maximum size of data written is the fixed payload size, see 
   * getPayloadSize().  However, you can write less, and the remainder
   * will just be filled with zeroes.
   * 
   * @param buf Pointer to the data to be sent
   * @param len Number of bytes to be sent
   * @return True if the payload was delivered successfully false if not
   */
  boolean write( const void* buf, uint8_t len );

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
   * @note I specifically chose 'void*' as a data type to make it easier
   * for beginners to use.  No casting needed.
   *
   * @param buf Pointer to a buffer where the data should be written
   * @param len Maximum number of bytes to read into the buffer
   * @return True if the payload was delivered successfully false if not
   */
  boolean read( void* buf, uint8_t len ) ;

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
   * @warning Pipes 1-5 should share the first 32 bits.
   * Only the least significant byte should be unique, e.g.
   * 
   * @code
   *   openReadingPipe(1,0xF0F0F0F0AA);
   *   openReadingPipe(2,0xF0F0F0F066);
   * @endcode
   * 
   * @todo Enforce the restriction that pipes 1-5 must share the top 32 bits
   *
   * @param number Which pipe# to open, 0-5.
   * @param address The 40-bit address of the pipe to open.
   */
  void openReadingPipe(uint8_t number, uint64_t address);

  /**@}*/
  /**
   * @name Optional public interface 
   * 
   *  Methods you may want to use but are not needed for regular operation 
   */
  /**@{*/

  /**
   * Set RF communication channel
   * 
   * @param channel Which RF channel to communicate on, 0-127
   */
  void setChannel(uint8_t channel);

  /**
   * Set Payload Size
   * 
   * This implementation uses a pre-stablished fixed payload size for all
   * transmissions.  If this method is never called, the driver will always
   * transmit the maximum payload size (32 bytes), no matter how much
   * was sent to write().
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
  void printDetails(void) ;
  
  /**
   * Enter low-power mode
   *
   * To return to normal power mode, either write() some data or
   * startListening().
   */
  void powerDown(void);

  /**
   * Test whether there are bytes available to be read
   *
   * Use this version to discover on which pipe the message
   * arrived.
   *
   * @param[out] pipe_num Which pipe has the payload available
   * @return True if there is a payload available, false if none is
   */
  boolean available(uint8_t* pipe_num);

  /**
   * Enable custom payloads on the acknowledge packets
   *
   * Ack payloads are a handy way to return data back to senders without
   * manually changing the radio modes on both units.  
   *
   * @see examples/pingpair_pl/pingpair_pl.pde
   */
  void enableAckPayload(void);

  /**
   * Write an ack payload for the specified pipe
   *
   * The next time a message is received on @p pipe, the data in @p buf will
   * be sent back in the acknowledgement.
   *
   * @warning According to the data sheet, only three of these can be pending
   * at any time.  I have not tested this.
   *
   * @param pipe Which pipe# (typically 1-5) will get this response.
   * @param buf Pointer to data that is sent
   * @param len Length of the data to send, up to 32 bytes max.  Not affected
   * by the static payload set by setPayloadSize().
   */
  void writeAckPayload(uint8_t pipe, const void* buf, uint8_t len);

  /**
   * Determine if an ack payload was received in the most recent call to
   * write().
   *
   * Call read() to retrieve the ack payload.
   *
   * @warning Calling this function clears the internal flag which indicates
   * a payload is available.  If it returns true, you must read the packet
   * out as the very next interaction with the radio, or the results are
   * undefined.
   *
   * @return True if an ack payload is available.
   */
  boolean isAckPayloadAvailable(void);
  
  /**@}*/
};

/**
 * @example pingpair.pde
 * 
 * This is an example of how to use the RF24 class.  Write this sketch to two 
 * different nodes, connect the role_pin to ground on one.  The ping node sends
 * the current time to the pong node, which responds by sending the value back.
 * The ping node can then see how long the whole cycle took.
 */

/**
 * @example starping.pde
 *
 * This sketch is a more complex example of using the RF24 library for Arduino.  
 * Deploy this on up to six nodes.  Set one as the 'pong receiver' by tying the 
 * role_pin low, and the others will be 'ping transmit' units.  The ping units
 * unit will send out the value of millis() once a second.  The pong unit will 
 * respond back with a copy of the value.  Each ping unit can get that response
 * back, and determine how long the whole cycle took.
 *
 * This example requires a bit more complexity to determine which unit is which.
 * The pong receiver is identified by having its role_pin tied to ground.
 * The ping senders are further differentiated by a byte in eeprom.
 */

/**
 * @example pingpair_pl.pde 
 *
 * This is an example of how to do two-way communication without changing 
 * transmit/receive modes.  Here, a payload is set to the transmitter within 
 * the Ack packet of each transmission.  Note that the payload is set BEFORE
 * the sender's message arrives.
 */

/**
 * @example pingpair_sleepy.pde 
 *
 * This is an example of how to use the RF24 class to create a battery-
 * efficient system.  It is just like the pingpair.pde example, but the
 * ping node powers down the radio and sleeps the MCU after every
 * ping/pong cycle.
 */

/**
 * @mainpage Driver for nRF24L01 2.4GHz Wireless Transceiver
 *
 * Design Goals: This library is designed to be...
 * @li Maximally compliant with the intended operation of the chip
 * @li Easy for beginners to use
 * @li Consumed with a public interface that's similiar to other Arduino standard libraries
 * @li Built against the standard SPI library.
 *
 * Please refer to:
 *
 * @li <a href="http://maniacbug.github.com/RF24/">Documentation Main Page</a>
 * @li <a href="http://maniacbug.github.com/RF24/classRF24.html">RF24 Class Documentation</a>
 * @li <a href="https://github.com/maniacbug/RF24/">Source Code</a>
 * @li <a href="https://github.com/maniacbug/RF24/archives/master">Downloads Page</a>
 * @li <a href="http://www.nordicsemi.com/files/Product/data_sheet/nRF24L01_Product_Specification_v2_0.pdf">Chip Datasheet</a>
 *
 * This chip uses the SPI bus, plus two chip control pins.  Remember that pin 10 must still remain an output, or
 * the SPI hardware will go into 'slave' mode.
 */

#endif // __RF24_H__
// vim:ai:cin:sts=2 sw=2 ft=cpp

