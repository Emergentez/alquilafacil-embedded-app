/**
* @file Actuator.cpp
 * @brief Implements the Actuator base class.
 *
 * Provides core functionality for actuators in the Modest IoT Nano-framework, including command
 * propagation to an assigned handler. Subclasses should configure hardware and define specific
 * command execution logic.
 *
 */


#include "Actuator.h"

Actuator::Actuator(int pin, CommandHandler* commandHandler)
    : pin(pin), handler(commandHandler) {}

void Actuator::handle(Command command) {
    if (handler != nullptr) {
        handler->handle(command);
    }
}

void Actuator::setHandler(CommandHandler* commandHandler) {
    handler = commandHandler;
}
