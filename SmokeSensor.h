#ifndef SMOKE_SENSOR_H
#define SMOKE_SENSOR_H

#include "Sensor.h"

class SmokeSensor : public Sensor {
public:
  static const int SMOKE_DETECTED_EVENT_ID = 1; ///< Unique ID for button press event.
  static const Event SMOKE_DETECTED_EVENT; ///< Predefined event for button presses.

  int digitalPin;
  int analogPin;

  SmokeSensor(int digitalPin,int analogPin, EventHandler* eventHandler = nullptr);

  int readValue();
  void check();
};

#endif