#include "Robot.hpp"

Robot::Robot(uint8_t* EN, uint8_t* IN1, uint8_t* IN2)
{
    leftWheel = Motor(*EN, *IN1, *IN2);
    rightWheel = Motor(*(EN+1), *(IN1+1), *(IN2+1));
    weapon = Motor(*(EN+2), *(IN1+2), *(IN2+2));
}

void Robot::init()
{
    leftWheel.init();
    rightWheel.init();
}

void Robot::moveForward(uint8_t speed)
{
    Serial.println("Moving forward!");
    leftWheel.turnCW(speed);
    rightWheel.turnCW(speed);
}

void Robot::moveBackward(uint8_t speed)
{
    Serial.println("Moving backward!");
    leftWheel.turnCCW(speed);
    rightWheel.turnCCW(speed);
}

void Robot::turnLeft(uint8_t speed)
{
    Serial.println("Sbinning left");
    leftWheel.turnCCW(speed);
    rightWheel.turnCW(speed);
}

void Robot::turnRight(uint8_t speed)
{
    Serial.println("Sbinning right!");
    leftWheel.turnCW(speed);
    rightWheel.turnCCW(speed);
}

void Robot::stop()
{
    Serial.println("Stopping!");
    leftWheel.stop();
    rightWheel.stop();
}