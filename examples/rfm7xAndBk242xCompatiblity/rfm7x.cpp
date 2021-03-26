//**************************************************************
//Compiler          : GCC
//Author            : jnk0le@hotmail.com
//                    https://github.com/jnk0le
//License           : MIT
//**************************************************************

#if defined(__AVR_ARCH__)
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <util/atomic.h>

#define CRITICAL_SECTION ATOMIC_BLOCK(ATOMIC_RESTORESTATE)

#else
#include <cmsis_device.h>

// workaround for ATOMIC_BLOCK
__attribute__((always_inline)) inline int __int_disable_irq(void)
{
  int primask;
  asm volatile("mrs %0, PRIMASK\n"
               : "=r"(primask));
  asm volatile("cpsid i\n");
  return primask & 1;
}

__attribute__((always_inline)) inline void __int_restore_irq(int* primask)
{
  if (!(*primask)) {
    asm volatile("" ::
                 : "memory");
    asm volatile("cpsie i\n");
  }
}

#define CRITICAL_SECTION for (int primask_save __attribute__((__cleanup__(__int_restore_irq))) = __int_disable_irq(), __ToDo = 1; __ToDo; __ToDo = 0)

#endif

#include "rfm7x.h"
#include <Arduino.h>
#include <stdint.h>

#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
const __flash uint8_t rfm7x_init_struct[] =
#else
const uint8_t rfm7x_init_struct[] = // generic for all architectures // table will be placed in SRAM if your mcu doesn't have unified memory space (flash + ram)
#endif
{
  ////////////////////////////////////////// bank 1 initialization registers //////////////////////////////////////////

  RFM7x_BANK1_REG0,
  RFM7x_BANK1_REG1,
  RFM7x_BANK1_REG2,
  RFM7x_BANK1_REG3,
  RFM7x_BANK1_REG4,
  RFM7x_BANK1_REG5,
  RFM7x_BANK1_REG6,
  RFM7x_BANK1_REG7,
  RFM7x_BANK1_REG8,
  RFM7x_BANK1_REG9,
  RFM7x_BANK1_REGA,
  RFM7x_BANK1_REGB,
  RFM7x_BANK1_REGC,
  RFM7x_BANK1_REGD,
  RFM7x_BANK1_RAMP_CURVE,

  ////////////////////////////////////////// bank 0 initialization registers //////////////////////////////////////////
#ifndef RFM7x_DO_NOT_INITIALIZE_BANK0
  RFM7x_BANK0_REG_CONFIG, // PTX/PRX mode - doesn't care, it will be set later with rest commands
  RFM7x_BANK0_REG_EN_AA,
  RFM7x_BANK0_REG_EN_RXADDR,
  RFM7x_BANK0_REG_SETUP_AW,
  RFM7x_BANK0_REG_SETUP_RETR,
  RFM7x_BANK0_REG_RF_CH,
  RFM7x_BANK0_REG_RF_SETUP,

  RFM7x_BANK0_REG_STATUS, // status register that have to be initialized - not documented
  RFM7x_BANK0_REG_OBSERVE_TX, // status register that have to be initialized - not documented
  RFM7x_BANK0_REG_CD, // status register that have to be initialized - not documented

#ifndef RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS
  0xE7, // pipe0 default address // just dummy byte to fill space for loading whole bank0 in one-run // single byte write might be undefined
  0xC2, // pipe1 default address // just dummy byte to fill space for loading whole bank0 in one-run // single byte write might be undefined

  RFM7x_PIPE2_RX_ADDRESS, // pipe 2 address // LSB only
  RFM7x_PIPE3_RX_ADDRESS, // pipe 3 address // LSB only
  RFM7x_PIPE4_RX_ADDRESS, // pipe 4 address // LSB only
  RFM7x_PIPE5_RX_ADDRESS, // pipe 5 address // LSB only
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_RX_PAYLOAD_LEN_REGS) && !defined(RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS)
  0xE7, // TX default address // just dummy byte to fill space for loading whole bank0 in one-run // single byte write might be undefined

  RFM7x_PIPE0_RX_PAYLOAD_LEN, // pipe 0 - payload length // 0 equals to dynamic payload ??
  RFM7x_PIPE1_RX_PAYLOAD_LEN, // pipe 1 - payload length // 0 equals to dynamic payload ??
  RFM7x_PIPE2_RX_PAYLOAD_LEN, // pipe 2 - payload length // 0 equals to dynamic payload ??
  RFM7x_PIPE3_RX_PAYLOAD_LEN, // pipe 3 - payload length // 0 equals to dynamic payload ??
  RFM7x_PIPE4_RX_PAYLOAD_LEN, // pipe 4 - payload length // 0 equals to dynamic payload ??
  RFM7x_PIPE5_RX_PAYLOAD_LEN, // pipe 5 - payload length // 0 equals to dynamic payload ??

  RFM7x_BANK0_REG_FIFO_STATUS, // status register that have to be initialized - not documented
