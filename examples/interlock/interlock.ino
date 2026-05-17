/*
 * Frugal IoT example - Control_Interlock
 *
 * Turns on a pump only if flow confirms within 5 seconds.
 */

#include "Frugal-IoT.h"

System_Frugal frugal_iot("dev", "developers", "interlock", "Pump Interlock Demo");

void setup() {
  frugal_iot.pre_setup();
  frugal_iot.configure_mqtt("frugaliot.naturalinnovation.org", "dev", "public");
  frugal_iot.configure_power(Power_Loop, 10000, 10000);

  // Flow sensor
  Sensor_Flow* flow = new Sensor_Flow("flow", "Flow", 4, 450.0, 0.5, "blue", true);
  frugal_iot.sensors->add(flow);

  // Pump relay on GPIO15
  Actuator_Digital* pump = new Actuator_Digital("pump", "Pump", 15, "blue");
  frugal_iot.actuators->add(pump);

  // Interlock: command -> out -> pump; feedback from flow
  Control_Interlock* interlock = new Control_Interlock("interlock", "Interlock");
  frugal_iot.controls->add(interlock);

  // Wire interlock output to pump
  interlock->outputs[0]->wireTo(frugal_iot.messages->path("pump/on"));
  // Wire flow feedback to interlock
  interlock->inputs[1]->wireTo(frugal_iot.messages->path("flow/output"));

  frugal_iot.setup();
  Serial.println(F("FrugalIoT Interlock Starting Loop"));
}

void loop() {
  frugal_iot.loop();
}
