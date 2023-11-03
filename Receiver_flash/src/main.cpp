#include <Arduino.h>
#include "esp_now.h"
#include "WiFi.h"
#include "Wire.h"
#include "Transmitter.hpp"

// Broadcast address
uint8_t broadcast_addr[] = {0x44, 0x17, 0x93, 0x5E, 0x4A, 0x6C};

struct_message transmit_msg = {0, 0, false, false, 0};
state totalState;
RemoteControl remote = RemoteControl(transmit_msg, totalState);

esp_now_peer_info_t peerInfo;

void setup() {
  remote.init();
  Serial.begin(115200);
  while(!Serial);

  remote.calibrate_joystick();
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // If initialization is successful, register the send callback to get status of transmitted packet.
  esp_now_register_send_cb(OnDataSent);

  // Register peer
  memcpy(peerInfo.peer_addr, broadcast_addr, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  // Add peer
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }

  // Register a callback function that will be called when data is received.
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  remote.update_data();
  remote.update_message();
  remote.print_values();

  struct_message transmission = remote.getMessage();
  esp_err_t result = esp_now_send(broadcast_addr, (uint8_t*) &transmission, sizeof(remote.getMessage()));

  if(result = ESP_OK)
  {
    Serial.println("Sent with success");
  }
  else
  {
    Serial.println("Error sending the data");
  }

  delay(100);
}