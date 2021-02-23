/**
 * @file TimeEventExample.cpp
 * @author Gabriel A. Sieben (gsieben@geogab.net)
 * @brief 
 * @version 1.0.2
 * @date 19-February-2021
 * 
 * @copyright (c) 2021 - MIT License (see license file)
 * 
 */

#include <TimeEventExample.h>

TimeEvent tevent(10);

void test();
void test2();
void test3();

/****** Setup ******/
void setup() {
  Serial.begin(115200);
  Serial.println("\r\n### S T A R T ###");
  delay(500);                         // Crash delay
  pinMode(LED_BUILTIN, OUTPUT);       // Internal LED 
}


/****** Main Loop ******/
void loop() {
  tevent.Reset();                           // Must always be placed at the beginning of a loop

  tevent.Check(1000, 0, test);              // Executes function 1 every second

  tevent.Check(1000, 100, test2);           // Executes function 2 every second. It is delayed by 100 milliseconds from the previous one 

  tevent.Check(10000, 0, test3);            // Executes the function every 10 seconds

  if(tevent.Check(500, 0)) {                // function within if - every 0,5 seconds
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}


void test() {
  static uint16_t seconds;
  seconds++;
  Serial.printf("%d sec\r\n",seconds);
}

void test2() {
  Serial.println(".");
}

void test3() {
  Serial.println("-------------------");
}