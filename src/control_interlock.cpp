/* Frugal IoT - Control_Interlock - command confirmation guard */

#include "_settings.h"
#include "control_interlock.h"
#include "Frugal-IoT.h"

Control_Interlock::Control_Interlock(const char* const id, const char * const name)
  : Control(id, name,
    std::vector<IN*> {
      new INbool(id, "command", "Command", false, "black", true),
      new INfloat(id, "feedback", "Feedback", 0.0, 2, 0.0, 1000.0, "black", true),
      new INfloat(id, "threshold", "Threshold", 0.5, 2, 0.0, 1000.0, "black", false),
      new INuint16(id, "confirmMs", "Confirm Ms", 5000, 0, 60000, "black", false)
    },
    std::vector<OUT*> {
      new OUTbool(id, "out", "Out", false, "black", true),
      new OUTbool(id, "fault", "Fault", false, "red", true)
    }
  ) {
}

void Control_Interlock::act() {
  bool command = inputs[0]->boolValue();
  float feedback = inputs[1]->floatValue();
  float threshold = inputs[2]->floatValue();
  uint16_t confirmMs = ((INuint16*)inputs[3])->value;

  if (!command) {
    confirmStartMs = 0;
    ((OUTbool*)outputs[0])->set(false);
    ((OUTbool*)outputs[1])->set(false);
    return;
  }

  bool fault = outputs[1]->boolValue();
  if (!fault) {
    if (confirmStartMs == 0) {
      confirmStartMs = millis();
    }
    if ((millis() - confirmStartMs) > confirmMs && feedback < threshold) {
      fault = true;
      ((OUTbool*)outputs[1])->set(true);
    }
  }

  ((OUTbool*)outputs[0])->set(command && !fault);
}
