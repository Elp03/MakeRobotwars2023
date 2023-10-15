#include "espnow.hpp"
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>


void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
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
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&inncomming_message, incomingData, sizeof(inncomming_message));
  Serial.print("Bytes received: ");
  Serial.println(len);
}