#include <Arduino.h>

// put function declarations here:
#define pin_robot_state 39
#define pin_robot_x_axis 34
#define pin_robot_y_axis 35
#define pin_wepon_state 36
#define pin_wepon_speed 33




struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_robot_speed;
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

robot_values robot;
wepon_values wepon;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  pinMode(pin_robot_state, INPUT);
  pinMode(pin_robot_x_axis, INPUT);
  pinMode(pin_robot_y_axis, INPUT);
  pinMode(pin_wepon_state, INPUT);
  pinMode(pin_wepon_speed, INPUT);

}

void loop() {
  update_data(); 
  update_struct();

  delay(1000);
}

void update_data(){
  robot.state =  digitalRead(pin_robot_state);
  robot.x_axis = analogRead(pin_robot_x_axis);
  robot.y_axis = analogRead(pin_robot_y_axis);
  wepon.state= digitalRead(pin_wepon_state);
  wepon.speed = analogRead(pin_wepon_speed);
}

void update_struct(){
  conntroller_message.message_robot_speed = (robot.state ? true : false);
  conntroller_message.message_robot_x_axis = robot.x_axis;
  conntroller_message.message_robot_y_axis = robot.y_axis;
  conntroller_message.message_wepon_state = (wepon.state ? true : false);
  conntroller_message.message_wepon_speed = wepon.speed;
}

void print_values(){
  Serial.print("Robot state:"); Serial.println(robot.state);
  Serial.print("Robot x:"); Serial.println(robot.x_axis);
  Serial.print("Robot y:"); Serial.println(robot.y_axis);
  Serial.print("wepon state:"); Serial.println(wepon.state);
  Serial.print("wepon pot:"); Serial.println(wepon.speed);
}