#pragma once

#include <Arduino.h>

#define BATTERY_SENSE_PIN 4
#define MAX_BATTERY_SENSE_VOLTAGE 38.26130719
#define MAX_BATTERY_VOLTAGE 24.8
#define MIN_BATTERY_VOLTAGE 18.0

/**
 * @brief Initialized battery.
 * 
 */
void battery_init();

/**
 * @brief Gets battery voltage.
 * 
 * @return float 
 */
float battery_get_voltage();

/**
 * @brief Gets battery state of charge from 0.0 to 1.0
 * 
 * @return float 
 */
float battery_get_charge();