#include "controller.hpp"
#include <Arduino.h>


controller::controller(robot_values* obj_robot_vals, weapon_values* obj_weapon_vals, struct_message* obj_message):
                      robot_vals{obj_robot_vals}, weapon_vals{obj_weapon_vals}, message{obj_message} {}

void controller::init(){
    robot_vals->x_axis = analogRead(pin_robot_x_axis);
    robot_vals->y_axis = analogRead(pin_robot_y_axis);
    weapon_vals->state= digitalRead(pin_weapon_state);
    weapon_vals->speed = analogRead(pin_weapon_speed);
}

void controller::update_data(){
  robot_vals -> x_axis = analogRead(pin_robot_x_axis);
  robot_vals -> y_axis = analogRead(pin_robot_y_axis);
  weapon_vals -> state= digitalRead(pin_weapon_state);
  weapon_vals -> speed = analogRead(pin_weapon_speed);
}

void controller::update_struct(){
  message -> message_robot_x_axis = robot_vals -> x_axis;
  message -> message_robot_y_axis = robot_vals -> y_axis;
  message -> message_weapon_state = (weapon_vals -> state);
  message -> message_weapon_speed = weapon_vals -> speed;
}

void controller::print_values(){
  Serial.print("Robot x:"); Serial.println(robot_vals -> x_axis);
  Serial.print("Robot y:"); Serial.println(robot_vals -> y_axis);
  Serial.print("Weapon state:"); Serial.println(weapon_vals -> state);
  Serial.print("Weapon speed:"); Serial.println(weapon_vals -> speed);
}

esp_err_t controller::send_message(uint8_t* robot_address)
{
  esp_err_t result = esp_now_send(robot_address, (uint8_t *) this->message, sizeof(this->message));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}


