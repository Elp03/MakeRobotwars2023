#include "Receiver.hpp"

Receiver::Receiver(struct_message* obj_message): message{obj_message} {}

void Receiver::print_values() const
{
  Serial.print("Robot x:"); Serial.println(message->message_robot_x_axis);
  Serial.print("Robot y:"); Serial.println(message->message_robot_y_axis);
  Serial.print("wepon state:"); Serial.println(message->message_wepon_state);
  Serial.print("wepon pot:"); Serial.println(message->message_wepon_speed);
}

struct_message* Receiver::get_message() const
{
    return message;
}