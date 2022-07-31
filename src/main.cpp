#include <Arduino.h>

#include "Remote.h"
#include "Encoder.h"
#include "MotorController.h"
#include "Battery.h"

void setup() {
  Serial.begin(115200);

  battery_init();
  encoder_init();
  motor_controller_init();
  remote_init();
}

void loop() {
  remote_update();
  
  motor_controller_set_throttle(remote_get_throttle());
  motor_controller_update();

  remote_set_speed(encoder_get_speed_mph());
  remote_set_battery(battery_get_charge());
}