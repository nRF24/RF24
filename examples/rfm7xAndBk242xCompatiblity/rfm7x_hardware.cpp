#if defined(ARDUINO)
	#include <Arduino.h>
	#include <SPI.h>
#elif defined(__AVR_ARCH__)
	#include <avr/io.h>
#else
	#include <cmsis_device.h>
#endif

#include "rfm7x_hardware.h"

void rfm7x_io_init(void) //hardcoded at the moment
{
	RFM7x_CSN_HI;
	RFM7x_CE_LOW;

#if defined(USE_EXAMPLE_SPI_MEGA328)
	//set ce to output
	//set csn to output
#elif defined(USE_EXAMPLE_SPI_XMEGA)

	//PORTC.DIRSET = PIN4_bm | PIN1_bm; // as output
#elif defined(USE_EXAMPLE_SPI_STM32F0)

	//RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

	//GPIOA->MODER  |= (1 << __builtin_ctz(GPIO_MODER_MODER3)) | (1 << __builtin_ctz(GPIO_MODER_MODER4)); // set PA3 and PA4 to output
#elif defined(USE_EXAMPLE_SPI_ARDUINO)
		
	pinMode(8,OUTPUT); // ce
	pinMode(9,OUTPUT); //csn
#else // soft
	//set ce to output
	//set csn to output
#endif
}

void spi_init(void)
{
#if defined(USE_EXAMPLE_SPI_MEGA328)
	DDRB |= (1 << PB3) | (1 << PB5); // configure output pins
	PORTB |= (1 << PB4); // pullup miso

	SPCR |= (1 << SPE) | (1 << MSTR);
	SPSR |= (1 << SPI2X);
	
#elif defined(USE_EXAMPLE_SPI_XMEGA)
	PORTC.DIRSET = PIN5_bm | PIN7_bm; // sck , mosi
	PORTC.PIN6CTRL = PORT_OPC_PULLUP_gc; // pullup miso
	SPIC.CTRL = SPI_ENABLE_bm | SPI_MASTER_bm | SPI_MODE_0_gc | SPI_PRESCALER_DIV4_gc; // 32MHz/4
#elif defined(USE_EXAMPLE_SPI_STM32F0)

	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	GPIOA->MODER  |= (2 << __builtin_ctz(GPIO_MODER_MODER5))|(2 << __builtin_ctz(GPIO_MODER_MODER6))|(2 << __builtin_ctz(GPIO_MODER_MODER7)); // PA5, PA6, PA7 as alternate
	//GPIOA->AFR[0] &= ~((0x0f << __builtin_ctz(GPIO_AFRL_AFR5))|(0x0f << __builtin_ctz(GPIO_AFRL_AFR6))|(0x0f << __builtin_ctz(GPIO_AFRL_AFR7)));
	//GPIOA->AFR[0] |= (0 << __builtin_ctz(GPIO_AFRL_AFR5))|(0 << __builtin_ctz(GPIO_AFRL_AFR6))|(0 << __builtin_ctz(GPIO_AFRL_AFR7));

	GPIOA->OSPEEDR |= (3 << __builtin_ctz(GPIO_OSPEEDR_OSPEEDR5))|(3 << __builtin_ctz(GPIO_OSPEEDR_OSPEEDR7)); // set SCK and MOSI into high speed mode
	GPIOA->PUPDR |= (1 << __builtin_ctz(GPIO_PUPDR_PUPDR6)); // pullup miso

	SPI1->CR2 |= SPI_CR2_FRXTH; // RXNE treshold at 1 byte
	SPI1->CR1 = SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_SPE | (2 << __builtin_ctz(SPI_CR1_BR)) | SPI_CR1_MSTR; // soft NSS force to master, enable, PCLK/8, master
	//SSOE ???
#elif defined(USE_EXAMPLE_SPI_ARDUINO)
	SPI.begin();
	
	// necessary?
	//SPI.setBitOrder(MSBFIRST);
	//SPI.setDataMode(SPI_MODE0);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
#else
	// can be optimized into single write if port wiring allows
	SOFT_SPI_SCK_DIRSET();
	SOFT_SPI_MOSI_DIRSET();
	SOFT_SPI_MISO_DIRSET(); // always input after POR, can be commented out
	SOFT_SPI_MISO_PULLUP_SET(); // ??
#endif
}

uint8_t spi_rw(uint8_t data)
{
#if defined(USE_EXAMPLE_SPI_MEGA328)
	SPDR = data;
	while (!(SPSR & (1 << SPIF)));

	return SPDR;
	
#elif defined(USE_EXAMPLE_SPI_XMEGA)
	SPIC.DATA = dat;
	while(!(SPIC.STATUS & (1<<7))); // no SPIF defined

	return SPIC.DATA;

#elif defined(USE_EXAMPLE_SPI_STM32F0)
	
	while( (SPI1->SR & SPI_SR_BSY) );
	*(uint8_t *)&(SPI1->DR) = data; // cast to make 8 bit transfer and thus transmit only 8bit frame
	while( !(SPI1->SR & SPI_SR_RXNE) );
	data = SPI1->DR;
	return data;
#elif defined(USE_EXAMPLE_SPI_ARDUINO)
	uint8_t tmp = SPI.transfer(data);
	return tmp;
#else
	for(uint_fast8_t i = 0; i < 8; i++)
	{
		if (data & 0x80) 
			SOFT_SPI_MOSI_HI();
		else 
			SOFT_SPI_MOSI_LO();
		
		//_delay_us(0.125);
		//_delay_us(1);
		delayMicroseconds(1);
		SOFT_SPI_SCK_HI();
		delayMicroseconds(1);
		// _delay_us(1);
		
		data <<= 1;
		 
		if (SOFT_SPI_MISO_READ()) 
			data |= 0x01; // data++

		// _delay_us(0.125);
		delayMicroseconds(1);
		SOFT_SPI_SCK_LO();
		// _delay_us(0.125);
		delayMicroseconds(1);
	 }
	 
	 return data;
#endif	
}

void spi_reg_write(uint8_t reg, uint8_t dat)
{
	spi_rw(reg);
	spi_rw(dat);
}

uint8_t spi_reg_read(uint8_t reg)
{
	uint8_t tmp;
	
	spi_rw(reg);
	tmp = spi_rw(0);
	
	return tmp; // spi_rw(spi_rw(reg))
}

void spi_reg_buff_write(uint8_t reg, uint8_t *buff, uint8_t len)
{
	spi_rw(reg);
	
	for(uint8_t i=0; i<len; i++)
		spi_rw(buff[i]);
}

void spi_buff_write(uint8_t *buff, uint8_t len)
{
	for(uint_fast8_t i=0; i<len; i++)
		spi_rw(buff[i]);
}

void spi_reg_buff_read(uint8_t reg, uint8_t *buff, uint8_t len)
{
	spi_rw(reg);
	
	for(uint8_t i=0; i<len; i++)
		buff[i] = spi_rw(0);
}

void spi_buff_read(uint8_t *buff, uint8_t len)
{
	for(uint_fast8_t i=0; i<len; i++)
		buff[i] = spi_rw(0);
}
