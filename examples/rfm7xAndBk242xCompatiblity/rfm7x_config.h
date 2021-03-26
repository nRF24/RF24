#ifndef RFM7X_CONFIG_H_
#define RFM7X_CONFIG_H_

#define RFM7x_MODULECHIP_USED 3
// 0 // BK2401 ??? // same as BK2421 without 2 mbps data-rate
// 1 // BK2421 aka RFM70
// 2 // BK2423 aka RFM73 // usually full component COBs - (VDDPA path present) - mostly 0.6$ "power enhanced" mini-modules on aliexpress
// 3 // BK2425 aka RFM75 // pinout clearly suggests that, it is well known "COB-with-missing-components-module" nrf24l01+ fakes
// 4 // BK2411/BK2412 // those are especially designed as an nrf24L01 (without +) fake (green PCB with 5 row header), but none of them can be found // NOT TESTED
// 5 // BK5811 // 5.1/5.8GHz RF chip // NOT TESTED

// bk2491 is probably a canceled chip, which name appears as a title of various number of datasheets
// bk2461 // bk2535 // bk2533 // undocumented SOC
// bk2433 // bk2451 // bk2452 // undocumented SOCs with usb
// bk5822/23 // 5.8GHz ASK transciever // used in ETC
// bk5933 // 5.1/5.8GHz undocumented SOC (usb ?)

/*********************************************************************/

//#define RFM7x_USE_UNIVERSAL_SPI_BUFF_RW_FUNCTIONS // buff write and buff read // ?? // not complete
//#define RFM7x_ATOMIC_REG_ACCES // disable interrupts when CSN goes low to prevent race conditions with interrupts // just a global cli, can be prematured to disable only specific sources // not fully tested
//#define RFM7x_FLUSH_TX_AND_RX_WHILE_SWITCHING_MODES // probably may be required by ACK payloads (W_ACK_PAYLOAD command) // not fully tested
#define RFM7x_DO_NOT_INITIALIZE_BANK0 // do not initialize bank0 registers in case of using other libs to do so // 4 (read-only) status registers are still being initialized // addresses are also not initialized
#define RFM7x_USE_PIPE0_ADDRESS_FOR_TX_ADDRESS // initialize TX address with the data from PIPE0_RX_ADDRESS // those have to be the same in AUTO_ACK mode // RFM7x_TX_ADDRESS is ignored

#define RFM7x_DO_NOT_INITIALIZE_RX_PAYLOAD_LEN_REGS // only 2 bytes gain on avr // by omiting initialization of pyload length registers and dummy bytes
#define RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS // only 8 bytes gain on avr // by omiting initialization of payload length, pipe 2-5 addr, and dummy bytes

#define RFM7x_AVR_DO_NOT_PUT_INIT_STRUCT_IN_FLASH // currently workaround rfm7x_reg_buff_write_P() function is used that might make bigger code in some cases

/**************** hardcoded config of bank0 registers ****************/

//comment out to free space in init_struct // LSB byte is first
#define RFM7x_PIPE0_RX_ADDRESS 0x34, 0x43, 0x10, 0x10, 0x01 // have to be the same as TX_ADDRESS in order to communiacate in AUTO_ACK mode.
//#define RFM7x_PIPE1_RX_ADDRESS 0x11, 0x02, 0x03, 0x04, 0x05
//#define RFM7x_TX_ADDRESS       0x34, 0x43, 0x10, 0x10, 0x01    // have to be the same as PIPE0_RX_ADDRESS in order to communiacate in AUTO_ACK mode.

// do not comment out config below

#define RFM7x_PIPE0_RX_ADDRESS_SIZE 5
#define RFM7x_PIPE1_RX_ADDRESS_SIZE 5
#define RFM7x_TX_ADDRESS_SIZE 5
//size of the vectors above