#endif

  //0x00, // dummy
  //0x00, // dummy
  //0x00, // dummy
  //0x00, // dummy

  //RFM7x_BANK0_REG_DYNPD,
  //RFM7x_BANK0_REG_FEATURE,

#if defined(RFM7x_TX_ADDRESS) && !defined(RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS)
  RFM7x_TX_ADDRESS,
#endif
#ifdef RFM7x_PIPE0_RX_ADDRESS
  RFM7x_PIPE0_RX_ADDRESS,
#endif
#ifdef RFM7x_PIPE1_RX_ADDRESS
  RFM7x_PIPE1_RX_ADDRESS,
#endif

#endif //RFM7x_DO_NOT_INITIALIZE_BANK0
};

void rfm7x_init(void)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
    const __flash uint8_t* p_init_struct = rfm7x_init_struct;
#else
    const uint8_t* p_init_struct = rfm7x_init_struct;
#endif

    if ((0x80 & rfm7x_reg_read(RFM7x_REG_STATUS)) == 0)
      rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // select bank 1

    for (uint_fast8_t i = 0; i < RFM7x_BANK1_ENTRIES; i++) {
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
      if (i != RFM7x_BANK1_ENTRIES - 1) {
        rfm7x_reg_buff_write_P(i, p_init_struct, 4);
        p_init_struct += 4;
      } else {
        rfm7x_reg_buff_write_P(i, p_init_struct, 11);
        p_init_struct += 11;
      }
#else
      if (i != RFM7x_BANK1_ENTRIES - 1) {
        rfm7x_reg_buff_write(i, (uint8_t*)p_init_struct, 4);
        p_init_struct += 4;
      } else {
        rfm7x_reg_buff_write(i, (uint8_t*)p_init_struct, 11);
        p_init_struct += 11;
      }
#endif
    }

    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0

    rfm7x_reg_write(RFM7x_REG_FEATURE, 0x01); // check if "feature register" is writable before (de)activating it

    if (!rfm7x_reg_read(RFM7x_REG_FEATURE))
      rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x73); // activate feature register if not activated

    for (uint_fast8_t i = 0; i < RFM7x_BANK0_ENTRIES; i++) {
      rfm7x_reg_write(i, *p_init_struct++);
    }

#if defined(RFM7x_TX_ADDRESS) || defined(RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS)
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
    rfm7x_reg_buff_write_P(RFM7x_REG_TX_ADDR, p_init_struct, RFM7x_TX_ADDRESS_SIZE);
#else
    rfm7x_reg_buff_write(RFM7x_REG_TX_ADDR, (uint8_t*)p_init_struct, RFM7x_TX_ADDRESS_SIZE);
#endif

#ifndef RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS
    p_init_struct += RFM7x_TX_ADDRESS_SIZE;
#endif
#endif

#ifdef RFM7x_PIPE0_RX_ADDRESS
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
    rfm7x_reg_buff_write_P(RFM7x_REG_RX_ADDR_P0, p_init_struct, RFM7x_PIPE0_RX_ADDRESS_SIZE);
#else
    rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P0, (uint8_t*)p_init_struct, RFM7x_PIPE0_RX_ADDRESS_SIZE);
#endif

    p_init_struct += RFM7x_PIPE0_RX_ADDRESS_SIZE;
#endif

#ifdef RFM7x_PIPE1_RX_ADDRESS
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
    rfm7x_reg_buff_write_P(RFM7x_REG_RX_ADDR_P1, p_init_struct, RFM7x_PIPE1_RX_ADDRESS_SIZE);
