#pragma once

#include "Encoder.h"

#define MOTOR_PIN 2

#define PWM1_CH    0
#define PWM1_RES   16
#define PWM1_FREQ  50

#define MIN_DUTY 3277
#define MAX_DUTY 6554
#define MAX_DELTA_V 6.0

#define BATTERY_VOLTAGE 24.0
#define MOTOR_KV 0.51306 // note this is meters per second per volt NOT rpm per volt
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