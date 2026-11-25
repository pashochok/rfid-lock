#include <Arduino.h>
#include "pins.h"
#include "Keypad.h"
#include "Lock.h"

Keypad keypad(KEYPAD_ROWS, KEYPAD_COLS);
Lock lock(SERVO_PIN, SERVO_OPEN_TIME);
const uint8_t PIN_MAX = 4;
char pin[PIN_MAX + 1];
uint8_t len = 0;
void setup()
{
  Serial.begin(9600);
  keypad.begin();
  lock.begin();
}

void loop()
{
  keypad.update(millis());
  lock.update(millis());

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
      if (strcmp(pin, "1234") == 0)
      {
        lock.open(millis());
        Serial.println("OPEN");
      }
      else
      {
        Serial.println("DENIED");
      }

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
