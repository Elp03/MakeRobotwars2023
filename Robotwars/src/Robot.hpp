#ifndef ROBOT_H
#define ROBOT_H
#include "Motor.hpp"

typedef enum{
    NEUTRAL = 0,
    FORWARD = 1,
    BACKWARD = 2,
    RIGHT = 3,
    LEFT = 4
}direction;

typedef struct
{
    int robot_x_axis;
    int robot_y_axis;
    bool robot_state;
    bool weapon_state;
    int weapon_speed;
    direction dir;
}state;

class Robot
{
    private:
        Motor leftWheel;
        Motor rightWheel;
        Motor weapon;
        state* robotState;
    public:
        Robot(uint8_t* EN, uint8_t* IN1, uint8_t* IN2, state* state_message);
        void init();
        void moveForward(uint8_t speed);
        void moveBackward(uint8_t speed);
        void turnLeft(uint8_t speed);
        void turnRight(uint8_t speed);
        void stop();
        void moveCommand();
        state* getRobotState() const;
};

void print_values(state *print_info);

#endif /*ROBOT_H*/