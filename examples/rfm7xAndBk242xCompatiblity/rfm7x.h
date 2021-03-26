#ifndef RFM7x_H_
#define RFM7x_H_

/************************************************************************************
 *  Author: jnk0le@hotmail.com                                                      *
 *  https://github.com/jnk0le                                                       *
 *  This library is distributed under MIT license terms                             *
 ************************************************************************************/

#include "rfm7x_config.h"
#include "rfm7x_hardware.h"

#ifdef __cplusplus
	extern "C" {
#endif

#define RFM7x_CMD_READ_REG              0x00
#define RFM7x_CMD_WRITE_REG             0x20
#define RFM7x_CMD_R_RX_PAYLOAD          0x61 
#define RFM7x_CMD_W_TX_PAYLOAD          0xA0
#define RFM7x_CMD_FLUSH_TX              0xE1
#define RFM7x_CMD_FLUSH_RX              0xE2
#define RFM7x_CMD_REUSE_TX_PL           0xE3
#define RFM7x_CMD_W_TX_PAYLOAD_NOACK    0xB0
#define RFM7x_CMD_W_ACK_PAYLOAD         0xA8
#define RFM7x_CMD_ACTIVATE              0x50
#define RFM7x_CMD_R_RX_PL_WID           0x60
#define RFM7x_CMD_NOP                   0xFF

#define RFM7x_REG_CONFIG                0x00 // 'Config'
#define RFM7x_REG_EN_AA                 0x01 // 'Enable Auto Acknowledgment'
#define RFM7x_REG_EN_RXADDR             0x02 // 'Enabled RX addresses'
#define RFM7x_REG_SETUP_AW              0x03 // 'Setup address width'
#define RFM7x_REG_SETUP_RETR            0x04 // 'Setup Auto. Retrans'
#define RFM7x_REG_RF_CH                 0x05 // 'RF channel'
#define RFM7x_REG_RF_SETUP              0x06 // 'RF setup'
#define RFM7x_REG_STATUS                0x07 // 'Status'
#define RFM7x_REG_OBSERVE_TX            0x08 // 'Observe TX'
#define RFM7x_REG_CD                    0x09 // 'Carrier Detect'
#define RFM7x_REG_RX_ADDR_P0            0x0A // 'RX address pipe0'
#define RFM7x_REG_RX_ADDR_P1            0x0B // 'RX address pipe1'
#define RFM7x_REG_RX_ADDR_P2            0x0C // 'RX address pipe2'
#define RFM7x_REG_RX_ADDR_P3            0x0D // 'RX address pipe3'
#define RFM7x_REG_RX_ADDR_P4            0x0E // 'RX address pipe4'
#define RFM7x_REG_RX_ADDR_P5            0x0F // 'RX address pipe5'
#define RFM7x_REG_TX_ADDR               0x10 // 'TX address'
#define RFM7x_REG_RX_PW_P0              0x11 // 'RX payload width, pipe0'
#define RFM7x_REG_RX_PW_P1              0x12 // 'RX payload width, pipe1'
#define RFM7x_REG_RX_PW_P2              0x13 // 'RX payload width, pipe2'
#define RFM7x_REG_RX_PW_P3              0x14 // 'RX payload width, pipe3'
#define RFM7x_REG_RX_PW_P4              0x15 // 'RX payload width, pipe4'
#define RFM7x_REG_RX_PW_P5              0x16 // 'RX payload width, pipe5'
#define RFM7x_REG_FIFO_STATUS           0x17 // 'FIFO Status Register'
#define RFM7x_REG_DYNPD                 0x1c // 'Enable dynamic payload length'
#define RFM7x_REG_FEATURE               0x1d // 'Feature' register address

// Status Register
#define RFM7x_STATUS_IRQ_RX_DR          0x40 
#define RFM7x_STATUS_IRQ_TX_DS          0x20 
#define RFM7x_STATUS_IRQ_MAX_RT         0x10
#define RFM7x_STATUS_IRQ_TX_FULL        0x01
#define RFM7x_STATUS_RBANK              0x80
#define RFM7x_STATUS_RX_PIPE_NUM        0x0E

// FIFO Status Register
#define RFM7x_FIFO_STATUS_TX_REUSE      0x40
#define RFM7x_FIFO_STATUS_TX_FULL       0x20
#define RFM7x_FIFO_STATUS_TX_EMPTY      0x10
#define RFM7x_FIFO_STATUS_RX_FULL       0x02
#define RFM7x_FIFO_STATUS_RX_EMPTY      0x01

// Config Register
#define RFM7x_CONFIG_MASK_RX_DR         0x40 // Mask interrupt caused by RX_DR when 1
#define RFM7x_CONFIG_MASK_TX_DS         0x20 // Mask interrupt caused by TX_DS when 1
#define RFM7x_CONFIG_MASK_MAX_RT        0x10 // Mask interrupt caused by MAX_RT when 1
#define RFM7x_CONFIG_EN_CRC             0x08
#define RFM7x_CONFIG_CRCO               0x04
#define RFM7x_CONFIG_POWER              0x02 // 1 - Power up ; 0 - Power down
#define RFM7x_CONFIG_PRIM_RX            0x01 // 1 - Receiver ; 0 - Transmitter

//RF config register
#define RFM7x_RF_SETUP_LNA_HCURR        0x01
#define RFM7x_RF_SETUP_RF_DR_HIGH		0x08 // not high
#define RFM7x_RF_SETUP_RF_DR_LOW		0x20 // and not low // doesn't exists in bk2421/bk2411
#define RFM7x_RF_SETUP_PLL_LOCK         0x10 // doesn't exists in bk2421/bk2411
#define BK2411_RF_SETUP_DREG_ON         0x20 // "Digital regulator can be shut down or not "
#define RFM7x_RF_SETUP_RSSI_EN          0x40 // bk2411/12/5811 only 
//RF_PWR mask ??

//EN_AA
//EN_RXADDR
//SETUP_RETR
//OBSERVE_TX
//DYNPD

// Feature Register
#define RFM7x_FEATURE_EN_DPL            0x04
#define RFM7x_FEATURE_EN_ACK_PAY        0x02
#define RFM7x_FEATURE_EN_DYN_ACK        0x01

//////////////////////////////////////////////////////////////////

#define RFM7x_BANK0_REG_CONFIG     ((RFM7x_BANK0_CONF_PWR_UP << 1)|(RFM7x_BANK0_CONF_CRCO << 2)|(RFM7x_BANK0_CONF_EN_CRC << 3)|(RFM7x_BANK0_CONF_MASK_MAX_RT << 4)|(RFM7x_BANK0_CONF_MASK_TX_DS << 5)|(RFM7x_BANK0_CONF_MASK_RX_DR << 6))
#define RFM7x_BANK0_REG_EN_AA      ((RFM7x_BANK0_CONF_ENAA_P0 << 0)|(RFM7x_BANK0_CONF_ENAA_P1 << 1)|(RFM7x_BANK0_CONF_ENAA_P2 << 2)|(RFM7x_BANK0_CONF_ENAA_P3 << 3)|(RFM7x_BANK0_CONF_ENAA_P4 << 4)|(RFM7x_BANK0_CONF_ENAA_P5 << 5))
#define RFM7x_BANK0_REG_EN_RXADDR  ((RFM7x_BANK0_CONF_ERX_P0 << 0)|(RFM7x_BANK0_CONF_ERX_P1 << 1)|(RFM7x_BANK0_CONF_ERX_P2 << 2)|(RFM7x_BANK0_CONF_ERX_P3 << 3)|(RFM7x_BANK0_CONF_ERX_P4 << 4)|(RFM7x_BANK0_CONF_ERX_P5 << 5))
#define RFM7x_BANK0_REG_SETUP_AW   ((RFM7x_BANK0_CONF_AW))
#define RFM7x_BANK0_REG_SETUP_RETR ((RFM7x_BANK0_CONF_ARC)|(RFM7x_BANK0_CONF_ARD << 4))
#define RFM7x_BANK0_REG_RF_CH      (RFM7x_BANK0_CONF_RF_CH)

#if (RFM7x_MODULECHIP_USED == 4) // bk2411, bk2412
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_BANK0_CONF_LNA_HCURR)|((RFM7x_BANK0_CONF_RF_PWR & 0x03) << 1)|((RFM7x_BANK0_CONF_RF_PWR >> 2) << 4)|(RFM7x_BANK0_CONF_RF_DR << 3)|(BK2411_BANK0_CONF_DREG_ON << 5)|(RFM7x_BANK0_CONF_RSSI_EN << 6))
#elif (RFM7x_MODULECHIP_USED == 5) // bk5811
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_BANK0_CONF_LNA_HCURR)|((RFM7x_BANK0_CONF_RF_PWR & 0x03) << 1)|((RFM7x_BANK0_CONF_RF_PWR >> 2) << 4)|(RFM7x_BANK0_CONF_RF_DR << 3)|(RFM7x_BANK0_CONF_RSSI_EN << 6))
#else
	#define RFM7x_BANK0_REG_RF_SETUP ((RFM7x_BANK0_CONF_LNA_HCURR)|(RFM7x_BANK0_CONF_RF_PWR << 1)|((RFM7x_BANK0_CONF_RF_DR & 0x01) << 3)|((RFM7x_BANK0_CONF_RF_DR >> 1) << 5))
