#include "Receiver.hpp"

void print_values(struct_message *print_info)
{
    Serial.print("Robot state: ");
    Serial.println(print_info->message_robot_state);
    Serial.print("Robot x: ");
    Serial.println(print_info->message_robot_x_axis);
    Serial.print("Robot y:");
    Serial.println(print_info->message_robot_y_axis);
    Serial.print("Weapon state:");
    Serial.println(print_info->message_weapon_state);
    Serial.print("Weapon pot:");
    Serial.println(print_info->message_weapon_speed);
}

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(&incoming_controller_message, incomingData, sizeof(incoming_controller_message));
    Serial.println("Bytes received: ");
    Serial.println(len);
    print_values(&incoming_controller_message);
}