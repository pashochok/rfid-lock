#include "Keypad.h"
#include <Arduino.h>
#include "pins.h"
const char KEYMAP[4][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};

void Keypad::begin()
{
    for (uint8_t p : KEYPAD_ROWS)
        pinMode(p, INPUT_PULLUP);
    for (uint8_t p : KEYPAD_COLS)
        pinMode(p, INPUT_PULLUP);
}

char Keypad::scan()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t rowPin = KEYPAD_ROWS[i];
        pinMode(rowPin, OUTPUT);
        digitalWrite(rowPin, LOW);
        for (uint8_t j = 0; j < 3; j++)
        {
            uint8_t colPin = KEYPAD_COLS[j];
            if (digitalRead(colPin) == LOW)
            {
                pinMode(rowPin, INPUT_PULLUP);
                return KEYMAP[i][j];
            }
        }
        pinMode(rowPin, INPUT_PULLUP);
    }
    return '\0';
}