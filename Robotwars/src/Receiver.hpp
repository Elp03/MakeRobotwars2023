#ifndef RECEIVER_H
#define RECEIVER_H
#include "espnow.hpp"
#include "esp_now.h"
#include "Wire.h"
#include "WiFi.h"

//Structure example to send data
//Must match the receiver structure
struct struct_message
{
  int message_robot_x_axis;
  int message_robot_y_axis; 
  bool message_wepon_state;
  int message_wepon_speed;
};

class Receiver : public espnow
{
    private:
        uint8_t* controller_addr;
        struct_message* message;
    public:
        Receiver(struct_message* obj_message);
        void print_values() const;
        struct_message* get_message() const;
};

#endif /*RECEIVER_H*/