#else
    rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P1, (uint8_t*)p_init_struct, RFM7x_PIPE1_RX_ADDRESS_SIZE);
#endif
#endif

#ifdef RFM7x_DO_NOT_INITIALIZE_BANK0
    rfm7x_reg_write(RFM7x_REG_STATUS, RFM7x_BANK0_REG_STATUS);
    rfm7x_reg_write(RFM7x_REG_OBSERVE_TX, RFM7x_BANK0_REG_OBSERVE_TX);
    rfm7x_reg_write(RFM7x_REG_CD, RFM7x_BANK0_REG_CD);
    rfm7x_reg_write(RFM7x_REG_FIFO_STATUS, RFM7x_BANK0_REG_FIFO_STATUS);

#elif defined(RFM7x_DO_NOT_INITIALIZE_RX_PAYLOAD_LEN_REGS) || defined(RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS)
    rfm7x_reg_write(RFM7x_REG_FIFO_STATUS, RFM7x_BANK0_REG_FIFO_STATUS);
#endif

    rfm7x_reg_write(RFM7x_REG_DYNPD, RFM7x_BANK0_REG_DYNPD);
    rfm7x_reg_write(RFM7x_REG_FEATURE, RFM7x_BANK0_REG_FEATURE);
  }
}

#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
const __flash uint8_t rfm7x_REG4_toggle_struct[] =
#else
const uint8_t rfm7x_REG4_toggle_struct[] =
#endif
{
  0x06 | RFM7x_BANK1_REG4 // 0x06 will be or'ed with first element (bits 25,26 set)
};

void rfm7x_toggle_reg4(void) // MIGHT NOT BE THE CASE FOR BK2411/BK2412/BK5811
{
  //	one of the chinese documents (rfm73 -> rfm75 migration) says that it should be executed after every PWR_UP, not only during initialization

  // 	4. RFM75 PowerUP after the first packet of data sent unsuccessful solution
  // 	RFM75 from the POWER DOWN state to switch to POWER UP state, send the first packet is not successful, the reason
  // 	Is the PLL is not locked, the solution is as follows:
  // 	Before transmitting data normally, please follow the following procedure:
  // 	Power up = 1
  // 	Wait for 2ms
  // 	Operate the bank1 register, writing a 1 to bit 25 of register 04
  // 	Wait 20us
  // 	Operate the bank1 register, writing a 0 to bit 25 of register 04
  // 	Wait for 0.5ms.
  // 	Then normal launch.

  //	AN0008
  //	9.  Toggle REG4<25?26>, write 1 to bit25, bit 26, then write 0 to them.

#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1

#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
    rfm7x_reg_buff_write_P(0x04, rfm7x_REG4_toggle_struct, 4);
    _delay_us(20); // if not required then this function may not be required, so better to leave it here
    rfm7x_reg_buff_write_P(0x04, &rfm7x_init_struct[16], 4);
#else
    rfm7x_reg_buff_write(0x04, (uint8_t*)rfm7x_REG4_toggle_struct, 4);
    //_delay_us(20); // if not required then this function may not be required, so better to leave it here
    rfm7x_reg_buff_write(0x04, (uint8_t*)&rfm7x_init_struct[16], 4);
#endif

    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
  }
}

void rfm7x_cmd_write(uint8_t reg, uint8_t dat)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;
    rfm7x_spi_rw(reg);
    rfm7x_spi_rw(dat);
    RFM7x_CSN_HI;
  }
}

uint8_t rfm7x_cmd_read(uint8_t reg)
{
  uint8_t tmp;

#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;
    rfm7x_spi_rw(reg);
    tmp = rfm7x_spi_rw(0); // rfm7x_spi_rw(rfm7x_spi_rw())
    RFM7x_CSN_HI;
  }

  return tmp;
}

#ifdef RFM7x_USE_UNIVERSAL_SPI_BUFF_RW_FUNCTIONS
void rfm7x_cmd_buff_write(uint8_t reg, uint8_t* buff, uint8_t len)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;
    rfm7x_spi_rw(reg);
    rfm7x_buff_write(buff, len);
    RFM7x_CSN_HI;
  }
}

