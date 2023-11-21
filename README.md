# 🇵🇱 Czujnik wilgotnośći gleby
Prosty czujnik wilgotności gleby używający mikrokontrolera Arduino UNO. 

## Użyte elementy

- [Arduino UNO](https://botland.com.pl/arduino-seria-podstawowa-oryginalne-plytki/1060-arduino-uno-rev3-a000066-7630049200050.html)
- [Czujnik wilgotności gleby](https://botland.com.pl/gravity-czujniki-pogodowe/10305-dfrobot-gravity-analogowy-czujnik-wilgotnosci-gleby-odporny-na-korozje-sen0193-5903351243155.html?cd=18298825651&ad=&kd=&gclid=CjwKCAjwgqejBhBAEiwAuWHioMwWA4SEuGi1RUKJWuG2f7o5MhYemAxIOgkFh670djLlfkb2HUvX_BoCisoQAvD_BwE)
- [Wyświetlacz LCD (2x16) wraz z modułem I2C](https://botland.com.pl/wyswietlacze-alfanumeryczne-i-graficzne/2351-wyswietlacz-lcd-2x16-znakow-niebieski-konwerter-i2c-lcm1602-5904422309244.html)

## Kod
Ten program jest napisany w języku programowania C++.

👉 [Wyświetl kod](https://github.com/vBagieta/SimpleSoilMoistureSensor/blob/main/soil-moisture-sensor.ino)

## Wykorzystane biblioteki
- [hd44780](https://www.arduinolibraries.info/libraries/hd44780)
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

# Połączenia
| Pin Arduino | Pin wyświetlacza | Pin czujnika |
|-------------|------------------|--------------|
| GND         | GND              | GND          |
| A4         | SDA              | ❌            |
| A5         | SCL             | ❌            |
| A0          | ❌                | AOUT         |
| 5V          | VCC              | ❌            |
| 3.3V        | ❌                | VCC          |

# Kalibracja
### Kod do kalibracji czujnika
Pin danych z czujnika został podpięty do pinu `A0`.

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
### Kroki
Na początku zapisz najwyższą wartość, jaką czujnik uzyskuje, gdy jest suchy. Zmień wartość w kodzie (domyślnie 603) na zmierzoną:
```cpp
const int dryValue = 616; -> const int dryValue = TWOJA_WARTOŚĆ;
```

Następnie zmierz wartość, jaką czujnik uzyskuje, gdy jest najbardziej mokry. Zmierz wartość na zmierzoną.

```cpp
const int wetValue = 292; -> const int wetValue = TWOJA_WARTOŚĆ;
```


Teraz wystarczy załadować kod do Arduino i wszytko powinno działać!

# Zasada działania

Czujnik co 100ms sprawdza poziom wilgotności gleby. Następnie ta wartość jest przesyłana do Arduino, gdzie zostaje przetworzona. Na jej podstawie kontroler określa procent wilgotność gleby zgodnie ze zmienną:

```cpp
percent = 100-((soilCapacityValue-(dryValue-wetValue))*100)/wetValue;
```

Ta zmienna prezentuje poziom wilgotności w procentach, na podstawie której tworzony jest pasek wilgotności gleby.

# Koniec

Jeżeli wykonałeś wszytkie kroki i myślałeś czujnik powinien być gotowy do pracy!

# 🇬🇧 Soil Moisture Sensor
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

Now, upload the code to Arduino, and everything should work!

# Operating Principle

The sensor checks the soil moisture level every 100ms. The value is then transmitted to Arduino, where it is processed. Based on this value, the controller determines the percentage of soil moisture according to the formula:

```cpp
percent = 100-((soilCapacityValue-(dryValue-wetValue))*100)/wetValue;
```

This variable represents the moisture level in percentage, used to create the soil moisture bar.

# Conclusion

If you have followed all the steps, the sensor should be ready to work!