#endif

#define RFM7x_BANK0_REG_DYNPD      ((RFM7x_BANK0_CONF_DPL_P0 << 0)|(RFM7x_BANK0_CONF_DPL_P1 << 1)|(RFM7x_BANK0_CONF_DPL_P2 << 2)|(RFM7x_BANK0_CONF_DPL_P3 << 3)|(RFM7x_BANK0_CONF_DPL_P4 << 4)|(RFM7x_BANK0_CONF_DPL_P5 << 5))
#define RFM7x_BANK0_REG_FEATURE    ((RFM7x_BANK0_CONF_EN_DYN_ACK)|(RFM7x_BANK0_CONF_EN_ACK_PAY << 1)|(RFM7x_BANK0_CONF_EN_DPL << 2))
 
#ifdef RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS
	#ifdef RFM7x_TX_ADDRESS_SIZE
		#undef RFM7x_TX_ADDRESS_SIZE
	#endif

	#define RFM7x_TX_ADDRESS_SIZE RFM7x_PIPE0_RX_ADDRESS_SIZE
#endif

	#define RFM7x_BANK0_ENTRIES_BASE 10

#if !defined(RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS)
	#define RFM7x_BANK0_ENTRIES_RX_ADDR 6
#else
	#define RFM7x_BANK0_ENTRIES_RX_ADDR 0
#endif

#if !defined(RFM7x_DO_NOT_INITIALIZE_RX_PAYLOAD_LEN_REGS)&&!defined(RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS)	
	#define RFM7x_BANK0_ENTRIES_RX_LEN 8
