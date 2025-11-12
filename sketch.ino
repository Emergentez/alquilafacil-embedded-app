#include "ModestIoT.h"
#include "MonitoringLocalDevice.h"
#include <time.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

#define DEBOUNCE_DELAY_MS 200

MonitoringLocalDevice device; // Instancia global del device

// --- ISRs ---

bool flagSmoke = false;
bool flagRestrictedArea = false;
bool flagInnerMovement = false;
bool flagOuterMovement = false;
bool flagSound = false;



void IRAM_ATTR triggerSmokeDetected() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last > DEBOUNCE_DELAY_MS) {
    flagSmoke = true;
    last = now;
  }
}

void IRAM_ATTR triggerRestrictedAreaDetected() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last > DEBOUNCE_DELAY_MS) {
    flagRestrictedArea = true;
    last = now;
  }
}

void IRAM_ATTR triggerInnerMovementDetected() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last > DEBOUNCE_DELAY_MS) {
    flagInnerMovement = true;
    last = now;
  }
}

void IRAM_ATTR triggerOuterMovementDetected() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last > DEBOUNCE_DELAY_MS) {
    flagOuterMovement = true;
    last = now;
  }
}

void IRAM_ATTR triggerSoundDetected(){
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last > DEBOUNCE_DELAY_MS) {
    flagSound = true;
    last = now;
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("\nWiFi conectado.");

  configTime(0, 0, "pool.ntp.org"); // NTP para obtener hora  
  
  attachInterrupt(
    digitalPinToInterrupt(MonitoringLocalDevice::SMOKE_DIGITAL_PIN),
    triggerSmokeDetected,
    RISING
  );

  attachInterrupt(
    digitalPinToInterrupt(MonitoringLocalDevice::RESTRICTED_AREA_PIN),
    triggerRestrictedAreaDetected,
    RISING
  );

  attachInterrupt(
    digitalPinToInterrupt(MonitoringLocalDevice::INNER_MOVEMENT_SENSOR_PIN),
    triggerInnerMovementDetected,
    RISING
  );

  attachInterrupt(
    digitalPinToInterrupt(MonitoringLocalDevice::OUTER_MOVEMENT_SENSOR_PIN),
    triggerOuterMovementDetected,
    RISING
  );

  attachInterrupt(
    digitalPinToInterrupt(MonitoringLocalDevice::SOUND_SENSOR_PIN),
    triggerSoundDetected,
    RISING
  );
}

void loop() {
  if (flagSmoke){
    flagSmoke = false;
    device.on(SmokeSensor::SMOKE_DETECTED_EVENT);
  }
  if (flagRestrictedArea){
    flagRestrictedArea = false;
    device.triggerRestrictedAreaEvent(RestrictedAreaMovementSensor::RESTRICTED_AREA_ACCESS_DETECTED_EVENT);
  }
  if (flagInnerMovement){
    flagInnerMovement = false;
    device.on(EntryMovementSensor::INNER_MOVEMENT_DETECTED_EVENT);
  }
  if (flagOuterMovement){
    flagOuterMovement = false;
    device.on(EntryMovementSensor::OUTER_MOVEMENT_DETECTED_EVENT);
  }
  if (flagSound){
    flagSound = false;
    device.on(SoundSensor::SOUND_DETECTED_EVENT);
  }
  delay(10); // this speeds up the simulation
}
