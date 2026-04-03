/*
    Copyright (c) 2007 Stefan Engelke <mbox@stefanengelke.de>
    Portions Copyright (C) 2011 Greg Copeland

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#ifndef NRF24L01_H_
#define NRF24L01_H_

#include <stdint.h>

namespace nRF24L01 {

/* Memory Map */
constexpr uint8_t NRF_CONFIG   = 0x00;
constexpr uint8_t EN_AA        = 0x01;
constexpr uint8_t EN_RXADDR    = 0x02;
constexpr uint8_t SETUP_AW     = 0x03;
constexpr uint8_t SETUP_RETR   = 0x04;
constexpr uint8_t RF_CH        = 0x05;
constexpr uint8_t RF_SETUP     = 0x06;
constexpr uint8_t NRF_STATUS   = 0x07;
constexpr uint8_t OBSERVE_TX   = 0x08;
constexpr uint8_t CD           = 0x09;
constexpr uint8_t RX_ADDR_P0   = 0x0A;
constexpr uint8_t RX_ADDR_P1   = 0x0B;
constexpr uint8_t RX_ADDR_P2   = 0x0C;
constexpr uint8_t RX_ADDR_P3   = 0x0D;
constexpr uint8_t RX_ADDR_P4   = 0x0E;
constexpr uint8_t RX_ADDR_P5   = 0x0F;
constexpr uint8_t TX_ADDR      = 0x10;
constexpr uint8_t RX_PW_P0     = 0x11;
constexpr uint8_t RX_PW_P1     = 0x12;
constexpr uint8_t RX_PW_P2     = 0x13;
constexpr uint8_t RX_PW_P3     = 0x14;
constexpr uint8_t RX_PW_P4     = 0x15;
constexpr uint8_t RX_PW_P5     = 0x16;
constexpr uint8_t FIFO_STATUS  = 0x17;
constexpr uint8_t DYNPD        = 0x1C;
constexpr uint8_t RF24_FEATURE = 0x1D;

/* Bit Mnemonics */
constexpr uint8_t MASK_RX_DR  = 6;
constexpr uint8_t MASK_TX_DS  = 5;
constexpr uint8_t MASK_MAX_RT = 4;
constexpr uint8_t EN_CRC      = 3;
constexpr uint8_t CRCO        = 2;
constexpr uint8_t PWR_UP      = 1;
constexpr uint8_t PRIM_RX     = 0;
constexpr uint8_t ENAA_P5     = 5;
constexpr uint8_t ENAA_P4     = 4;
constexpr uint8_t ENAA_P3     = 3;
constexpr uint8_t ENAA_P2     = 2;
constexpr uint8_t ENAA_P1     = 1;
constexpr uint8_t ENAA_P0     = 0;
constexpr uint8_t ERX_P5      = 5;
constexpr uint8_t ERX_P4      = 4;
constexpr uint8_t ERX_P3      = 3;
constexpr uint8_t ERX_P2      = 2;
constexpr uint8_t ERX_P1      = 1;
constexpr uint8_t ERX_P0      = 0;
constexpr uint8_t AW          = 0;
constexpr uint8_t ARD         = 4;
constexpr uint8_t ARC         = 0;
constexpr uint8_t PLL_LOCK    = 4;
constexpr uint8_t CONT_WAVE   = 7;
constexpr uint8_t RF_DR       = 3;
constexpr uint8_t RF_PWR      = 6;
constexpr uint8_t RX_DR       = 6;
constexpr uint8_t TX_DS       = 5;
constexpr uint8_t MAX_RT      = 4;
constexpr uint8_t RX_P_NO     = 1;
constexpr uint8_t TX_FULL     = 0;
constexpr uint8_t PLOS_CNT    = 4;
constexpr uint8_t ARC_CNT     = 0;
constexpr uint8_t TX_REUSE    = 6;
constexpr uint8_t FIFO_FULL   = 5;
constexpr uint8_t TX_EMPTY    = 4;
constexpr uint8_t RX_FULL     = 1;
constexpr uint8_t RX_EMPTY    = 0;
constexpr uint8_t DPL_P5      = 5;
constexpr uint8_t DPL_P4      = 4;
constexpr uint8_t DPL_P3      = 3;
constexpr uint8_t DPL_P2      = 2;
constexpr uint8_t DPL_P1      = 1;
constexpr uint8_t DPL_P0      = 0;
constexpr uint8_t EN_DPL      = 2;
constexpr uint8_t EN_ACK_PAY  = 1;
constexpr uint8_t EN_DYN_ACK  = 0;

/* Instruction Mnemonics */
constexpr uint8_t R_REGISTER    = 0x00;
constexpr uint8_t W_REGISTER    = 0x20;
constexpr uint8_t REGISTER_MASK = 0x1F;
constexpr uint8_t ACTIVATE      = 0x50;
constexpr uint8_t R_RX_PL_WID   = 0x60;
constexpr uint8_t R_RX_PAYLOAD  = 0x61;
constexpr uint8_t W_TX_PAYLOAD  = 0xA0;
constexpr uint8_t W_ACK_PAYLOAD = 0xA8;
constexpr uint8_t FLUSH_TX      = 0xE1;
constexpr uint8_t FLUSH_RX      = 0xE2;
constexpr uint8_t REUSE_TX_PL   = 0xE3;
constexpr uint8_t RF24_NOP      = 0xFF;

/* Non-P omissions */
constexpr uint8_t LNA_HCURR = 0;

/* P model memory Map */
constexpr uint8_t RPD                 = 0x09;
constexpr uint8_t W_TX_PAYLOAD_NO_ACK = 0xB0;

/* P model bit Mnemonics */
constexpr uint8_t RF_DR_LOW   = 5;
constexpr uint8_t RF_DR_HIGH  = 3;
constexpr uint8_t RF_PWR_LOW  = 1;
constexpr uint8_t RF_PWR_HIGH = 2;

} // namespace nRF24L01

#endif // NRF24L01_H_
