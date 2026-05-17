/*
 * Frugal IoT example - Actuator_Valve latching valve
 *
 * Open/close coils on GPIO12 and GPIO14.
 */

#include "Frugal-IoT.h"

System_Frugal frugal_iot("dev", "developers", "valve", "Latching Valve Demo");

void setup() {
  frugal_iot.pre_setup();
  frugal_iot.configure_mqtt("frugaliot.naturalinnovation.org", "dev", "public");
  frugal_iot.configure_power(Power_Loop, 10000, 10000);

  // Valve: open coil on 12, close coil on 14
  frugal_iot.actuators->add(new Actuator_Valve("valve", "Valve", 12, 14, "blue"));

  frugal_iot.setup();
  Serial.println(F("FrugalIoT Valve Starting Loop"));
}

void loop() {
  frugal_iot.loop();
}
