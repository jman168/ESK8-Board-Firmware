#include <Arduino.h>

#include "Remote.h"
#include "Encoder.h"
#include "MotorController.h"
#include "Battery.h"

Remote *remote;

void setup() {
  Serial.begin(115200);

  battery_init();
  encoder_init();
  motor_controller_init();

  remote = new Remote();
}

void loop() {
  remote->handle();
  
  motor_controller_set_throttle(remote->getThrottle());
  motor_controller_update();

  Serial.println(remote->isConnected());

  remote->setSpeed(encoder_get_speed_mph());
  remote->setBattery(battery_get_charge());
}