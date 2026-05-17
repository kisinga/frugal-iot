#ifndef SENSOR_FLOW_H
#define SENSOR_FLOW_H

#include "sensor_float.h"

/* Pulse-counter flow sensor.
 * Measures L/min from pulse frequency.
 * One instance per device (ISR uses static singleton).
 */
class Sensor_Flow : public Sensor_Float {
  public:
    Sensor_Flow(const char* const id, const char * const name, uint8_t pin, float pulsesPerLiter, float faultThreshold, const char* color, bool retain);
    void setup() override;
  protected:
    float readFloat() override;
    static void onPulse();
    static Sensor_Flow* instance;
    volatile uint32_t pulseCount;
    uint32_t lastPulseCount;
    uint32_t lastReadMs;
    uint8_t pin;
    float pulsesPerLiter;
    float faultThreshold;
};

#endif // SENSOR_FLOW_H
