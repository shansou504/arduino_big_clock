// INSTRUCTIONS
// 1. Set the variables in the [DATETIME VARIABLES] section
// 2. In Setup() uncomment the time and date setting
//    methods to set the time. Then flash the program.
// 3. In Setup() comment the time and date setting. Then
//    flash again. This will prevent the time from being 
//    overwritten each time it boots up. If the DS3231 
//    module contains a coin cell battery, it will remember
//    the time and it won't need to be set each time the
//    program is flashed.

#include <DS3231.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

DS3231 myRTC;
LiquidCrystal_I2C lcd(0x27,16,2);

//##########################################
// DATETIME VARIABLES    <-- SET VALUES HERE
//##########################################
uint8_t year = 25;
uint8_t month = 12;
uint8_t date = 14;
uint8_t dOW = 1;
uint8_t hour = 17; // use 24h to set hour
uint8_t minute = 02;
uint8_t second = 0;
bool h12Flag;
bool pmFlag;

// VARIABLES FOR PRINTING TO LCD
uint8_t hh_now;
uint8_t h1_now;
uint8_t h2_now;
uint8_t mm_now;
uint8_t m1_now;
uint8_t m2_now;
uint8_t ss_now;

// CUSTOM CHARACTERS
// For number segments that cannot be defined by ASCII
uint8_t seg0[8] = {0x1F,0x10,0x10,0x10,0x10,0x10,0x10};
uint8_t seg1[8] = {0x1F,0X01,0X01,0X01,0X01,0X01,0X01};
uint8_t seg2[8] = {0X01,0X01,0X01,0X01,0X01,0X01,0X1F};
uint8_t seg3[8] = {0X1F,0X00,0X00,0X00,0X00,0X00,0X1F};
uint8_t seg4[8] = {0X1F,0X01,0X01,0X01,0X01,0X01,0X1F};
uint8_t seg5[8] = {0X1F,0x10,0x10,0x10,0x10,0x10,0X1F};
uint8_t seg6[8] = {0X1F,0X00,0X00,0X00,0X00,0X00,0X00};
uint8_t seg7[8] = {0X01,0X01,0X01,0X01,0X01,0X01,0X01};

// Number definitions [top-left, top-right, bottom-left, bottom-right]
int num0[4] = {0,1,'L',2};
int num1[4] = {' ',7,' ',7};
int num2[4] = {3,4,'L','_'};
int num3[4] = {3,4,'_',2};
int num4[4] = {'L',2,' ',7};
int num5[4] = {5,3,'_',2};
int num6[4] = {5,3,'L',2};
int num7[4] = {6,1,' ',7};
int num8[4] = {5,4,'L',2};
int num9[4] = {5,4,'_',2};

// Number array
int *num_arr[10] = {num0,num1,num2,num3,num4,num5,num6,num7,num8,num9};

// SETUP
void setup() {
  // Start the I2C interface
  Wire.begin();

  //##########################################
  // UNCOMMENT TO SET TIME AND DATE
  // COMMENT TO PREVENT OVERWRITING
  //##########################################
  
  /*
  myRTC.setClockMode(true);  // false => 24h; true => 12h
  myRTC.setYear(year);
  myRTC.setMonth(month);
  myRTC.setDate(date);
  myRTC.setDoW(dOW);
  myRTC.setHour(hour);
  myRTC.setMinute(minute);
  myRTC.setSecond(second);
  //*/

  // Assigning custom characters to an internal index.
  // The LCD module can store a maximum of 8 custom
  // characters. Use ASCII for other segments.
  lcd.init(); 
  lcd.createChar(0, seg0);
  lcd.createChar(1, seg1);
  lcd.createChar(2, seg2);
  lcd.createChar(3, seg3);
  lcd.createChar(4, seg4);
  lcd.createChar(5, seg5);
  lcd.createChar(6, seg6);
  lcd.createChar(7, seg7);
  lcd.clear();
  lcd.backlight();
}

void loop() {
  ///*
  hh_now = myRTC.getHour(h12Flag, pmFlag);
  h1_now = hh_now / 10;
  h2_now = hh_now % 10;
  mm_now = myRTC.getMinute();
  m1_now = mm_now / 10;
  m2_now = mm_now % 10;
  ss_now = myRTC.getSecond();
  if (h1_now != 0) {
    lcd.setCursor(0,0);
    lcd.printByte(num_arr[h1_now][0]);
    lcd.printByte(num_arr[h1_now][1]);
    lcd.setCursor(0,1);
    lcd.printByte(num_arr[h1_now][2]);
    lcd.printByte(num_arr[h1_now][3]);
  } else {
    lcd.setCursor(0,0);
    lcd.print("  ");
    lcd.setCursor(0,1);
    lcd.print("  ");
  }
  lcd.setCursor(3,0);
  lcd.printByte(num_arr[h2_now][0]);
  lcd.printByte(num_arr[h2_now][1]);
  lcd.setCursor(3,1);
  lcd.printByte(num_arr[h2_now][2]);
  lcd.printByte(num_arr[h2_now][3]);
  lcd.setCursor(6,0);
  lcd.print(".");
  lcd.setCursor(6,1);
  lcd.print(".");
  lcd.setCursor(8,0);
  lcd.printByte(num_arr[m1_now][0]);
  lcd.printByte(num_arr[m1_now][1]);
  lcd.setCursor(8,1);
  lcd.printByte(num_arr[m1_now][2]);
  lcd.printByte(num_arr[m1_now][3]);
  lcd.setCursor(11,0);
  lcd.printByte(num_arr[m2_now][0]);
  lcd.printByte(num_arr[m2_now][1]);
  lcd.setCursor(11,1);
  lcd.printByte(num_arr[m2_now][2]);
  lcd.printByte(num_arr[m2_now][3]);
  lcd.setCursor(14,1);
  if (pmFlag) {
    lcd.print("PM");
  } else {
    lcd.print("AM");
  }
  //*/
  delay(59999);
}