void rfm7x_cmd_buff_read(uint8_t reg, uint8_t* buff, uint8_t len)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;
    rfm7x_spi_rw(reg);
    rfm7x_buff_read(buff, len);
    RFM7x_CSN_HI;
  }
}
#else
void rfm7x_cmd_buff_write(uint8_t reg, uint8_t* buff, uint8_t len)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;

    rfm7x_spi_rw(reg);

    for (uint_fast8_t i = 0; i < len; i++)
      rfm7x_spi_rw(buff[i]);

    RFM7x_CSN_HI;
  }
}

void rfm7x_cmd_buff_read(uint8_t reg, uint8_t* buff, uint8_t len)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;

    rfm7x_spi_rw(reg);

    for (uint_fast8_t i = 0; i < len; i++)
      buff[i] = rfm7x_spi_rw(0);

    RFM7x_CSN_HI;
  }
}
#endif

#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH) // temporary workaround ??
void rfm7x_cmd_buff_write_P(uint8_t reg, const __flash uint8_t* buff, uint8_t len) // __memx ????
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    RFM7x_CSN_LOW;

    rfm7x_spi_rw(reg);

    for (uint_fast8_t i = 0; i < len; i++)
      rfm7x_spi_rw(buff[i]);

    RFM7x_CSN_HI;
  }
}
#endif

uint8_t rfm7x_is_present(void)
{
  uint8_t tmp1, tmp2;
  tmp1 = rfm7x_reg_read(RFM7x_REG_STATUS);
  rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53);
  tmp2 = rfm7x_reg_read(RFM7x_REG_STATUS);
  rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53);
  return (tmp1 ^ tmp2) == 0x80;
}

void rfm7x_power_up(void)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
  tmp |= 0x02; // set PWR_UP bit
  rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
}

void rfm7x_power_down(void)
{
  RFM7x_CE_LOW;

  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
  tmp &= 0xFD; // clear PWR_UP bit
  rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
}

void rfm7x_mode_receive(void)
{
  RFM7x_CE_LOW;
  uint8_t tmp;

  //tmp = rfm7x_reg_read(RFM7x_REG_STATUS);
  // handle requests here ??
  //rfm7x_reg_write(RFM7x_REG_STATUS, tmp); // clear interrupt requests

  rfm7x_reg_write(RFM7x_REG_STATUS, 0x70); // clear interrupt requests

  tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
  tmp |= 0x01; // set RX bit
  rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);

#ifdef RFM7x_FLUSH_TX_AND_RX_WHILE_SWITCHING_MODES
  rfm7x_cmd_write(RFM7x_CMD_FLUSH_TX, 0);
#endif
  rfm7x_cmd_write(RFM7x_CMD_FLUSH_RX, 0); // it have to be flushed, otherwise doesn't work

  RFM7x_CE_HI;
}

void rfm7x_mode_transmit(void)
{
  RFM7x_CE_LOW;
  uint8_t tmp;

  //tmp = rfm7x_reg_read(RFM7x_REG_STATUS);
  // handle requests here ??
  //rfm7x_reg_write(RFM7x_REG_STATUS, tmp); // clear interrupt requests

  rfm7x_reg_write(RFM7x_REG_STATUS, 0x70); // clear interrupt requests, otherwise further communication is not possible if MAX_RT is asserted

  tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);
  tmp &= 0xFE; // clear RX bit
  rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);

#ifdef RFM7x_FLUSH_TX_AND_RX_WHILE_SWITCHING_MODES
  rfm7x_cmd_write(RFM7x_CMD_FLUSH_RX, 0);
#endif
  rfm7x_cmd_write(RFM7x_CMD_FLUSH_TX, 0); // it have to be flushed, otherwise chip doesn't work

  RFM7x_CE_HI;
}

uint8_t rfm7x_receive(uint8_t* buff)
{
  uint8_t p = rfm7x_receive_next_pipe();

  if (p == 0x07)
    return 0;

  uint8_t len = rfm7x_receive_next_length();

  rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);

  return len;
}

void rfm7x_receive_nocheck(uint8_t* buff)
{
  uint8_t len = rfm7x_receive_next_length();
  rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);
}

uint8_t rfm7x_receive_p_(uint8_t* pipe, uint8_t* buff)
{
  uint8_t p = rfm7x_receive_next_pipe();

  if (p == 0x07)
    return 0;

  *pipe = p;
  uint8_t len = rfm7x_receive_next_length();

  rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);

  return len;
}

