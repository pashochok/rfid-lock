#include <Arduino.h>
#include "Keypad.h"

Keypad keypad;

void setup()
{
  Serial.begin(9600);
  keypad.begin();
}

void loop()
{
  char scanChar = keypad.scan();
  if (scanChar != '\0')
  {
    Serial.println(scanChar);
  }
}
