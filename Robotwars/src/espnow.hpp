#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>

class espnow
{
private:
    /* data */
public:
    espnow();
    ~espnow();
    String success;
    esp_now_peer_info_t peerInfo;
    
    void init(uint8_t* reciver_addr);
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);
    
};

espnow::espnow(/* args */)
{
}

espnow::~espnow()
{
}
