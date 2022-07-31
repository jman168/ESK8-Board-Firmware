#include "MotorController.h"

Servo motor_controller_motor;

float motor_controller_throttle = 0.0;

float clamp(float input, float minV = -1.0, float maxV = 1.0) {
    return min(max(input, minV), maxV);
}

float motor_controller_mps_to_voltage(float mps) {
    return mps/MOTOR_KV;
}

void motor_controller_init() {
    motor_controller_motor.attach(MOTOR_PIN);
}

void motor_controller_update() {
    motor_controller_set_voltage(clamp(motor_controller_mps_to_voltage(encoder_get_speed_mps()) + motor_controller_throttle*MAX_DELTA_V, -MAX_VOLTAGE, MAX_VOLTAGE));
}

void motor_controller_set_voltage(float voltage) {
    float power = ( voltage/BATTERY_VOLTAGE + 1.0 ) / 2.0;
    int MS = MIN_MS + (MAX_MS-MIN_MS) * power;

    motor_controller_motor.writeMicroseconds(MS);
}

void motor_controller_set_throttle(float throttle) {
    motor_controller_throttle = throttle;
}