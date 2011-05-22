/*
 Copyright (C) 2011 James Coliz, Jr. <maniacbug@ymail.com>
 
 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 2 as published by the Free Software Foundation.
 */

/**
 * Example RF Radio Ping Star Group with Relay 
 *
 * This sketch is a very complex example of using the RF24 library for Arduino.  
 * Deploy this on any number of nodes to create a basic mesh network.  I have
 * tested this on 6 nodes, but it should work on many more.  Although if there
 * are a lot more nodes, increase the ping_interval, or the base will be
 * overwhelmed!
 *
 * There are three different roles a node can be:
 *
 * @li Leaf.  Leaf nodes send a ping to the base unit, and wait for a pong in 
 * return
 * 
 * @li Relay.  Relay nodes do the same as a leaf node, AND they relay pings
 * from leaf nodes toward the base, and relay pongs toward the leaves.
 *
 * @li Base.  One node is the base station, which receives pings, and sends
 * a pong back out.
 *
 * The address of each node is a number from 0 to n (the # of known nodes).
 * It is set in EEPROM.  To change a node's address, send the character code
 * for that address.  e.g. send the character '5' to set address 5.
 *
 * The role is determined from the topology table.  Leafs have no children.
 * The base node has no parent.  Relays have parents and children.
 */
 
#include <SPI.h>
#include <EEPROM.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

// Set up nRF24L01 radio on SPI bus plus pins 8 & 9

RF24 radio(8,9);

//
// Topology
//

struct node_info
{
  uint64_t talking_pipe; // Pipe used to talk to parent node
  uint64_t listening_pipe; // Pipe used to listen to parent node
  uint8_t parent_node; // Address of parent node
};

const node_info topology[] =
{
  { 0x0000000000LL, 0x0000000000LL,-1 }, // Base
  { 0xF0F0F0F0E1LL, 0x3A3A3A3AE1LL, 0 }, // Relay
  { 0xF0F0F0F0D2LL, 0x3A3A3A3AD2LL, 1 }, // Leaf
  { 0xF0F0F0F0C3LL, 0x3A3A3A3AC3LL, 1 }, // Leaf
  { 0xF0F0F0F0B4LL, 0x3A3A3A3AB4LL, 1 }, // Leaf
  { 0xF0F0F0F0A5LL, 0x3A3A3A3AA5LL, 0 }, // Leaf, direct to Base
};
const short num_nodes = sizeof(topology)/sizeof(node_info);

/**
 * Find where to send a message to reach the target node
 *
 * Given the @p target_node, find the child or parent of
 * the @p current_node which will relay messages for the target.
 *
 * This is needed in a multi-hop system where the @p current_node
 * is not adjacent to the @p target_node in the topology
 */
uint8_t find_node( uint8_t current_node, uint8_t target_node )
{
  uint8_t out_node = target_node;
  bool found_target = false;
  while ( ! found_target )
  {
    if ( topology[out_node].parent_node == current_node )
    {
      found_target = true; 
    }
    else
    {
      out_node = topology[out_node].parent_node;

      // If we've made it all the way back to the base without finding
      // common lineage with the to_node, we will just send it to our parent
      if ( out_node == 0 || out_node == -1 )
      {
	out_node = topology[current_node].parent_node;
	found_target = true;
      }
    }
  }
  return out_node;
}

//
// Role management
//
// Set up role.  This sketch uses the same software for all the nodes
// in this system.  Doing so greatly simplifies testing.  Role is
// determined by the topology table.
//

// The various roles supported by this sketch
typedef enum { role_invalid = 0, role_base, role_relay, role_leaf } role_e;

// The debug-friendly names of those roles
const char* role_friendly_name[] = { "invalid", "Base", "Relay", "Leaf" };

// The role of the current running sketch
role_e role;

//
// Address management
//

// Where in EEPROM is the address stored?
const uint8_t address_at_eeprom_location = 0;

