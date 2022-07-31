#include "MotorController.h"

Servo motor_controller_motor;

float motor_controller_throttle = 0.0;
bool motor_controller_stop = true;

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
    if(motor_controller_stop) {
        if(abs(encoder_get_speed_mps()) > STOPPED_THRESHOLD) { // if the board is not stopped try to stop it
            if(encoder_get_speed_mps() > 0.0) {
                motor_controller_set_voltage(clamp(motor_controller_mps_to_voltage(encoder_get_speed_mps()) - STOP_VOLTAGE, -MAX_VOLTAGE, MAX_VOLTAGE));
            }

            if(encoder_get_speed_mps() < 0.0) {
                motor_controller_set_voltage(clamp(motor_controller_mps_to_voltage(encoder_get_speed_mps()) + STOP_VOLTAGE, -MAX_VOLTAGE, MAX_VOLTAGE));
            }
        }   

        else { // if the board is stopped apply 0 output.
            motor_controller_set_voltage(0.0);
        }
    }
    
    else { // only to run of the board is not commanded to stop.
        motor_controller_set_voltage(clamp(motor_controller_mps_to_voltage(encoder_get_speed_mps()) + motor_controller_throttle*MAX_DELTA_V, -MAX_VOLTAGE, MAX_VOLTAGE));
    }
}

void motor_controller_set_voltage(float voltage) {
    float power = ( voltage/BATTERY_VOLTAGE + 1.0 ) / 2.0;
    int MS = MIN_MS + (MAX_MS-MIN_MS) * power;

    motor_controller_motor.writeMicroseconds(MS);
}

void motor_controller_set_throttle(float throttle) {
    motor_controller_throttle = throttle;
}

void motor_controller_set_stop(bool stop) {
    motor_controller_stop = stop;
}