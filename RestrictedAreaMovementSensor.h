#ifndef RESTRICTED_AREA_MOVEMENT_SENSOR_H
#define RESTRICTED_AREA_MOVEMENT_SENSOR_H

#include "Sensor.h"

class RestrictedAreaMovementSensor : public Sensor {
public:
    static const int RESTRICTED_AREA_ACCESS_DETECTED_EVENT_ID = 2; ///< Unique ID for button press event.
    static const Event RESTRICTED_AREA_ACCESS_DETECTED_EVENT; ///< Predefined event for button presses.
    
    RestrictedAreaMovementSensor(int pin, EventHandler* eventHandler = nullptr);
};

#endif