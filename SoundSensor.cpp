#include "SoundSensor.h"
#include <Arduino.h>

const Event SoundSensor::SOUND_DETECTED_EVENT = Event(SOUND_DETECTED_EVENT_ID);

SoundSensor::SoundSensor(int digitalPin, EventHandler* eventHandler)
    : Sensor(digitalPin, eventHandler) {
    pinMode(digitalPin, INPUT);
}

//Esto no se usa
void SoundSensor::check() {
    if (digitalRead(digitalPin) == HIGH) {
        //on(SMOKE_DETECTED_EVENT); // Propaga el evento
    }
}