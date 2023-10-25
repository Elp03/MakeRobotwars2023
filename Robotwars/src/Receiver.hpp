#ifndef RECEIVER_H
#define RECEIVER_H
#include "Arduino.h"
struct struct_message
{
    int message_robot_x_axis;
    int message_robot_y_axis;
    bool message_robot_state;
    bool message_weapon_state;
    int message_weapon_speed;
};

static struct_message incoming_controller_message;

void print_values(struct_message *print_info);
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);

#endif /*RECEIVER_H*/