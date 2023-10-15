//sending data
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>
// REPLACE WITH THE MAC Address of your receiver 
//sender venstre
uint8_t robot_address[] = {0x0C, 0x8B, 0x95, 0x76, 0x81, 0xA0};

//reciver høyre
//uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x66, 0x5D, 0x38};


// Variable to store if sending data was successful
String success;

//Structure example to send data
//Must match the receiver structure
struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_robot_state;
  bool message_wepon_state;
  int message_wepon_speed;
};

struct_message inncomming_controller_message;
struct_message sending_message;

esp_now_peer_info_t peerInfo;

void print_values(){
  Serial.print("Robot state:"); Serial.println(inncomming_controller_message.message_robot_state);
  Serial.print("Robot x:"); Serial.println(inncomming_controller_message.message_robot_x_axis);
  Serial.print("Robot y:"); Serial.println(inncomming_controller_message.message_robot_y_axis);
  Serial.print("wepon state:"); Serial.println(inncomming_controller_message.message_wepon_state);
  Serial.print("wepon pot:"); Serial.println(inncomming_controller_message.message_wepon_speed);
}

// Callback when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&inncomming_controller_message, incomingData, sizeof(inncomming_controller_message));
  Serial.print("Bytes received: ");
  Serial.println(len);
  print_values();
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
 
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
  delay(1000);
}