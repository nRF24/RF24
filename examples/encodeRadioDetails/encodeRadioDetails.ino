/*
   See documentation at https://nRF24.github.io/RF24
   See License information at root directory of this library
   Authors: Brendan Doherty (2bndy5), Douglas Quigg (dstroy0)
*/

/**
   A simple example of sending debug info from 1 nRF24L01 transceiver to another.

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
uint8_t payload[40] = {0};

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
  encodeRadioDetails packing order:

  1 csn_pin
  2 ce_pin
  3 spi_speed
  4 getChannel()
  5 getDataRate()
  6 getPALevel()
  7 ((read_register(RF_SETUP) & 1) * 1)
  8 getCRCLength()
  9 ((read_register(SETUP_AW) & 3) + 2)
  10 getPayloadSize()
  11 (read_register(SETUP_RETR) >> ARD)
  12 (read_register(SETUP_RETR) & 0x0F)
  13 (read_register(OBSERVE_TX) >> 4)
  14 (read_register(OBSERVE_TX) & 0x0F)
  15 static_cast<bool>(read_register(FEATURE) & _BV(EN_DYN_ACK))
  16 static_cast<bool>(read_register(FEATURE) & _BV(EN_ACK_PAY))
  17 ((read_register(DYNPD) && (read_register(FEATURE) &_BV(EN_DPL))) * 1)
  18 (static_cast<bool>(temp_8_bit & _BV(ENAA_P5)) + 48)
  19 (static_cast<bool>(temp_8_bit & _BV(ENAA_P4)) + 48)
  20 (static_cast<bool>(temp_8_bit & _BV(ENAA_P3)) + 48)
  21 (static_cast<bool>(temp_8_bit & _BV(ENAA_P2)) + 48)
  22 (static_cast<bool>(temp_8_bit & _BV(ENAA_P1)) + 48)
  23 (static_cast<bool>(temp_8_bit & _BV(ENAA_P0)) + 48)
  24 (read_register(NRF_CONFIG) & _BV(PRIM_RX))

  25 tx_address_forty_bit_array[0]
  26 tx_address_forty_bit_array[1]
  27 tx_address_forty_bit_array[2]
  28 tx_address_forty_bit_array[3]
  29 tx_address_forty_bit_array[4]

  30 pipe_address_forty_bit_array[0]
  31 pipe_address_forty_bit_array[1]
  32 pipe_address_forty_bit_array[2]
  33 pipe_address_forty_bit_array[3]
  34 pipe_address_forty_bit_array[4]
  35 pipe_address_forty_bit_array[0]
  36 pipe_address_forty_bit_array[1]
  37 pipe_address_forty_bit_array[2]
  38 pipe_address_forty_bit_array[3]
  39 pipe_address_forty_bit_array[4]

  40 pipe_eight_bit_register_array[0]
  41 pipe_eight_bit_register_array[0]
  42 pipe_eight_bit_register_array[0]
  43 pipe_eight_bit_register_array[0]

  44 read_register(EN_RXADDR)
*/

/*
  https://www.rapidtables.com/convert/number/binary-to-decimal.html
  Enter in your binary number and this will convert it to decimal (base10) for you
  a uint16_t has 16 bits, a uint8_t has 8 bits, a boolean value is packed into one bit
  in the bit array.  Trailing zeros are padding
*/

void loop() {
  if (role) {
    uint8_t split_payload_2d_array[2][21] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 99}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 101}};  // split the payload to get below 32 bytes payload limit, mark the end for reassembly
    for (int i = 0; i < 20; i++)
    {
      split_payload_2d_array[0][i] = payload[i]; // first 20 elements
      split_payload_2d_array[1][i] = payload[i]; // second 20 elements
    }
    for (int i = 0; i < 2; i++) // iterate twice to transmit, because we split our payload into two pieces
    {
      // This device is a TX node
      unsigned long start_timer = micros();                    // start the timer
      bool report = radio.write(&split_payload_2d_array[i], sizeof(split_payload_2d_array[i]));      // transmit one half at a time & save the report
      unsigned long end_timer = micros();                      // end the timer
      if (report) {
        Serial.print(F("Transmission successful! "));          // payload was delivered
        Serial.print(F("Time to transmit = "));
        Serial.print(end_timer - start_timer);                 // print the timer result
        Serial.print(F(" us. split_payload_2d_array["));
        Serial.print(i);
        Serial.println(F("] represented in binary (base2):\n"));
        int number_of_payload_elements = sizeof(split_payload_2d_array) / sizeof(split_payload_2d_array[0][0]);  // get number of elements by dividing the size of split_payload_2d_array by its first element
        for (int j = 0; j < (number_of_payload_elements - 1); i++) {                // iterate over all the elements of payload !!!except the reassembly marker!!!
          Serial.print(F("payload array index :")); // each array index points to 8 bits
          Serial.print(i);
          Serial.print(F(" contents: 0b"));                     // you can manually decode this output by following the packing order of encodeRadioDetails
          Serial.println(split_payload_2d_array[i][j], BIN);    // print the payload's value in binary, 8 bits, 0b00000000
        }
      } else {
        Serial.println(F("Transmission failed or timed out")); // payload was not delivered
      }
      // to make this example readable in the serial monitor
      delay(60000);  // slow transmissions down by 1 minute
    }
  } else {
    // This device is a RX node
    static uint8_t reassembly_buffer[40] = {0}; // place to store encoded_details
    static bool message_one_received = false;     // message sentinel
    static bool message_two_received = false;     // message sentinel
    uint8_t pipe;
    if (radio.available(&pipe)) {             // is there a payload? get the pipe number that recieved it
      uint8_t bytes = radio.getPayloadSize(); // get the size of the payload
      radio.read(&payload, bytes);            // fetch payload from FIFO
      Serial.print(F("Received "));
      Serial.print(bytes);                    // print the size of the payload
      Serial.print(F(" bytes on pipe "));
      Serial.print(pipe);                     // print the pipe number
      Serial.println(F("; received payload represented in binary (base2):\n"));
      for (int i = 0; i < (bytes - 1); i++) {       // iterate over the entire received payload !!!except for the reassembly marker!!!
        Serial.print(F("payload array index :"));   // each array index points to 8 bits
        Serial.print(i);
        Serial.print(F(" contents: 0b"));     // you can manually decode this output by following the packing order of encodeRadioDetails
        Serial.println(payload[i], BIN);      // print the payload's value in binary, 8 bits, 0b00000000

        //reassemble payload
        if (payload[20] == 99)   // first message array elements
        {
          reassembly_buffer[i] = payload[i];
          message_one_received = true;
        }
        if (payload[20] == 101)  // second message array elements
        {
          reassembly_buffer[i + 20] = payload[i];
          message_two_received = true;
        }
      }

      if (message_one_received == true && message_two_received == true) // we have both pieces of the message, time to reassemble
      {
        char debugging_information[870] = {'\0'};                   // char buffer to store output
        radio.decodeRadioDetails(debugging_information, reassembly_buffer);   // decode the payload and output debugging_information
        Serial.println(debugging_information);                      // display debugging information

        //reinitialize message sentinels and reassembly_buffer
        message_one_received = false;
        message_two_received = false;
        for (int i = 0; i < (sizeof(reassembly_buffer) / sizeof(reassembly_buffer[0])); i++)
        {
          reassembly_buffer[i] = 0;
        }
      }
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
