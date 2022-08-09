#include "MotorController.h"

float clamp(float input, float minV = -1.0, float maxV = 1.0) {
    return min(max(input, minV), maxV);
}

MotorController::MotorController(SparkMax *spark): _currentController(CURRENT_P, CURRENT_I, CURRENT_D, MAX_VOLTAGE) {
    _spark = spark;
}

void MotorController::update() {
    float current = getSignedCurrent();
    float pidOutput = _currentController.compute(current);

    if(_throttle == 0.0 && abs(_spark->getVelocity()) < STOPPED_THRESHOLD) {
        reset();
        setVoltage(0.0);
    }

    else {
        setVoltage(pidOutput);
    }
}

void MotorController::setVoltage(float voltage) {
    _setVoltage = clamp(voltage, -MAX_VOLTAGE, MAX_VOLTAGE);
    _spark->setVoltage(
        _setVoltage
    );
}

void MotorController::setThrottle(float throttle) {
    _throttle = throttle;
    _currentController.set(_throttle*MAX_CURRENT);
}

float MotorController::getSignedCurrent() {
    float backEMF = _spark->getVelocity() / MOTOR_KV;
    float voltageDiff = _setVoltage - backEMF;

    if(voltageDiff < 0.0) {
        return -_spark->getOutputCurrent();
    } else {
        return _spark->getOutputCurrent();
    }
}

void MotorController::reset() {
    _currentController.reset();
}