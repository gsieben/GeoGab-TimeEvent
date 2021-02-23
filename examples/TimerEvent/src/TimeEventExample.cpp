/**
 * @file TimeEventExample.cpp
 * @author Gabriel A. Sieben (gsieben@geogab.net)
 * @brief 
 * @version 1.0.1
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
  delay(500);   // Crash delay
}


/****** Main Loop ******/
void loop() {
  tevent.Reset();                         // Must always be placed at the beginning of a loop

  tevent.Check(1000, 0, test);            // Führt jede Sekunde die Funktion 1 aus

  tevent.Check(1000, 100, test2);         // Führt jede Sekunde die Funktion 2 aus. Sie ist um 100 millisekunden gegenüber der vorherigen zeitversetzt 

  tevent.Check(10000, 0, test3);          // Führt alle 10 Sekunden die Funktion aus

  if(tevent.Check(30000, 0)) {            // Funktion innerhalb vom if - alle 30 sekunden
    Serial.println("==== 30 full ====");
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