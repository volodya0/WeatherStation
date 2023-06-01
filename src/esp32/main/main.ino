#include <WiFi.h>
#include <HTTPClient.h>
#include <HardwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include "WeatherDataPool.h"

using namespace std;

String testUrl = "https://catfact.ninja/fact";
WeatherDataPool dataPool;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    lcd.init();
    lcd.backlight();

    Serial.begin(9600);
    delay(10);

    dataPool.AddRecord("first record");
}

int i = 0;

void loop()
{

    i++;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(String(i));
    lcd.setCursor(0, 4);
    lcd.print(Serial.readString());
    delay(2000);
}

// void display(std::string s1, std::string s2)
// {
//     lcd.clear();
//     lcd.setCursor(0, 0);
//     lcd.print(s1.c_str());
//     lcd.setCursor(0, 1);
//     lcd.print(s2.c_str());
//     delay(2000);
// }