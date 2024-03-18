/*
 *
 */

#ifndef RF24_UTILITY_PIGPIO_GPIO_H_
#define RF24_UTILITY_PIGPIO_GPIO_H_

#include <stdexcept>

/** Specific exception for GPIO errors */
class GPIOException : public std::runtime_error
{
public:
    explicit GPIOException(const std::string& msg)
        : std::runtime_error(msg)
    {
    }
};

class GPIO
{
public:
    /* Constants */
    static const int DIRECTION_OUT = 1;
    static const int DIRECTION_IN = 0;

    static const int OUTPUT_HIGH = 1;
    static const int OUTPUT_LOW = 0;

    GPIO();

    /**
     * Similar to Arduino pinMode(pin,mode);
     * @param port
     * @param DDR
     */
    static void open(int port, int DDR);

    /**
     *
     * @param port
     */
    static void close(int port);

    /**
     * Similar to Arduino digitalRead(pin);
     * @param port
     */
    static int read(int port);

    /**
     * Similar to Arduino digitalWrite(pin,state);
     * @param port
     * @param value
     */
    static void write(int port, int value);

    virtual ~GPIO();

private:
};

#endif /* RF24_UTILITY_PIGPIO_GPIO_H_ */
