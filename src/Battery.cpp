#include "Battery.h"

void battery_init() {
    pinMode(BATTERY_SENSE_PIN, INPUT);
}

float battery_get_voltage() {
    float total = 0.0;

    for(int i = 0; i < 10; i++) {
        total += analogRead(BATTERY_SENSE_PIN);
    }

    float value = total/10.0;
    return (value/1023.0)*MAX_BATTERY_SENSE_VOLTAGE;
}

float battery_get_charge() {
    return (battery_get_voltage()-MIN_BATTERY_VOLTAGE)/(MAX_BATTERY_VOLTAGE-MIN_BATTERY_VOLTAGE);
}