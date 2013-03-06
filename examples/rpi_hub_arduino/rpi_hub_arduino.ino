/*
 This program sends readings from four or more sensor readings and appends
 addr data pipes to the beginning of the payloads. 

 The receiver is a RPi accepting 6 pipes and display received payload to the screen

 RPi receiver will return the receive payload for sender to calculate the rtt
 if the string compared matched

 Max payload size is 32 bytes

Forked RF24 at github :-
https://github.com/stanleyseow/RF24

 Date : 5/03/2013

 Written by Stanley Seow
 stanleyseow@gmai.com
*/

#include <LiquidCrystal.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define RF_SETUP 0x17

LiquidCrystal lcd(10, 7, 3, 4, 5, 6);
// Make way for the SPI pins
// 10 -> LCD 4
// 7  -> LCD 6
// 3  -> LCD 11
// 4  -> LCD 12
// 5  -> LCD 13
// 6  -> LCD 14

// Set up nRF24L01 radio on SPI pin for CE, CSN
RF24 radio(8,9);

// Radio pipe addresses for the 2 nodes to communicate.
// const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0xF0F0F0F0D2LL };
// const uint64_t pipes[2] = { 0xF0F0F0F0E2LL, 0xF0F0F0F0D2LL };
// const uint64_t pipes[2] = { 0xF0F0F0F0E3LL, 0xF0F0F0F0D2LL };
 const uint64_t pipes[2] = { 0xF0F0F0F0F1LL, 0xF0F0F0F0D2LL };
// const uint64_t pipes[2] = { 0xF0F0F0F0F2LL, 0xF0F0F0F0D2LL };
// Pipe0 is F0F0F0F0D2 ( same as reading pipe )

char receivePayload[32];
int counter=0;
int timeoutTimer = 500;
int loops = 0;

void setup(void)
{

  // Setup LCD
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Ard Remote Node 2");
  
  Serial.begin(57600);
  
  printf_begin();
  printf("Sending nodeID & 4 sensor data\n\r");

  radio.begin();

  // Enable this seems to work better
  radio.enableDynamicPayloads();
  radio.setAutoAck(1);

  // Setup default radio settings  
  
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(76);
  radio.setCRCLength(RF24_CRC_16);
  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]); 
  radio.openReadingPipe(1,pipes[1]); 

  // Send only, ignore listening mode
  //radio.startListening();

  // Dump the configuration of the rf unit for debugging
  radio.printDetails(); 
  delay(1000); 
}

void loop(void)
{
  int Data1,Data2,Data3,Data4 = 0;
  char temp[5];
  char nodeID[12];
  bool timeout=0;
  int timeout_timer = 500;

  // Use the last 2 pipes address as nodeID  
  sprintf(nodeID,"%X",pipes[0]);
  
  char outBuffer[31]=""; // Clear the outBuffer before every loop
  unsigned long send_time, rtt = 0;
    
    // Get readings from sensors
    Data1 = counter++;
    Data2 = analogRead(0);
    Data3 = analogRead(1);
    Data4 = random(0,1000);
    
    if ( counter > 999 ) counter = 0;

    // Append nodeID to the beginning of the payload    
    strcat(outBuffer,nodeID);
    strcat(outBuffer,",");
    
    // Convert int to strings and append with zeros if number smaller than 3 digits
    // 000 to 999
    
    sprintf(temp,"%03d",Data1);  
    strcat(outBuffer,temp);
    
    strcat(outBuffer,",");
    
    sprintf(temp,"%04d",Data2);
    strcat(outBuffer,temp);
    
    strcat(outBuffer,",");

    sprintf(temp,"%04d",Data3);
    strcat(outBuffer,temp);
   
    strcat(outBuffer,",");
   
    sprintf(temp,"%03d",Data4);
    strcat(outBuffer,temp); 
    
    // End string with 0
    // strcat(outBuffer,0);
            
    printf("outBuffer: %s len: %d\n\r",outBuffer, strlen(outBuffer));
    
    //lcd.clear();
    //lcd.setCursor(0,0);

    lcd.setCursor(2,0);
    lcd.print(outBuffer);

    send_time = millis();
    
    // Stop listening and write to radio 
    radio.stopListening();
    
    // Send to hub
    if ( radio.write( outBuffer, strlen(outBuffer)) ) {
       printf("Send successful\n\r"); 
       lcd.setCursor(0,0);
       lcd.print("1:");
    }
    else {
       printf("Send failed\n\r");
       lcd.setCursor(0,0);
       lcd.print("0:");  
    }
  
    radio.startListening();
    delay(20);  

    lcd.setCursor(0,1);
    lcd.print("R:              ");
  
  while ( radio.available() && !timeout ) {

         uint8_t len = radio.getDynamicPayloadSize();
         radio.read( receivePayload, len); 
         // receive_payload[len] = 0;
         Serial.print("inBuffer:  ");
         Serial.println(receivePayload);
         
         lcd.setCursor(2,1);
         lcd.print(receivePayload);
        
         // Compare receive payload with outBuffer        
         if ( ! strcmp(outBuffer, receivePayload) ) {
             rtt = millis() - send_time;
             
             // Send beep to Pin 2
             digitalWrite(2,HIGH);
           
             lcd.setCursor(0,1);
             lcd.print("R:              ");
             
             lcd.setCursor(2,1);
             lcd.print(rtt);
             Serial.println(rtt);       
         }       
    
    // Check for timeout and exit the while loop
    if ( millis() - send_time > timeout_timer ) {
         lcd.setCursor(2,1);
         lcd.print("Timeout");
         Serial.println("Timeout!!!");
         timeout = 1;
         loops = 0;
     }          
      Serial.print(loops++);
      delay(10);
   } // End while  
 
    
    Serial.flush();
    delay(250);
    digitalWrite(2,LOW);
    
  }