// What flag value is stored there so we know the value is valid?
const uint8_t valid_eeprom_flag = 0xdf;

// What is our address (SRAM cache of the address from EEPROM)
// This is an index into the topology[] table above
uint8_t node_address = -1;

//
// Payload
//

struct payload_t
{
  uint8_t from_node;
  uint8_t to_node;
  uint16_t id;
  unsigned long time;
  
  static uint16_t next_id;
  
  payload_t(void) {}
  payload_t(uint8_t _from, uint8_t _to, const unsigned long& _time): from_node(_from), to_node(_to), id(next_id++), time(_time) {}
};

uint16_t payload_t::next_id;

void payload_printf(const char* name, const payload_t& pl)
{
  printf("%s Payload from:%u to:%u id:%u time:%lu",name,pl.from_node,pl.to_node,pl.id,pl.time);
}

//
// Setup/loop shared statics
//

static unsigned long last_ping_sent_at;
static bool waiting_for_pong = false;
static short consecutive_timeouts;
const unsigned long ping_interval = 2000; // ms
const unsigned long pong_timeout = 250; // ms
const unsigned long ping_phase_shift = 100; // ms
const short timeout_shift_threshold = 3;

// Space to track the last packet we received from each node, useful
// for tracking lost packets
static uint16_t last_id_received[num_nodes];

void setup(void)
{
  //
  // Address
  //

  // Look for the token in EEPROM to indicate the following value is
  // a validly set node address 
  if ( EEPROM.read(address_at_eeprom_location) == valid_eeprom_flag )
  {
    // Read the address from EEPROM
    uint8_t reading = EEPROM.read(address_at_eeprom_location+1);

    // If it is in a valid range for node addresses, it is our
    // address.
    if ( reading <= 5 )
      node_address = reading;
  } 
  
  //
  // Role
  //

  // Role is determined by address.
  if ( node_address != -1 )
  {
    // Node #0 is the base, by definition
    if ( node_address == 0 )
      role = role_base;
    else
    {
      // Otherwise, it is probably a leaf node
      role = role_leaf;

      // If there are any nodes in the topology table which consider this
      // a parent, then we are a relay.
      int i = num_nodes;
      while (i--)
      {
      	if ( topology[i].parent_node == node_address )
	{
	  role = role_relay;
	  break;
	}
      }
    }
  }

  //
  // Print preamble
  //
  
  Serial.begin(9600);
  printf_begin();
  printf("\n\rRF24/examples/starping_relay/\n\r");
  printf("ROLE: %s\n\r",role_friendly_name[role]);
  printf("ADDRESS: %i\n\r",node_address);

  //
  // Setup and configure rf radio
  //
  
  radio.begin();

  //
  // Open pipes to other nodes for communication
  //
  
  // Each leaf node has a talking pipe that it will ping into, and a listening 
  // pipe that it will listen for the pong.  Relay nodes also do this.
  if ( role == role_leaf )
  {
    // Write on our talking pipe
    radio.openWritingPipe(topology[node_address].talking_pipe);
    
    // Listen on our listening pipe 
    radio.openReadingPipe(1,topology[node_address].listening_pipe);
  }
 
  // Relay nodes have a special function.  They open their listening pipe on pipe
  // #0.  This will get over-written every time we open a writing pipe.  So
  // Remember to re-open the reading pipe whenever we start to listen again.
  if ( role == role_relay )
  { 
    // Write on our talking pipe
    radio.openWritingPipe(topology[node_address].talking_pipe);
    
    // Listen on our listening pipe 
    radio.openReadingPipe(0,topology[node_address].listening_pipe);
  }

  // The base and relay nodes listen on all their children node's talking pipes
  // and sends the pong back on the child node's specific listening pipe.
  if ( role == role_base || role == role_relay )
  {
    // First child listening pipe is #1
    uint8_t current_pipe = 1;
  
    // The topology table tells us who our children are
    int i = num_nodes;
    while (i--)
    {
      if ( topology[i].parent_node == node_address )
	radio.openReadingPipe(current_pipe++,topology[i].talking_pipe);
    }
  }
  
  //
  // Start listening
  //
  
  radio.startListening();
  
  //
  // Dump the configuration of the rf unit for debugging
  //
  
  radio.printDetails();

  //
  // Prompt the user to assign a node address if we don't have one
  //

  if ( role == role_invalid )
  {
    printf("\n\r*** NO NODE ADDRESS ASSIGNED *** Send 0 through 5 to assign an address\n\r");
  }
}

