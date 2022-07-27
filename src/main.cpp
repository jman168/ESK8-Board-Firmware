#include <Arduino.h>

#include "Remote.h"
#include "Encoder.h"
#include "MotorController.h"

Remote *remote;
Encoder *encoder;
MotorController *motorController;

void setup() {
  Serial.begin(115200);

  remote = new Remote();
  encoder = new Encoder();
  motorController = new MotorController(encoder);
}

void loop() {
  remote->handle();
  
  motorController->setThrottle(remote->getThrottle());
  motorController->update();
  // Serial.println(remote->getThrottle());
  
  remote->setSpeed(encoder->getSpeedMPH());
  remote->setBattery((remote->getThrottle() + 1.0)*0.5);
}