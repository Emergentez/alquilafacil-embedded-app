#ifndef SENSOR_H
#define SENSOR_H

/**
 * @file Sensor.h
 * @brief Declares the Sensor base class.
 * 
 * This abstract base class represents input devices in the Modest IoT Nano-framework, providing
 * a foundation for sensors that generate events. It includes event propagation to an optional
 * handler, supporting the framework’s event-driven design.

 */


#include "EventHandler.h"

class Sensor : public EventHandler {
protected:
    int pin; ///< GPIO pin assigned to the sensor.
    EventHandler* handler; ///< Optional handler to receive propagated events.

public:
    /**
     * @brief Constructs a Sensor with a pin and optional event handler.
     * @param pin The GPIO pin for the sensor.
     * @param eventHandler Pointer to an EventHandler to receive events (default: nullptr).
     */
    Sensor(int pin, EventHandler* eventHandler = nullptr);

    /**
     * @brief Handles an event by propagating it to the assigned handler.
     * @param event The event to handle.
     */
    void on(Event event) override;

    /**
     * @brief Sets or updates the event handler for this sensor.
     * @param eventHandler Pointer to the new EventHandler.
     */
    void setHandler(EventHandler* eventHandler);
};

#endif // SENSOR_H