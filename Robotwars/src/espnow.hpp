



class espnow
{
private:
    /* data */
public:
    espnow(/* args */);
    ~espnow();
    String success;
    esp_now_peer_info_t peerInfo;
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status)
};

espnow::espnow(/* args */)
{
}

espnow::~espnow()
{
}