#else
	#define RFM7x_BANK0_ENTRIES_RX_LEN 0
#endif

#ifdef RFM7x_DO_NOT_INITIALIZE_BANK0
	#define RFM7x_BANK0_ENTRIES 0
#else
	#define RFM7x_BANK0_ENTRIES (RFM7x_BANK0_ENTRIES_BASE + RFM7x_BANK0_ENTRIES_RX_ADDR + RFM7x_BANK0_ENTRIES_RX_LEN)
#endif

////////////////////////////////////////// bank 1 initialization registers //////////////////////////////////////////
// datasheet values are given as little endian - LSB should be first
// "replacing" manual have big endian order - MSB should be first
// of course they are different and no one knows which ones are correct
// regs 0 to 8 are double reversed so MSB is written first // regs 9 to 14 are LSB first // reg 8 is also LSB first (when read)
// most of those registers are write only

#define RFM7x_BANK1_ENTRIES 15 // including RAMP_CURVE

#if (RFM7x_MODULECHIP_USED == 0 || RFM7x_MODULECHIP_USED == 1) // BK2421 aka RFM70 + BK2401

	#define RFM7x_BANK1_REG0  0x40, 0x4B, 0x01, 0xE2
	#define RFM7x_BANK1_REG1  0xC0, 0x4B, 0x00, 0x00
	#define RFM7x_BANK1_REG2  0xD0, 0xFC, 0x8C, 0x02

	#if (RFM70_BANK1_REG3_MODE == 0)
		#define RFM7x_BANK1_REG3  0x99, 0x00, 0x39, 0x41
	#elif (RFM70_BANK1_REG3_MODE == 1)
		#define RFM7x_BANK1_REG3  0xF9, 0x00, 0x39, 0x41
	#elif (RFM70_BANK1_REG3_MODE == 2)
		#define RFM7x_BANK1_REG3  0x03, 0x00, 0x12, 0x00
	#endif

	#if (RFM70_BANK1_REG4_MODE == 0)
		#define RFM7x_BANK1_REG4  0xD9, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM70_BANK1_REG4_MODE == 1)
		#define RFM7x_BANK1_REG4  0xC9, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM70_BANK1_REG4_MODE == 2)
		#define RFM7x_BANK1_REG4  0xF9, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM70_BANK1_REG4_MODE == 3)
		#define RFM7x_BANK1_REG4  0xB9, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM70_BANK1_REG4_MODE == 4)
		#define RFM7x_BANK1_REG4  0x09, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM70_BANK1_REG4_MODE == 5)
		#define RFM7x_BANK1_REG4  0xD9, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x86, 0x21
	#elif (RFM70_BANK1_REG4_MODE == 6)
		#define RFM7x_BANK1_REG4  0xD9, 0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x82, 0x1B
	#elif (RFM70_BANK1_REG4_MODE == 7)
		#define RFM7x_BANK1_REG4  0xF9, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x84, 0x0B
	#elif (RFM70_BANK1_REG4_MODE == 8)
		#define RFM7x_BANK1_REG4  0xF9, 0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x84, 0x1B
	#elif (RFM70_BANK1_REG4_MODE == 9)
		#define RFM7x_BANK1_REG4  0xF9, 0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x80, 0x1B
	#elif (RFM70_BANK1_REG4_MODE == 10)
		#define RFM7x_BANK1_REG4  0xF9, 0x86|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x82, 0x1B
	#elif (RFM70_BANK1_REG4_MODE == 11)
		#define RFM7x_BANK1_REG4  0xC1, 0x8E|(RFM70_CONFIG_UNDOCUMENTED_RX_SEN << 5)|(RFM70_CONFIG_TX_PWR << 4), 0x9A, 0x0B
	#endif

	#if (RFM70_BANK1_REG5_MODE == 0)
		#define RFM7x_BANK1_REG5  0x24, 0x06, 0x7F, 0xA6
	#elif (RFM70_BANK1_REG5_MODE == 1)
		#define RFM7x_BANK1_REG5  (RFM73_RSSI_THRESHOLD_LEVEL << 2), 0x02, 0x7F, 0xA6
	#endif

	#define RFM7x_BANK1_REG6  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG7  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG8  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG9  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGA  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGB  0x00, 0x00, 0x00, 0x00

	#if (RFM70_BANK1_REGC_MODE == 0)
		#define RFM7x_BANK1_REGC  0x00, 0x12, 0x73, 0x00
	#elif (RFM70_BANK1_REGC_MODE == 1)
		#define RFM7x_BANK1_REGC  0x00, 0x12, 0x73, 0x05
	#elif (RFM70_BANK1_REGC_MODE == 2)
		#define RFM7x_BANK1_REGC  0x00, 0x1a, 0x73, 0x00
	#endif

	#if (RFM70_BANK1_REGD_MODE == 0)
		#define RFM7x_BANK1_REGD  0x36, 0xB4, 0x80, 0x00
	#elif (RFM70_BANK1_REGD_MODE == 1)
		#define RFM7x_BANK1_REGD  0x46, 0xB4, 0x80, 0x00
	#endif

	#if (RFM70_BANK1_RAMP_CURVE_MODE == 0)
		#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF
	#elif (RFM70_BANK1_RAMP_CURVE_MODE == 1)
		#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x10, 0x04, 0x82, 0x20, 0x08, 0x08, 0xF2, 0x7D, 0xEF, 0xFF
	#endif

