#include <Arduino.h>

#include "Remote.h"
#include "FRCCan.h"
#include "SparkMax.h"
#include "MotorController.h"

#define MIN_BATTERY_VOLTAGE 18.0
#define MAX_BATTERY_VOLTAGE 24.8

#define RPM_TO_MPH_FACTOR 0.002755899

SparkMax *spark;

float getCharge();

void setup() {
  Serial.begin(115200);

  FRCCan.begin(D8, D6, 8e6);

  spark = new SparkMax(1);

  remote_init();
  motor_controller_init(spark);
}

void loop() {  
  FRCCan.handle();
  remote_update();
  
  motor_controller_set_throttle(remote_get_throttle());

  if(remote_is_connected()) {
    FRCCan.enable();
  }    
  else {
    FRCCan.disable();
  }

  remote_set_speed(spark->getVelocity() * RPM_TO_MPH_FACTOR);
  remote_set_battery(getCharge());

  motor_controller_update();
}

float getCharge() {
  float voltage = spark->getInputVoltage();
  return (voltage-MIN_BATTERY_VOLTAGE)/(MAX_BATTERY_VOLTAGE-MIN_BATTERY_VOLTAGE);
}