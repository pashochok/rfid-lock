#pragma once
#include <stdint.h>
#include <Servo.h>

class Lock
{
public:
    Lock(uint8_t pin, uint32_t durationMs);
    void begin();
    void open(uint32_t openTime);
    void update(uint32_t updateTime);
    bool isOpen();

private:
    Servo servo_;
    uint8_t pin_;
    uint32_t durationMs_;
    bool isOpen_ = false;
    uint32_t openTime = 0;
};
