#include <Arduino.h>

#include "Remote.h"
#include "Encoder.h"

Remote *remote;
Encoder *encoder;

void setup() {
  Serial.begin(115200);

  remote = new Remote();
  encoder = new Encoder();
}

void loop() {
  remote->handle();
  Serial.println(remote->getThrottle());
  remote->setSpeed(encoder->getSpeedMPH());
  remote->setBattery((remote->getThrottle() + 1.0)*0.5);
}