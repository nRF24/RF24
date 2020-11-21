# Common Issues

## Settings that must match
Before you report undesirable behavior, please make sure that the
following RF24 configurations match on both receiving and transmitting
nRF24L01 transceivers:
1. `RF24::setAddressWidth()`
2. `RF24::setChannel()`
3. `RF24::setDataRate()`
4. `RF24::setAutoAck()`
5. `RF24::enableDynamicPayloads()` or `RF24::disableDynamicPayloads()`
6. `RF24::enableAckPayload()` or `RF24::disableAckPayload()` (requires auto-ack and
   dynamic payloads features)
7. `RF24::setPayloadSize()` (only if the dynamic payloads feature is disabled -- it is disabled by default)
8. `RF24::setCRCLength()` or `RF24::disableCRC()` (the auto-ack feature
   automatically enables CRC because it is required)

Also, it helps to think of an address as a path (a commonly shared route)
instead of an identifying device destination. This means that addresses
have to match for a payload to travel from one transceiver to another.
However, the pipe numbers assigned with the matching address do not have
to match. You can think of pipes as parking spots for the packets, while
all packets' payloads live in a TX or RX FIFO buffer. Remember that the
TX FIFO buffers and the RX FIFO buffers both have a maximum occupancy of
3 payloads (regardless of the maximum 32-byte payload size).

## Here are the most common issues and their solutions.

### write() always returns true after setAutoAck(false)
Don't disabled the auto-ack feature. RF24::write() has no reason to doubt
that the payload was delivered if the auto-ack feature is disabled. We
recommend you read the docs about RF24::setAutoAck() before disabling the
auto-ack feature.

### write() returns false when the payload was received
If the settings match on both endpoint transceivers, then this can only
mean that the receiving nRF24L01 failed to send an acknowledgement (ACK)
packet back to the transmitting nRF24L01. Usually this is due to
instability (electric noise) in the power lines (VCC and GND) going to
the receiving nRF24L01.

If you're not receiving ACK packets correctly/reliably on data rates
lower than 2MBPS, try adding a big capacitor close to the module/chip.
Example issues: [#264](https://github.com/nRF24/RF24/issues/264)
[#211](https://github.com/nRF24/RF24/issues/211).

For reliability, please use Electrolytic or Tantalum capacitors. Ceramic
capacitors may not be good enough (depending on the manufacturing source).
