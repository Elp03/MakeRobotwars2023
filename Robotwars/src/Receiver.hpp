#ifndef RECEIVER_H
#define RECEIVER_H
#include "espnow.hpp"
#include "esp_now.h"
#include "Wire.h"
#include "WiFi.h"

// Global variable to store the message from the callback
uint8_t* gl_message;

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
        esp_now_peer_info_t peerInfo;
    public:
        Receiver(uint8_t* obj_cont_addr, struct_message* obj_message);
        void init();
        void print_values() const;
        struct_message* get_message() const;
        void set_message();
};

void data_sent_cb(const uint8_t *mac_addr, esp_now_send_status_t status);
void data_recv_cb(const uint8_t *mac, const uint8_t *incomingData, int len);

#endif /*RECEIVER_H*/