#pragma once
#include <stdint.h>

class Ds1302
{
public:
    Ds1302(uint8_t ce, uint8_t sclk, uint8_t oi);
    void begin();
    uint8_t readRegister(uint8_t cmd);
    uint8_t ce_;
    uint8_t sclk_;
    uint8_t oi_;
    uint8_t cmd_;

private:
    void writeByte(uint8_t b);
    uint8_t readByte();
};