#define RFM7x_PIPE2_RX_ADDRESS 0xC3
#define RFM7x_PIPE3_RX_ADDRESS 0xC4
#define RFM7x_PIPE4_RX_ADDRESS 0xC5
#define RFM7x_PIPE5_RX_ADDRESS 0xC6
// for the rest pipes, 4 MSB bytes are the same as PIPE1 address
// not included if RFM7x_DO_NOT_INITIALIZE_P2_RX_ADDRESS_AND_PAYLOAD_LEN_REGS is defined

#define RFM7x_BANK0_CONF_PWR_UP 1
// usually we want to power chip up during initialization
// in some rare cases (battery operated) it have to be initialized in PWR_DOWN just to save some power
// 1: POWER UP
// 0: POWER DOWN

#define RFM7x_BANK0_CONF_EN_CRC 1
// Enable CRC. Forced high if one of the bits in the EN_AA is high
// 0: CRC disabled
// 1: CRC enabled

#define RFM7x_BANK0_CONF_CRCO 1
// CRC encoding scheme
// '0' - 1 byte
// '1' - 2 bytes

#define RFM7x_BANK0_CONF_MASK_RX_DR 1
// Mask interrupt caused by RX_DR
// 1: Interrupt not reflected on the IRQ pin
// 0: Reflect RX_DR as active low interrupt on the IRQ pin

#define RFM7x_BANK0_CONF_MASK_TX_DS 1
// Mask interrupt caused by TX_DS
// 1: Interrupt not reflected on the IRQ pin
// 0: Reflect TX_DS as active low interrupt on the IRQ pin

#define RFM7x_BANK0_CONF_MASK_MAX_RT 1
// Mask interrupt caused by MAX_RT
// 1: Interrupt not reflected on the IRQ pin
// 0: Reflect MAX_RT as active low interrupt on the IRQ pin

#define RFM7x_BANK0_CONF_ENAA_P0 1
#define RFM7x_BANK0_CONF_ENAA_P1 1
#define RFM7x_BANK0_CONF_ENAA_P2 1
#define RFM7x_BANK0_CONF_ENAA_P3 1
#define RFM7x_BANK0_CONF_ENAA_P4 1
#define RFM7x_BANK0_CONF_ENAA_P5 1
// Enable auto acknowledgement data pipe N
// If one of the pipes is cofigured into AA CRC is forced
// All have to disabled for no AA TX mode ????

#define RFM7x_BANK0_CONF_ERX_P0 1
#define RFM7x_BANK0_CONF_ERX_P1 0
#define RFM7x_BANK0_CONF_ERX_P2 0
#define RFM7x_BANK0_CONF_ERX_P3 0
#define RFM7x_BANK0_CONF_ERX_P4 0
#define RFM7x_BANK0_CONF_ERX_P5 0
// Enable data pipe N

#define RFM7x_BANK0_CONF_AW 3
// RX/TX Address field width
// 0 - Illegal
// 1 - 3 bytes
// 2 - 4 bytes
// 3 - 5 bytes
// LSB byte is used if address width is below 5 bytes

#define RFM7x_BANK0_CONF_ARD 15
// Auto Retransmission Delay (Delay defined from end of transmission to start of next transmission)
// according to nrf24l01+ datasheet ARD should be 500us or more if ACK payload mode is used (W_ACK_PAYLOAD command)
// 250kbps mode requires 500us retransmit delay even if ACK payload is not used but is activated
// 0 - Wait 250 us
// 1 - Wait 500 us
// 2 - Wait 750 us
// 15 - Wait 4000 us

#define RFM7x_BANK0_CONF_ARC 15
// Auto Retransmission Count
// 0 - Re-Transmit disabled
// 1 - Up to 1 Re-Transmission on fail of AA
// 15 - Up to 15 Re-Transmission on fail of AA

#define RFM7x_BANK0_CONF_RF_CH 10
// select used frequency channel in 1 MHz steps (kb2411 starts at 2397, rest at 2400)
// beken and hoperf datasheets says about 83 channels available, but electrical specification (except bk2411) says about 127 channels

#define RFM7x_BANK0_CONF_LNA_HCURR 1
// Setup LNA gain
// 0:Low gain(20dB down)
// 1:High gain

