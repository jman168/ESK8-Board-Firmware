#include "MotorController.h"

float motor_controller_throttle = 0.0;

float clamp(float input, float minV = -1.0, float maxV = 1.0) {
    return min(max(input, minV), maxV);
}

float motor_controller_mps_to_voltage(float mps) {
    return mps/MOTOR_KV;
}

void motor_controller_init() {
    ledcAttachPin(MOTOR_PIN, PWM1_CH);
    ledcSetup(PWM1_CH, PWM1_FREQ, PWM1_RES);
}

void motor_controller_update() {
    motor_controller_set_voltage(clamp(motor_controller_mps_to_voltage(encoder_get_speed_mps()) + motor_controller_throttle*MAX_DELTA_V, -MAX_VOLTAGE, MAX_VOLTAGE));
}

void motor_controller_set_voltage(float voltage) {
    float power = ( voltage/BATTERY_VOLTAGE + 1.0 ) / 2.0;
    uint32_t duty = MIN_DUTY + (MAX_DUTY-MIN_DUTY) * power;

    ledcWrite(PWM1_CH, duty);
}

void motor_controller_set_throttle(float throttle) {
    motor_controller_throttle = throttle;
}