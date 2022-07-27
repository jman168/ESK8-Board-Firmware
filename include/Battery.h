#pragma once

#include <Arduino.h>

#define BATTERY_SENSE_PIN 4
#define MAX_BATTERY_SENSE_VOLTAGE 38.26130719
#define MAX_BATTERY_VOLTAGE 24.8
#define MIN_BATTERY_VOLTAGE 18.0

class Battery {
    public:
        double getVoltage();

        /**
         * @brief returns the charge of the battery from 0.0 to 1.0
         * 
         * @return double 
         */
        double getCharge();
};