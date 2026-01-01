# epaper-orrery

Create an image of our solar system on a [4.2" waveshare e-paper display v2](https://www.waveshare.com/4.2inch-e-paper-module.htm). 

**Warning!**

According to [waveshare's wiki](https://www.waveshare.com/wiki/4.2inch_e-Paper_Module_Manual#Precautions), you can damage your display *if you leave the display powered on for a long period of time*, or *partially refresh too often* without a full refresh.

## Interface

Connect a microcontroller to the display's carrier board. It uses one way SPI. Image data travels on the SDA/DIN line, with commands over the DC line. I'm using a raspberry pi, so have included the pinout in the table below. 

|Pin | Desc |
|-|-|
| RST | Hardware reset | 
| DC | Data/Command line|
| CS | Chip select | |
| CLK | Clock |
| DIN | *MISO* (master in slave out) aka *SDI* (serial data in).<br> Connect this to your host's *MOSI* (master out slave in) aka *SDO* (serial data out) |
| GND | Ground |
| VCC | Power (3.3 or 5v) |

The display expects two black and white images to be written to two different registers each time you'd like to display something- each representing a 4-level grayscale image. Each of the resultant pixel’s grayscale value is formed by combining the corresponding pixels from these two images.