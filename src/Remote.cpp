#include "Remote.h"

Remote::Remote() {
    _radio = new RF24(22, 21);

    if(!_radio->begin()) {
        Serial.println("Radio hardware is not responding!!");
    }

    _radio->setPALevel(RF24_PA_HIGH);

    _radio->enableDynamicPayloads();

    _radio->enableAckPayload();

    _radio->openWritingPipe((const uint8_t*)&_remoteAddr);
    _radio->openReadingPipe(1, (const uint8_t*)&_boardAddr);

    writeAckPacket();

    _radio->startListening();
}

void Remote::handle() {
    uint8_t pipe;
    if (_radio->available(&pipe)) {
        lastPacket = millis();
        ControlPacket packet;
        _radio->read(&packet, sizeof(packet));
        _throttle = packet.throttle;
        writeAckPacket();
    }
}

float Remote::getThrottle() {
    return _throttle;
}

void Remote::setBattery(float battery) {
    _battery = battery;
}

void Remote::setSpeed(float speed) {
    _speed = speed;
}

bool Remote::isConnected() {
    return !((millis() - lastPacket) >= 100);
}

void Remote::writeAckPacket() {
    AKCPacket ackPacket;
    ackPacket.battery = _battery;
    ackPacket.speed = _speed;
    _radio->writeAckPayload(1, &ackPacket, sizeof(ackPacket));
}