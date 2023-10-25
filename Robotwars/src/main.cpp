#include <Arduino.h>
#include "Motor.hpp"
#include "Robot.hpp"
#include "Receiver.hpp"
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#define EN1 12
#define IN1_1 13
#define IN1_2 14
#define EN2 33
#define IN2_1 26
#define IN2_2 32

uint8_t broadcast_addr[] = {0x0C, 0x8B, 0x95, 0x76, 0x81, 0xA0};

// uint8_t broadcast_addr[] = {0x7C, 0x9E, 0xBD, 0x66, 0x5D, 0x38};

struct_message sending_message;

esp_now_peer_info_t peerInfo;

const size_t buffer_size = 3;
uint8_t EN_array[buffer_size] = {EN1, EN2, 0};
uint8_t IN1_array[buffer_size] = {IN1_1, IN2_1, 0};
uint8_t IN2_array[buffer_size] = {IN1_2, IN2_2, 0};

Robot sbinnala(EN_array, IN1_array, IN2_array);

void setup() {
  sbinnala.init();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW!");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  Serial.println("Sbin sequence started!");
  uint8_t speed_x = map(incoming_controller_message.message_robot_x_axis, 0, 4095, 0, 255);
  uint8_t speed_y = map(incoming_controller_message.message_robot_y_axis, 0, 4095, 0, 255);
  sbinnala.moveForward(speed_y);
  delay(1000);
  sbinnala.stop();
  delay(1000);
  sbinnala.moveBackward(speed_y);
  delay(1000);
  sbinnala.stop();
  delay(1000);
  sbinnala.turnLeft(speed_x);
  delay(1000);
  sbinnala.stop();
  delay(1000);
  sbinnala.turnRight(speed_x);
  delay(1000);
  sbinnala.stop();
  delay(1000);
}