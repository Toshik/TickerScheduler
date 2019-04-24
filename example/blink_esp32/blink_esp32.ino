/**
   This example demonstrates how to schedule tasks(tested on ESP32).


   ------------------------------------------------------------
   Project: TickerScheduler
   Source: https://github.com/ahmadSum1/TickerScheduler

   Filename: blink_esp32.ino
   Version: 1.0
   Author: @ahmadSum1 (Sakib Ahmed)
   24/04/2019
*/

#include <TickerScheduler.h>

#define LED1 LED_BUILTIN
#define LED2 15

TickerScheduler ts(2);

void blink1() {
  digitalWrite(LED1, !digitalRead(LED1));
}

void blink2() {
  digitalWrite(LED2, !digitalRead(LED2));
}

void setup() {
  pinMode(LED1, OUTPUT);
  digitalWrite(LED1, LOW);

  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, LOW);

  ts.add(0, 1000, [&](void *) {
    blink1();
  }, nullptr, true);
  ts.add(1, 2000, [&](void *) {
    blink2();
  }, nullptr, true);
}

void loop() {
  ts.update();
}
