# Soil Moisture Sensor
A simple soil moisture sensor using an Arduino UNO microcontroller.

## Components Used

- [Arduino UNO](https://botland.com.pl/arduino-seria-podstawowa-oryginalne-plytki/1060-arduino-uno-rev3-a000066-7630049200050.html)
- [Soil Moisture Sensor](https://botland.com.pl/gravity-czujniki-pogodowe/10305-dfrobot-gravity-analogowy-czujnik-wilgotnosci-gleby-odporny-na-korozje-sen0193-5903351243155.html?cd=18298825651&ad=&kd=&gclid=CjwKCAjwgqejBhBAEiwAuWHioMwWA4SEuGi1RUKJWuG2f7o5MhYemAxIOgkFh670djLlfkb2HUvX_BoCisoQAvD_BwE)
- [LCD Display (2x16) with I2C Module](https://botland.com.pl/wyswietlacze-alfanumeryczne-i-graficzne/2351-wyswietlacz-lcd-2x16-znakow-niebieski-konwerter-i2c-lcm1602-5904422309244.html)

## Code
This program is written in the C++ programming language.

👉 [View Code](https://github.com/vBagieta/SimpleSoilMoistureSensor/blob/main/soil-moisture-sensor.ino)

## Used Libraries
- [hd44780](https://www.arduinolibraries.info/libraries/hd44780)
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

# Connections
| Arduino Pin | Display Pin | Sensor Pin |
|-------------|-------------|------------|
| GND         | GND         | GND        |
| A4         | SDA              | ❌            |
| A5         | SCL             | ❌            |
| A0          | ❌          | AOUT       |
| 5V          | VCC         | ❌          |
| 3.3V        | ❌          | VCC        |

# Calibration
### Sensor Calibration Code
The sensor data pin is connected to pin `A0`.

```cpp
void setup() {
  Serial.begin(9600);
}
void loop() {
  int value;
  value = analogRead(A0);
  Serial.println(value);
  delay(100);
}
```
### Steps
First, record the highest value the sensor obtains when dry. Change the value in the code (default is 603) to the measured value:
```cpp
const int dryValue = 616; -> const int dryValue = YOUR_VALUE;
```

Next, measure the value the sensor obtains when wettest. Measure and replace the value in the code:
```cpp
const int wetValue = 292; -> const int wetValue = YOUR_VALUE;
```

Now, upload the code to the Arduino and everything should work!
