librf24-WiringPi
================

This version of librf24-rpi takes the vanilla GPIO version (see folder "librf24"), removes the GPIO library used there, and replaces it with WiringPi. This allows WiringPi to be used in conjunction with this library, whereas there were compatability issues before.

IMPORTANT
=========

Note that there is a small difference between this version of the library and others. Because WiringPi allows you to use one of three pin numbering schemes (via wiringPiSetup, wiringPiSetupGpio/wiringPiSetupSys, and wiringPiSetupPhys), you have to pass along a constant to RF24::begin to let it know which scheme to use. Constants to use are below:

**wiringPiSetup** - WPI_MODE_PINS
**wiringPiSetupGpio** - WPI_MODE_GPIO
**wiringPiSetupSys** - WPI_MODE_GPIO_SYS (in this library, it's implemented the same as WPI_MODE_GPIO)
**wiringPiSetupPhys** - WPI_MODE_PHYS

Existing code can be retrofitted to use this library by changing two lines:
1. In the program initialization, call wiringPiSetupGpio();
2. In radio.begin(), add the WPI_MODE_GPIO argument to get radio.begin(WPI_MODE_GPIO);

Note that EVERY pin referenced in your code, including the CE pin you pass to the constructor, must use whatever pin numbering scheme you tell WiringPi to use.

Contact
=======

Trey Keown - jfktrey@gmail.com