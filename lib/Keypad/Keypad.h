#pragma once
#include <stdint.h>

class Keypad {
public:
    void begin();
    void update(uint32_t now);
    char getKey();
private:
    char scan();
    char candidate_ = '\0';
    uint32_t candidateSince_ = 0;
    char stable_ = '\0';
    bool pressedEvent_ = false;
};
