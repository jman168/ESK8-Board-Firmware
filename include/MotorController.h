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

class MotorController {
    public:
        MotorController(Encoder *encoder);

        void update();
        void setVoltage(double voltage);
        void setThrottle(double throttle);

    private:
        Encoder *_encoder;

        double _throttle;

    private:
        float mpsToVoltage(float mps);

        static float clamp(float input, float minV, float maxV);
};