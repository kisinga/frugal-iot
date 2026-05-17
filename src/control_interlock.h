#ifndef CONTROL_INTERLOCK_H
#define CONTROL_INTERLOCK_H

#include "control.h"

/* Generic command-confirmation interlock.
 * Passes command through only if feedback confirms within timeout.
 * Threshold = 0.5 works for bool feedback; higher values for analog.
 */
class Control_Interlock : public Control {
  public:
    Control_Interlock(const char* const id, const char * const name);
    void act() override;
  protected:
    uint32_t confirmStartMs = 0;
};

#endif // CONTROL_INTERLOCK_H
