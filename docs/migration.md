# Migration guide

@tableofcontents

<!-- markdownlint-disable MD033 MD031 -->

This is a collection of snippets that highlight preferred API over the deprecated original API.

## isAckPayloadAvailable()

> **Deprecated since v1.4.2**

This function is equivalent to `RF24::available()`.
Any use of `RF24::isAckPayloadAvailable()` is interchangeable with `RF24::available()`.

<table><tr>
<th>Old</th>
<th>New (supported)</th>
</tr><tr><td>

```cpp
if radio.isAckPayloadAvailable() { /* .. */ }
```

</td><td>

```cpp
if radio.available() { /* .. */ }
```

</td></tr></table>

## 64-bit integer addresses

Any function that accept an address in the form of `uint64_t` is discouraged. This includes

- `RF24::openReadingPipe(uint8_t, uint64_t)`
   > **Deprecated since v1.3.11**
- `RF24::openWritingPipe(uint64_t)`
   > **Deprecated since v1.3.11**
- `RF24::stopListening(const uint64_t)`
   > **Deprecated since v1.5**

These functions' address parameter use a 64-bit unsigned integer (`uint64_t`).
The nRF24L01 can only use up to 40 bit addresses.
Thus, there is an unused 24 bits being allocated for addresses using these functions.

There are overloaded functions that use a buffer instead:

- `RF24::openReadingPipe(uint8_t, const uint8_t*)`
- `RF24::openWritingPipe(const uint8_t*)`
- `RF24::stopListening(const uint8_t*)`

These eliminate the unnecessary 24 bits by only using the length of the buffer (`uint8_t*`)
specified by `RF24::setAddressWidth()`.

@see The `RF24::openWritingPipe(const uint8_t*)` is now deprecated in favor of the
overloaded `RF24::stopListening(const uint8_t*)` function.
See the section below for more detail.

> [!CAUTION]
> The endianness (byte order) of a buffer is reversed compared to a 64-bit integer.
> ```c
> uint64_t address = 0xB3B4B5B6C2;
> // is the same address as
> uint8_t address[5] = {0xC2, 0xB6, 0xB5, 0xB4, 0xB3};
> ```
> Notice the MSB (Most Significant Byte) `0xC2` is last in the integer but first in the buffer.

<table><tr>
<th>Old</th>
<th>New (supported)</th>
</tr><tr><td>

```cpp
uint64_t address = 0xB3B4B5B6C2;
radio.openReadingPipe(1, address);
```

</td><td>

```cpp
uint8_t address[5] = {0xC2, 0xB6, 0xB5, 0xB4, 0xB3};
radio.openReadingPipe(1, address);
```

</td></tr></table>

> [!NOTE]
> Our examples actually use a C-string casted as an array of 6 bytes.
> That's because a C-string (`char*`) must be NULL terminated (`\0` at the end) in memory.
> ```c
> uint8_t address[][6] = { "1Node", "2Node" };
> // is equivalent to
> uint8_t address[][6] = { { '1', 'N', 'o', 'd', 'e', '\0' },
>                          { '2', 'N', 'o', 'd', 'e', '\0' } };
> ```

## isFifo(bool, bool)

> **Deprecated since v1.4.11**

Introduced as a compliment to `RF24::isFifo(bool)` in v1.4.3, this function was
supposed to provide a specific detail about a specified radio's FIFO. However, it was
discovered that the function may not highlight binary corruption (`RF24_FIFO_INVALID`)
observed in the SPI bus' MISO line.

A fix was introduced using enumerated values of `rf24_fifo_state_e`.
Since then, `RF24::isFifo(bool)` is now preferred as it accurately describes the result.

<table><tr>
<th>Old</th>
<th>New (supported)</th>
</tr><tr><td>

```cpp
bool rxFifoEmpty = radio.isFifo(false, true);
```

</td><td>

```cpp
bool rxFifoEmpty = radio.isFifo(false) == RF24_FIFO_EMPTY;
```

</td></tr></table>

## maskIRQ()

> **Deprecated since v1.5**

Originally `RF24::maskIRQ()` was the only function provided to influence the radio's IRQ pin.
However, the 3 required boolean parameters made this prone to bugs in user code.
The parameters' meaning was confusingly reversed, and they were easily misplaced in the wrong order.

A better approach was introduced with `RF24::setStatusFlags()`.
It's 1 parameter accepts values defined by the `rf24_irq_flags_e` enumerated constants.
These constant values specify individual events;
they can also be OR'd together to specify multiple events.

<table><tr>
<th>Old</th>
<th>New (supported)</th>
</tr><tr><td>