#define RFM7x_BANK0_CONF_RF_PWR 3
//bk2421/bk2423 aka rfm70/73
// 0 - -10 dBm
// 1 - -5 dBm
// 2 -  0 dBm
// 3 -  5 dBm

//bk2425 aka rfm75
// have to be set together with txIctrl in bank1 for exact power level, otherwise -1dBm(or undefined as usual) // user_guide_of_RF75
// 3 - value for 4,-1 dBm power levels
// 2 - value for -7 dBm power level
// 1 - value for -12,-18 dBm power levels
// 0 - value for -18,-25 dBm power levels

//bk2411/bk2412
// one of the bits occupies 'PLL_LOCK' location
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

#define RFM7x_BANK0_CONF_RF_DR 0
//Air Data Rate
// 0 - 1Mbps
// 1 - 2Mbps
// 2 - 250Kbps // bk2423/bk2425 only
// 3 - 2Mbps // bk2423/bk2425 only

#define RFM7x_BANK0_CONF_RSSI_EN 1 // bk2411, bk2412, bk5811 only // rest chips have this setting in bank1
// Enable RSSI measurement
// 0: Disable
// 1: Enable

#define BK2411_BANK0_CONF_DREG_ON 1 // bk2411 only
// Digital regulator can be shut down or not
// 0: Can be shut down in stand-by I mode
// 1: Always on in any state except power down

#define RFM7x_PIPE0_RX_PAYLOAD_LEN 0
#define RFM7x_PIPE1_RX_PAYLOAD_LEN 0
#define RFM7x_PIPE2_RX_PAYLOAD_LEN 0
#define RFM7x_PIPE3_RX_PAYLOAD_LEN 0
#define RFM7x_PIPE4_RX_PAYLOAD_LEN 0
#define RFM7x_PIPE5_RX_PAYLOAD_LEN 0
// 0 == dynamic payload ??? // 1-32 == static payload length ??

#define RFM7x_BANK0_CONF_DPL_P5 1
#define RFM7x_BANK0_CONF_DPL_P4 1
#define RFM7x_BANK0_CONF_DPL_P3 1
#define RFM7x_BANK0_CONF_DPL_P2 1
#define RFM7x_BANK0_CONF_DPL_P1 1
#define RFM7x_BANK0_CONF_DPL_P0 1
// Enable dynamic payload length data pipe N (Requires EN_DPL and ENAA_PN)

#define RFM7x_BANK0_CONF_EN_DYN_ACK 1
// Enables the W_TX_PAYLOAD_NOACK command

#define RFM7x_BANK0_CONF_EN_ACK_PAY 1
// Enables Payload with ACK (W_ACK_PAYLOAD command)
// probably may need flushing RX and TX together while switching modes
// according to nrf24l01+ datasheet, 250kbps mode requires 500us retransmit delay even if ACK payload is not used

#define RFM7x_BANK0_CONF_EN_DPL 1
// Enables Dynamic Payload Length

/*********************************************************************/
// all changes below have to be followed by HARD reset of the module (unconnect power supply and short power rails),
// otherwise module can keep previous contents and work flawlessly long enough to waste you a 'few' hours for debugging when it stops working (going below 0.3V is still not enough)

// magic values that have to be written into read-only status registers, otherwise chips will refuse to work after some time or a few power cycles

#define RFM7x_BANK0_REG_STATUS 0x70
// The default value that comes from all example codes (0x07) might be intended as a fix for hidden silicon bug, or just erratum from 0x70 that should clear all pending flags

#define RFM7x_BANK0_REG_OBSERVE_TX 0x00
#define RFM7x_BANK0_REG_CD 0x00
#define RFM7x_BANK0_REG_FIFO_STATUS 0x00

/******** bk2421/01 aka RFM70 - compatibility and sensitivity *******/

#define RFM70_BANK1_REG3_MODE 1
// 0 // default recommended value
// 1 // "In order to smooth the use of RF-2400PA" (Inhaos rebrand of bk2421 + PA) // also "high power mode" for rfm73
// 2 // datasheet "reset value"

