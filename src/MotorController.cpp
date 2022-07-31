#include "MotorController.h"

MotorController::MotorController() {
    ledcAttachPin(MOTOR_PIN, PWM1_CH);
    ledcSetup(PWM1_CH, PWM1_FREQ, PWM1_RES);
}

void MotorController::update() {
    setVoltage(clamp(mpsToVoltage(encoder_get_speed_mps()) + _throttle*MAX_DELTA_V, -MAX_VOLTAGE, MAX_VOLTAGE));
}

void MotorController::setVoltage(double voltage) {
    double power = ( voltage/BATTERY_VOLTAGE + 1.0 ) / 2.0;
    uint32_t duty = MIN_DUTY + (MAX_DUTY-MIN_DUTY) * power;

    ledcWrite(PWM1_CH, duty);
}

void MotorController::setThrottle(double throttle) {
    _throttle = throttle;
}

float MotorController::mpsToVoltage(float mps) {
    if(mps > 0.0) {
        return mps/MOTOR_KV;
    } else if(mps < 0.0) {
        return mps/MOTOR_KV;
    } else {
        return 0.0;
    }
}

float MotorController::clamp(float input, float minV = -1.0, float maxV = 1.0) {
    return min(max(input, minV), maxV);
}