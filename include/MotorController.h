#pragma once

#include "SparkMax.h"
#include "PIDController.h"

#define MOTOR_KV 487.0
#define MAX_VOLTAGE 11.0

#define CURRENT_P 0.0
#define CURRENT_I 1.6
#define CURRENT_D 0.0

#define STOPPED_THRESHOLD 400.0

#define MAX_CURRENT 45.0
#define BRAKE_VOLTAGE 2.5

class MotorController {
    public:
        MotorController(SparkMax *spark);

        /**
         * @brief Updates the motor controller (should be called periodically to ensure smooth operation).
         * 
         */
        void update();

        /**
         * @brief Sets the voltage applied to the motor controller.
         * 
         * @param voltage 
         */
        void setVoltage(float voltage);

        /**
         * @brief Sets the throttle output of the motor controller.
         * 
         * @param throttle 
         */
        void setThrottle(float throttle);

        /**
         * @brief Gets the signed current applied to the motor phases.
         * 
         * @return float 
         */
        float getSignedCurrent();

        /**
         * @brief Resets the PID loops.
         * 
         */
        void reset();

    private:
        PIDController _currentController; // current PID loop
        SparkMax *_spark; // spark max

        float _throttle = 0.0; // the set throttle
        float _brake = 0.0;
        float _setVoltage = 0.0; // the set voltage
};