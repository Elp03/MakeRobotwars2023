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

void Robot::moveForward()
{
    Serial.println("Moving forward!");
    leftWheel.turnCW();
    rightWheel.turnCW();
}

void Robot::moveBackward()
{
    Serial.println("Moving backward!");
    leftWheel.turnCCW();
    rightWheel.turnCCW();
}

void Robot::turnLeft()
{
    Serial.println("Sbinning left");
    leftWheel.turnCCW();
    rightWheel.turnCW();
}

void Robot::turnRight()
{
    Serial.println("Sbinning right!");
    leftWheel.turnCW();
    rightWheel.turnCCW();
}

void Robot::stop()
{
    Serial.println("Stopping!");
    leftWheel.stop();
    rightWheel.stop();
}