#pragma once
#include <stdint.h>

class Led {
public:
    Led(uint8_t pin);
    void begin();
    void on();
    void off();

private:
    uint8_t _pin;
};