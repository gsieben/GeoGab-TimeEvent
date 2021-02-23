/**
 * @file TimeEventExtended.cpp
 * @author Gabriel A. Sieben (gsieben@geogab.net)
 * @brief 
 * @version 1.0.1
 * @date 23-February-2021
 * 
 * @copyright (c) 2021 - MIT License (see license file)
 * 
 */

#include <TimeEventExtended.h>

TimeEvent tevent(10);

void test1();
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
  tevent.Reset();                     // Must always be placed at the beginning of a loop

  tevent.Check(1000, 0, test1);       // Executes function 1 every second

  tevent.Check(1000, 100, test2);     // Executes function 2 every second. It is delayed by 100 milliseconds from the previous one 

  tevent.Check(10000, 0, test3);      // Executes the function every 10 seconds

  if(tevent.Check(500, 0)) {          // function within if - every 0,5 seconds
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }

  if(tevent.Check(5000, 500)) {      // Print the runtimes as example (will not show too much as there is almost no runtime. Wie im readme erwähnt wird die runtime von if(tevent.Check..) nicht berechnet.)
    uint32_t overallrt=tevent.Runtime[0]+tevent.Runtime[1]+tevent.Runtime[2];
    if (overallrt) {    // Quick runtimes are faster than 1 milli second -> will lead to a divison by zero crash
      Serial.println("\r\nFunction\tRuntime\tPercentage");

      Serial.print("test\t\t");
      Serial.print(tevent.Runtime[0]);
      Serial.print("\t");
      Serial.println(tevent.Runtime[0]*100/overallrt);

      Serial.print("test1\t\t");
      Serial.print(tevent.Runtime[1]);
      Serial.print("\t");
      Serial.println(tevent.Runtime[1]*100/overallrt);

      Serial.print("test2\t\t");
      Serial.print(tevent.Runtime[2]);
      Serial.print("\t");
      Serial.println(tevent.Runtime[2]*100/overallrt);

      Serial.print("Overall\t\t");
      Serial.println(overallrt);
      Serial.println();
    }
  }

}

uint32 val;

void test1() {
  // Just do something to get a runtime without the optimizer recognizing it as useless ;-)
  for (uint16_t i=0;i<10000;i++) {
    val=cos(i)*100;
  }
  Serial.print("test1: ");
  Serial.println(val);
}

void test2() {
  // Just do something to get a runtime without the optimizer recognizing it as useless ;-)
  for (uint16_t i=0;i<20000;i++) {
    val=sin(i)*100;
  }
  Serial.print("test2: ");
  Serial.println(val);
}

void test3() {
  Serial.println("-------------------");
}