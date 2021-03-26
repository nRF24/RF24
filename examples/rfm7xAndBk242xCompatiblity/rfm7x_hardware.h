#ifndef RFM7X_HARDWARE_H_
#define RFM7X_HARDWARE_H_

#include <Arduino.h>

//#define USE_EXAMPLE_SPI_MEGA328
//#define USE_EXAMPLE_SPI_XMEGA
//#define USE_EXAMPLE_SPI_STM32F0
#define USE_EXAMPLE_SPI_ARDUINO
//else soft

//haedcoded at the moment
#define RFM7x_CSN_LOW digitalWrite(8, LOW)
#define RFM7x_CSN_HI  digitalWrite(8, HIGH)

#define RFM7x_CE_LOW  digitalWrite(7, LOW)
#define RFM7x_CE_HI   digitalWrite(7, HIGH)

#if !defined(USE_EXAMPLE_SPI_MEGA328) && !defined(USE_EXAMPLE_SPI_XMEGA) && !defined(USE_EXAMPLE_SPI_STM32F0) && !defined(USE_EXAMPLE_SPI_ARDUINO)
// tiny 2313 in this case

#define SOFT_SPI_MOSI_DIRSET() DDRB |= (1 << PB5)
#define SOFT_SPI_MISO_DIRSET() DDRB &= ~(1 << PB6)
#define SOFT_SPI_SCK_DIRSET() DDRB |= (1 << PB7)
#define SOFT_SPI_MISO_PULLUP_SET() PORTB |= (1 << PB6)

#define SOFT_SPI_MOSI_HI() PORTB |= (1 << PB5)
#define SOFT_SPI_MOSI_LO() PORTB &= ~(1 << PB5)

#define SOFT_SPI_SCK_HI() PORTB |= (1 << PB7)
#define SOFT_SPI_SCK_LO() PORTB &= ~(1 << PB7)

#define SOFT_SPI_MISO_READ() PINB &(1 << PB6)
#endif

//define here your functions if needed (also add extern declaration above)
#define rfm7x_spi_rw(__data) spi_rw(__data)
#define rfm7x_buff_write(__buff,__len) spi_buff_write(__buff,__len)
#define rfm7x_buff_read(__buff,__len) spi_buff_read(__buff,__len)

#ifdef __cplusplus
	extern "C" {
#endif

	void rfm7x_io_init(void); // initialize CE and CSN outputs

	void spi_init(void);

	uint8_t spi_rw(uint8_t data);

	//universal spi functions (no CSN/SS handling)
	void spi_reg_write(uint8_t reg, uint8_t dat);
	uint8_t spi_reg_read(uint8_t reg);

	void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len);
	void spi_buff_write(uint8_t *buff, uint8_t len);

	void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len);
	void spi_buff_read(uint8_t *buff, uint8_t len);

#ifdef __cplusplus
	}
#endif

#endif // RFM7X_HARDWARE_H_
