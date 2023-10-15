#include "espnow.hpp"
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

void espnow::init(uint8_t reciver_addr){
     // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, reciver_addr, 6);
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

void espnow::OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
  if (status ==0){
    success = "Delivery Success :)";
  }
  else{
    success = "Delivery Fail :(";
  }
}

//for both
void espnow::OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&inncomming_message, incomingData, sizeof(inncomming_message));
  Serial.print("Bytes received: ");
  Serial.println(len);
}


