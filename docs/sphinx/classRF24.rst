RF24 class
~~~~~~~~~~

.. cpp:class:: RF24

    .. doxygenfunction:: RF24 (rf24_gpio_pin_t, rf24_gpio_pin_t, uint32_t)
    .. doxygenfunction:: begin (void)
    .. doxygenfunction:: begin (_SPI *spiBus)

Dynamically Instantiated Pins
=============================

.. doxygenfunction:: RF24::RF24 (uint32_t _spi_speed=RF24_SPI_SPEED)
.. doxygenfunction:: RF24::begin (rf24_gpio_pin_t _cepin, rf24_gpio_pin_t _cspin)
.. doxygenfunction:: RF24::begin (_SPI *spiBus, rf24_gpio_pin_t _cepin, rf24_gpio_pin_t _cspin)

Basic API
============

.. doxygenfunction:: RF24::startListening
.. doxygenfunction:: RF24::stopListening
.. doxygenfunction:: RF24::available (void)
.. doxygenfunction:: RF24::available (uint8_t *pipe_num)
.. doxygenfunction:: RF24::read
.. doxygenfunction:: RF24::write (const void *buf, uint8_t len)
.. doxygenfunction:: RF24::openWritingPipe (const uint8_t *address)
.. doxygenfunction:: RF24::openWritingPipe (uint64_t address)
.. doxygenfunction:: RF24::openReadingPipe (uint8_t number, const uint8_t *address)
.. doxygenfunction:: RF24::openReadingPipe (uint8_t number, uint64_t address)
.. doxygenfunction:: RF24::closeReadingPipe

Advanced API
============

.. doxygenfunction:: RF24::isChipConnected
.. doxygenfunction:: RF24::isValid
.. doxygenfunction:: RF24::isPVariant
.. doxygenfunction:: RF24::whatHappened

Debugging helpers
*******************

.. doxygenvariable:: RF24::failureDetected
.. doxygenfunction:: RF24::printDetails
.. doxygenfunction:: RF24::printPrettyDetails
.. doxygenfunction:: RF24::getARC

Advanced Transmission
*********************

.. doxygenfunction:: RF24::write (const void *buf, uint8_t len, const bool multicast)
.. doxygenfunction:: RF24::writeAckPayload
.. doxygenfunction:: RF24::writeFast (const void *buf, uint8_t len)
.. doxygenfunction:: RF24::writeFast (const void *buf, uint8_t len, const bool multicast)
.. doxygenfunction:: RF24::reUseTX
.. doxygenfunction:: RF24::writeBlocking
.. doxygenfunction:: RF24::startFastWrite
.. doxygenfunction:: RF24::startWrite
.. doxygenfunction:: RF24::txStandBy()
.. doxygenfunction:: RF24::txStandBy (uint32_t timeout, bool startTx=0)

Power Management
****************

.. doxygenfunction:: RF24::powerDown
.. doxygenfunction:: RF24::powerUp

FIFO Management
***************

.. doxygenfunction:: RF24::rxFifoFull
.. doxygenfunction:: RF24::flush_tx
.. doxygenfunction:: RF24::flush_rx
.. doxygenfunction:: RF24::isFifo (bool about_tx)
.. doxygenfunction:: RF24::isFifo (bool about_tx, bool check_empty)

Ambiguous Signal Detection
**************************

.. doxygenfunction:: RF24::startConstCarrier
.. doxygenfunction:: RF24::stopConstCarrier
.. doxygenfunction:: RF24::testCarrier
.. doxygenfunction:: RF24::testRPD

Configuration API
==================

.. doxygenfunction:: RF24::setAddressWidth
.. doxygenfunction:: RF24::setRetries
.. doxygenfunction:: RF24::maskIRQ
.. doxygenfunction:: RF24::toggleAllPipes

Channel (Frequency)
*******************

.. doxygenfunction:: RF24::setChannel
.. doxygenfunction:: RF24::getChannel

Dynamic Delays
**************
.. doxygenvariable:: RF24::txDelay
.. doxygenvariable:: RF24::csDelay

Payload Sizes
*************

.. doxygenfunction:: RF24::setPayloadSize
.. doxygenfunction:: RF24::getPayloadSize
.. doxygenfunction:: RF24::enableDynamicPayloads
.. doxygenfunction:: RF24::disableDynamicPayloads
.. doxygenfunction:: RF24::getDynamicPayloadSize

Auto-Acknowledgement
********************

.. doxygenfunction:: RF24::setAutoAck (bool enable)
.. doxygenfunction:: RF24::setAutoAck (uint8_t pipe, bool enable)
.. doxygenfunction:: RF24::enableAckPayload
.. doxygenfunction:: RF24::disableAckPayload
.. doxygenfunction:: RF24::enableDynamicAck
.. doxygenfunction:: RF24::isAckPayloadAvailable

Radiation Options
*****************

.. doxygenfunction:: RF24::setPALevel
.. doxygenfunction:: RF24::getPALevel
.. doxygenfunction:: RF24::setDataRate
.. doxygenfunction:: RF24::getDataRate
.. doxygenfunction:: RF24::setRadiation

CRC Lengths
***********

.. doxygenfunction:: RF24::setCRCLength
.. doxygenfunction:: RF24::getCRCLength
.. doxygenfunction:: RF24::disableCRC

Protected API
==============

These are the members and functions made available to derivatives that inherit from the RF24 class.

.. doxygenfunction:: RF24::beginTransaction
.. doxygenfunction:: RF24::endTransaction
.. doxygenfunction:: RF24::read_register (uint8_t reg)
.. doxygenfunction:: RF24::read_register (uint8_t reg, uint8_t *buf, uint8_t len)
.. doxygenvariable:: RF24::ack_payloads_enabled
.. doxygenvariable:: RF24::addr_width
.. doxygenvariable:: RF24::dynamic_payloads_enabled