#define RFM70_BANK1_REG4_MODE 0
// 0 // recommended datasheet value
// 1 // probably not correct value from early datasheet (v0.4)
// 2 // (0) with (0xD9 -> 0xF9) // found in some codes/libs for rfm70/73
// 3 // (0) with (0xD9 -> 0xB9) // probably it comes from the early example codes // doesn't work ???????
// 4 // (0) with (0xD9 -> 0x09) // weird value that gave someone better range
// 5 // "single carrier mode" from datasheet - constant wave mode (after translation from chienglish) // instead of 'PLL_LOCK' ?? // testing purposes only
// 6 // NOT DOCUMENTED NOR TESTED // value for rfm73 in replace manual (rfm70->rfm73)
// 7 // NOT DOCUMENTED NOR TESTED // undocumented "high power mode" up to 15dBm (rfm73/bk2423)
// 8 // NOT DOCUMENTED NOR TESTED // (7) mixed with (6) - (0x0B -> 0x1B), (0x9E -> 0xB6)
// 9 // NOT DOCUMENTED NOR TESTED // (7) mixed with (6) - (0x0B -> 0x1B), (0xBE -> 0xB6), (0x84 -> 0x80)
// 10 // NOT DOCUMENTED NOR TESTED // (7) mixed with (6) - (0x0B -> 0x1B), (0xBE -> 0xB6), (0x84 -> 0x82)
// 11 // "In order to smooth the use of RF-2400PA" (Inhaos rebrand of bk2421 + PA)

#define RFM70_CONFIG_UNDOCUMENTED_RX_SEN 0
// Sensitivity in RX mode
// 0: Normal mode
// 1: High sensitivity mode(different CD detection values) // NOT DOCUMENTED NOR TESTED

#define RFM70_CONFIG_TX_PWR 1
// RF output power in TX mode:
// 0:Low power(-30dB down)
// 1:High power

#define RFM70_BANK1_REG5_MODE 1
// 0 // RSSI disabled
// 1 // RSSI enabled // consumes about 1 mA // bk2421 vs nRF24l01 guide

#define RFM70_RSSI_THRESHOLD_LEVEL 9 // 0-15
// 0: -97 dBm, 2 dB/step, 15: -67 dBm // datasheet and bk2421 vs nRF24l01 guide
// 2: -105 dBm, 2 dB/step (at least above 5) 15: -73 dBm // replace manual (rfm70->rfm73)
// who is correct ?

#define RFM70_BANK1_REGC_MODE 0
// 0 // default recommended value // 120 us PLL settling time
// 1 // NOT DOCUMENTED NOR TESTED // nrf24L01+ compatible mode from rfm73 // 130 us PLL settling time (may be 200us like in bk2411, or just not work)
// 2 // probably not correct value from early datasheet (v0.4) // also power-up value in rfm73 (70 not tested)

#define RFM70_BANK1_REGD_MODE 0
// 0 // recommended datasheet value
// 1 // NOT DOCUMENTED NOR TESTED // value for rfm73, from replace manual (rfm70->rfm73) // (bank1 is so documented that it might be obtained experimentally)

#define RFM70_BANK1_RAMP_CURVE_MODE 0
// 0 // rfm70/bk2421 // default recommended datasheet value
// 1 // NOT DOCUMENTED NOR TESTED // rfm73 datasheet and power-up value

/********************************************************************/

/********** bk2423 aka RFM73 - compatibility and sensitivity ********/

#define RFM73_BANK1_REG3_MODE 0
// 0 // default recommended value
// 1 // AN0007 "high power mode" 3-15dBm - may require additional low/band-pass filter for compliance with FCC rules // also "In order to smooth the use of RF-2400PA" (Inhaos rebrand of bk2421 + PA)
// 2 // datasheet "reset value"

