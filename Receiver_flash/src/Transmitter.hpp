#ifndef TRANSMITTER_H
#define TRANSMITTER_H
#include "Arduino.h"
#include "esp_now.h"
#include "driver/adc.h"

#define ROBOT_STATE_PIN 39
#define ROBOT_X_PIN 34
#define ROBOT_Y_PIN 35
#define WEAPON_STATE_PIN 36
#define WEAPON_SPEED_PIN 33

#define WINDOW_SIZE 10
#define X 0
#define Y 1
#define DEADZONE 30

#define CALIBRATION_TIME_MS 10000

typedef enum
{
    NEUTRAL = 0,
    FORWARD = 1,
    BACKWARD = 2,
    RIGHT = 3,
    LEFT = 4
}dir_t;

typedef struct
{
    int message_robot_x_axis;
    int message_robot_y_axis;
    bool message_robot_state;
    bool message_weapon_state;
    int message_weapon_speed;
    dir_t message_robot_direction;
}struct_message;

typedef struct
{
    bool robot_state;
    int robot_x;
    int robot_y;
    bool weapon_state;
    int weapon_speed;
    dir_t robot_direction;
}state;

extern struct_message transmit_msg;

class RemoteControl
{
    private:
        struct_message msg;
        state total_state;
        int ma_indices[2] = {0, 0};
        int ma_sums[2] = {0, 0};
        int ma_readings[2][WINDOW_SIZE];
        uint16_t calibrate_data[4] = {0, 0, 0, 0};
    public:
        RemoteControl(struct_message objMsg, state objState);
        void init() const;
        struct_message getMessage() const;
        void update_data();
        void update_message();
        void print_values() const;
        int filter_meas(int coordinate, int measurement);
        dir_t direction(int x_coord, int y_coord);
        void calibrate_joystick();
};

void OnDataSent(const uint8_t* mac, esp_now_send_status_t status);
void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len);
const char* direction_to_string(dir_t joystick_dir);
#endif /*TRANSMITTER_H*/