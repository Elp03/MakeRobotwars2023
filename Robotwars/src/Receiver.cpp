#include "Receiver.hpp"

Receiver::Receiver(uint8_t* obj_cont_addr, struct_message* obj_message): controller_addr{obj_cont_addr}, message{obj_message} {}

void Receiver::init()
{
    // Init ESP-NOW
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    // Once ESPNow is successfully Init, we will register for Send CB to
    // get the status of Trasnmitted packet
    esp_now_register_send_cb(data_sent_cb);

    // Register peer
    memcpy(peerInfo.peer_addr, controller_addr, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    // Add peer
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }
    // Register for a callback function that will be called when data is received
    esp_now_register_recv_cb(data_recv_cb);
}

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

void Receiver::set_message()
{
    memcpy(this->message, gl_message, sizeof(this->message));
}

void data_sent_cb(const uint8_t* mac_addr, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void data_recv_cb(const uint8_t *mac, const uint8_t *incomingData, int len)
{
    memcpy(gl_message, incomingData, sizeof(gl_message));
    Serial.print("Bytes received: ");
    Serial.println(len);
}