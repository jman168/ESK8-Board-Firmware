#pragma once

#include <SPI.h>
#include "RF24.h"

/**
 * @brief Initializes the remote.
 * 
 */
void remote_init();

/**
 * @brief Updates the remote. Checks for packets, sends most recent speed measurements, etc...
 * 
 */
void remote_update();

/**
 * @brief Gets the throttle from the remote.
 * 
 * @return float 
 */
float remote_get_throttle();

/**
 * @brief Sets the battery level (from 0.0 to 1.0) to be sent to the remote.
 * 
 */
void remote_set_battery(float battery);

/**
 * @brief Sets the speed (in miles per hour) to be sent to the remote.
 * 
 */
void remote_set_speed(float speed);

/**
 * @brief Gets if a remote is connected. This function returns true if it has received a packet from the remote in the last 100ms. This function should be used for safety to prevent run away boards.
 * 
 */
bool remote_is_connected();