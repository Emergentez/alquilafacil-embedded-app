#include "RestrictedAreaMovementSensor.h"
#include <Arduino.h>

const Event RestrictedAreaMovementSensor::RESTRICTED_AREA_ACCESS_DETECTED_EVENT = Event(RESTRICTED_AREA_ACCESS_DETECTED_EVENT_ID);

RestrictedAreaMovementSensor::RestrictedAreaMovementSensor(int pin, EventHandler* eventHandler)
    : Sensor(pin, eventHandler) {
    pinMode(pin, INPUT_PULLUP);
}