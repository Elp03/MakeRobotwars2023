#ifndef ROBOT_H
#define ROBOT_H
#include "Motor.hpp"

class Robot
{
    private:
        Motor leftWheel;
        Motor rightWheel;
        Motor weapon;
    public:
        Robot(uint8_t* EN, uint8_t* IN1, uint8_t* IN2);
        void init();
        void moveForward();
        void moveBackward();
        void turnLeft();
        void turnRight();
        void stop();
};

#endif /*ROBOT_H*/