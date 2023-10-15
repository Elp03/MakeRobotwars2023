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


//for robot
const size_t buffer_size = 3;
uint8_t EN_array[buffer_size] = {EN1, EN2, 0};
uint8_t IN1_array[buffer_size] = {IN1_1, IN2_1, 0};
uint8_t IN2_array[buffer_size] = {IN1_2, IN2_2, 0};

Robot sbinnala(EN_array, IN1_array, IN2_array);
controller theBOSS();


 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 


  sbinnala.init();
  theBOSS.init();

  

  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, robot_address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);

}

void loop() {
  update_data(); 
  update_struct();
  print_values();

  esp_err_t result = esp_now_send(robot_address, (uint8_t *) &conntroller_message, sizeof(conntroller_message));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
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