```cpp
// IRQ pin only activated by "RX Data Ready" event
radio.maskIRQ(1, 1, 0);

// IRQ pin activated by "TX Data Sent" and TX Data Failed" events
radio.maskIRQ(0, 0, 1);

// IRQ pin activated by all events
radio.maskIRQ(0, 0, 0);

// IRQ pin disabled
radio.maskIRQ(1, 1, 1);
```

</td><td>

```cpp
// IRQ pin only activated by "RX Data Ready" event
radio.setStatusFlags(RF24_RX_DR);

// IRQ pin activated by "TX Data Sent" and TX Data Failed" events
radio.setStatusFlags(RF24_TX_DS | RF24_TX_DF);

// IRQ pin activated by all events
radio.setStatusFlags(RF24_IRQ_ALL);

// IRQ pin disabled
radio.setStatusFlags(RF24_IRQ_NONE);
// or equivalently
radio.setStatusFlags();
```

</td></tr></table>

## whatHappened()

> **Deprecated since v1.5**

Originally, `RF24::whatHappened()` was the only way to clear the events that triggered the IRQ pin.
Like `maskIRQ()`, this was also prone to bugs because of the 3 required boolean parameters
(passed by reference).

The aptly named `RF24::clearStatusFlags()` is designed to be a replacement for `RF24::whatHappened()`.
Like `RF24::clearStatusFlags()`, `RF24::setStatusFlags()` takes 1 parameter whose value is defined by
the `rf24_irq_flags_e` enumerated constants. These constant values specify individual flags;
they can also be OR'd together to specify multiple flags.

Additionally, `RF24::clearStatusFlags()` returns the STATUS byte containing the flags that
caused the IRQ pin to go active LOW.
This allows the user code to allocate less memory when diagnosing the IRQ pin's meaning.

<table><tr>
<th>Old</th>
<th>New (supported)</th>
</tr><tr><td>

```cpp
bool tx_ds, tx_df, rx_dr;
radio.whatHappened(tx_ds, tx_df, rx_dr);
```

</td><td>

```cpp
uint8_t flags = radio.clearStatusFlags();
// or equivalently
uint8_t flags = radio.clearStatusFlags(RF24_IRQ_ALL);

// focus on the events you care about
if (flags & RF24_TX_DS) { /* TX data sent */ }
if (flags & RF24_TX_DF) { /* TX data failed to send */ }
if (flags & RF24_RX_DR) { /* RX data is in the RX FIFO */ }

// only clear the "TX Data Sent" and TX Data Failed" events
radio.clearStatusFlags(RF24_TX_DS | RF24_TX_DF);

// only clear the "RX Data Ready" event
radio.clearStatusFlags(RF24_RX_DR);
```

</td></tr></table>

## openWritingPipe(const uint8_t*)

> Deprecated since v1.5

Originally, `RF24::openWritingPipe(const uint8_t*)` was just a compliment to
`RF24::openReadingPipe()`.
It changes the address on pipe 0 because that is the only pipe that can be
used for transmitting.

Unfortunately, there was a bug that prevented the given TX address from being
persistent on pipe 0 if the user code also set an RX address to pipe 0.
This bug would surface when switching between RX mode and TX mode (via
`RF24::startListening()` and `RF24::stopListening()` respectively) or after
`RF24::stopConstCarrier()` (if `RF24::isPVariant()` returns `true`).

The solution is to cache the TX address on the `RF24` instance.
Consequently, this solution did not fit well with the traditional order of
functions used to set up the radio's TX or RX mode.

By overloading `RF24::stopListening(const uint8_t*)`, we are able to ensure proper radio
setup without requiring certain functions are called in a certain order.

- Use `RF24::stopListening(const uint8_t*)` to set the TX address and enter inactive TX mode.
  `RF24::openReadingPipe()` can now (as of v1.5) be used in TX mode without consequence.
- Use `RF24::stopListening()` to enter inactive TX mode without changing the TX address.

> [!warning]
> Avoid using pipe 0 for RX operations to improve performance and reliability.
>
> For implementation detail, see the source for `RF24::openReadingPipe()` and
> `RF24::stopListening()`. Ultimately, the datasheet's Appendix A has a detailed
> example outlining the order of a proper radio setup.

<table><tr>
<th>Old</th>
<th>New (supported)</th>
</tr><tr><td>

```cpp
// set TX address (pipe 0)
radio.openWritingPipe(tx_address);

// set RX address (pipe 1)
radio.openReadingPipe(1, rx_address);

// idle radio using inactive TX mode
radio.stopListening();
```

</td><td>

```cpp
// set TX address (pipe 0)
radio.stopListening(tx_address); // enters inactive TX mode

// set RX address (pipe 1)
radio.openReadingPipe(1, rx_address);
```

</td></tr></table>
