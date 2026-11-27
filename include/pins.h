#pragma once
#include "Keypad.h"
#include <stdint.h>

constexpr uint8_t KEYPAD_ROWS[Keypad::ROWS] = {6, 7, 8, 9};
constexpr uint8_t KEYPAD_COLS[Keypad::COLS] = {5, 4, 3};

constexpr uint8_t SERVO_PIN = 2;
constexpr uint32_t SERVO_OPEN_TIME = 5000;

constexpr uint8_t DS1302_SCLK = A5;
constexpr uint8_t DS1302_IO = A4;
constexpr uint8_t DS1302_CE = A3;
