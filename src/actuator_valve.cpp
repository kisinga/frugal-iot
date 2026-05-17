/* Frugal IoT - Actuator_Valve - latching valve with two coils */

#include "_settings.h"
#include "actuator_valve.h"
#include "Frugal-IoT.h"

Actuator_Valve::Actuator_Valve(const char * const id, const char * const name, uint8_t openPin, uint8_t closePin, const char* color)
  : Actuator(id, name),
    openPin(openPin), closePin(closePin),
    position(new INuint16(id, "position", "Position", 0, 0, 100, color, false))
{
  inputs.push_back(position);
}

void Actuator_Valve::setup() {
  Actuator::setup();
  pinMode(openPin, OUTPUT);
  pinMode(closePin, OUTPUT);
  digitalWrite(openPin, LOW);
  digitalWrite(closePin, LOW);
}

void Actuator_Valve::stop() {
  digitalWrite(openPin, LOW);
  digitalWrite(closePin, LOW);
  coilActive = false;
  coilDeadline = 0;
  if (state == OPENING) state = EST_OPEN;
  if (state == CLOSING) state = EST_CLOSED;
}

void Actuator_Valve::openCoil() {
  digitalWrite(closePin, LOW);
  digitalWrite(openPin, HIGH);
  coilActive = true;
  state = OPENING;
}

void Actuator_Valve::closeCoil() {
  digitalWrite(openPin, LOW);
  digitalWrite(closePin, HIGH);
  coilActive = true;
  state = CLOSING;
}

void Actuator_Valve::act() {
  uint16_t target = position->value;
  if (target >= 50 && state != EST_OPEN && state != OPENING) {
    openCoil();
    coilDeadline = millis() + travelTimeMs;
  } else if (target < 50 && state != EST_CLOSED && state != CLOSING) {
    closeCoil();
    coilDeadline = millis() + travelTimeMs;
  }
}

void Actuator_Valve::dispatchTwig(const String &topicActuatorId, const String &topicLeaf, const String &payload, bool isSet) {
  if (isSet && topicActuatorId == id && topicLeaf == "travelTimeMs") {
    travelTimeMs = payload.toInt();
    writeConfigToFSandEcho(topicLeaf, payload);
    return;
  }
  Actuator::dispatchTwig(topicActuatorId, topicLeaf, payload, isSet);
}

void Actuator_Valve::loop() {
  if (coilActive && millis() >= coilDeadline) {
    stop();
  }
}
