#pragma once

#include <Arduino.h>
#include <functional>
#include "FunctionalInterrupt.h"

#define HALL_A 25
#define HALL_B 26
#define HALL_C 27

#define COUNTS_PER_METER 568.183146838
#define COUNTS_PER_MILE 914402.139309818

const uint8_t NEXT_HALL_STATE[7] = {
    0b00000000, // 00000000
    0b00000011, // 00000001
    0b00000110, // 00000010
    0b00000010, // 00000011
    0b00000101, // 00000100
    0b00000001, // 00000101
    0b00000100, // 00000110
  };

const uint8_t PREV_HALL_STATE[7] = {
    0b00000000, // 00000000
    0b00000101, // 00000001
    0b00000011, // 00000010
    0b00000001, // 00000011
    0b00000110, // 00000100
    0b00000101, // 00000101
    0b00000110, // 00000110
  };

class Encoder {
    public:
        Encoder();

        double getPositionMeters();
        double getPositionMiles();

        double getSpeedMPS();
        double getSpeedMPH();

    private:
        uint8_t _currentRotorState;
        unsigned long _lastCount = 0;
        long _rotorPosition = 0;
        double _countsPerSecond = 0;

    private:

        void updateEncoder();

        uint8_t getRotorState();
};

