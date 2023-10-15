#include <Arduino.h>
//sending data
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#include "Motor.hpp"
#include "Robot.hpp"
#include "controller.hpp"
#include "espnow.hpp"

//for robot
#define EN1 12
#define IN1_1 13
#define IN1_2 14
#define EN2 33
#define IN2_1 26
#define IN2_2 32

uint8_t controller_address[] = {0x7C, 0x9E, 0xBD, 0x66, 0x5D, 0x38};
uint8_t robot_address[] = {0x44, 0x17, 0x93, 0x5E, 0x4A, 0x6C};

// for controller + robot
robot_values rval_t;
weapon_values wval_t;
struct_message message;

//for robot
const size_t buffer_size = 3;
uint8_t EN_array[buffer_size] = {EN1, EN2, 0};
uint8_t IN1_array[buffer_size] = {IN1_1, IN2_1, 0};
uint8_t IN2_array[buffer_size] = {IN1_2, IN2_2, 0};

Robot sbinnala(EN_array, IN1_array, IN2_array);
controller theBOSS(&rval_t, &wval_t, &message); 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 


  sbinnala.init();
  theBOSS.init();

  

  WiFi.mode(WIFI_STA);

}

void loop() {
  theBOSS.update_data(); 
  theBOSS.update_struct();
  theBOSS.print_values();
  theBOSS.send_message(robot_address);
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
