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

/**
 * @brief Initializes the encoder.
 * 
 */
void encoder_init();

/**
 * @brief Gets the position of the board in meters.
 * NOTE: This is NOT the distance traveled.
 * 
 * @return float 
 */
float encoder_get_position_meters();

/**
 * @brief Gets the position of the board in miles.
 * NOTE: This is NOT the distance traveled.
 * 
 * @return float 
 */
float encoder_get_position_miles();

/**
 * @brief Gets the speed in meters per second.
 * 
 * @return float 
 */
float encoder_get_speed_mps();

/**
 * @brief Gets the speed in miles per hour.
 * 
 * @return float 
 */
float encoder_get_speed_mph();