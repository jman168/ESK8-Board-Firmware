#include <Arduino.h>

#include "Remote.h"
#include "Encoder.h"
#include "MotorController.h"
#include "Battery.h"

Remote *remote;
Encoder *encoder;
MotorController *motorController;
Battery *battery;

void setup() {
  Serial.begin(115200);

  remote = new Remote();
  encoder = new Encoder();
  battery = new Battery();
  motorController = new MotorController(encoder);
}

void loop() {
  remote->handle();
  
  motorController->setThrottle(remote->getThrottle());
  motorController->update();
  Serial.println(battery->getVoltage());
  
  remote->setSpeed(encoder->getSpeedMPH());
  remote->setBattery(battery->getCharge());
}