#define RFM73_BANK1_REG4_MODE 1 // literally the worst register - all datasheets/AN's have different "correct" values for this register
// 0 // rfm70/bk2421 and rfm73/bk2423 datasheet values // AN0007 and AN0008 "default setting of reg4"
// 1 // replace manual (rfm70->rfm73), also used in all libraries which are not plain conversion from rfm70 // is said to be 3 dB gain in 1MHz and required for proper operation at 2MHz
// 2 // AN0007 "high power mode" up to 15dBm // RF_PWR in bank 0 should be set to 5dBm // may require additional low/band-pass filter for compliance with FCC rules
// 3 // (0) mixed with (1) // only obvious parts - (0x0B -> 0x1B), (0xBE -> 0xB6)
// 4 // (2) mixed with (1) // only obvious parts - (0x0B -> 0x1B), (0xBE -> 0xB6)
// 5 // (2) mixed with (1) // clear also bit 10 - (0x0B -> 0x1B), (0xBE -> 0xB6), (0x84 -> 0x80)
// 6 // "single carrier mode" from datasheet - constant wave mode (after translation from chienglish) // instead of 'PLL_LOCK' ?? // testing purposes only
// 7 // (4) with (0x84 -> 0x82)
// 8 // (0) with (0xD9 -> 0xF9) // found in some codes/libs for rfm70/73
// 9 // (0) with (0xD9 -> 0xB9) // probably it comes from the eary example codes // ??doesn't work on rfm70???
// 10 // (1) with (0xD9 -> 0xB9)
// 11 // (0) with (0xD9 -> 0x09) // weird value for rfm70 that gave someone better range
// 12 // (11) mixed with (3)
// 13 // adapt rfm70 "In order to smooth the use of RF-2400PA" (Inhaos rebrand of bk2421 + PA)
// 14 // (13) mixed with (1) - (0x0B -> 0x1B)
// 15 // (13) mixed with (1) - (0x0B -> 0x1B), (0xBE -> 0xB6)
// 16 // (15) with - (0x9A -> 9C)
// 17 // (15) with - (0x9A -> 9E)

#define RFM73_CONFIG_RX_SEN 1
// Sensitivity in RX mode
// 0: Normal mode
// 1: High sensitivity mode(different CD detection values)

#define RFM73_CONFIG_TX_PWR 1
// RF output power in TX mode:
// 0:Low power(-30dB down)
// 1:Normal power

#define RFM73_BANK1_REG5_MODE 1
// 0 // RSSI disabled
// 1 // RSSI enabled

#define RFM73_RSSI_THRESHOLD_LEVEL 9 // 0-15
// in bk2423/rfm73 RSSI level is not linear to threshold level
// RSSI levels are different at 250k/1M and 2M air data rate
// refering to AN0007, high sense mode affects rssi levels, so the default level is in N/A region // actually not true

#define RFM73_BANK1_REGC_MODE 1
// 0 // rfm70/bk2421 compatible // 120 us PLL settling time
// 1 // nrf24L01+ compatible // 130 us PLL settling time
// 2 // initial value after power up // 120 us PLL settling time // not used/mentioned anywhere
// 3 // initial value after power up // 130 us PLL settling time // not used/mentioned anywhere

#define RFM73_CONFIG_COMPATIBLE_MODE 1
// transmitter and receiver have to use the same mode, otherwise transmitter is seeing 100% packet loss
// This field probably controls the inversion of NO_ACK bit in the air payload in DPL mode
// 0:Static compatible // SI24R1 compatible
// 1:Dynamic compatible // recommended default value

#define RFM73_BANK1_REGD_MODE 1
// 0 // rfm70/bk2421 and rfm73/bk2423 datasheet values, also initial value that can be read after module power-up
// 1 // replace manual (rfm70->rfm73), also used in all libraries which are not plain conversion from rfm70 // it is said to be 3 dB gain in 1MHz and required for proper operation at 2MHz

#define RFM73_BANK1_RAMP_CURVE_MODE 1
// 0 // value recommended in rfm73/bk2423 datasheets, also the initial value that can be read after module power-up
// 1 // value recommended in rfm70/bk2421 datasheets and replace manual (rfm70->rfm73), also used in all libraries

