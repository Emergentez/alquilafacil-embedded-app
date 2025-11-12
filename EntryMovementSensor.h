#ifndef MOVEMENT_SENSOR_H
#define MOVEMENT_SENSOR_H

#include "Sensor.h"

class EntryMovementSensor : public Sensor {
public:
    static const int INNER_MOVEMENT_DETECTED_EVENT_ID = 3;
    static const int OUTER_MOVEMENT_DETECTED_EVENT_ID = 4;

    static const Event INNER_MOVEMENT_DETECTED_EVENT;
    static const Event OUTER_MOVEMENT_DETECTED_EVENT;

    EntryMovementSensor(int pin, EventHandler* handler = nullptr);

private:

};

#endif // MOVEMENT_SENSOR_H