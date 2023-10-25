#ifndef ROBOT_H
#define ROBOT_H
#include "Motor.hpp"
#include "Receiver.hpp"

class Robot
{
    private:
        Motor leftWheel;
        Motor rightWheel;
        Motor weapon;
    public:
        Robot(uint8_t* EN, uint8_t* IN1, uint8_t* IN2);
        void init();
        void moveForward(uint8_t speed);
        void moveBackward(uint8_t speed);
        void turnLeft(uint8_t speed);
        void turnRight(uint8_t speed);
        void stop();
};

#endif /*ROBOT_H*/