/********************************************************************/

/********** bk2425 aka RFM75 - compatibility and sensitivity ********/

#define RFM75_BANK1_REG3_MODE 0
// 0 // recommended bk2425/rfm75 value
// 1 // datasheet "reset value"
// 3 // NOT DOCUMENTED NOR TESTED // (0) with undocumented high power mode bits set // no high power ??
// 4 // adapt rfm73 value from replace manual (rfm70->rfm73)
// 5 // NOT DOCUMENTED NOR TESTED // adapt rfm73 "high power" mode (AN0007) // NOT WORKING

#define RFM75_BANK1_REG4_MODE 0
// 0 // recommended value for 1Mbps
// 1 // recommended value for 2Mbps
// 2 // recommended value for 250kbps
// 3 // "single carrier mode" from datasheet - constant wave mode (after translation from chienglish) // instead of 'PLL_LOCK' ??
// 4 // NOT DOCUMENTED NOR TESTED // (0) with adapted rfm73 "high power" mode (AN0007) // clear undocumented bit 9 // no high power ??
// 5 // NOT DOCUMENTED NOR TESTED // (1) with adapted rfm73 "high power" mode (AN0007) // clear undocumented bit 9 // no high power ??
// 6 // NOT DOCUMENTED NOR TESTED // (2) with adapted rfm73 "high power" mode (AN0007) // clear undocumented bit 9 // no high power ??

#define RFM75_CONFIG_UNDOCUMENTED_RX_SEN 0
// Sensitivity in RX mode
// 0: Normal mode
// 1: High sensitivity mode(different CD detection values) // NOT DOCUMENTED NOR TESTED

#define RFM75_CONFIG_txIctrl 7 // reg4 <29:27> = txIctrl[2:0] in bk2423 // AN0007
// have to be set together with RF_PWR for exact power level, otherwise -1dBm(or undefined as usual) // user_guide_of_RF75
// 7 - value for 4 dBm power level
// 3 - value for -12,-18 dBm power levels
// 2 - value for -12 dBm power level
// 0 - value for -1,-7,-18,-25 dBm power levels

#define RFM75_BANK1_REG5_MODE 2
// 0 // recommended value for 1Mbps // RSSI disabled
// 1 // recommended value for 2Mbps and 250kbps // RSSI disabled
// 2 // recommended value for 1Mbps // RSSI enabled
// 3 // recommended value for 2Mbps and 250kbps // RSSI enabled
// 4 // NOT DOCUMENTED NOR TESTED // recommended value for 1Mbps // RSSI with selectable threshold
// 5 // NOT DOCUMENTED NOR TESTED // recommended value for 2Mbps and 250kbps // RSSI with selectable threshold
// 6 // rfm73 value adapted for 1Mbps // RSSI disabled
// 7 // rfm73 value adapted for 2Mbps and 250kbps // RSSI disabled
// 8 // rfm73 value adapted for 1Mbps // RSSI with selectable threshold
// 9 // rfm73 value adapted for 2Mbps and 250kbps // RSSI with selectable threshold

#define RFM75_UNDOCUMENTED_RSSI_THRESHOLD_LEVEL 9 // 0-15? // value is left shifted by 2 into MSB // 9
// officially there is no RSSI threshold for this chip, but obviously it's so undocumented that it could be implemented

#define RFM75_BANK1_REGC_MODE 1
// 0 // rfm70/bk2421 compatible // 120 us PLL settling time
// 1 // nrf24L01+ compatible // 130 us PLL settling time
// 2 // rfm73 adapt // initial value after power up // 120 us PLL settling time // not used/mentioned anywhere
// 3 // rfm73 adapt // initial value after power up // 130 us PLL settling time // not used/mentioned anywhere

#define RFM75_CONFIG_COMPATIBLE_MODE 0 //0 works when rfm receives and nrf24 transmits
// transmitter and receiver have to use the same mode, otherwise transmitter is seeing 100% packet loss
// This field probably controls the inversion of NO_ACK bit in the air payload in DPL mode
// 0:Static compatible // SI24R1 compatible
// 1:Dynamic compatible // recommended default value

