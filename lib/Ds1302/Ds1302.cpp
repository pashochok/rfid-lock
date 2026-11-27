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