#elif (RFM7x_MODULECHIP_USED == 2) // BK2423 aka RFM73

	#define RFM7x_BANK1_REG0  0x40, 0x4B, 0x01, 0xE2
	#define RFM7x_BANK1_REG1  0xC0, 0x4B, 0x00, 0x00
	#define RFM7x_BANK1_REG2  0xD0, 0xFC, 0x8C, 0x02

	#if (RFM73_BANK1_REG3_MODE == 0)
		#define RFM7x_BANK1_REG3  0x99, 0x00, 0x39, 0x41
	#elif (RFM73_BANK1_REG3_MODE == 1)
		#define RFM7x_BANK1_REG3  0xF9, 0x00, 0x39, 0x41
	#elif (RFM73_BANK1_REG3_MODE == 2)
		#define RFM7x_BANK1_REG3  0x03, 0x00, 0x12, 0x00
	#endif

	#if (RFM73_BANK1_REG4_MODE == 0)
		#define RFM7x_BANK1_REG4  0xD9, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM73_BANK1_REG4_MODE == 1)
		#define RFM7x_BANK1_REG4  0xD9, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x82, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 2)
		#define RFM7x_BANK1_REG4  0xF9, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x84, 0x0B
	#elif (RFM73_BANK1_REG4_MODE == 3)
		#define RFM7x_BANK1_REG4  0xD9, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x86, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 4)
		#define RFM7x_BANK1_REG4  0xF9, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x84, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 5)
		#define RFM7x_BANK1_REG4  0xF9, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x80, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 6)
		#define RFM7x_BANK1_REG4  0xD9, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x86, 0x21
	#elif (RFM73_BANK1_REG4_MODE == 7)
		#define RFM7x_BANK1_REG4  0xF9, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x82, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 8)
		#define RFM7x_BANK1_REG4  0xF9, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM73_BANK1_REG4_MODE == 9)
		#define RFM7x_BANK1_REG4  0xB9, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM73_BANK1_REG4_MODE == 10)
		#define RFM7x_BANK1_REG4  0xB9, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x82, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 11)
		#define RFM7x_BANK1_REG4  0x09, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x86, 0x0B
	#elif (RFM73_BANK1_REG4_MODE == 12)
		#define RFM7x_BANK1_REG4  0x09, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x82, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 13)
		#define RFM7x_BANK1_REG4  0xC1, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x9A, 0x0B
	#elif (RFM73_BANK1_REG4_MODE == 14)
		#define RFM7x_BANK1_REG4  0xC1, 0x8E|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x9A, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 15)
		#define RFM7x_BANK1_REG4  0xC1, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x9A, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 16)
		#define RFM7x_BANK1_REG4  0xC1, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x9C, 0x1B
	#elif (RFM73_BANK1_REG4_MODE == 17)
		#define RFM7x_BANK1_REG4  0xC1, 0x86|(RFM73_CONFIG_RX_SEN << 5)|(RFM73_CONFIG_TX_PWR << 4), 0x9E, 0x1B
	#endif

	#if (RFM73_BANK1_REG5_MODE == 0)
		#define RFM7x_BANK1_REG5  0x24, 0x06, 0x7F, 0xA6
	#elif (RFM73_BANK1_REG5_MODE == 1)
		#define RFM7x_BANK1_REG5  (RFM73_RSSI_THRESHOLD_LEVEL << 2), 0x02, 0x7F, 0xA6
	#endif

	#define RFM7x_BANK1_REG6  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG7  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG8  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG9  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGA  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGB  0x00, 0x00, 0x00, 0x00

	#if (RFM73_BANK1_REGC_MODE == 0)
		#define RFM7x_BANK1_REGC  0x00, 0x10|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x00
	#elif (RFM73_BANK1_REGC_MODE == 1)
		#define RFM7x_BANK1_REGC  0x00, 0x10|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x05
	#elif (RFM73_BANK1_REGC_MODE == 2)
		#define RFM7x_BANK1_REGC  0x00, 0x18|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x00
	#elif (RFM73_BANK1_REGC_MODE == 3)
		#define RFM7x_BANK1_REGC  0x00, 0x18|(RFM73_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x05
	#endif

	#if (RFM73_BANK1_REGD_MODE == 0)
		#define RFM7x_BANK1_REGD  0x36, 0xB4, 0x80, 0x00
	#elif (RFM73_BANK1_REGD_MODE == 1)
		#define RFM7x_BANK1_REGD  0x46, 0xB4, 0x80, 0x00
	#endif

	#if (RFM73_BANK1_RAMP_CURVE_MODE == 0)
		#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x10, 0x04, 0x82, 0x20, 0x08, 0x08, 0xF2, 0x7D, 0xEF, 0xFF
	#elif (RFM73_BANK1_RAMP_CURVE_MODE == 1)
		#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF
	#endif

