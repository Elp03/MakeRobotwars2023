
#define pin_robot_state 39
#define pin_robot_x_axis 34
#define pin_robot_y_axis 35
#define pin_wepon_state 36
#define pin_wepon_speed 33

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

struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_robot_state;
  bool message_wepon_state;
  int message_wepon_speed;
};

class controller
{
private:
    /* data */
public:
    void init(robot_values* robot, wepon_values* weapon);
    void update_data(robot_values* robot, wepon_values* wepon);
    void print_values(robot_values* robot, wepon_values* wepon);
    void update_struct(robot_values* robot, wepon_values* wepon, struct_message* controller_message);
    controller();
};

