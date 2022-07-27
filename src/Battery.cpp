#include "Battery.h"

double Battery::getVoltage() {
    double total = 0.0;

    for(int i = 0; i < 10; i++) {
        total += analogRead(BATTERY_SENSE_PIN);
    }

    double value = total/10.0;
    return (value/4095.0)*MAX_BATTERY_SENSE_VOLTAGE;
}

double Battery::getCharge() {
    return (getVoltage()-MIN_BATTERY_VOLTAGE)/(MAX_BATTERY_VOLTAGE-MIN_BATTERY_VOLTAGE);
}