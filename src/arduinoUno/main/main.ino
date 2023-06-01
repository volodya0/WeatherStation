#include <SoftwareSerial.h>

void setup()
{
    Serial.begin(9600);
}

int i = 0;
void loop()
{
    Serial.println("hello from 9600 from arduino" + String(i++));
    delay(1500);
}
