#ifndef ACTUATOR_VALVE_H
#define ACTUATOR_VALVE_H

#include "actuator.h"

/* Latching valve actuator with open/close coils.
 * Position control is open-loop estimate based on travelTimeMs.
 */
class Actuator_Valve : public Actuator {
  public:
    Actuator_Valve(const char * const id, const char * const name, uint8_t openPin, uint8_t closePin, const char* color);
    void setup() override;
    void loop() override;
    void act() override;
    void dispatchTwig(const String &topicActuatorId, const String &topicLeaf, const String &payload, bool isSet) override;
  protected:
    uint8_t openPin;
    uint8_t closePin;
    INuint16* position;
    uint16_t travelTimeMs = 1000;
    enum State { UNKNOWN, OPENING, CLOSING, EST_OPEN, EST_CLOSED };
    State state = UNKNOWN;
    uint32_t coilDeadline = 0;
    bool coilActive = false;
    void stop();
    void openCoil();
    void closeCoil();
};

#endif // ACTUATOR_VALVE_H
