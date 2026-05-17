/* Frugal IoT - Sensor_Flow - pulse-counter flow sensor */

#include "_settings.h"
#include "sensor_flow.h"
#include "Frugal-IoT.h"

Sensor_Flow* Sensor_Flow::instance = nullptr;

Sensor_Flow::Sensor_Flow(const char* const id, const char * const name, uint8_t pin, float pulsesPerLiter, float faultThreshold, const char* color, bool retain)
  : Sensor_Float(id, name, 2, 0.0, 1000.0, color, retain),
    pulseCount(0), lastPulseCount(0), lastReadMs(0),
    pin(pin), pulsesPerLiter(pulsesPerLiter), faultThreshold(faultThreshold) {
}

void Sensor_Flow::setup() {
  Sensor_Float::setup();
  pinMode(pin, INPUT_PULLUP);
  instance = this;
  attachInterrupt(digitalPinToInterrupt(pin), onPulse, RISING);
}

void Sensor_Flow::onPulse() {
  if (instance) {
    instance->pulseCount++;
  }
}

float Sensor_Flow::readFloat() {
  noInterrupts();
  uint32_t currentCount = pulseCount;
  interrupts();

  uint32_t now = millis();
  uint32_t deltaCount = currentCount - lastPulseCount;
  uint32_t deltaMs = now - lastReadMs;

  float lpm = 0.0f;
  if (deltaMs > 0 && pulsesPerLiter > 0.0f) {
    lpm = (deltaCount * 60000.0f) / (pulsesPerLiter * deltaMs);
  }

  lastPulseCount = currentCount;
  lastReadMs = now;
  return lpm;
}
