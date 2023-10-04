#include <Arduino.h>
//sending data
#include <esp_now.h>
#include <WiFi.h>

#include <Wire.h>

// put function declarations here:
#define pin_robot_state 39
#define pin_robot_x_axis 34
#define pin_robot_y_axis 35
#define pin_wepon_state 36
#define pin_wepon_speed 33

uint8_t broadcastAddress[] = {0x7C, 0x9E, 0xBD, 0x66, 0x5D, 0x38};


struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_robot_state;
  bool message_wepon_state;
  int message_wepon_speed;
};

struct robot_values 
{
  bool state;
  int y_axis;
  int x_axis;
};

struct wepon_values 
{
  bool state;
  int speed;
};

struct_message conntroller_message;
struct_message inncomming_message;

robot_values robot;
wepon_values wepon;

String success;
esp_now_peer_info_t peerInfo;


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
void update_data(){
  robot.state =  digitalRead(pin_robot_state);
  robot.x_axis = analogRead(pin_robot_x_axis);
  robot.y_axis = analogRead(pin_robot_y_axis);
  wepon.state= digitalRead(pin_wepon_state);
  wepon.speed = analogRead(pin_wepon_speed);
}

void update_struct(){
  conntroller_message.message_robot_state = (robot.state);
  conntroller_message.message_robot_x_axis = robot.x_axis;
  conntroller_message.message_robot_y_axis = robot.y_axis;
  conntroller_message.message_wepon_state = (wepon.state);
  conntroller_message.message_wepon_speed = wepon.speed;
}

void print_values(){
  Serial.print("Robot state:"); Serial.println(robot.state);
  Serial.print("Robot x:"); Serial.println(robot.x_axis);
  Serial.print("Robot y:"); Serial.println(robot.y_axis);
  Serial.print("wepon state:"); Serial.println(wepon.state);
  Serial.print("wepon pot:"); Serial.println(wepon.speed);
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&inncomming_message, incomingData, sizeof(inncomming_message));
  Serial.print("Bytes received: ");
  Serial.println(len);
}
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  pinMode(pin_robot_state, INPUT);
  pinMode(pin_robot_x_axis, INPUT);
  pinMode(pin_robot_y_axis, INPUT);
  pinMode(pin_wepon_state, INPUT);
  pinMode(pin_wepon_speed, INPUT);

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
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
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

  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &conntroller_message, sizeof(conntroller_message));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  delay(1000);
}