uint8_t rfm7x_receive_s(uint8_t* buff, uint8_t length)
{
  uint8_t p = rfm7x_receive_next_pipe();

  if (p == 0x07)
    return p;

  rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, length);

  return p;
}

uint8_t rfm7x_receive_f(uint8_t* buff, uint8_t* pipe, uint8_t* length)
{
  uint8_t p = rfm7x_receive_next_pipe();

  if (p == 0x07)
    return 0;

  uint8_t len = rfm7x_receive_next_length();

  *pipe = p;
  *length = len;

  rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, len);

  return 1;
}

void rfm7x_set_rssi_threshold_step(uint8_t level)
{
#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1

    RFM7x_CSN_LOW;
    rfm7x_spi_rw(0x05 | 0x20);

#if (RFM7x_MODULECHIP_USED == 2)
    uint8_t tmp;

    switch (level) {
      case 0:
        tmp = 0x00;
        break;
      case 1:
        tmp = 0x02;
        break;
      case 2:
        tmp = 0x01;
        break;
      case 3:
        tmp = 0x03;
        break;
      case 4:
        tmp = 0x08;
        break;
      case 5:
        tmp = 0x0A;
        break;
      case 6:
        tmp = 0x09;
        break;
      case 7:
        tmp = 0x0B;
        break;
      case 8:
        tmp = 0x04;
        break;
      case 9:
        tmp = 0x06;
        break;
      case 10:
        tmp = 0x05;
        break;
      case 11:
        tmp = 0x07;
        break;
      case 12:
        tmp = 0x0C;
        break;
      case 13:
        tmp = 0x0E;
        break;
      case 14:
        tmp = 0x0D;
        break;
      case 15:
        tmp = 0x0F;
        break;
      default:
        tmp = level;
        break;
    }

    rfm7x_spi_rw(tmp << 2);
#else
    rfm7x_spi_rw(level << 2);
#endif
    rfm7x_spi_rw(rfm7x_init_struct[21]);
    rfm7x_spi_rw(rfm7x_init_struct[22]);
    rfm7x_spi_rw(rfm7x_init_struct[23]);
    RFM7x_CSN_HI;

    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
  }
}

void rfm7x_set_crc_length(uint8_t len)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_CONFIG);

  tmp &= ~(RFM7x_CONFIG_EN_CRC | RFM7x_CONFIG_CRCO); // clear EN_CRC and CRCO

  if (len == 0) {
    rfm7x_reg_write(RFM7x_REG_EN_AA, 0); // Auto ACK have to be disabled before disabling CRC
    rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
  } else {
    tmp |= (RFM7x_CONFIG_EN_CRC); // set EN_CRC

    if (len & 0x02) // if 2 byte encoding scheme is selected, set CRCO
      tmp |= (RFM7x_CONFIG_CRCO);

    //rfm7x_reg_write(RFM7x_REG_EN_AA, 0x3f); //????
    rfm7x_reg_write(RFM7x_REG_CONFIG, tmp);
  }
}

void rfm7x_set_tx_pwr(uint8_t level)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);

#if (RFM7x_MODULECHIP_USED == 0) | (RFM7x_MODULECHIP_USED == 1) | (RFM7x_MODULECHIP_USED == 2) // bk2401//bk2421/bk2423

  tmp |= (level << 1);
  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);

#elif (RFM7x_MODULECHIP_USED == 3) // bk2425

  uint8_t txictrl_tmp = 0;

  switch (level) {
    default:
    case 0: // -25 dBm
    case 1: // -18 dBm
      break;
    case 2: // -12 dBm
      level -= 1;
      txictrl_tmp = 1;
      break;

    case 3: // -7 dBm
      level -= 1;
      txictrl_tmp = 2;
      break;

    case 4: // -1 dBm
      level -= 1;
      break;

    case 5: // 4 dBm
      level -= 2;
      txictrl_tmp = 7;
      break;
  }

  tmp |= (level << 1);
  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);