#elif (RFM7x_MODULECHIP_USED == 3) // bk2425 aka RFM75

	#define RFM7x_BANK1_REG0  0x40, 0x4B, 0x01, 0xE2
	#define RFM7x_BANK1_REG1  0xC0, 0x4B, 0x00, 0x00
	#define RFM7x_BANK1_REG2  0xD0, 0xFC, 0x8C, 0x02

	#if (RFM75_BANK1_REG3_MODE == 0)
		#define RFM7x_BANK1_REG3  0x99, 0x00, 0x39, 0x21
	#elif (RFM75_BANK1_REG3_MODE == 1)
		#define RFM7x_BANK1_REG3  0x03, 0x00, 0x12, 0x00
	#elif (RFM75_BANK1_REG3_MODE == 2)
		#define RFM7x_BANK1_REG3  0xF9, 0x00, 0x39, 0x21
	#elif (RFM75_BANK1_REG3_MODE == 3)
		#define RFM7x_BANK1_REG3  0x99, 0x00, 0x39, 0x41
	#elif (RFM75_BANK1_REG3_MODE == 4)
		#define RFM7x_BANK1_REG3  0xF9, 0x00, 0x39, 0x41
	#endif

	#if (RFM75_BANK1_REG4_MODE == 0)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x82, 0x1B
	#elif (RFM75_BANK1_REG4_MODE == 1)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x82, 0xDB
	#elif (RFM75_BANK1_REG4_MODE == 2)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x8A, 0xDB
	#elif (RFM75_BANK1_REG4_MODE == 3)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x82, 0x21
	#elif (RFM75_BANK1_REG4_MODE == 4)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x80, 0x1B
	#elif (RFM75_BANK1_REG4_MODE == 5)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x80, 0xDB
	#elif (RFM75_BANK1_REG4_MODE == 6)
		#define RFM7x_BANK1_REG4  0xC1|(RFM75_CONFIG_txIctrl << 3), 0x96|(RFM75_CONFIG_UNDOCUMENTED_RX_SEN << 5), 0x88, 0xDB
	#endif

	#if (RFM75_BANK1_REG5_MODE == 0)
		#define RFM7x_BANK1_REG5  0x24, 0x06, 0x0F, 0xA6
	#elif (RFM75_BANK1_REG5_MODE == 1)
		#define RFM7x_BANK1_REG5  0x24, 0x06, 0x0F, 0xB6
	#elif (RFM75_BANK1_REG5_MODE == 2)
		#define RFM7x_BANK1_REG5  0x24, 0x02, 0x0F, 0xA6
	#elif (RFM75_BANK1_REG5_MODE == 3)
		#define RFM7x_BANK1_REG5  0x24, 0x02, 0x0F, 0xB6
	#elif (RFM75_BANK1_REG5_MODE == 4)
		#define RFM7x_BANK1_REG5  (RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2), 0x02, 0x0F, 0xA6
	#elif (RFM75_BANK1_REG5_MODE == 5)
		#define RFM7x_BANK1_REG5  (RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2), 0x02, 0x0F, 0xB6
	#elif (RFM75_BANK1_REG5_MODE == 6)
		#define RFM7x_BANK1_REG5  0x24, 0x06, 0x7F, 0xA6
	#elif (RFM75_BANK1_REG5_MODE == 7)
		#define RFM7x_BANK1_REG5  0x24, 0x06, 0x7F, 0xB6
	#elif (RFM75_BANK1_REG5_MODE == 8)
		#define RFM7x_BANK1_REG5  (RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2), 0x02, 0x7F, 0xA6
	#elif (RFM75_BANK1_REG5_MODE == 9)
		#define RFM7x_BANK1_REG5  (RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL << 2), 0x02, 0x7F, 0xB6
	#endif

	#define RFM7x_BANK1_REG6  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG7  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG8  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG9  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGA  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGB  0x00, 0x00, 0x00, 0x00

	#if (RFM75_BANK1_REGC_MODE == 0)
		#define RFM7x_BANK1_REGC  0x00, 0x10|(RFM75_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x00
	#elif (RFM75_BANK1_REGC_MODE == 1)
		#define RFM7x_BANK1_REGC  0x00, 0x10|(RFM75_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x05
	#elif (RFM75_BANK1_REGC_MODE == 2)
		#define RFM7x_BANK1_REGC  0x00, 0x18|(RFM75_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x00
	#elif (RFM75_BANK1_REGC_MODE == 3)
		#define RFM7x_BANK1_REGC  0x00, 0x18|(RFM75_CONFIG_COMPATIBLE_MODE << 1), 0x73, 0x05
	#endif

	#if (RFM75_BANK1_REGD_MODE == 0)
		#define RFM7x_BANK1_REGD  0x36, 0xB4, 0x80, 0x00
	#elif (RFM75_BANK1_REGD_MODE == 1)
		#define RFM7x_BANK1_REGD  0x46, 0xB4, 0x80, 0x00
	#endif

	#if (RFM75_BANK1_RAMP_CURVE_MODE == 0)
		#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF
	#elif (RFM75_BANK1_RAMP_CURVE_MODE == 1)
		#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x10, 0x04, 0x82, 0x20, 0x08, 0x08, 0xF2, 0x7D, 0xEF, 0xFF
	#endif

