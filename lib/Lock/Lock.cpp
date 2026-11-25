#include "Lock.h"
#include "Arduino.h"

Lock::Lock(uint8_t pin, uint32_t durationMs)
{
    pin_ = pin;
    durationMs_ = durationMs;
}

void Lock::begin()
{
    servo_.attach(pin_);
    isOpen_ = false;
    servo_.write(0);
}

void Lock::open(uint32_t now)
{
    openTime = now;
    servo_.write(90);
    isOpen_ = true;
}

void Lock::update(uint32_t now)
{
    if (!isOpen_)
        return;
    if (now - openTime > durationMs_)
    {
        servo_.write(0);
        isOpen_ = false;
    }
}

bool Lock::isOpen()
{
    return isOpen_;
}