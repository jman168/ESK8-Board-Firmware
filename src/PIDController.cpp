#include "PIDController.h"

PIDController::PIDController(double p, double i, double d, double iZone) {
    _p = p;
    _i = i;
    _d = d;
    _iZone = iZone;
}

void PIDController::set(double setPoint) {
    _setPoint = setPoint;
}

double PIDController::compute(double feedback) {
    unsigned long time = micros();
    double deltaT = (time-lastCompute)/1000000.0;
    lastCompute = time;

    double error = _setPoint - feedback;

    _proportionalTerm = (error)                         * _p;
    _integralTerm +=    (error * deltaT)                * _i;
    _derivativeTerm =   ((error - _lastError) / deltaT) * _d;

    if(_integralTerm < -_iZone)
        _integralTerm = -_iZone;

    if(_integralTerm > _iZone)
        _integralTerm = _iZone;

    _lastError = error;

    return _proportionalTerm + _integralTerm + _derivativeTerm;
}