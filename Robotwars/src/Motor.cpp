#include "Motor.hpp"

Motor::Motor(uint8_t ENPin, uint8_t IN1_Pin, uint8_t IN2_Pin): 
    enablePin{ENPin},
    dirCCWPin{IN1_Pin},
    dirCWPin{IN2_Pin} {}

void Motor::init()
{
    pinMode(enablePin, OUTPUT);
    pinMode(dirCCWPin, OUTPUT);
    pinMode(dirCWPin, OUTPUT);
}

void Motor::stop()
{
    analogWrite(enablePin, 0);
}

void Motor::turnCCW(uint8_t speed)
{
    Serial.println("Turning wheel CCW!");
    digitalWrite(dirCCWPin, HIGH);
    digitalWrite(dirCWPin, LOW);
    analogWrite(enablePin, speed);
}

void Motor::turnCW(uint8_t speed)
{
    Serial.println("Turning wheel CW!");
    digitalWrite(dirCCWPin, LOW);
    digitalWrite(dirCWPin, HIGH);
    analogWrite(enablePin, speed);
}