#elif (RFM7x_MODULECHIP_USED == 4) // bk2411/2412

	#define RFM7x_BANK1_REG0  0x41, 0x4B, 0x01, 0xF2
	#define RFM7x_BANK1_REG1  0xC0, 0x4B, 0x06, 0x30
	#define RFM7x_BANK1_REG2  0xA0, 0xFC, 0xC4, 0x00

	#if (BK2411_BANK1_REG3_MODE == 0)
		#define RFM7x_BANK1_REG3  0x17, 0x00, 0x35, 0x60
	#elif (BK2411_BANK1_REG3_MODE == 1)
		#define RFM7x_BANK1_REG3  0x03, 0x00, 0x12, 0x00
	#endif

	#if (BK2411_BANK1_REG4_MODE == 0)
		#define RFM7x_BANK1_REG4  0x41, 0x99, 0x00, 0x0B
	#elif (BK2411_BANK1_REG4_MODE == 1)
		#define RFM7x_BANK1_REG4  0x41, 0x99, 0x10, 0x0B
	#elif (BK2411_BANK1_REG4_MODE == 2)
		#define RFM7x_BANK1_REG4  0x41, 0x11, 0x04, 0x21
	#elif (BK2411_BANK1_REG4_MODE == 3)
		#define RFM7x_BANK1_REG4  0x41, 0x98|(BK2411_XTALFC >> 3), 0x00|(BK2411_XTALFC << 5), 0x0B
	#elif (BK2411_BANK1_REG4_MODE == 4)
		#define RFM7x_BANK1_REG4  0x41, 0x98|(BK2411_XTALFC >> 3), 0x10|(BK2411_XTALFC << 5), 0x0B
	#elif (BK2411_BANK1_REG4_MODE == 5)
		#define RFM7x_BANK1_REG4  0x41, 0x10|(BK2411_XTALFC >> 3), 0x04|(BK2411_XTALFC << 5), 0x21
	#endif

	#define RFM7x_BANK1_REG5  (BK2411_RSSI_THRESHOLD_LEVEL << 2), 0x01, 0x17, 0xBE
	#define RFM7x_BANK1_REG6  0x00, 0x00, 0x40, 0x00
	#define RFM7x_BANK1_REG7  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG8  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG9  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGA  0xF6, 0x4E, 0xF5, 0xF6
	#define RFM7x_BANK1_REGB  0x5C, 0x18, 0x51, 0xD6

	#if (BK2411_BANK1_REGC_MODE == 0)
		#define RFM7x_BANK1_REGC  0x40, 0x55, 0x00, 0x2D
	#elif (BK2411_BANK1_REGC_MODE == 1)
		#define RFM7x_BANK1_REGC  0x60, 0x50, 0x00, 0x2D
	#elif (BK2411_BANK1_REGC_MODE == 2)
		#define RFM7x_BANK1_REGC  0x00|(BK2411_TX_RAMP_SEL << 5), 0x50|(BK2411_TX_LOCK_SEL << 1)|(BK2411_TX_RAMP_SEL >> 3), 0x00, 0x2D
	#endif

	#if (BK2411_BANK1_REGD_MODE == 0)
		#define RFM7x_BANK1_REGD  0x00, 0x70, 0x00, 0x00
	#elif (BK2411_BANK1_REGD_MODE == 1)
		#define RFM7x_BANK1_REGD  0x00, 0x04, 0x00, 0x00
	#elif (BK2411_BANK1_REGD_MODE == 2)
		#define RFM7x_BANK1_REGD  0x00, 0x74, 0x00, 0x00
	#elif (BK2411_BANK1_REGD_MODE == 3)
		#define RFM7x_BANK1_REGD  0xFF, 0x71, 0x00, 0x00
	#elif (BK2411_BANK1_REGD_MODE == 4)
		#define RFM7x_BANK1_REGD  0xFF, 0x05, 0x00, 0x00
	#elif (BK2411_BANK1_REGD_MODE == 5)
		#define RFM7x_BANK1_REGD  0xFF, 0x75, 0x00, 0x00
	#elif (BK2411_BANK1_REGD_MODE == 3)
		#define RFM7x_BANK1_REGD  (BK2411_LEN_LONG), (BK2411_LONG_PL)|(BK2411_GFSK_BT << 1)|(BK2411_MODU_MOD << 2)|(BK2411_CYST_ACCU <<4), 0x00, 0x00
	#endif

	#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x10, 0x08, 0x82, 0x40, 0x10, 0x08, 0xF2, 0x7C, 0xEF, 0xCF

#elif (RFM7x_MODULECHIP_USED == 5) // bk5811

	#if (BK5811_BANK1_DEFAULT_BAND == 0)
		#define RFM7x_BANK1_REG0  0x04, 0x05, 0x78, 0x33
	#elif (BK5811_BANK1_DEFAULT_BAND == 1)
		#define RFM7x_BANK1_REG0  0x04, 0x05, 0x78, 0x32
	#endif

	#define RFM7x_BANK1_REG1  0xC0, 0x05, 0xAE, 0x00

	#if (BK5811_BANK1_DEFAULT_BAND == 0)
		#define RFM7x_BANK1_REG2  0xE8, 0x80, 0x8C, 0xD3
	#elif (BK5811_BANK1_DEFAULT_BAND == 1)
		#define RFM7x_BANK1_REG2  0xE8, 0x80, 0x0C, 0xD2
	#endif

	#if (BK5811_BANK1_DEFAULT_BAND == 0)
		#define RFM7x_BANK1_REG3  0x18, 0x0D, 0x7D, 0x6C
	#elif (BK5811_BANK1_DEFAULT_BAND == 1)
		#define RFM7x_BANK1_REG3  0x19, 0x0D, 0x7D, 0x6D
	#endif

	#if (BK5811_BANK1_REG4_MODE == 0)
		#define RFM7x_BANK1_REG4  0xE9, 0x8E, 0x82, 0x1B
	#elif (BK5811_BANK1_REG4_MODE == 1)
		#define RFM7x_BANK1_REG4  0xE9, 0x8E, 0x82, 0x21
	#endif

	#define RFM7x_BANK1_REG5  (BK5811_RSSI_THRESHOLD_LEVEL << 2), 0x10, 0xFF, 0xA6
	#define RFM7x_BANK1_REG6  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG7  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG8  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REG9  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGA  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGB  0x00, 0x00, 0x00, 0x00
	#define RFM7x_BANK1_REGC  0x00, 0x12, 0x73, 0x00
	#define RFM7x_BANK1_REGD  0x36, 0xB4, 0x80, 0x00

	#define RFM7x_BANK1_RAMP_CURVE  0x41, 0x20, 0x08, 0x04, 0x81, 0x20, 0xCF, 0xF7, 0xFE, 0xFF, 0xFF
