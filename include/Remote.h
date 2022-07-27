#pragma once

#include <SPI.h>
#include "RF24.h"

struct AKCPacket {
    float speed;
    float battery;
};

struct ControlPacket {
    float throttle;
};

class Remote {
    public:
        Remote();

        void handle();

        float getThrottle();
        void setBattery(float battery);
        void setSpeed(float speed);
        bool isConnected();

    private:
        RF24 *_radio;

        float _throttle;
        float _battery = 0.0;
        float _speed = 0.0;
        unsigned long lastPacket = 0;

        const char _boardAddr[6] = "BESK8"; // board address
        const char _remoteAddr[6] = "RESK8"; // remote address

    private:
        void writeAckPacket();
};