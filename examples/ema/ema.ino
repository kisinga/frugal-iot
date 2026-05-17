/*
 * Frugal IoT example - Control_EMA filter
 *
 * Smooths noisy sensor data with an exponential moving average.
 */

#include "Frugal-IoT.h"

System_Frugal frugal_iot("dev", "developers", "ema", "EMA Filter Demo");

void setup() {
  frugal_iot.pre_setup();
  frugal_iot.configure_mqtt("frugaliot.naturalinnovation.org", "dev", "public");
  frugal_iot.configure_power(Power_Loop, 10000, 10000);

  // Add a sensor (e.g., analog)
  Sensor_Analog* sensor = new Sensor_Analog("analog", "Analog", A0, "blue", true);
  frugal_iot.sensors->add(sensor);

  // Add EMA filter
  Control_EMA* ema = new Control_EMA("ema", "EMA", 0.0, 2, 0.0, 1023.0);
  frugal_iot.controls->add(ema);

  // Wire sensor -> EMA
  ema->inputs[0]->wireTo(frugal_iot.messages->path("analog/output"));

  frugal_iot.setup();
  Serial.println(F("FrugalIoT EMA Starting Loop"));
}

void loop() {
  frugal_iot.loop();
}