#endif

//////////////////////////////////////////////////////////////////
//??????
/*#if defined(RFM7x_TX_ADDRESS)&&defined(RFM7x_PIPE0_RX_ADDRESS)&&defined(RFM7x_PIPE1_RX_ADDRESS)
	#define RFM7x_LONG_ADDR_ENTRIES 3
#elif (defined(RFM7x_TX_ADDRESS)&&defined(RFM7x_PIPE0_RX_ADDRESS))||(defined(RFM7x_PIPE0_RX_ADDRESS)&&defined(RFM7x_PIPE1_RX_ADDRESS))||(defined(RFM7x_TX_ADDRESS)&&defined(RFM7x_PIPE1_RX_ADDRESS))
	#define RFM7x_LONG_ADDR_ENTRIES 2
#elif defined(RFM7x_TX_ADDRESS)||defined(RFM7x_PIPE0_RX_ADDRESS)||defined(RFM7x_PIPE1_RX_ADDRESS)
	#define RFM7x_LONG_ADDR_ENTRIES 1
#else
	#define RFM7x_LONG_ADDR_ENTRIES 0
#endif*/

//////////////////////////////////////////////////////////////////

void rfm7x_init(void);

// one of the chinese AN's (rfm73 -> rfm75) says that it should be executed after every PWR_UP, not only during initialization
void rfm7x_toggle_reg4(void); // MIGHT NOT BE THE CASE FOR BK2411/BK2412/BK5811

#define rfm7x_reg_write(__reg,__dat) rfm7x_cmd_write(RFM7x_CMD_WRITE_REG|(__reg),__dat)
#define rfm7x_reg_read(__reg) rfm7x_cmd_read(RFM7x_CMD_READ_REG|(__reg))

void rfm7x_cmd_write(uint8_t reg, uint8_t dat);
uint8_t rfm7x_cmd_read(uint8_t reg);

#define rfm7x_reg_buff_write(__reg,__buff,__len) rfm7x_cmd_buff_write(RFM7x_CMD_WRITE_REG|(__reg),__buff,__len)
#define rfm7x_reg_buff_read(__reg,__buff,__len) rfm7x_cmd_buff_read(RFM7x_CMD_READ_REG|(__reg),__buff,__len)

void rfm7x_cmd_buff_write(uint8_t reg, uint8_t *buff, uint8_t len);
void rfm7x_cmd_buff_read(uint8_t reg, uint8_t *buff, uint8_t len);

#if defined(__AVR_ARCH__)&&!defined(RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH) // temporary workaround ??
	#define rfm7x_reg_buff_write_P(__reg,__buff,__len) rfm7x_cmd_buff_write_P(RFM7x_CMD_WRITE_REG|(__reg),__buff,__len)
	
#ifdef	__cplusplus
	void rfm7x_cmd_buff_write_P(uint8_t reg, const uint8_t* buff, uint8_t len);
#else
	void rfm7x_cmd_buff_write_P(uint8_t reg, const __flash uint8_t* buff, uint8_t len);
#endif
	
#endif

uint8_t rfm7x_is_present(void);

void rfm7x_power_up(void);
void rfm7x_power_down(void); // this function will not wait for finishing any ongoing transmission (results may be undefined)

void rfm7x_mode_receive(void);
void rfm7x_mode_transmit(void);

inline void rfm7x_mode_standby(void) { RFM7x_CE_LOW; }

inline uint8_t rfm7x_tx_fifo_full(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & RFM7x_FIFO_STATUS_TX_FULL) != 0; }
inline uint8_t rfm7x_tx_fifo_empty(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & RFM7x_FIFO_STATUS_TX_EMPTY) != 0; }
		
inline uint8_t rfm7x_rx_fifo_full(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & RFM7x_FIFO_STATUS_RX_FULL) != 0; }
inline uint8_t rfm7x_rx_fifo_empty(void) { return (rfm7x_reg_read(RFM7x_REG_FIFO_STATUS) & RFM7x_FIFO_STATUS_RX_EMPTY) != 0; }

inline uint8_t rfm7x_receive_next_pipe(void) { return (rfm7x_reg_read(RFM7x_REG_STATUS) >> 1) & 0x07; }
inline uint8_t rfm7x_receive_next_length(void) { return rfm7x_cmd_read(RFM7x_CMD_R_RX_PL_WID); }

uint8_t rfm7x_receive(uint8_t *buff); // returns received length // 0x00 - nothing received, or empty packet
void rfm7x_receive_nocheck(uint8_t *buff);

uint8_t rfm7x_receive_p_(uint8_t *pipe, uint8_t *buff); // returns received length // 0x00 - nothing received
static inline uint8_t rfm7x_receive_p(uint8_t *buff, uint8_t *pipe) __attribute__((always_inline));
static inline uint8_t rfm7x_receive_p(uint8_t *buff, uint8_t *pipe) { return rfm7x_receive_p_(pipe, buff); }

