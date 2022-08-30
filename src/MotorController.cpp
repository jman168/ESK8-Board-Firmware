#include "MotorController.h"

float clamp(float input, float minV = -1.0, float maxV = 1.0) {
    return min(max(input, minV), maxV);
}

MotorController::MotorController(SparkMax *spark): _currentController(CURRENT_P, CURRENT_I, CURRENT_D, MAX_VOLTAGE) {
    _spark = spark;
}

// void MotorController::update() {
//     float current = getSignedCurrent();
//     float pidOutput = _currentController.compute(current);

//     if(_throttle == 0.0 && abs(_spark->getVelocity()) < STOPPED_THRESHOLD) {
//         reset();
//         setVoltage(0.0);
//     }

//     else {
//         setVoltage(pidOutput);
//     }
// }

void MotorController::update() {
    float current = getSignedCurrent();
    float pidOutput = _currentController.compute(current);
    float velocity = _spark->getVelocity();

    if(abs(velocity) < STOPPED_THRESHOLD) { // if board is stopped
        if(_throttle == 0.0) {
            setVoltage(0.0);
            _currentController.setIntegrator(0.0);
        } else {
            setVoltage(pidOutput);
        }
    }

    // pulse width module a voltage between 0.0V and the computed free spin voltage
    else if(_brake > 0.0) { // if breaking
        double voltage = velocity / MOTOR_KV;
        _currentController.setIntegrator(voltage);        

        if(velocity > 0.0) {
            voltage -= BRAKE_VOLTAGE*_brake;
        } if(velocity < 0.0) {
            voltage += BRAKE_VOLTAGE*_brake;
        }
        
        setVoltage(voltage);
    }

    else { // if accelerating
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
    float velocity = _spark->getVelocity();

    if(velocity > STOPPED_THRESHOLD) { // if rolling forwards
        if(throttle >= 0.0) {
            _throttle = throttle;
            _brake = 0.0;
        } else {
            _throttle = 0.0;
            _brake = -throttle;
        }
    } else if(velocity < -STOPPED_THRESHOLD) { // if rolling backwards
        if(throttle >= 0.0) {
            _throttle = 0.0;
            _brake = throttle;
        } else {
            _throttle = throttle;
            _brake = 0.0;
        }
    } else { // if the board is stopped
        _throttle = throttle;
    }

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