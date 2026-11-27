#pragma once
#include <stdint.h>

struct DateTime
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

class Ds1302
{
public:
    Ds1302(uint8_t ce, uint8_t sclk, uint8_t oi);
    DateTime now();
    void begin();
    uint8_t readRegister(uint8_t cmd);
    uint8_t seconds();
    uint8_t minutes();
    uint8_t hours();
    uint8_t day();
    uint8_t mounth();
    uint16_t year();
    uint8_t ce_;
    uint8_t sclk_;
    uint8_t oi_;
    uint8_t cmd_;

private:
    void writeByte(uint8_t b);
    uint8_t bcdToDec(uint8_t bcd);
    uint8_t readByte();
};