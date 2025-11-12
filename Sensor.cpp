/**
* @file Sensor.cpp
 * @brief Implements the Sensor base class.
 *
 * Provides core functionality for sensors in the Modest IoT Nano-framework, including event
 * propagation to an assigned handler. Subclasses should configure hardware and define specific
 * event generation logic.
 *
 */

#include "Sensor.h"

Sensor::Sensor(int pin, EventHandler* eventHandler)
    : pin(pin), handler(eventHandler) {}

void Sensor::on(Event event) {
    if (handler != nullptr) {
        handler->on(event);
    }
}

void Sensor::setHandler(EventHandler* eventHandler) {
    handler = eventHandler;
}
