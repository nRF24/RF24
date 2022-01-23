/*
   See documentation at https://nRF24.github.io/RF24
   See License information at root directory of this library
   Authors: Brendan Doherty (2bndy5), Douglas Quigg (dstroy0)
*/

/**
   A simple example of sending data from 1 nRF24L01 transceiver to another.

   This example was written to be used on 2 devices, one acting as the encodeRadioDetails sender and another acting as the decodeRadioDetails receiver.
   Use the Serial Monitor to change each node's behavior.
*/
#include <SPI.h>
#include "printf.h"
#include "RF24.h"

// instantiate an object for the nRF24L01 transceiver
RF24 radio(7, 8); // using pin 7 for the CE pin, and pin 8 for the CSN pin


// Let these addresses be used for the pair
uint8_t address[][6] = {"1Node", "2Node"};
// It is very helpful to think of an address as a path instead of as
// an identifying device destination

// to use different addresses on a pair of radios, we need a variable to
// uniquely identify which address this radio will use to transmit
bool radioNumber = 1; // 0 uses address[0] to transmit, 1 uses address[1] to transmit

// Used to control whether this node is sending or receiving
bool role = false;  // true = TX role, false = RX role
/*
  For this example, we'll be using a payload containing
  radio details encoded with RF24::encodeRadioDetails()
  it is sent by the sender and decoded by the receiver
  using decodeRadioDetails(), you can manually decode
  your encoded details by printing out the payload value
  in binary by or blinking a led for each bit in the
  payload
*/
uint32_t payload[10] = {0};

void setup() {

  Serial.begin(115200);
  while (!Serial) {
    // some boards need to wait to ensure access to serial over USB
  }

  // initialize the transceiver on the SPI bus
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {} // hold in infinite loop
  }

  // print example's introductory prompt
  Serial.println(F("RF24/examples/GettingStarted"));

  // To set the radioNumber via the Serial monitor on startup
  Serial.println(F("Which radio is this? Enter '0' or '1'. Defaults to '0'"));
  while (!Serial.available()) {
    // wait for user input
  }
  char input = Serial.parseInt();
  radioNumber = input == 1;
  Serial.print(F("radioNumber = "));
  Serial.println((int)radioNumber);

  // role variable is hardcoded to RX behavior, inform the user of this
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  // Set the PA Level low to try preventing power supply related problems
  // because these examples are likely run with nodes in close proximity to
  // each other.
  radio.setPALevel(RF24_PA_LOW);  // RF24_PA_MAX is default.

  // save on transmission time by setting the radio to only transmit the
  // number of bytes we need to transmit
  radio.setPayloadSize(sizeof(payload)); // float datatype occupies 4 bytes

  // set the TX address of the RX node into the TX pipe
  radio.openWritingPipe(address[radioNumber]);     // always uses pipe 0

  // set the RX address of the TX node into a RX pipe
  radio.openReadingPipe(1, address[!radioNumber]); // using pipe 1

  // additional setup specific to the node's role
  if (role) {
    radio.stopListening();  // put radio in TX mode
  } else {
    radio.startListening(); // put radio in RX mode
  }

  // For debugging info
  // printf_begin();             // needed only once for printing details
  // radio.printDetails();       // (smaller) function that prints raw register values
  // radio.printPrettyDetails(); // (larger) function that prints human readable data

  radio.encodeRadioDetails(payload); //NOT human readable, very small when used on its own (no output), no printf needed, puts debugging information into a bit array
} // setup

