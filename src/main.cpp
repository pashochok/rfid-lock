#include <Arduino.h>
#include "pins.h"
#include "Keypad.h"
#include "Lock.h"
#include "Ds1302.h"

Keypad keypad(KEYPAD_ROWS, KEYPAD_COLS);
Ds1302 ds1302(DS1302_CE, DS1302_SCLK, DS1302_IO);
Lock lock(SERVO_PIN, SERVO_OPEN_TIME);
const uint8_t PIN_MAX = 4;
char pin[PIN_MAX + 1];
uint8_t len = 0;
uint32_t lastPrint = 0;
void setup()
{
  Serial.begin(9600);
  keypad.begin();
  lock.begin();
  ds1302.begin();
}

void loop()
{
  keypad.update(millis());
  lock.update(millis());
  uint32_t now = millis();
  char buffer[20];
  if (now - lastPrint >= 1000)
  {
    lastPrint += 1000;
    DateTime date = ds1302.now();
    snprintf(buffer, sizeof(buffer), "%u-%02u-%02u %02u:%02u:%02u", date.year, date.month, date.day, date.hour, date.minute, date.second);
    Serial.println(buffer);
  }

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
