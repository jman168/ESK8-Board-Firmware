#include <Arduino.h>

#include "Remote.h"

Remote *remote;

void setup() {
  Serial.begin(115200);

  remote = new Remote();
}

void loop() {
  remote->handle();
  Serial.println(remote->getThrottle());
  remote->setSpeed((remote->getThrottle() + 1.0)*15.0);
  remote->setBattery((remote->getThrottle() + 1.0)*0.5);
}