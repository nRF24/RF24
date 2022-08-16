#include "RF24_arch_config.h"


static uint32_t rf24_get_time_us()
{
    return 1000 * HAL_GetTick() + 1000 - (SysTick->VAL / (SystemCoreClock / 1000000));
}


void delayMicroseconds(uint32_t usecs)
{
    uint32_t now = rf24_get_time_us();
    uint32_t blocked_until = now + usecs;
    while (blocked_until > rf24_get_time_us()) {}
}


DummySpi::DummySpi(SPI_HandleTypeDef *hspi) {
    _hspi = hspi;
}


void DummySpi::begin() {
    HAL_SPI_Init(_hspi);
}


uint8_t DummySpi::transfer(uint8_t data_to_send) {
    const uint16_t size = 1;
    uint8_t rx_data;
    HAL_SPI_TransmitReceive(_hspi, &data_to_send, &rx_data, size, HAL_MAX_DELAY);
    return rx_data;
}

uint32_t DummySpi::get_baud() {
    // This method was tested with stm32f103c8t6. It may be different on other architectures
    const uint8_t actual_config = _hspi->Init.BaudRatePrescaler;
    uint16_t preescaler = 2;
    if ((actual_config & SPI_CR1_BR_0) > 0)
        preescaler = 2 * preescaler;
    if ((actual_config & SPI_CR1_BR_1) > 0)
        preescaler = 4 * preescaler;
    if ((actual_config & SPI_CR1_BR_2) > 0)
        preescaler = 16 * preescaler;
    uint32_t baud = SystemCoreClock / preescaler;
    return baud;
}