void ping_if_ready(void);
void handle_pong(const payload_t& payload);
void check_pong_timeout(void);

void loop(void)
{
  //
  // Leaf role.  Repeatedly send the current time
  //
  
  if ( role == role_leaf ) 
  {
    ping_if_ready();
    check_pong_timeout();

    // Did we get a pong?
    if ( radio.available() )
    {
      // Dump the payloads until we've gotten everything
      payload_t payload;
      boolean done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &payload, sizeof(payload_t) );

	handle_pong(payload);
      }  
    }
  }
  
  //
  // Relay role.  Forward packets to the appropriate destination
  //

  if ( role == role_relay )
  {
#if 1    
    // Relay role is ALSO a ping sender!!
    ping_if_ready();    
    check_pong_timeout();
#endif
    // if there is data ready
    uint8_t pipe_num;
    if ( radio.available(&pipe_num) )
    {
      // Dump the payloads until we've gotten everything
      payload_t payload;
      boolean done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &payload, sizeof(payload_t) );

        // Is this for us?
        if ( payload.to_node == node_address )
	{
	  handle_pong(payload);
	}
	else
	{
	  // Relay it
	  
	  // Spew it
	  printf("%lu ",millis());
	  payload_printf("RELAY",payload);
	  printf(" on pipe %u. ",pipe_num);

	  // Which pipe should we use to get the message to the "to_node"?
	  // We need to find a node who is OUR CHILD that either IS the to_node
	  // or has the to_node as one of ITS children.  Failing that, we'll just
	  // send it back to the parent to deal with.
	  uint8_t out_node = find_node(node_address,payload.to_node);

	  // First, stop listening so we can talk
	  radio.stopListening();

	  // If this node is our child, we talk on it's listening pipe.
	  uint64_t out_pipe;
	  if ( topology[out_node].parent_node == node_address )
	    out_pipe = topology[out_node].listening_pipe;
	  
	  // Otherwise, it's our parent so we talk on OUR talking pipe
	  else
	    out_pipe = topology[node_address].talking_pipe;
	  
	  // Open the correct pipe for writing.  
	  radio.openWritingPipe(out_pipe);
      
      	  // Send the payload back out 
	  bool ok = radio.write( &payload, sizeof(payload_t) );
      
      	  // Debug spew 
	  uint16_t pipe_id = out_pipe & 0xffff;
	  printf("OUT on pipe %04x %s.\n\r",pipe_id,ok?"ok":"failed");
	  
	  // Now, resume listening so we catch the next packets.
	  radio.startListening();
	}
      }
    }
  }
  
  //
  // Base role.  Receive each packet, dump it out, and send it back
  //
  
  if ( role == role_base )
  {
    // if there is data ready
    uint8_t pipe_num;
    if ( radio.available(&pipe_num) )
    {
      // Dump the payloads until we've gotten everything
      payload_t ping;
      boolean done = false;
      while (!done)
      {
        // Fetch the payload, and see if this was the last one.
        done = radio.read( &ping, sizeof(payload_t) );
  
        // Spew it
	printf("%lu ",millis());
	payload_printf("PING",ping);
	printf(" on pipe %u. ",pipe_num);

	// Track the packets lost since we last heard from this node
	// Packet loss is generally a sign of poor system health
	uint16_t* last_id_ptr = &last_id_received[ping.from_node];
	if ( *last_id_ptr && ping.id > *last_id_ptr )
	{
	  uint16_t lost = ping.id - *last_id_ptr - 1;
	  if ( lost )
	    printf(" lost %u",lost);
	}
	*last_id_ptr = ping.id;
      }
      
      // First, stop listening so we can talk
      radio.stopListening();
      
      // Construct the return payload (pong)
      payload_t pong(node_address,ping.from_node,ping.time);

      // Find the correct pipe for writing.  We can only talk on one of our
      // direct children's listening pipes.  If the to_node is further out,
      // it will get relayed.
      uint8_t out_node = find_node(node_address,pong.to_node);

      // Open the correct pipe for writing
      radio.openWritingPipe(topology[out_node].listening_pipe);

      // Retain the low 2 bytes to identify the pipe for the spew
      uint16_t pipe_id = topology[out_node].listening_pipe & 0xffff;
            
      // Send the final one back.
      bool ok = radio.write( &pong, sizeof(payload_t) );  
      payload_printf(" ...PONG",pong);
      printf(" on pipe %04x %s.\n\r",pipe_id,ok?"ok":"failed");
      
      // Now, resume listening so we catch the next packets.
      radio.startListening();
    }
  }
  

  //
  // Listen for serial input, which is how we set the address
  //
  if (Serial.available())
  {
    // If the character on serial input is in a valid range...
    char c = Serial.read();
    if ( c >= '0' && c <= '5' )
    {
      // It is our address
      EEPROM.write(address_at_eeprom_location,valid_eeprom_flag);
      EEPROM.write(address_at_eeprom_location+1,c-'0');

      // And we are done right now (no easy way to soft reset)
      printf("\n\rManually reset address to: %c\n\rPress RESET to continue!",c);
      while(1);
    }
  }
}

