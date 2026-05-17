#ifndef CONTROL_EMA_H
#define CONTROL_EMA_H

#include "control.h"

/* Exponential Moving Average filter.
 * Sits between sensor and actuator for float values.
 * Acknowledges Sensor_Uint16::smooth; this is float-capable and configurable.
 */
class Control_EMA : public Control {
  public:
    Control_EMA(const char* const id, const char * const name, float initialValue, uint8_t width, float min, float max);
    void act() override;
};

#endif // CONTROL_EMA_H
