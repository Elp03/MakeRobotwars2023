#include <Arduino.h>
#include "Motor.hpp"
#include "Robot.hpp"
#define EN1 12
#define IN1_1 13
#define IN1_2 14
#define EN2 33
#define IN2_1 26
#define IN2_2 32

const size_t buffer_size = 3;
uint8_t EN_array[buffer_size] = {EN1, EN2, 0};
uint8_t IN1_array[buffer_size] = {IN1_1, IN2_1, 0};
uint8_t IN2_array[buffer_size] = {IN1_2, IN2_2, 0};

Robot sbinnala(EN_array, IN1_array, IN2_array);

void setup() {
  sbinnala.init();
  Serial.begin(115200);
}

void loop() {
  Serial.println("Sbin sequence started!");
  sbinnala.moveForward();
  delay(1000);
  sbinnala.stop();
  delay(1000);
  sbinnala.moveBackward();
  delay(1000);
  sbinnala.stop();
  delay(1000);
  sbinnala.turnLeft();
  delay(1000);
  sbinnala.stop();
  delay(1000);
  sbinnala.turnRight();
  delay(1000);
  sbinnala.stop();
  delay(1000);
}