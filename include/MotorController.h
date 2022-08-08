#pragma once

#include "SparkMax.h"
#include "PIDController.h"

#define MOTOR_KV 487.0
#define MAX_VOLTAGE 7.5

#define STOPPED_THRESHOLD 400.0

#define MAX_CURRENT 50.0

/**
 * @brief Initializes the motor controller.
 * 
 */
void motor_controller_init(SparkMax *spark);

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
 * @brief Sets the throttle output of the motor controller.
 * 
 * @param throttle 
 */
void motor_controller_set_throttle(float throttle);

/**
 * @brief Gets the signed current applied to the motor phases.
 * 
 * @return float 
 */
float motor_controller_get_signed_current();

/**
 * @brief Sets weather or not to stop the board. This will slowly bring the board to a stop and then apply full break. Useful for emergency stops.
 * NOTE: Throttle will not to anything when in a stop state.
 * 
 * @param stop 
 */
void motor_controller_set_stop(bool stop);