#ifndef SOUND_SENSOR_H
#define SOUND_SENSOR_H

#include "Sensor.h"

class SoundSensor : public Sensor {
public:
  static const int SOUND_DETECTED_EVENT_ID = 7; ///< Unique ID for button press event.
  static const Event SOUND_DETECTED_EVENT; ///< Predefined event for button presses.

  int digitalPin;

  SoundSensor(int digitalPin, EventHandler* eventHandler = nullptr);

  void check();
};

#endif