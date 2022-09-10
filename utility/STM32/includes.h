#ifndef RF24_UTILITY_STM32_INCLUDES_H_
#define RF24_UTILITY_STM32_INCLUDES_H_

#if defined(STM32F1)
    #include "stm32f1xx_hal.h"
    #include "stm32f1xx_hal_gpio.h"
    #include "stm32f1xx_hal_spi.h"
#elif defined(STM32F3)
    #include "stm32f3xx_hal.h"
    #include "stm32f3xx_hal_gpio.h"
    #include "stm32f3xx_hal_spi.h"
#elif defined(STM32F4)
    #include "stm32f4xx_hal.h"
    #include "stm32f4xx_hal_gpio.h"
    #include "stm32f4xx_hal_spi.h"
#endif

#endif // RF24_UTILITY_STM32_INCLUDES_H_
