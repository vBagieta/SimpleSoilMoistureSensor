# 🇵🇱 Czujnik wilgotnośći gleby
Prosty czujnik wilgotności gleby używający mikrokontrolera Arduino UNO. 

[Wyświetl kod](https://github.com/vBagieta/soil-moisture-sensor/blob/main/soil-moisture-sensor.ino)
### Użyte elementy
- [Arduino UNO](https://botland.com.pl/arduino-seria-podstawowa-oryginalne-plytki/1060-arduino-uno-rev3-a000066-7630049200050.html)
- [Czujnik wilgotności gleby](https://botland.com.pl/gravity-czujniki-pogodowe/10305-dfrobot-gravity-analogowy-czujnik-wilgotnosci-gleby-odporny-na-korozje-sen0193-5903351243155.html?cd=18298825651&ad=&kd=&gclid=CjwKCAjwgqejBhBAEiwAuWHioMwWA4SEuGi1RUKJWuG2f7o5MhYemAxIOgkFh670djLlfkb2HUvX_BoCisoQAvD_BwE)
- [Wyświetlacz LCD (2x16) wraz z modułem I2C](https://botland.com.pl/wyswietlacze-alfanumeryczne-i-graficzne/2351-wyswietlacz-lcd-2x16-znakow-niebieski-konwerter-i2c-lcm1602-5904422309244.html)

### Język programowania

Ten program jest napisany w języku programowania C++.


### Wykorzystane biblioteki
- [hd44780](https://www.arduinolibraries.info/libraries/hd44780)
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)


# Połączenia

| Pin I2C  | Pin Arduino |
|-------------------|-------------|
| GND               | GND         |
| VCC               | 5V          |
| SDA               | SDA         |
| SCL               | SCL         |

| Pin czujnika | Pin Arduino |
|--------------|-------------|
| GND          | GND         |
| VCC          | 3.3V        |
| AUOT         | A0          |

# Kalibracja
### Kod do kalibracji czujnika
Pin danych z czujnika został podpięty do pinu `A0`!

```cpp
void setup() {
  Serial.begin(9600);
}
void loop() {
  int val;
  val = analogRead(A0);
  Serial.println(val);
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
```percent = 100-((soilCapacityValue-(dryValue-wetValue))*100)/wetValue;```

Na podstawie tej wartości funkcja `displayMoistureBar` tworzy z niestandardowych znaków pasek postępu, który uwzględnia już błąd pomiarowy (109% -> 100%, -10% -> 0%). Błąd pomiarowy powstaje wskutek złej kalibracji czujnika.

W podobny sposób funkcja `displayFixedPercentage` przedstawia już wartość która jeżeli nie zawiera się w przedziale 0-100, zostanie zamieniona na najbliższą wartość (0% lub 100%). 

Funkcje po przetworzeniu wszystkich danych tworzą obraz na wyświetlaczu, komunikując się z nim modułem I2C. 

# 🇺🇸 Soil Moisture Sensor
A simple soil moisture sensor using the Arduino UNO microcontroller.

[View Code](https://github.com/vBagieta/soil-moisture-sensor/blob/main/soil-moisture-sensor.ino)

### Components Used
- [Arduino UNO](https://botland.com.pl/arduino-seria-podstawowa-oryginalne-plytki/1060-arduino-uno-rev3-a000066-7630049200050.html)
- [Soil Moisture Sensor](https://botland.com.pl/gravity-czujniki-pogodowe/10305-dfrobot-gravity-analogowy-czujnik-wilgotnosci-gleby-odporny-na-korozje-sen0193-5903351243155.html?cd=18298825651&ad=&kd=&gclid=CjwKCAjwgqejBhBAEiwAuWHioMwWA4SEuGi1RUKJWuG2f7o5MhYemAxIOgkFh670djLlfkb2HUvX_BoCisoQAvD_BwE)
- [LCD Display (2x16) with I2C Module](https://botland.com.pl/wyswietlacze-alfanumeryczne-i-graficzne/2351-wyswietlacz-lcd-2x16-znakow-niebieski-konwerter-i2c-lcm1602-5904422309244.html)

### Programming Language
This program is written in the C++ programming language.

### Used Libraries
- [hd44780](https://www.arduinolibraries.info/libraries/hd44780)
- [Wire](https://www.arduino.cc/reference/en/language/functions/communication/wire/)

# Connections

| Display Pin  | Arduino Pin |
|--------------|-------------|
| GND          | GND         |
| VCC          | 5V          |
| SDA          | SDA         |
| SCL          | SCL         |

| Sensor Pin   | Arduino Pin |
|--------------|-------------|
| GND          | GND         |
| VCC          | 3.3V        |
| AUOT         | A0          |

# Calibration
### Sensor Calibration Code
The sensor data pin is connected to pin `A0`!

```cpp
void setup() {
  Serial.begin(9600);
}
void loop() {
  int val;
  val = analogRead(A0);
  Serial.println(val);
  delay(100);
}
```

### Steps
1. First, record the highest value the sensor obtains when it's dry. Change the value in the code (default is 603) to the measured value:
   ```cpp
   const int dryValue = 616; -> const int dryValue = YOUR_VALUE;
   ```

2. Then measure the value the sensor obtains when it's most wet. Measure and update the value in the code:
   ```cpp
   const int wetValue = 292; -> const int wetValue = YOUR_VALUE;
   ```

Now, load the code onto Arduino, and everything should work!

# Operating Principle

The sensor checks the soil moisture level every 100ms. Subsequently, this value is transmitted to Arduino, where it undergoes processing. Based on this information, the controller determines the soil moisture percentage using the formula:
```percent = 100-((soilCapacityValue-(dryValue-wetValue))*100)/wetValue;```

Using this value, the `displayMoistureBar` function creates a progress bar with custom characters, accounting for measurement errors (109% -> 100%, -10% -> 0%). Measurement errors result from sensor miscalibration.

Similarly, the `displayFixedPercentage` function presents a value that, if outside the range of 0-100, will be rounded to the nearest limit (0% or 100%).

After processing all the data, all the functions generate an image on the display by communicating with the I2C module.
