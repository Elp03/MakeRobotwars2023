#include "esp_now.h"
#define pin_robot_x_axis 34
#define pin_robot_y_axis 35
#define pin_weapon_state 36
#define pin_weapon_speed 33

struct robot_values 
{
  int y_axis;
  int x_axis;
};

struct weapon_values 
{
  bool state;
  int speed;
};

struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_weapon_state;
  int message_weapon_speed;
};

class controller
{
private:
    robot_values* robot_vals;
    weapon_values* weapon_vals;
    struct_message* message;
public:
    controller(robot_values* obj_robot_vals, weapon_values* obj_weapon_vals, struct_message* obj_message);
    void init();
    void update_data();
    void print_values();
    void update_struct();
    esp_err_t send_message(uint8_t* robot_address);
};

