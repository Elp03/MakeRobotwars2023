#include "Robot.hpp"

Robot::Robot(uint8_t* EN, uint8_t* IN1, uint8_t* IN2, state* state_message)
{
    leftWheel = Motor(*EN, *IN1, *IN2, 0);
    rightWheel = Motor(*(EN+1), *(IN1+1), *(IN2+1), 1);
    weapon = Motor(*(EN+2), *(IN1+2), *(IN2+2), 4);
    robotState = state_message;
}

void Robot::init()
{
    leftWheel.init();
    rightWheel.init();
    weapon.init();
}

void Robot::moveForward(uint8_t speed)
{
    leftWheel.turnCW(speed);
    rightWheel.turnCW(speed);
}

void Robot::moveBackward(uint8_t speed)
{
    leftWheel.turnCCW(speed);
    rightWheel.turnCCW(speed);
}

void Robot::turnLeft(uint8_t speed)
{
    leftWheel.turnCCW(speed);
    rightWheel.turnCW(speed);
}

void Robot::turnRight(uint8_t speed)
{
    leftWheel.turnCW(speed);
    rightWheel.turnCCW(speed);
}

void Robot::stop()
{
    leftWheel.stop();
    rightWheel.stop();
}

void Robot::moveCommand()
{
    switch (robotState->dir)
    {
    case NEUTRAL:
    {
        stop();
        break;
    }
    case FORWARD:
    {
        uint8_t speed_y = map(abs(robotState->robot_y_axis), 0, 2550, 0, 255);
        moveForward(speed_y);
        break;
    }
    case BACKWARD:
    {
        uint8_t speed_y = map(abs(robotState->robot_y_axis), 0, 2550, 0, 255);
        moveBackward(speed_y);
        break;
    }
    case RIGHT:
    {
        uint8_t speed_x = map(abs(robotState->robot_x_axis), 0, 2550, 0, 255);
        turnRight(speed_x);
        break;
    }
    case LEFT:
    {
        uint8_t speed_x = map(abs(robotState->robot_x_axis), 0, 2550, 0, 255);
        turnLeft(speed_x);
        break;
    }
    default:
        stop();
        break;
    }
}

state* Robot::getRobotState() const
{
    return robotState;
}

void print_values(state *print_info)
{
    Serial.print("Robot state: ");
    Serial.println(print_info->robot_state);
    Serial.print("Robot x: ");
    Serial.println(print_info->robot_x_axis);
    Serial.print("Robot y: ");
    Serial.println(print_info->robot_y_axis);
    Serial.print("Weapon state: ");
    Serial.println(print_info->weapon_state);
    Serial.print("Weapon pot: ");
    Serial.println(print_info->weapon_speed);
    Serial.print("Direction: ");
    Serial.println(String((int)(print_info->dir)));
}

