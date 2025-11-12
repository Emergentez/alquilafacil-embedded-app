#ifndef DEVICE_H
#define DEVICE_H

/**
 * @file Device.h
 * @brief Declares the Device interface.
 *
 * This abstract base class in the Modest IoT Nano-framework combines event and command handling,
 * serving as the foundation for complete IoT devices that integrate sensors and actuators.
 *

 */



#include "EventHandler.h"
#include "CommandHandler.h"

class Device : public EventHandler, public CommandHandler {
public:
    /**
     * @brief Handles an event received by the device.
     * @param event The event to process.
     */
    virtual void on(Event event) override = 0;

    /**
     * @brief Handles a command issued to the device.
     * @param command The command to execute.
     */
    virtual void handle(Command command) override = 0;

    virtual ~Device() = default; ///< Virtual destructor for safe inheritance.
};

#endif // DEVICE_H
