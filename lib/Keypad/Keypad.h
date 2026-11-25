#pragma once
#include <stdint.h>

class Keypad
{
public:
    Keypad(const uint8_t *rows, const uint8_t *cols);
    void begin();
    void update(uint32_t now);
    char getKey();
    static constexpr uint8_t ROWS = 4;
    static constexpr uint8_t COLS = 3;

private:
    char scan();
    char candidate_ = '\0';
    uint32_t candidateSince_ = 0;
    char stable_ = '\0';
    bool pressedEvent_ = false;
    const uint8_t *rows_;
    const uint8_t *cols_;
};
