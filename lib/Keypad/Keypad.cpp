#include <Arduino.h>
constexpr uint8_t ROW_PINS[4] = {6, 7, 8, 9};
constexpr uint8_t COL_PINS[3] = {5, 4, 3};

const uint8_t pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  Serial.begin(9600);
  for (uint8_t p : pins) pinMode(p, INPUT_PULLUP);
  Serial.println("Press keys one by one");
}

void loop() {
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(pins[i], OUTPUT);       // "опускаємо" один вивід у LOW
    digitalWrite(pins[i], LOW);
    for (uint8_t j = i + 1; j < 8; j++) {
      if (digitalRead(pins[j]) == LOW) {  // натиснута кнопка замкнула i та j
        Serial.print("keypad pin ");
        Serial.print(i + 1);
        Serial.print(" + ");
        Serial.println(j + 1);
        delay(300);
      }
    }
    pinMode(pins[i], INPUT_PULLUP);  // повертаємо назад
  }
}