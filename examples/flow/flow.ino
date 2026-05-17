/*
 * Frugal IoT example - Sensor_Flow pulse counter
 *
 * Connect a flow meter to a digital pin with pull-up.
 */

#include "Frugal-IoT.h"

System_Frugal frugal_iot("dev", "developers", "flow", "Flow Meter Demo");

void setup() {
  frugal_iot.pre_setup();
  frugal_iot.configure_mqtt("frugaliot.naturalinnovation.org", "dev", "public");
  frugal_iot.configure_power(Power_Loop, 10000, 10000);

  // Flow sensor on GPIO4: 450 pulses/liter, fault below 0.5 L/min
  frugal_iot.sensors->add(new Sensor_Flow("flow", "Flow", 4, 450.0, 0.5, "blue", true));

  frugal_iot.setup();
  Serial.println(F("FrugalIoT Flow Starting Loop"));
}

void loop() {
  frugal_iot.loop();
}
