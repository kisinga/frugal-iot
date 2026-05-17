/* Frugal IoT - Control_EMA - Exponential Moving Average filter */

#include "_settings.h"
#include "control_ema.h"
#include "Frugal-IoT.h"

Control_EMA::Control_EMA(const char* const id, const char * const name, float initialValue, uint8_t width, float min, float max)
  : Control(id, name,
    std::vector<IN*> {
      new INfloat(id, "raw", "Raw", initialValue, width, min, max, "black", true),
      new INfloat(id, "alpha", "Alpha", 0.3, 2, 0.0, 1.0, "black", false)
    },
    std::vector<OUT*> {
      new OUTfloat(id, "smoothed", "Smoothed", initialValue, width, min, max, "black", true)
    }
  ) {
}

void Control_EMA::act() {
  const float raw = inputs[0]->floatValue();
  const float alpha = inputs[1]->floatValue();
  float smoothed = outputs[0]->floatValue();
  smoothed = alpha * raw + (1.0f - alpha) * smoothed;
  ((OUTfloat*)outputs[0])->set(smoothed);
}
