#include <Arduino.h>
#include "Keypad.h"

Keypad keypad;
const uint8_t PIN_MAX = 8;
char pin[PIN_MAX + 1];
uint8_t len = 0;
void setup()
{
  Serial.begin(9600);
  keypad.begin();
}

void loop()
{
  keypad.update(millis());

  char scanChar = keypad.getKey();
  if (scanChar != '\0')
  {

    if (scanChar == '*')
    {
      len = 0;
      return;
    }
    if (scanChar == '#')
    {
      pin[len] = '\0';
      Serial.println(pin);
      len = 0;
      return;
    }
    if (len < PIN_MAX)
    {
      pin[len] = scanChar;
      len++;
    }
  }
}
