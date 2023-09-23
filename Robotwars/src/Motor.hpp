#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"

class Motor
{
    private:
        uint8_t enablePin;
        uint8_t dirCCWPin;
        uint8_t dirCWPin;
    public:
        Motor(uint8_t ENPin = 0, uint8_t IN1Pin = 0, uint8_t IN2_Pin = 0);
        void init();
        void stop();
        void turnCCW();
        void turnCW();
};

#endif /*MOTOR_H*/