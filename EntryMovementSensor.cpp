#include "EntryMovementSensor.h"
#include <Arduino.h>

const Event EntryMovementSensor::INNER_MOVEMENT_DETECTED_EVENT = Event(INNER_MOVEMENT_DETECTED_EVENT_ID);
const Event EntryMovementSensor::OUTER_MOVEMENT_DETECTED_EVENT = Event(OUTER_MOVEMENT_DETECTED_EVENT_ID);

EntryMovementSensor::EntryMovementSensor(int pin, EventHandler* eventHandler)
    : Sensor(pin, eventHandler) {
    pinMode(pin, INPUT_PULLUP);
}