#ifndef TOGGABLE_LED_DEVICE_H
#define TOGGABLE_LED_DEVICE_H

/**
 * @file ToggableLedDevice.h
 * @brief Declares the ToggableLedDevice class.
 * 
 * An example implementation of the Modest IoT Nano-framework (C++ Edition), demonstrating a device
 * that toggles an LED based on button presses. Depends on the framework from
 * https://github.com/avelasquezn/Modest-IoT-Nano-framework-Cpp.
 * 
 * @author Angel Velasquez
 * @date March 22, 2025
 * @version 0.1
 */

/*
 * This file is part of the ToggableLedDevice-Example-Cpp project.
 * Copyright (c) 2025 Angel Velasquez
 *
 * Licensed under the Creative Commons Attribution-NoDerivatives 4.0 International (CC BY-ND 4.0).
 * You may use, copy, and distribute this software in its original, unmodified form, provided
 * you give appropriate credit to the original author (Angel Velasquez) and include this notice.
 * Modifications, adaptations, or derivative works are not permitted.
 * 
 * Full license text: https://creativecommons.org/licenses/by-nd/4.0/legalcode
 */

#include "Device.h"
#include "EntryMovementSensor.h"
#include "RestrictedAreaMovementSensor.h"
#include "SmokeSensor.h"
#include "SoundSensor.h"

#include <WiFi.h>
#include <HTTPClient.h>

class MonitoringLocalDevice : public Device {
private:
    SmokeSensor smokeSensor; ///< Button sensor instance from the framework.
    RestrictedAreaMovementSensor restrictedAreaMovementSensor;
    EntryMovementSensor innerMovementSensor;
    EntryMovementSensor outerMovementSensor;
    SoundSensor soundSensor;

    Event pendingEvent;
    bool hasPendingEvent = false;

public:
    static const int RESTRICTED_AREA_PIN = 15; ///< Default GPIO pin for the button.
    static const int SMOKE_ANALOG_PIN = 35; ///< Default GPIO pin for the LED.
    static const int SMOKE_DIGITAL_PIN = 32;

    static const int INNER_MOVEMENT_SENSOR_PIN = 25;
    static const int OUTER_MOVEMENT_SENSOR_PIN = 26;
    
    static const int SOUND_SENSOR_PIN = 21;


    static const unsigned long MOVEMENT_TIMEOUT_MS = 5000; // Tiempo máximo entre sensores

    MonitoringLocalDevice(int restrictedAreaPin = RESTRICTED_AREA_PIN, int smokeAnalogPin = SMOKE_ANALOG_PIN, int smokeDigitalPin = SMOKE_DIGITAL_PIN, int innerMovementPin = INNER_MOVEMENT_SENSOR_PIN, int outerMovementPin = OUTER_MOVEMENT_SENSOR_PIN,int soundPin = SOUND_SENSOR_PIN); ///< Constructor with configurable pins and initial LED state.
    
    //Variables que guardan la ultima activación de los sensores de movimiento de la entrada
    unsigned long lastInnerSensorTriggerTime = 0;
    unsigned long lastOuterSensorTriggerTime = 0;

    void on(Event event) override; ///< Handles button press events.
    void handle(Command command) override; ///< Handles LED command responses (e.g., state reporting).
    void check();

    void triggerRestrictedAreaEvent(Event event);
    void triggerSmokeSensorEvent(Event event);
    void triggerInnerMovementSensorEvent(Event event);
    void triggerOuterMovementSensorEvent(Event event);
    void triggerSoundSensorEvent(Event event);

    //void triggerButtonEvent(Event event); ///< Triggers a button event externally (e.g., from ISR).
    void sendEventToServer(const char* sensorType, String message, const char* endpointUrl);


};

#endif // TOGGABLE_LED_DEVICE_H