#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1

    RFM7x_CSN_LOW;
    rfm7x_spi_rw(0x04 | 0x20);
    rfm7x_spi_rw((rfm7x_init_struct[16] & 0x38) | txictrl_tmp);
    rfm7x_spi_rw(rfm7x_init_struct[17]);
    rfm7x_spi_rw(rfm7x_init_struct[18]);
    rfm7x_spi_rw(rfm7x_init_struct[19]);
    RFM7x_CSN_HI;

    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
  }

#elif (RFM7x_MODULECHIP_USED == 4) | (RFM7x_MODULECHIP_USED == 5) // bk2411//bk2412//bk5811

  tmp |= ((level & 0x03) << 1) | ((level >> 2) << 4); // to optimize ?
  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);

#endif
}

void rfm7x_set_lna_gain(uint8_t enable)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);

  if (enable)
    tmp |= RFM7x_RF_SETUP_LNA_HCURR;
  else
    tmp &= ~(RFM7x_RF_SETUP_LNA_HCURR);

  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
}

void rfm7x_set_datarate(uint8_t datarate)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);

#if (RFM7x_MODULECHIP_USED == 0) | (RFM7x_MODULECHIP_USED == 1) | (RFM7x_MODULECHIP_USED == 4) | (RFM7x_MODULECHIP_USED == 5) // bk2401/bk2421/bk2411/bk2412/bk5811
  tmp &= ~(RFM7x_RF_SETUP_RF_DR_HIGH);

  if (datarate & 0x01)
    tmp |= RFM7x_RF_SETUP_RF_DR_HIGH;

  //tmp |= ((datarate & 0x01) << 3);
#elif (RFM7x_MODULECHIP_USED == 2) | (RFM7x_MODULECHIP_USED == 3) // bk2423/bk2425
  tmp &= ~(RFM7x_RF_SETUP_RF_DR_HIGH | RFM7x_RF_SETUP_RF_DR_LOW);

  if (datarate & 0x01)
    tmp |= RFM7x_RF_SETUP_RF_DR_HIGH;

  if (datarate & 0x02)
    tmp |= RFM7x_RF_SETUP_RF_DR_LOW;

  //tmp |= ((datarate & 0x01) << 3)|(((datarate >> 1) & 0x01) << 5);
#endif

  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
}

#if (RFM7x_MODULECHIP_USED == 4) || (RFM7x_MODULECHIP_USED == 5)
void rfm7x_enable_rssi_measurements(uint8_t enable)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);

  if (enable)
    tmp |= RFM7x_RF_SETUP_RSSI_EN;
  else
    tmp &= ~(RFM7x_RF_SETUP_RSSI_EN);

  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
}
#endif

#if (RFM7x_MODULECHIP_USED == 4)
void rfm7x_dreg_enable(uint8_t enable)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_RF_SETUP);

  if (enable)
    tmp |= BK2411_RF_SETUP_DREG_ON;
  else
    tmp &= ~(BK2411_RF_SETUP_DREG_ON);

  rfm7x_reg_write(RFM7x_REG_RF_SETUP, tmp);
}
#endif

void rfm7x_enable_pipe_autoack(uint8_t pipe, uint8_t enabled)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_EN_AA);

  tmp &= ~(1 << pipe);

  if (enabled)
    tmp |= (1 << pipe);

  rfm7x_reg_write(RFM7x_REG_EN_AA, tmp);
}

void rfm7x_enable_pipe_receive(uint8_t pipe, uint8_t enabled)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_EN_RXADDR);

  tmp &= ~(1 << pipe);

  if (enabled)
    tmp |= (1 << pipe);

  rfm7x_reg_write(RFM7x_REG_EN_RXADDR, tmp);
}

void rfm7x_enable_dynamic_payload_feature(uint8_t enable)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_FEATURE);

  tmp &= ~(RFM7x_FEATURE_EN_DPL);

  if (enable)
    tmp |= RFM7x_FEATURE_EN_DPL;

  rfm7x_reg_write(RFM7x_REG_FEATURE, tmp);
}

void rfm7x_enable_ack_payload_feature(uint8_t enable)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_FEATURE);

  tmp &= ~(RFM7x_FEATURE_EN_ACK_PAY);

  if (enable)
    tmp |= RFM7x_FEATURE_EN_ACK_PAY;

  rfm7x_reg_write(RFM7x_REG_FEATURE, tmp);
}

