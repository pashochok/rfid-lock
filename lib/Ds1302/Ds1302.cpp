#include <Arduino.h>
#include <Ds1302.h>

Ds1302::Ds1302(uint8_t ce, uint8_t sclk, uint8_t oi)
{
    ce_ = ce;
    sclk_ = sclk;
    oi_ = oi;
};

void Ds1302::begin()
{
    pinMode(ce_, OUTPUT);
    digitalWrite(ce_, LOW);

    pinMode(sclk_, OUTPUT);
    digitalWrite(sclk_, LOW);
};

DateTime Ds1302::now()
{
    DateTime d;
    d.second = seconds();
    d.year = year();
    d.month = mounth();
    d.day = day();
    d.hour = hours();
    d.minute = minutes();
    return d;
}
uint8_t Ds1302::bcdToDec(uint8_t bcd)
{
    int8_t tens = (bcd >> 4) & 0x0F;
    int8_t seconds = bcd & 0x0F;
    return tens * 10 + seconds;
}

uint8_t Ds1302::seconds()
{
    uint8_t value = readRegister(0x81);
    uint8_t raw = value & 0x7F;
    return bcdToDec(raw);
};

uint8_t Ds1302::minutes()
{
    uint8_t value = readRegister(0x83);
    uint8_t raw = value & 0x7F;
    return bcdToDec(raw);
};

uint8_t Ds1302::hours()
{
    uint8_t value = readRegister(0x85);
    uint8_t raw = value & 0x3F;
    return bcdToDec(raw);
};

uint8_t Ds1302::day()
{
    uint8_t value = readRegister(0x87);
    uint8_t raw = value & 0x3F;
    return bcdToDec(raw);
};

uint8_t Ds1302::mounth()
{
    uint8_t value = readRegister(0x89);
    uint8_t raw = value & 0x1F;
    return bcdToDec(raw);
};

uint16_t Ds1302::year()
{
    uint8_t value = readRegister(0x8D);
    return bcdToDec(value) + 2000;
};

uint8_t Ds1302::readRegister(uint8_t cmd)
{
    digitalWrite(ce_, HIGH);
    writeByte(cmd);
    uint8_t value = readByte();
    digitalWrite(ce_, LOW);
    return value;
};

void Ds1302::writeByte(uint8_t b)
{
    pinMode(oi_, OUTPUT);
    for (uint8_t i = 0; i < 8; i++)
    {
        uint8_t bit = (b >> i) & 1;
        digitalWrite(oi_, bit);
        digitalWrite(sclk_, HIGH);
        digitalWrite(sclk_, LOW);
    }
};

uint8_t Ds1302::readByte()
{
    pinMode(oi_, INPUT);
    uint8_t value = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (digitalRead(oi_) == HIGH)
        {
            value |= (1 << i);
        };
        digitalWrite(sclk_, HIGH);
        digitalWrite(sclk_, LOW);
    }
    return value;
};