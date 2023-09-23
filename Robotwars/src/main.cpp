#include <Arduino.h>

// put function declarations here:
#define pin_robot_state 39
#define pin_robot_x_axis 34
#define pin_robot_y_axis 35
#define pin_wepon_state 36
#define pin_wepon_speed 33

bool robot_state;
int robot_y_axis;
int robot_x_axis;
bool wepon_state;
int wepon_speed;


struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_robot_on_state;
  bool message_wepon_on_state;
  int message_wepon_speed_state;
};

struct_message conntroller_message;

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
  robot_state =  digitalRead(pin_robot_state);
  robot_x_axis = analogRead(pin_robot_x_axis);
  robot_y_axis = analogRead(pin_robot_y_axis);
  wepon_state = digitalRead(pin_wepon_state);
  wepon_speed = analogRead(pin_wepon_speed);

  Serial.print("Robot state:"); Serial.println(robot_state);
  Serial.print("Robot x:"); Serial.println(robot_x_axis);
  Serial.print("Robot y:"); Serial.println(robot_y_axis);
  Serial.print("wepon state:"); Serial.println(wepon_state);
  Serial.print("wepon pot:"); Serial.println(wepon_speed);
  delay(1000);
}