void rfm7x_enable_noack_payload_feature(uint8_t enable)
{
  uint8_t tmp = rfm7x_reg_read(RFM7x_REG_FEATURE);

  tmp &= ~(RFM7x_FEATURE_EN_DYN_ACK);

  if (enable)
    tmp |= RFM7x_FEATURE_EN_DYN_ACK;

  rfm7x_reg_write(RFM7x_REG_FEATURE, tmp);
}

void rfm7x_set_transmit_address(uint8_t* addr)
{
  uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
  size += 2;
  rfm7x_reg_buff_write(RFM7x_REG_TX_ADDR, addr, size);
}

void rfm7x_open_writing_pipe(uint64_t addr)
{
  uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
  size += 2;

  //initialize also RX0 ?
  rfm7x_reg_buff_write(RFM7x_REG_TX_ADDR, (uint8_t*)&addr, size); // just push that onto the stack, forget about shifts
}

//pipe 1 and 2 (??)
void rfm7x_set_receive_address(uint8_t pipe, uint8_t* addr)
{
  uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
  size += 2;
  rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P0 + pipe, addr, size);
}

void rfm7x_open_reading_pipe(uint8_t pipe, uint64_t addr)
{
  rfm7x_enable_pipe_receive(pipe, 1);

  if (pipe >= 2) {
    rfm7x_reg_write(RFM7x_REG_RX_ADDR_P0 + pipe, (addr & 0xff));
  } else {
    uint8_t size = rfm7x_reg_read(RFM7x_REG_SETUP_AW);
    size += 2;

    rfm7x_reg_buff_write(RFM7x_REG_RX_ADDR_P0 + pipe, (uint8_t*)&addr, size); // just push that onto the stack, forget about shifts // LE archs only ?
  }
}

#if (RFM7x_MODULECHIP_USED == 5)

#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
const __flash uint8_t rfm7x_swapbandtune_struct[] =
#else
const uint8_t rfm7x_swapbandtune_struct[] = // generic for all architectures // table will be placed in SRAM if your mcu doesn't have unified memory space (flash + ram)
#endif
{
#if (BK5811_BANK1_DEFAULT_BAND == 0) // 5.1GHz in rfm7x_init_struct

  0x04, 0x05, 0x78, 0x32, // reg 0
  0xC0, 0x05, 0xAE, 0x00, // reg 1 // dummy
  0xE8, 0x80, 0x0C, 0xD2, // reg 2
  0x19, 0x0D, 0x7D, 0x6D // reg 3

#else //(BK5811_BANK1_DEFAULT_BAND == 1) // 5.8GHz in rfm7x_init_struct

  0x04, 0x05, 0x78, 0x33, // reg 0
  0xC0, 0x05, 0xAE, 0x00, // reg 1 // dummy
  0xE8, 0x80, 0x8C, 0xD3, // reg 2
  0x18, 0x0D, 0x7D, 0x6C // reg 3
#endif
};

void bk5811_set_frequency_band(uint8_t range)
{
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
  const __flash uint8_t* p_swapband_struct;
#else
  const uint8_t* p_swapband_struct;
#endif

#if (BK5811_BANK1_DEFAULT_BAND == 0) // 5.1GHz in rfm7x_init_struct
  if (range)
    p_swapband_struct = rfm7x_init_struct;
  else
    p_swapband_struct = rfm7x_swapbandtune_struct;
#else //(BK5811_BANK1_DEFAULT_BAND == 1) // 5.8GHz in rfm7x_init_struct
  if (range)
    p_swapband_struct = rfm7x_swapbandtune_struct;
  else
    p_swapband_struct = rfm7x_init_struct;
#endif

#ifdef RFM7x_ATOMIC_REG_ACCES
  CRITICAL_SECTION
#endif
  {
    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 1

    for (uint_fast8_t i = 0; i < 4; i++) {
#if defined(__AVR_ARCH__) && !defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH)
      rfm7x_reg_buff_write_P(i, p_swapband_struct + i * 4, 4);
#else
      rfm7x_reg_buff_write(i, p_swapband_struct + i * 4, 4);
#endif
    }

    rfm7x_cmd_write(RFM7x_CMD_ACTIVATE, 0x53); // toggle to bank 0
  }
}
#endif
