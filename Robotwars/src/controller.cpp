#include "controller.hpp"
#include <Arduino.h>


controller::controller(){

}
void controller::init(robot_values* robot, wepon_values* wepon){
    robot->state =  digitalRead(pin_robot_state);
    robot->x_axis = analogRead(pin_robot_x_axis);
    robot->y_axis = analogRead(pin_robot_y_axis);
    wepon->state= digitalRead(pin_wepon_state);
    wepon->speed = analogRead(pin_wepon_speed);
}

void controller::update_data(robot_values* robot, wepon_values* wepon){
  robot -> state =  digitalRead(pin_robot_state);
  robot -> x_axis = analogRead(pin_robot_x_axis);
  robot -> y_axis = analogRead(pin_robot_y_axis);
  wepon -> state= digitalRead(pin_wepon_state);
  wepon -> speed = analogRead(pin_wepon_speed);
}

void controller::update_struct(robot_values* robot, wepon_values* wepon, struct_message* controller_message){
  controller_message -> message_robot_state = (robot -> state);
  controller_message -> message_robot_x_axis = robot -> x_axis;
  controller_message -> message_robot_y_axis = robot -> y_axis;
  controller_message -> message_wepon_state = (wepon -> state);
  controller_message -> message_wepon_speed = wepon -> speed;
}

void controller::print_values(robot_values* robot, wepon_values* wepon){
  Serial.print("Robot state:"); Serial.println(robot -> state);
  Serial.print("Robot x:"); Serial.println(robot -> x_axis);
  Serial.print("Robot y:"); Serial.println(robot -> y_axis);
  Serial.print("wepon state:"); Serial.println(wepon -> state);
  Serial.print("wepon pot:"); Serial.println(wepon -> speed);
}


