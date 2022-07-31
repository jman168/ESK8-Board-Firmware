#include "Remote.h"

struct remote_ack_packet_t {
    float speed;
    float battery;
};

struct remote_controller_packet_t {
    float throttle;
};

RF24 *remote_radio;

float remote_throttle;
float remote_battery = 0.0;
float remote_speed = 0.0;
unsigned long remote_last_packet = 0;

const char remote_board_addr[6] = "BESK8"; // board address
const char remote_remote_addr[6] = "RESK8"; // remote address

void remote_write_ack_packet() {
    remote_ack_packet_t ack_packet;
    ack_packet.battery = remote_battery;
    ack_packet.speed = remote_speed;
    remote_radio->writeAckPayload(1, &ack_packet, sizeof(ack_packet));
}

void remote_init() {
    remote_radio = new RF24(22, 21);

    if(!remote_radio->begin()) {
        Serial.println("Radio hardware is not responding!!");
        while(true) {}
    }

    remote_radio->setPALevel(RF24_PA_HIGH);

    remote_radio->enableDynamicPayloads();

    remote_radio->enableAckPayload();

    remote_radio->openWritingPipe((const uint8_t*)&remote_remote_addr);
    remote_radio->openReadingPipe(1, (const uint8_t*)&remote_board_addr);

    remote_write_ack_packet();

    remote_radio->startListening();
}

void remote_update() {
    uint8_t pipe;
    if (remote_radio->available(&pipe)) {
        remote_last_packet = millis();
        remote_controller_packet_t packet;
        remote_radio->read(&packet, sizeof(packet));
        remote_throttle = packet.throttle;
        remote_write_ack_packet();
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