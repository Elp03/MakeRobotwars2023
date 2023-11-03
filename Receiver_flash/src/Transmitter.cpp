#include "Transmitter.hpp"

RemoteControl::RemoteControl(struct_message objMsg, state objState): msg{objMsg}, total_state{objState} {};

void RemoteControl::init() const
{
    pinMode(ROBOT_STATE_PIN, INPUT);
    pinMode(ROBOT_X_PIN, INPUT);
    pinMode(ROBOT_Y_PIN, INPUT);
    pinMode(WEAPON_STATE_PIN, INPUT);
    pinMode(WEAPON_SPEED_PIN, INPUT);
    adc1_config_width(ADC_WIDTH_10Bit);
}

struct_message RemoteControl::getMessage() const
{
    return this->msg;
}

void RemoteControl::update_data()
{
    uint16_t x_min = calibrate_data[0];
    uint16_t x_max = calibrate_data[1];
    uint16_t y_min = calibrate_data[2];
    uint16_t y_max = calibrate_data[3];
    total_state.robot_state = digitalRead(ROBOT_STATE_PIN);
    uint16_t x_measurement = analogRead(ROBOT_X_PIN);
    uint16_t y_measurement = analogRead(ROBOT_Y_PIN);
    if(x_measurement < x_min)
    {
        x_measurement = x_min;
    }
    if(x_measurement > x_max)
    {
        x_measurement = x_max;
    }
    if(y_measurement < y_min)
    {
        y_measurement = y_min;
    }
    if(y_measurement > y_max)
    {
        y_measurement = y_max;
    }
    int32_t x_calibed = (int32_t)(((x_measurement - x_min)*(100.0 - (-100.0)))/(x_max - x_min)) - 100.0;
    int32_t y_calibed = (int32_t)(((y_measurement - y_min)*(100.0 - (-100.0)))/(y_max - y_min)) - 100.0;
    total_state.robot_x = filter_meas(X, x_calibed);
    total_state.robot_y = filter_meas(Y, y_calibed);
    total_state.weapon_state = digitalRead(WEAPON_STATE_PIN);
    total_state.weapon_speed = analogRead(WEAPON_SPEED_PIN);
    total_state.robot_direction = direction(total_state.robot_x, total_state.robot_y);
}

void RemoteControl::update_message()
{
    msg.message_robot_state = total_state.robot_state;
    msg.message_robot_x_axis = total_state.robot_x;
    msg.message_robot_y_axis = total_state.robot_y;
    msg.message_weapon_state = total_state.weapon_state;
    msg.message_weapon_speed = total_state.weapon_speed;
    msg.message_robot_direction = total_state.robot_direction;
}

void RemoteControl::print_values() const
{
    Serial.print("Robot state: ");
    Serial.println(total_state.robot_state);
    Serial.print("Robot x: ");
    Serial.println(total_state.robot_x);
    Serial.print("Robot y: ");
    Serial.println(total_state.robot_y);
    Serial.print("Weapon state: ");
    Serial.println(total_state.weapon_state);
    Serial.print("Weapon speed: ");
    Serial.println(total_state.weapon_speed);
    Serial.print("Joystick direction: ");
    Serial.println(direction_to_string(total_state.robot_direction));
}

int RemoteControl::filter_meas(int coord, int measurement)
{
    ma_sums[coord] = ma_sums[coord] - ma_readings[coord][ma_indices[coord]];
    ma_readings[coord][ma_indices[coord]] = measurement;
    ma_sums[coord] = ma_sums[coord] + measurement;
    ma_indices[coord] = (ma_indices[coord] + 1) % WINDOW_SIZE;

    return ma_sums[coord]/WINDOW_SIZE;
}

dir_t RemoteControl::direction(int x_coord, int y_coord)
{
    if(abs(x_coord) >= abs(y_coord))
    {
        if(abs(x_coord) < DEADZONE)
        {
            return NEUTRAL;
        }
        else
        {
            if(x_coord < 0)
            {
                return LEFT;
            }
            else
            {
                return RIGHT;
            }
        }
    }
    else
    {
        if(abs(y_coord) < DEADZONE)
        {
            return NEUTRAL;
        }
        else
        {
            if(y_coord < 0)
            {
                return FORWARD;
            }
            else
            {
                return BACKWARD;
            }
        }
    }
}

void RemoteControl::calibrate_joystick()
{
    // CALIBRATION CODE HERE!!!
    unsigned int x_mid = analogRead(ROBOT_X_PIN);
    unsigned int y_mid = analogRead(ROBOT_Y_PIN);
    unsigned int x_min = x_mid;
    unsigned int x_max = x_mid;
    unsigned int y_min = y_mid;
    unsigned int y_max = y_mid;
    Serial.print("JOYSTICK CALIBRATION!");
    Serial.print("Rotate the joystick around...");
    unsigned long start_time = millis();
    while((millis() - start_time) < CALIBRATION_TIME_MS)
    {
        unsigned int x_meas = analogRead(ROBOT_X_PIN);
        unsigned int y_meas = analogRead(ROBOT_Y_PIN);
        if(x_meas < x_min)
        {
            x_min = x_meas;
            calibrate_data[0] = x_min;
        }
        if(x_meas > x_max)
        {
            x_max = x_meas;
            calibrate_data[1] = x_max;
        }
        if(y_meas < y_min)
        {
            y_min = y_meas;
            calibrate_data[2] = y_min;
        }
        if(y_meas > y_max)
        {
            y_max = y_meas;
            calibrate_data[3] = y_max;
        }
    }
    if((x_max - x_min) != x_mid)
    {
        if((x_max - x_mid) < (x_mid - x_min))
        {
            x_min = 2*x_mid - x_max;
            calibrate_data[0] = x_min;
        }
        else
        {
            x_max = 2*x_mid - x_min;
            calibrate_data[1] = x_max;
        }
    }
    if((y_max - y_min) != y_mid)
    {
        if((y_max - y_mid) < (y_mid - y_min))
        {
            y_min = 2*y_mid - y_max;
            calibrate_data[2] = y_min;
        }
        else
        {
            y_max = 2*y_mid - y_min;
            calibrate_data[3] = y_max;
        }
    }
}

void OnDataSent(const uint8_t* mac, esp_now_send_status_t status)
{
    Serial.print("\r\nLast Packet Send Status:\t");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void OnDataRecv(const uint8_t* mac, const uint8_t* incomingData, int len)
{
    memcpy(&transmit_msg, incomingData, sizeof(transmit_msg));
    Serial.print("Bytes received: ");
    Serial.println(len);
}

const char* direction_to_string(dir_t joystick_dir)
{
    switch(joystick_dir)
    {
        case NEUTRAL:
        {
            return "NEUTRAL";
        }
        case FORWARD:
        {
            return "FORWARD";
        }
        case BACKWARD:
        {
            return "BACKWARD";
        }
        case RIGHT:
        {
            return "RIGHT";
        }
        case LEFT:
        {
            return "LEFT";
        }
        default:
        {
            return "NEUTRAL";
        }
    }
}