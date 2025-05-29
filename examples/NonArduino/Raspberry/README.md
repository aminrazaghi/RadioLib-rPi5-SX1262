# Connection
| SX1262 | rPi5 |
| --- | --- |
| CS | 32: GPIO-12 |
| CLK | 23: SCLK |
| MOSI | 19: MOSI |
| MISO | 21: MISO |
| RESET | 22: GPIO-25 |
| BUSY | 13: GPIO-27 |
| RXEN | 16: GPIO-23 |
| TXEN | 15: GPIO-22 |
| DIO2 | - |
| DIO1 | 18: GPIO-24 |
| GND | 14: GND |
| 3V3 | 17: 3.3V |


# Commands:
```console
git clone https://github.com/jgromes/RadioLib.git

sudo apt install git build-essential libgpiod-dev
cd RadioLib/examples/NonArduino/Raspberry/
sudo ./clean.sh
sudo ./build.sh
sudo ./build/rpi-sx1261
```
