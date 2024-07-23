#include <Wire.h>
#include <hd44780.h>                          
#include <hd44780ioClass/hd44780_I2Cexp.h>

hd44780_I2Cexp lcd;
hd44780_I2Cexp lcd2(0x27);

const int LCD_COLS = 16;
const int LCD_ROWS = 2;

const int dryValue = 615;
const int wetValue = 292;

int percent;
int soilCapacityValue;

String soilHumidityTitle = "Soil Humidity";

byte middleEmptyChar[] = {
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,
  B11111
};

byte rightEmptyChar[] = {
  B11111,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B00001,
  B11111
};

byte leftHalfEmptyChar[] = {
  B11111,
  B10000,
  B10100,
  B10100,
  B10100,
  B10100,
  B10000,
  B11111
};

byte middleHalfEmptyChar[] = {
  B11111,
  B00000,
  B11000,
  B11000,
  B11000,
  B11000,
  B00000,
  B11111
};

byte rightHalfEmptyChar[] = {
  B11111,
  B00001,
  B00101,
  B00101,
  B00101,
  B00101,
  B00001,
  B11111
};

byte leftFullChar[] = {
  B11111,
  B10000,
  B10111,
  B10111,
  B10111,
  B10111,
  B10000,
  B11111
};

byte middleFullChar[] = {
  B11111,
  B00000,
  B11111,
  B11111,
  B11111,
  B11111,
  B00000,
  B11111
};

byte rightHalfChar[] = {
  B11111,
  B00001,
  B10001,
  B10001,
  B10001,
  B10001,
  B00001,
  B11111
};

byte rightFullChar[] = {
  B11111,
  B00001,
  B11101,
  B11101,
  B11101,
  B11101,
  B00001,
  B11111
};

byte rightRightHalfEmptyChar[] = {
  B11111,
  B00001,
  B10001,
  B10001,
  B10001,
  B10001,
  B00001,
  B11111
};

void setup()
{
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);

  if(status) { 
  status = -status; 

  hd44780::fatalError(status);
  }

  lcd.createChar(1, middleEmptyChar);
  lcd.createChar(2, rightEmptyChar);
  lcd.createChar(3, leftHalfEmptyChar);
  lcd.createChar(4, middleHalfEmptyChar);
  lcd.createChar(5, leftFullChar);
  lcd.createChar(6, middleFullChar);
  lcd.createChar(7, rightRightHalfEmptyChar);
  lcd.createChar(8, rightFullChar);
}

void loop() {
  soilCapacityValue = analogRead(A0);
  percent = 100-((soilCapacityValue-(dryValue-wetValue))*100)/wetValue;
  lcd.print(soilHumidityTitle);
  lcd.setCursor(0, 1);
  displayBar(percent);
  displayPercentage(percent);
  delay(100);
}

void displayBar(int x) {
    const int patterns[21][10] = {
        {3, 1, 1, 1, 1, 1, 1, 1, 1, 2}, //First bar (0-9%) will always appear as a HalfEmpty due to bytes limitations.
        {3, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {5, 1, 1, 1, 1, 1, 1, 1, 1, 2},
        {5, 4, 1, 1, 1, 1, 1, 1, 1, 2},
        {5, 6, 1, 1, 1, 1, 1, 1, 1, 2},
        {5, 6, 4, 1, 1, 1, 1, 1, 1, 2},
        {5, 6, 6, 1, 1, 1, 1, 1, 1, 2},
        {5, 6, 6, 4, 1, 1, 1, 1, 1, 2},
        {5, 6, 6, 6, 1, 1, 1, 1, 1, 2}, 
        {5, 6, 6, 6, 4, 1, 1, 1, 1, 2},
        {5, 6, 6, 6, 6, 1, 1, 1, 1, 2},
        {5, 6, 6, 6, 6, 4, 1, 1, 1, 2},
        {5, 6, 6, 6, 6, 6, 1, 1, 1, 2},
        {5, 6, 6, 6, 6, 6, 4, 1, 1, 2},
        {5, 6, 6, 6, 6, 6, 6, 1, 1, 2},
        {5, 6, 6, 6, 6, 6, 6, 4, 1, 2},
        {5, 6, 6, 6, 6, 6, 6, 6, 1, 2},
        {5, 6, 6, 6, 6, 6, 6, 6, 4, 2},
        {5, 6, 6, 6, 6, 6, 6, 6, 6, 2},
        {5, 6, 6, 6, 6, 6, 6, 6, 6, 7},
        {5, 6, 6, 6, 6, 6, 6, 6, 6, 8}
    };

    int index = x / 5;
    if (index > 20) index = 20;

    for (int i = 0; i < 10; ++i) {
        lcd.write(patterns[index][i]);
    }
}

void displayPercentage(int x) {
  if (x >= 100) {
    lcd.setCursor(11, 1);
    lcd.print("100%   ");
  } else if (x <= 0) {
    lcd.setCursor(11, 1);
    lcd.print("0%   ");
  } else {
    lcd.setCursor(11, 1);
    lcd.print(String(x) + "%   ");
  }
}

//Made by vBagieta ©2024
