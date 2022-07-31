#pragma once

#include <Servo.h>

#include "Encoder.h"

#define MOTOR_PIN D1

#define MIN_MS 1000
#define MAX_MS 2000
#define MAX_DELTA_V 6.0

#define BATTERY_VOLTAGE 24.0
#define MOTOR_KV 0.51306 // NOTE: this is meters per second per volt NOT rpm per volt
#define MAX_VOLTAGE 12.0

/**
 * @brief Initializes the motor controller.
 * 
 */
void motor_controller_init();

/**
 * @brief Updates the motor controller (should be called periodically to ensure smooth operation).
 * 
 */
void motor_controller_update();

/**
 * @brief Sets the voltage applied to the motor controller.
 * 
 * @param voltage 
 */
void motor_controller_set_voltage(float voltage);

/**
 * @brief Applies a throttle to the motor controller. This approximates a torque or a current applied to the motor phase.
 * 
 * @param throttle 
 */
void motor_controller_set_throttle(float throttle);