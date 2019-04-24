#include <TickerScheduler.h>

#define LED1 4
#define LED2 5

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
  
  ts.add(0, 1000, [&](void *) { blink1(); }, nullptr, true);
  ts.add(1, 3000, [&](void *) { blink2(); }, nullptr, true);
}

void loop() {
  ts.update();
}
