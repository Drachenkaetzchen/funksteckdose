This is the controller software for switching Intertechno compatible wireless controlled outlets via an RFM12 module plugged
onto a Raspberry Pi.

# Compiling

- Clone this repository
- Issue a `git submodule init` then `git submodule update` - this pulls in the librfm12
- Issue "make"

# Wiring up

By default, the program uses `/dev/spidev0.0`. If you have your RFM12 module on `CS1` instead of `CS0`, you need to change the SPI Device. Feel free to add command line parsing of the SPI device.

Additionally, I offer the `PiRFM12`, which is a simple adapter board on
https://www.tindie.com/products/Felicitus/pirfm12/. The source files for the board are available at
https://github.com/felicitus/pirfm12 if you wish to make your own board or improve my design.

# Usage

First, make sure you have loaded the `spi_bcm2708` module. Then you need to figure out the code for your wireless controlled outlet.
The FHEM wiki has some pointers for the code calculation: http://www.fhemwiki.de/wiki/Intertechno_Code_Berechnung. The complete
usage is:

```
Usage: ./funksteckdose [CODE] [OFF] [ON] [STATE]

[CODE]  The calculated system+device code. 10 byte length, use 0 and F for false and true. For more information see [1]
[OFF]   The off code, usually F0
[ON]    The on code, usually 0F
[STATE] Either the keyword 'off' or 'on'

[1] http://www.fhemwiki.de/wiki/Intertechno_Code_Berechnung
```

# Integration with OpenHAB

I use this program for controlling my outlets via OpenHAB. For that purpose, I copied the binary to /usr/local/bin and setuid root it:

```
cp funksteckdose /usr/local/bin/funksteckdose
chmod +s /usr/local/bin/funksteckdose
```

An example configuration line for switching an outlet off and on looks like this:

```
Switch Lights_Bedlamp "Bed Lamp" (Lights) {exec="OFF:/usr/local/bin/funksteckdose 00000FFFF0 0F F0 off,ON:/usr/local/bin/funksteckdose 00000FFFF0 0F F0 on"}
```