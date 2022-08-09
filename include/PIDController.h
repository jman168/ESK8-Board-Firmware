#pragma once 

#include <Arduino.h>    

class PIDController {
    public:
        /**
         * @brief Construct a new PIDController object.
         * 
         * @param p proportional coefficient of the controller
         * @param i integral coefficient of the controller
         * @param d derivative coefficient of the controller
         * @param iZone integration zone of the controller (the integral term will never be less than -iZone and greater than iZone).
         */
        PIDController(double p, double i, double d, double iZone);

        /**
         * @brief Sets the set piont of the controller.
         * 
         * @param setPoint 
         */
        void set(double setPoint);

        /**
         * @brief Computes the output of the controller based on the given feedback or input to the controller.
         * 
         * @param feedback 
         * @return double 
         */
        double compute(double feedback);

        /**
         * @brief Resets the PID loop to how it was when initialized.
         * 
         */
        void reset();

    private:
        unsigned long lastCompute = 0.0;

        double _p, _i, _d, _iZone;
        double _setPoint = 0.0;

        double _proportionalTerm = 0.0, _integralTerm = 0.0, _derivativeTerm = 0.0;
        double _lastError = 0.0;
};