void ping_if_ready(void)
{
  // Is it time to ping again?
  unsigned long now = millis();
  if ( now - last_ping_sent_at >= ping_interval )
  {
    last_ping_sent_at = now;
    waiting_for_pong = true;

    // First, stop listening so we can talk.
    radio.stopListening();

    // Write on our talking pipe.  The relay has to do this every time, because
    // we ALSO use pipe 0 as a listening pipe.
    radio.openWritingPipe(topology[node_address].talking_pipe);
    
    // Take the time, and send it to the base.  This will block until complete
    payload_t ping(node_address,0,millis());

    // Print details.
    printf("%lu ",millis());
    payload_printf(">PING",ping);
    bool ok = radio.write( &ping, sizeof(payload_t) );  
    if (ok)
      printf(" ok\n\r");
    else
      printf(" failed\n\r");

    // Now, continue listening
    radio.startListening();
  }
}

void handle_pong(const payload_t& payload)
{
  // Not waiting anymore, got one.
  waiting_for_pong = false;
  consecutive_timeouts = 0;

  // Print details.
  printf("%lu ",millis());
  payload_printf(">PONG",payload);
  printf(" Round-trip delay: %lu\n\r",millis()-payload.time);
}

void check_pong_timeout(void)
{
  // Have we timed out waiting for our pong?
  if ( waiting_for_pong && ( millis() - last_ping_sent_at > pong_timeout ) )
  {
    // Not waiting anymore, timed out.
    waiting_for_pong = false;

    // Timeouts usually happen because of collisions with other nodes
    // getting a pong just as we are trying to send a ping.  The best thing
    // to do right now is offset our ping timing to search for a slot
    // that's not occupied.
    //
    // Only do this after getting a few timeouts, so we aren't always skittishly
    // moving around the cycle.
    if ( ++consecutive_timeouts > timeout_shift_threshold )
      last_ping_sent_at += ping_phase_shift; 

    // Print details
    printf("%lu ",millis());
    printf("TIMED OUT.\n\r");
  }
}
// vim:ai:cin:sts=2 sw=2 ft=cpp
