//Libraries required to run this code
#include <Wire.h>
#include <hd44780.h>                          
#include <hd44780ioClass/hd44780_I2Cexp.h>

//Objects
hd44780_I2Cexp lcd; //Object used to control LCD display over the I2C module
hd44780_I2Cexp lcd2(0x27); //I2C Adress for the LCD display

//Options
const int LCD_COLS = 16; //Default LCD parameters
const int LCD_ROWS = 2;

const int dryValue = 615; //See https://github.com/vBagieta/SimpleSoilMoistureSensor/blob/main/README.md#kalibracja
const int wetValue = 292; //or https://github.com/vBagieta/SimpleSoilMoistureSensor/blob/main/README.md#calibration

int percent;
int soilCapacityValue;

String soilHumidityTitle = "Soil Humidity";  //Title on display

//Custom chars
byte middleEmptyChar[] = {   //There's some errors with custom chars, percentage bar may be 
  B11111,                    //displaying wrong value. I will fix that in the future.
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


//Code
void setup()
{
  //LCD initializing
  int status;
  status = lcd.begin(LCD_COLS, LCD_ROWS);

  //LCD checking
  if(status) { 
  status = -status; 

  hd44780::fatalError(status);
  }

  //Creating chars
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
  soilCapacityValue = analogRead(A0); //Read the value from sensor (Value from A0 analog port)
  percent = 100-((soilCapacityValue-(dryValue-wetValue))*100)/wetValue;  //Make percent using data
                                                                         //See github for more informations
  lcd.print(soilHumidityTitle); //Set title on LCD display
  lcd.setCursor(0, 1);
  displayMoistureBar(percent); //Display bar on LCD based on humidity percent
  displayFixedPercentage(percent); //Display only 0-100 percents next to the bar
  delay(100); //Delay this loop for 0.1s
}

void displayMoistureBar(int progress) { //Display bar on LCD (1 Segment = 10%, 1/2 Segment = 5%)
  if (progress >= 100) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(8);
  } else if (progress >= 95) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(7);
  } else if (progress >= 90) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(2);
  } else if (progress >= 85) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(4);
    lcd.write(2);
  } else if (progress >= 80) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 75) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(4);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 70) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 65) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 60) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 55) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 50) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 45) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 40) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 35) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 30) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 25) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 20) {
    lcd.write(5);
    lcd.write(6);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 15) {
    lcd.write(5);
    lcd.write(4);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 10) {
    lcd.write(5);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= 5) {
    lcd.write(3);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  } else if (progress >= -10) {
    lcd.write(3);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(1);
    lcd.write(2);
  }
}

void displayFixedPercentage(int percentage) {  //This function will display 100% even if real value is (for example) 103.
  if (percentage >= 100) {                     //Due to low accuracy sensor calibration.
    lcd.setCursor(11, 1);
    lcd.print("100%   ");
  } else if (percentage <= 0) {
    lcd.setCursor(11, 1);
    lcd.print("0%   ");
  } else {
    lcd.setCursor(11, 1);
    lcd.print(String(percentage) + "%   ");
  }
}

//This is the END! Enjoy.
//GitHub repo: https://github.com/vBagieta/SimpleSoilMoistureSensor/blob/main/README.md

//Made by vBagieta ©2023
