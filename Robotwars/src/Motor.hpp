#ifndef MOTOR_H
#define MOTOR_H
#include "Arduino.h"

class Motor
{
    private:
        uint8_t enablePin;
        uint8_t dirCCWPin;
        uint8_t dirCWPin;
        int PWMChannel;
    public:
        Motor(uint8_t ENPin = 0, uint8_t IN1Pin = 0, uint8_t IN2_Pin = 0, int PWM_channel = 0);
        void init();
        void stop();
        void turnCCW(uint8_t speed);
        void turnCW(uint8_t speed);
};

#endif /*MOTOR_H*/