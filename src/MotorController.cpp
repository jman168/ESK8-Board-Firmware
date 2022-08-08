#include "MotorController.h"

SparkMax *motor_controller_spark;
PIDController pidController(0.0, 0.4, 0.0, MAX_VOLTAGE);

float motor_controller_output_voltage = 0.0;
float motor_controller_throttle = 0.0;
bool motor_controller_stop = true;

float clamp(float input, float minV = -1.0, float maxV = 1.0) {
    return min(max(input, minV), maxV);
}

void motor_controller_init(SparkMax *spark) {
    motor_controller_spark = spark;
}

// void motor_controller_update() {
//     if(motor_controller_stop) {
//         if(abs(motor_controller_spark->getVelocity()) > STOPPED_THRESHOLD) { // if the board is not stopped try to stop it
//             if(motor_controller_spark->getVelocity() > 0.0) {
//                 motor_controller_set_current(-BREAKING_CURRENT);
//                 motor_controller_set_voltage(pidController.compute(motor_controller_get_signed_current()));
//             }

//             if(motor_controller_spark->getVelocity() < 0.0) {
//                 motor_controller_set_current(BREAKING_CURRENT);
//                 motor_controller_set_voltage(pidController.compute(motor_controller_get_signed_current()));
//             }
//         }   

//         else { // if the board is stopped apply 0 output.
//             motor_controller_set_voltage(0.0);
//         }
//     }
    
//     else { // only to run of the board is not commanded to stop.
//         motor_controller_set_voltage(pidController.compute(motor_controller_get_signed_current()));
//     }
// }

// void motor_controller_update() {
//     float current = motor_controller_get_signed_current();
//     float pidOutput = pidController.compute(current);

//     motor_controller_set_voltage(pidOutput);
// }

void motor_controller_update() {
    float current = motor_controller_get_signed_current();
    float pidOutput = pidController.compute(current);

    if(motor_controller_throttle == 0.0 && abs(motor_controller_spark->getVelocity()) < STOPPED_THRESHOLD) {
        motor_controller_set_voltage(0.0);
    }

    else {
        motor_controller_set_voltage(pidOutput);
    }
}

void motor_controller_set_voltage(float voltage) {
    motor_controller_output_voltage = clamp(voltage, -MAX_VOLTAGE, MAX_VOLTAGE);
    motor_controller_spark->setVoltage(
        clamp(voltage, -MAX_VOLTAGE, MAX_VOLTAGE)
    );
}

void motor_controller_set_throttle(float throttle) {
    motor_controller_throttle = throttle;
    pidController.set(throttle*MAX_CURRENT);
}

float motor_controller_get_signed_current() {
    float backEMF = motor_controller_spark->getVelocity() / MOTOR_KV;
    float voltageDiff = motor_controller_output_voltage - backEMF;

    if(voltageDiff < 0.0) {
        return -motor_controller_spark->getOutputCurrent();
    } else {
        return motor_controller_spark->getOutputCurrent();
    }
}

void motor_controller_set_stop(bool stop) {
    motor_controller_stop = stop;
}