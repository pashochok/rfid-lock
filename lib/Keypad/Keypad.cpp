#include "Keypad.h"
#include <Arduino.h>

namespace
{
    const char KEYMAP[4][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}};
}
Keypad::Keypad(const uint8_t *rows, const uint8_t *cols)
{
    rows_ = rows;
    cols_ = cols;
};
void Keypad::begin()
{
    for (uint8_t i = 0; i < ROWS; i++)
        pinMode(rows_[i], INPUT_PULLUP);
    for (uint8_t i = 0; i < COLS; i++)
        pinMode(cols_[i], INPUT_PULLUP);
};

char Keypad::scan()
{
    for (uint8_t i = 0; i < 4; i++)
    {
        uint8_t rowPin = rows_[i];
        pinMode(rowPin, OUTPUT);
        digitalWrite(rowPin, LOW);
        for (uint8_t j = 0; j < 3; j++)
        {
            uint8_t colPin = cols_[j];
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

void Keypad::update(uint32_t now)
{
    char raw = scan();

    if (raw != candidate_)
    {
        candidate_ = raw;
        candidateSince_ = now;
        return;
    }
    if (now - candidateSince_ < 25)
        return;

    if (stable_ != candidate_)
    {
        stable_ = candidate_;
        if (stable_)
            pressedEvent_ = true;
    }
}

char Keypad::getKey()
{
    if (pressedEvent_ == false)
    {
        return '\0';
    }

    pressedEvent_ = false; // віддали, скинули
    return stable_;
}