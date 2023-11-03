#include <Arduino.h>
#include "Motor.hpp"
#include "Robot.hpp"
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
#define EN1 2
#define IN1_1 13
#define IN1_2 14
#define EN2 4
#define IN2_1 26
#define IN2_2 32

uint8_t broadcast_addr[] = {0x0C, 0x8B, 0x95, 0x76, 0x81, 0xA0};
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

//uint8_t broadcast_addr[] = {0x7C, 0x9E, 0xBD, 0x66, 0x5D, 0x38};
state robot_info;
esp_now_peer_info_t peerInfo;

const size_t buffer_size = 3;
uint8_t EN_array[buffer_size] = {EN1, EN2, 0};
uint8_t IN1_array[buffer_size] = {IN1_1, IN2_1, 0};
uint8_t IN2_array[buffer_size] = {IN1_2, IN2_2, 0};

Robot sbinnala(EN_array, IN1_array, IN2_array, &robot_info);

void setup() {
  sbinnala.init();
  Serial.begin(115200);
  while(!Serial);
  WiFi.mode(WIFI_STA);

  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW!");
    return;
  }

  // Register peer
  memcpy(peerInfo.peer_addr, broadcast_addr, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if(esp_now_add_peer(&peerInfo)!= ESP_OK)
  {
    Serial.println("Failed to add peer!");
    return;
  }

  // Register data receive callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  //Serial.println("Sbin sequence started!");
  sbinnala.moveCommand();
  Serial.print("xakse");
  Serial.println(sbinnala.getRobotState()->robot_x_axis);
  delay(1000);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(sbinnala.getRobotState(), incomingData, sizeof(*sbinnala.getRobotState()));
    Serial.println("Bytes received: ");
    Serial.println(len);
    print_values(sbinnala.getRobotState());
}