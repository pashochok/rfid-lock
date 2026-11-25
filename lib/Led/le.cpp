#include "led.h"
#include <Arduino.h>

Led::Led(uint8_t pin){
    _pin = pin;
};

void Led::begin(){
    pinMode(_pin, OUTPUT);
};

void Led::on(){
    digitalWrite(_pin, HIGH);
};

void Led::off(){
    digitalWrite(_pin,LOW);
};

