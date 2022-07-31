#include <Arduino.h>

#include "Remote.h"
#include "Encoder.h"
#include "MotorController.h"
#include "Battery.h"

Remote *remote;
MotorController *motorController;

void setup() {
  Serial.begin(115200);

  remote = new Remote();
  motorController = new MotorController();
}

void loop() {
  remote->handle();
  
  motorController->setThrottle(remote->getThrottle());
  motorController->update();

  Serial.println(remote->isConnected());

  remote->setSpeed(encoder_get_speed_mph());
  remote->setBattery(battery_get_charge());
}