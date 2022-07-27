#include "Encoder.h"

Encoder::Encoder() {
    pinMode(HALL_A, INPUT);
    pinMode(HALL_B, INPUT);
    pinMode(HALL_C, INPUT);

    _currentRotorState = getRotorState();

    attachInterrupt(HALL_A, [this]() {updateEncoder();}, CHANGE);
    attachInterrupt(HALL_B, [this]() {updateEncoder();}, CHANGE);
    attachInterrupt(HALL_C, [this]() {updateEncoder();}, CHANGE);
}

double Encoder::getPositionMeters() {
    return _rotorPosition/COUNTS_PER_METER;
}

double Encoder::getPositionMiles() {
    return _rotorPosition/COUNTS_PER_MILE;
}

double Encoder::getSpeedMPS() {
    return _countsPerSecond/COUNTS_PER_METER;
}

double Encoder::getSpeedMPH() {
    return (_countsPerSecond*60.0*60.0)/COUNTS_PER_MILE;
}

void Encoder::updateEncoder() {
    unsigned long time = micros();
    double deltaT = (time-_lastCount)/1000000.0;
    _lastCount = time;

    uint8_t state = getRotorState();

    if(NEXT_HALL_STATE[_currentRotorState] == state) {
        _rotorPosition++;
        _countsPerSecond = _countsPerSecond*0.9 + (1.0/deltaT)*0.1;
    }

    if(PREV_HALL_STATE[_currentRotorState] == state) {
        _rotorPosition--;
        _countsPerSecond = _countsPerSecond*0.9 - (1.0/deltaT)*0.1;
    }

    _currentRotorState = state;
}

uint8_t Encoder::getRotorState() {
  return (digitalRead(HALL_A)) + (digitalRead(HALL_B)<<1) + (digitalRead(HALL_C)<<2);
}