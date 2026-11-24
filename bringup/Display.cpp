#include <Arduino.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);  // RS, E, D4, D5, D6, D7

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello, Pavlo!");
}

void loop() {
  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
}