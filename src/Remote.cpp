#include "Remote.h"

unsigned char REMOTE_ADDRESS[] = {0xBC, 0xDD, 0xC2, 0x2D, 0x1D, 0xBD};

struct remote_status_packet_t {
    float speed;
    float battery;
};

struct remote_control_packet_t {
    float throttle;
};


float remote_throttle;
float remote_battery = 0.0;
float remote_speed = 0.0;
unsigned long remote_last_packet = 0;
unsigned long remote_last_transmit = 0;

remote_status_packet_t remote_tx_packet;
remote_control_packet_t remote_rx_packet;

void remote_on_data(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
    remote_last_packet = millis();
    memcpy(&remote_rx_packet, incomingData, sizeof(remote_rx_packet));
    remote_throttle = remote_rx_packet.throttle;
}

void remote_init() {
    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        while(true) {};
    }

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_add_peer(REMOTE_ADDRESS, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
    esp_now_register_recv_cb(remote_on_data);
}

void remote_update() {
    unsigned long time = millis();

    if(time-remote_last_transmit >= 20) {
        remote_tx_packet.speed = remote_speed;
        remote_tx_packet.battery = remote_battery;
        esp_now_send(REMOTE_ADDRESS, (uint8_t *)&remote_tx_packet, sizeof(remote_tx_packet));
        remote_last_transmit = time;
    }
}

float remote_get_throttle() {
    return remote_throttle;
}

void remote_set_battery(float battery) {
    remote_battery = battery;
}

void remote_set_speed(float speed) {
    remote_speed = speed;
}

bool remote_is_connected() {
    return !((millis() - remote_last_packet) >= 100);
}