#include "SmokeSensor.h"
#include <Arduino.h>

const Event SmokeSensor::SMOKE_DETECTED_EVENT = Event(SMOKE_DETECTED_EVENT_ID);

SmokeSensor::SmokeSensor(int digitalPin, int analogPin, EventHandler* eventHandler)
    : Sensor(digitalPin, eventHandler), digitalPin(digitalPin), analogPin(analogPin) {
    pinMode(digitalPin, INPUT);
    pinMode(analogPin, INPUT);
}

int SmokeSensor::readValue() {
    return analogRead(analogPin);
}


//Esto no se usa
void SmokeSensor::check() {
    if (digitalRead(digitalPin) == HIGH) {
        //on(SMOKE_DETECTED_EVENT); // Propaga el evento
    }
}