inline void rfm7x_receive_nocheck_s(uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_read(RFM7x_CMD_R_RX_PAYLOAD, buff, length); }
uint8_t rfm7x_receive_s(uint8_t *buff, uint8_t length); // returns number of received pipe // 0x07 - nothing received

uint8_t rfm7x_receive_f(uint8_t *buff, uint8_t *pipe, uint8_t *length);

inline void rfm7x_transmit(uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_write(RFM7x_CMD_W_TX_PAYLOAD, buff, length); }
inline void rfm7x_transmit_noack(uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_write(RFM7x_CMD_W_TX_PAYLOAD_NOACK, buff, length); }

// used in RX mode // transmit message while ACK'ing received packet on selected pipe
inline void rfm7x_rx_ack_transmit(uint8_t pipe, uint8_t *buff, uint8_t length) { rfm7x_cmd_buff_write(RFM7x_CMD_W_ACK_PAYLOAD | pipe, buff, length); }

//uint8_t rfm7x_available(uint8_t *pipe); // normal receive mode // 
// reset irq flags??

void rfm7x_set_rssi_threshold_step(uint8_t level); // usually linear scale from 0 (-97/100dBm) to 15 (-67/70dBm) // bk2423 is also linearized by this function, some levels may be out of useable range (over -105dBm)
inline uint8_t rfm7x_read_CD(void) { return rfm7x_reg_read(RFM7x_REG_CD); }

//config
inline void rfm7x_set_channel(uint8_t channel) { rfm7x_reg_write(RFM7x_REG_RF_CH, channel); } // 0-83 , 0-127 , clears MAX_RT counter
void rfm7x_set_crc_length(uint8_t len);

//bk2421/bk2423 aka rfm70/73
// 0 - -10 dBm
// 1 - -5 dBm
// 2 -  0 dBm
// 3 -  5 dBm

//bk2425 aka rfm75
// 0 - -25 dBm
// 1 - -18 dBm
// 2 - -12 dBm
// 3 - -7 dBm
// 4 - -1 dBm
// 5 - 4 dBm

//bk2411/bk2412
// 0 - -35 dBm
// 1 - -25 dBm
// 2 - -15 dBm
// 3 - -5 dBm
// 4 - -5 dBm
// 5 - -5 dBm
// 6 - 0 dBm
// 7 - 5 dBm

//bk5811
// 0 - -35 dBm
// 1 - -30 dBm
// 2 - -30 dBm
// 3 - -24 dBm
// 4 - -12 dBm
// 5 - -8 dBm
// 6 - -4 dBm
// 7 - 0 dBm
void rfm7x_set_tx_pwr(uint8_t level);
void rfm7x_set_lna_gain(uint8_t enable);

// 0 - 1mbps
// 1 - 2mbps
// 2 - 250kbps // only 73/75
// 3 - 2mbps // only 73/75 (treat as reserved)
void rfm7x_set_datarate(uint8_t datarate);

#if (RFM7x_MODULECHIP_USED == 4)||(RFM7x_MODULECHIP_USED == 5)
	void rfm7x_enable_rssi_measurements(uint8_t enable);
#endif

#if (RFM7x_MODULECHIP_USED == 4)
	//enable on-chip "digital regulator"
	void rfm7x_dreg_enable(uint8_t enable);
#endif

//250us steps
inline void rfm7x_set_retransmits(uint8_t retransmits, uint8_t delay) { rfm7x_reg_write(RFM7x_REG_SETUP_RETR, (retransmits)|(delay<<4)); } 

// 3 to 5 bytes (2 byte width is reserved) 
inline void rfm7x_set_addres_width(uint8_t width) { rfm7x_reg_write(RFM7x_REG_SETUP_AW, width-2); } 

//0-32
inline void rfm7x_set_rx_pyaload_size(uint8_t pipe, uint8_t size) { rfm7x_reg_write(RFM7x_REG_RX_PW_P0+pipe, size); }

//void rfm7x_set_receiving_pipes(uint8_t mask);
//void rfm7x_set_autoack_pipes(uint8_t mask);
void rfm7x_enable_pipe_autoack(uint8_t pipe, uint8_t enabled);
void rfm7x_enable_pipe_receive(uint8_t pipe, uint8_t enabled);

//feature
void rfm7x_enable_dynamic_payload_feature(uint8_t enable);
void rfm7x_enable_ack_payload_feature(uint8_t enable);
void rfm7x_enable_noack_payload_feature(uint8_t enable);

// execute rfm7x_set_addres_width before (function reads AW from the chip)
//AVR: MSB       LSB
//  0x  44 33 22 11
void rfm7x_set_transmit_address(uint8_t* addr); // LSB first
void rfm7x_open_writing_pipe(uint64_t addr);

//pipe 1 and 2 (??)
void rfm7x_set_receive_address(uint8_t pipe, uint8_t* addr); // LSB first
inline void rfm7x_set_receive_address_pn(uint8_t pipe, uint8_t LSB_addr) { rfm7x_reg_write(RFM7x_REG_RX_ADDR_P0+pipe, LSB_addr); }

//all pipes
void rfm7x_open_reading_pipe(uint8_t pipe, uint64_t addr);

//observe tx
// lost packet reset

// irq ? 
//status flags

#if (RFM7x_MODULECHIP_USED == 5)
	// 0: 5.1GHz band
	// 1: 5.8GHz band
	void bk5811_set_frequency_band(uint8_t range);
#endif

#ifdef __cplusplus
	}
#endif

#endif /* RFM7x_H_ */
