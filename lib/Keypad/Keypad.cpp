#include "Keypad.h"
#include <Arduino.h>
#include "pins.h"

void Keypad::begin() {
    for (uint8_t p : pins) pinMode(p, INPUT_PULLUP);
}