// #include <Arduino.h>
// #include "Timestamp.h"

// void setup()
// {
//     Serial.begin(9600);

//     Serial.println("*******************************************************************");

//     Timestamp timestamp1(2023, 6, 5, 15, 0, 0);
//     Serial.println("Timestamp1 raw: 2023, 6, 5, 15, 0, 0 (2023-06-05 15:00:00)");
//     Serial.println("Timestamp1 string :" + timestamp1.getString());
//     unsigned long t1 = timestamp1.getTimestampFromComponents();
//     Serial.println("Timestamp1 stamp :" + String(t1));
//     Timestamp timestamp1Parsed(t1);
//     Serial.println("Timestamp1 parsed :" + timestamp1Parsed.getString());

//     Serial.println("*******************************************************************");

//     unsigned long unix_timestamp = 1681417200;
//     Timestamp timestamp2(unix_timestamp);
//     Serial.println("Timestamp2 raw: 1681417200 (2023-06-05 15:00:00)");
//     Serial.println("Timestamp2 string :" + timestamp2.getString());
//     unsigned long t2 = timestamp2.getTimestampFromComponents();
//     Serial.println("Timestamp2 stamp :" + String(t2));
//     Timestamp timestamp2Parsed(t2);
//     Serial.println("Timestamp2 parsed :" + timestamp2Parsed.getString());

//     Serial.println("*******************************************************************");

//     Timestamp timestamp3(2024, 2, 29, 12, 30, 45);
//     Serial.println("Timestamp3 raw: 2024, 2, 29, 12, 30, 45 (2024, 2, 29, 12, 30, 45)");
//     Serial.println("Timestamp3 string :" + timestamp3.getString());
//     unsigned long t3 = timestamp3.getTimestampFromComponents();
//     Serial.println("Timestamp3 stamp :" + String(t3));
//     Timestamp timestamp3Parsed(t3);
//     Serial.println("Timestamp3 parsed :" + timestamp3Parsed.getString());

//     Serial.println("*******************************************************************");

//     unix_timestamp = 1694200245;
//     Timestamp timestamp4(unix_timestamp);
//     Serial.println("Timestamp4 raw: 1694200245 (2024-02-29 12:30:450)");
//     Serial.println("Timestamp4 string :" + timestamp4.getString());
//     unsigned long t4 = timestamp4.getTimestampFromComponents();
//     Serial.println("Timestamp4 stamp :" + String(t4));
//     Timestamp timestamp4Parsed(t4);
//     Serial.println("Timestamp4 parsed :" + timestamp4Parsed.getString());

//     Serial.println("*******************************************************************");
// }

// void loop()
// {
//     // put your main code here, to run repeatedly:
// }