#define RFM75_BANK1_REGD_MODE 0
// 0 // recommended bk2425/rfm75 value
// 1 // adapt rfm73 value from replace manual (rfm70->rfm73)

#define RFM75_BANK1_RAMP_CURVE_MODE 0
// 0 // recommended bk2425/rfm75 value
// 1 // adapt rfm73 datasheet value

/*********************************************************************/

/************* bk2411/2412 - compatibility and sensitivity ***********/

#define BK2411_BANK1_REG3_MODE 0
// 0 // reccomended value
// 1 // "reset value"

#define BK2411_BANK1_REG4_MODE 0
// 0 // reccomended value for 1 mpbs
// 1 // reccomended value for 2 mbps
// 2 // constant wave mode
// 3 // (0) with selectable crystal offset compensation
// 4 // (1) with selectable crystal offset compensation
// 5 // (2) with selectable crystal offset compensation

#define BK2411_XTALFC 0b1000 // default // signed ??? or unsigned with center at 8 ???
// Crystal offset compensation, center at 8.
// User can adjust this register to compensate crystal offset

#define BK2411_RSSI_THRESHOLD_LEVEL 9 // 0-15
// 0: -97 dBm, 2 dB/step, 15: -67 dBm

#define BK2411_BANK1_REGC_MODE 0
// 0 // default recommended value // 300 us PLL, 110 us ramping
// 1 // NOT TESTED // bk2421 compatible // 120 us PLL, 40 us ramping
// 2 // PLL lock and ramping time configurable below

#define BK2411_TX_LOCK_SEL 1
// Tx PLL lock time selection
// 0: 120 us, 1: 200 us, 2: 300 us, 3: 500 us

#define BK2411_TX_RAMP_SEL 10
// Tx PA ramping time selection
// 0: 10 us, 1: 20us, 2: 30 us, \85 , 15: 160 us

#define BK2411_BANK1_REGD_MODE 0
// 0 // reccomended value for 1 mpbs // <100ppm crystal accurancy, GFSK, BT = 1
// 1 // recommended value for 2 mbps // <5ppm (!) crystal accurancy, FSK
// 2 // (1) with <100ppm crystal accurancy
// 3 // (0) in long payload mode (255 bytes)
// 4 // (1) in long payload mode (255 bytes)
// 5 // (2) in long payload mode (255 bytes)
// 6 // selectable below

#define BK2411_CYST_ACCU 7
// Crystal accuracy, the worse accuracy requires the larger value
// Using 7 for crystal accuracy to about 100 PPM
// Using 0 for crystal accuracy better than 5PPM

#define BK2411_MODU_MOD 0
// Modulation type
// 0: GFSK mode // cleaner spectrum
// 1: FSK mode // better sensitivity

#define BK2411_GFSK_BT 1
// GFSK filter bandwidth ?? // BT = filter\92s -3dB BW / data rate
// 0: BT = 1 // less adjecent bits interference, better sensitivity
// 1: BT = 0.5 // less out of band emmisions

#define BK2411_LONG_PL 0
// Enable long payload in normal payload mode
// 0: Normal payload mode
// 1: Enable long payload mode

#define BK2411_LEN_LONG 255
// Payload length for maximum 255 bytes payload

/*********************************************************************/

/*************** bk5811 - compatibility and sensitivity **************/

#define BK5811_BANK1_DEFAULT_BAND 1
// reg 0, 2 and 3
// 0: tune to 5.1GHz band
// 1: tune to 5.8GHz band

#define BK5811_BANK1_REG4_MODE 0
// 0: default recommended value
// 1: "single carrier mode" - constant wave mode (after translation from chienglish)

#define BK5811_RSSI_THRESHOLD_LEVEL 9 // 0-15
//RSSI Threshold for CD detect
//0: -100 dBm, 2 dB/step, 15: -70 dBm

/*********************************************************************/
#endif /* RFM7X_CONFIG_H_ */
