#include "Encoder.h"

uint8_t encoder_current_rotor_state;
unsigned long encoder_last_count = 0;
long encoder_rotor_position = 0;
float encoder_counts_per_second = 0;

uint8_t encoder_get_rotor_state() {
  return (digitalRead(HALL_A)) + (digitalRead(HALL_B)<<1) + (digitalRead(HALL_C)<<2);
}

IRAM_ATTR void encoder_update() {
    unsigned long time = micros();
    double deltaT = (time-encoder_last_count)/1000000.0;
    encoder_last_count = time;

    uint8_t state = encoder_get_rotor_state();

    if(NEXT_HALL_STATE[encoder_current_rotor_state] == state) {
        encoder_rotor_position++;
        encoder_counts_per_second = encoder_counts_per_second*0.9 + (1.0/deltaT)*0.1;
    }

    if(PREV_HALL_STATE[encoder_current_rotor_state] == state) {
        encoder_rotor_position--;
        encoder_counts_per_second = encoder_counts_per_second*0.9 - (1.0/deltaT)*0.1;
    }

    encoder_current_rotor_state = state;
}

void encoder_init() {
    pinMode(HALL_A, INPUT);
    pinMode(HALL_B, INPUT);
    pinMode(HALL_C, INPUT);

    encoder_current_rotor_state = encoder_get_rotor_state();

    attachInterrupt(HALL_A, encoder_update, CHANGE);
    attachInterrupt(HALL_B, encoder_update, CHANGE);
    attachInterrupt(HALL_C, encoder_update, CHANGE);
}

float encoder_get_position_meters() {
    return encoder_rotor_position/COUNTS_PER_METER;
}

float encoder_get_position_miles() {
    return encoder_rotor_position/COUNTS_PER_MILE;
}

float encoder_get_speed_mps() {
    return encoder_counts_per_second/COUNTS_PER_METER;
}

float encoder_get_speed_mph() {
    return (encoder_counts_per_second*60.0*60.0)/COUNTS_PER_MILE;
}