/*
     encodeRadioDetails packing order

     1  uint16_t csn_pin
     2  uint16_t ce_pin
     3  uint8_t static_cast<uint8_t>(spi_speed / 1000000)
     4  uint8_t getChannel()
     5  uint16_t static_cast<uint16_t>(getChannel() + 2400)  //not encoded in encoded_details!
     6  uint8_t getDataRate()
     7  uint8_t getPALevel()
     8  uint8_t (read_register(RF_SETUP) & 1) * 1)
     9  uint8_t getCRCLength()
     10 uint8_t ((read_register(SETUP_AW) & 3) + 2)
     11 uint8_t getPayloadSize()
     12 uint16_t ((read_register(SETUP_RETR) >> ARD) * 250 + 250)
     13 uint8_t (read_register(SETUP_RETR) & 0x0F)
     14 uint8_t (read_register(OBSERVE_TX) >> 4)
     15 uint8_t (read_register(OBSERVE_TX) & 0x0F)
     16 bool (static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK)) * 2)
     17 bool (static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY)) * 1)
     18 uint8_t ((read_register(DYNPD) && (read_register(FEATURE) &_BV(EN_DPL))) * 1)
     19 bool autoack_status_array[6]
        {
            (static_cast<bool>(autoAck & _BV(ENAA_P5)) + 48),
            (static_cast<bool>(autoAck & _BV(ENAA_P4)) + 48),
            (static_cast<bool>(autoAck & _BV(ENAA_P3)) + 48),
            (static_cast<bool>(autoAck & _BV(ENAA_P2)) + 48),
            (static_cast<bool>(autoAck & _BV(ENAA_P1)) + 48),
            (static_cast<bool>(autoAck & _BV(ENAA_P0)) + 48)
        }
     25 bool (read_register(NRF_CONFIG) & _BV(PRIM_RX))
     26 uint8_t tx_address[5]
        {
            TX_ADDR
        }

        //indicate whether pipes are open or closed after first address
     31 uint8_t pipe_forty_bit_address_array[5]
        {
            static_cast<uint8_t>(RX_ADDR_P0 + 0),
            static_cast<uint8_t>(RX_ADDR_P0 + 1)
        }
     41 uint8_t pipe_eight_bit_register_array[4]
        {
            static_cast<uint8_t>(RX_ADDR_P0 + 2),
            static_cast<uint8_t>(RX_ADDR_P0 + 3),
            static_cast<uint8_t>(RX_ADDR_P0 + 4),
            static_cast<uint8_t>(RX_ADDR_P0 + 5)
        }
*/

/*
  https://www.rapidtables.com/convert/number/binary-to-decimal.html
  Enter in your binary number and this will convert it to decimal (base10) for you
  a uint16_t has 16 bits, a uint8_t has 8 bits, a boolean value is packed into one bit
  in the bit array.  Trailing zeros are padding
 */

void loop() {

  if (role) {
    // This device is a TX node

    unsigned long start_timer = micros();                    // start the timer
    bool report = radio.write(&payload, sizeof(payload));      // transmit & save the report
    unsigned long end_timer = micros();                      // end the timer

    if (report) {
      Serial.print(F("Transmission successful! "));          // payload was delivered
      Serial.print(F("Time to transmit = "));
      Serial.print(end_timer - start_timer);                 // print the timer result
      Serial.println(F(" us. Sent: "));
      for (int i = 0; i < 10; i++) {  //print out each member of payload[] in binary
        Serial.println(payload[i], BIN);  //you can manually decode by following the packing order of encodeRadioDetails
      }
    } else {
      Serial.println(F("Transmission failed or timed out")); // payload was not delivered
    }

    // to make this example readable in the serial monitor
    delay(60000);  // slow transmissions down by 1 minute

  } else {
    // This device is a RX node

    uint8_t pipe;
    if (radio.available(&pipe)) {             // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);            // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);                    // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                     // print the pipe number
      Serial.println(F(": "));
      for (int i = 0; i < 10; i++) {
        Serial.println(payload[i], BIN);                // print the payload's value in binary
      }
      char debugging_information[870] = {'\0'};
      radio.decodeRadioDetails(debugging_information, payload);
      Serial.println(debugging_information);
    }
  } // role

  if (Serial.available()) {
    // change the role via the serial monitor

    char c = toupper(Serial.read());
    if (c == 'T' && !role) {
      // Become the TX node

      role = true;
      Serial.println(F("*** CHANGING TO TRANSMIT ROLE -- PRESS 'R' TO SWITCH BACK"));
      radio.stopListening();

    } else if (c == 'R' && role) {
      // Become the RX node

      role = false;
      Serial.println(F("*** CHANGING TO RECEIVE ROLE -- PRESS 'T' TO SWITCH BACK"));
      radio.startListening();
    }
  }

} // loop
