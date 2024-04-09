#include <string.h> // memset()
#include "spi.h"

SPIClass::SPIClass() : bus(nullptr)
{
}

void SPIClass::begin(spi_host_device_t busNo, uint32_t speed)
{
    spi_bus_config_t busConfig;
    // We will use the pins corresponding to the specified busNo (appropriate config option).
    // Users can also pass a customized bus config to SPIClass::begin() overload if/when
    // a secondary SPI bus is desired.
#ifdef CONFIG_RF24_DEFAULT_MOSI
    busConfig.mosi_io_num = CONFIG_RF24_DEFAULT_MOSI;
#else
    busConfig.mosi_io_num = -1; // GPIO13 on SPI2_HOST; GPIO23 on SPI3_HOST
#endif
    busConfig.data0_io_num = -1;
#ifdef CONFIG_RF24_DEFAULT_MISO
    busConfig.miso_io_num = CONFIG_RF24_DEFAULT_MISO;
#else
    busConfig.miso_io_num = -1; // GPIO12 on SPI2_HOST; GPIO19 on SPI3_HOST
#endif
    busConfig.data1_io_num = -1;
#ifdef CONFIG_RF24_DEFAULT_SCLK
    busConfig.sclk_io_num = CONFIG_RF24_DEFAULT_SCLK;
#else
    busConfig.sclk_io_num = -1; // GPIO14 on SPI2_HOST; GPIO18 on SPI3_HOST
#endif
    busConfig.quadwp_io_num = -1;
    busConfig.data2_io_num = -1;
    busConfig.quadhd_io_num = -1;
    busConfig.data3_io_num = -1;
    busConfig.data4_io_num = -1;
    busConfig.data5_io_num = -1;
    busConfig.data6_io_num = -1;
    busConfig.data7_io_num = -1;
    busConfig.max_transfer_sz = 33; // RF24 lib only buffers 33 bytes for SPI transactions
    busConfig.flags = 0;
    busConfig.isr_cpu_id = ESP_INTR_CPU_AFFINITY_AUTO;
    busConfig.intr_flags = 0;

    begin(busNo, speed, SPI_MODE0, &busConfig);
}

void SPIClass::begin(spi_host_device_t busNo, uint32_t speed, uint8_t mode, spi_bus_config_t* busConfig)
{
    esp_err_t ret = spi_bus_initialize(busNo, busConfig, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

    spi_device_interface_config_t device_conf;
    device_conf.mode = mode;
    device_conf.clock_source = SPI_CLK_SRC_DEFAULT;
    device_conf.clock_speed_hz = speed;
    device_conf.input_delay_ns = 0; // delay not needed between CSN assert and MISO start
    device_conf.spics_io_num = -1;  // RF24::csn() will control the CSN pin
    device_conf.flags = 0;
    // we won't be using queued or interrupt-triggered SPI transactions.
    // disable those related features' config
    device_conf.queue_size = 0;
    device_conf.pre_cb = nullptr;
    device_conf.post_cb = nullptr;

    ret = spi_bus_add_device(busNo, &device_conf, &bus);
    ESP_ERROR_CHECK(ret);
}

uint8_t SPIClass::transfer(uint8_t tx_)
{
    uint8_t recv = 0;
    transfernb(&tx_, &recv, 1);
    return recv;
}

void SPIClass::transfernb(const uint8_t* txBuf, uint8_t* rxBuf, uint32_t len)
{
    spi_transaction_t transactionConfig;
    memset(&transactionConfig, 0, sizeof(transactionConfig));
    transactionConfig.length = len * 8; // in bits, not bytes
    transactionConfig.tx_buffer = txBuf;
    transactionConfig.rx_buffer = rxBuf;
    esp_err_t ret = spi_device_polling_transmit(bus, &transactionConfig);
    ESP_ERROR_CHECK(ret);
}

void SPIClass::transfern(const uint8_t* buf, uint32_t len)
{
    transfernb(buf, NULL, len);
}

void SPIClass::beginTransaction()
{
    esp_err_t ret = spi_device_acquire_bus(bus, portMAX_DELAY);
    ESP_ERROR_CHECK(ret);
}

void SPIClass::endTransaction()
{
    spi_device_release_bus(bus);
}

SPIClass::~SPIClass()
{
    if (bus != nullptr) {
        esp_err_t ret = spi_bus_remove_device(bus);
        ESP_ERROR_CHECK(ret);
    }
}
