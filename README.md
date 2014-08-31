HDMI2C
======

HDMI I2C hacking n fooling around


## EDID
This simple tool dumps the content of the I2C EEPROM chip in the EDID of a display / TV.
There really isn't anything particuliar with that, i2c-dump in the [i2c-tool](www.lm-sensors.org/wiki/I2CTools) collection will work at least as well.
This more a little example on how you can communicate with I2C devices using HDMI/VGA/DVI port of your computer.
Before running that, you will need to install [i2c-dev](), and then loading the module i2c-dev with `sudo modprobe i2c-dev`

## adxl345
As it's names tells, it is meant to read an adxl345 accelerometer.

It uses combined read/write transaction without stop, so we should use 
```C
struct i2c_msg tx_msg, rx_msg;
// we should configure rx_msg and tx_msg
struct i2c_rdwr_ioctl_data exchange = {
	{tx_msg, rx_msg},	/* ptr to array of simple messages */
	2					/* number of messages to exchange */
};
ioctl(file, I2C_RDWR, &exchange);
```
from [i2c-dev lib](https://www.kernel.org/doc/Documentation/i2c/dev-interface).
So yeah, you will need the libi2c-dev lib. Il just had to type ```sudo apt-get install libi2c-dev``` on my computer.

In the future, this tool will also gives an FFT decomposition of the sampled signal, and maybe even to help balancing a rotating shaft.
