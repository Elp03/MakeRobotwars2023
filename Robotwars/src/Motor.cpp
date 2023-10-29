#include "Motor.hpp"

Motor::Motor(uint8_t ENPin, uint8_t IN1_Pin, uint8_t IN2_Pin, int PWM_channel): 
    enablePin{ENPin},
    dirCCWPin{IN1_Pin},
    dirCWPin{IN2_Pin},
    PWMChannel{PWM_channel} {}

void Motor::init()
{
    ledcSetup(PWMChannel, 5000, 8);
    ledcAttachPin(enablePin, PWMChannel);
    pinMode(dirCCWPin, OUTPUT);
    pinMode(dirCWPin, OUTPUT);
}

void Motor::stop()
{
    ledcWrite(enablePin, 0);
}

void Motor::turnCCW(uint8_t speed)
{
    digitalWrite(dirCCWPin, HIGH);
    digitalWrite(dirCWPin, LOW);
    ledcWrite(enablePin, speed);
}

void Motor::turnCW(uint8_t speed)
{
    digitalWrite(dirCCWPin, LOW);
    digitalWrite(dirCWPin, HIGH);
    ledcWrite(enablePin, speed);
}