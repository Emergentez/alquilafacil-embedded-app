#include <ArduinoJson.h>
#include <time.h>
#include "MonitoringLocalDevice.h"
#include <Arduino.h>

#define DEVICE_ID 2234
//#define ENDPOINT_URL "https://<linkdeledge>/api/v1/edge-node/edge/"

#define ENDPOINT_SMOKE "http://alquilafacil-app.chilecentral.cloudapp.azure.com:3000/api/v1/edge-node/edge/readings/smoke"
#define ENDPOINT_RESTRICTED "http://alquilafacil-app.chilecentral.cloudapp.azure.com:3000/api/v1/edge-node/edge/readings/restricted-area"
#define ENDPOINT_ENTRY "http://alquilafacil-app.chilecentral.cloudapp.azure.com:3000/api/v1/edge-node/edge/readings/capacity"
#define ENDPOINT_SOUND "http://alquilafacil-app.chilecentral.cloudapp.azure.com:3000/api/v1/edge-node/edge/readings/noise"

char timeStringBuffer[20];

#define CONTENT_TYPE_HEADER "Content-Type"
#define APPLICATION_JSON "application/json"

MonitoringLocalDevice::MonitoringLocalDevice(int restrictedAreaPin, int smokeAnalogPin, int smokeDigitalPin, int innerMovementPin, int outerMovementPin, int soundPin)
    : smokeSensor(smokeDigitalPin, smokeAnalogPin, this),
      restrictedAreaMovementSensor(restrictedAreaPin, this),
      innerMovementSensor(innerMovementPin, this),
      outerMovementSensor(outerMovementPin, this),
      soundSensor(soundPin, this),
      pendingEvent(Event(-1))
      {}

void MonitoringLocalDevice::on(Event event) {
  if (event == SmokeSensor::SMOKE_DETECTED_EVENT) {
    Serial.println("Humo detectado.");
    int analogValue = smokeSensor.readValue();

    String mensaje = "Humo detectado en el area (valor: " + String(analogValue) + ")";
    sendEventToServer("smoke", mensaje, ENDPOINT_SMOKE);
  }

  if (event == RestrictedAreaMovementSensor::RESTRICTED_AREA_ACCESS_DETECTED_EVENT) {
    Serial.println("Movimiento no autorizado detectado.");

    String mensaje = "Movimiento en el area restringida";
    sendEventToServer("restricted", mensaje, ENDPOINT_RESTRICTED);
  }

  if (event == EntryMovementSensor::INNER_MOVEMENT_DETECTED_EVENT){
    unsigned long now = millis();
    if(now - lastOuterSensorTriggerTime < MOVEMENT_TIMEOUT_MS){
      //Se activo el sensor 1 hace menos de 500 ms, es una entrada.
      Serial.println("Se detecto una entrada");
      String mensaje = "IN";
      sendEventToServer("entry", mensaje, ENDPOINT_ENTRY);
    } else {
        lastInnerSensorTriggerTime = now;
    }
  }

  if (event == EntryMovementSensor::OUTER_MOVEMENT_DETECTED_EVENT){
    unsigned long now = millis();
    if(now - lastInnerSensorTriggerTime < MOVEMENT_TIMEOUT_MS){
      //Se activo el sensor 2 hace menos de 500 ms, es una salida.
      Serial.println("Se detecto una salida");
      String mensaje = "OUT";
      sendEventToServer("entry", mensaje,ENDPOINT_ENTRY);
    } else {
        lastOuterSensorTriggerTime = now;
    }
  }

  if (event == SoundSensor::SOUND_DETECTED_EVENT){
    String mensaje = "Ruido fuerte detectado en el area";
    sendEventToServer("sound", mensaje, ENDPOINT_SOUND);
  }
}

void MonitoringLocalDevice::triggerRestrictedAreaEvent(Event event){
  restrictedAreaMovementSensor.on(event);
}

void MonitoringLocalDevice::triggerSmokeSensorEvent(Event event){
  smokeSensor.on(event);
}

void MonitoringLocalDevice::triggerInnerMovementSensorEvent(Event event){
  innerMovementSensor.on(event);
}

void MonitoringLocalDevice::triggerOuterMovementSensorEvent(Event event){
  outerMovementSensor.on(event);
}

void MonitoringLocalDevice::triggerSoundSensorEvent(Event event){
  soundSensor.on(event);
}

void MonitoringLocalDevice::sendEventToServer(const char* sensorType, String message, const char* endpointUrl) {
    Serial.println("Ingresa a la funcion");
    
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("No hay conexión WiFi. Evento no enviado.");
        return;
    }
    /*struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) {
        Serial.println("Error al obtener la hora.");
        return;
    }*/
    
    //strftime(timeStringBuffer, sizeof(timeStringBuffer), "%d/%m/%Y %H:%M", &timeinfo);
    JsonDocument dataRecord;
    dataRecord["device_id"] = DEVICE_ID;
    //dataRecord["sensor"] = sensorType;
    dataRecord["message"] = message;
    /*dataRecord["timestamp"] = String(timeStringBuffer);*/
    
    Serial.println("data creada");

    String jsonPayload;
    serializeJson(dataRecord, jsonPayload);

    Serial.println("data serializada");

    
    HTTPClient http;
    http.begin(endpointUrl);
    
    Serial.println("http inicializado");
    http.addHeader(CONTENT_TYPE_HEADER, APPLICATION_JSON);
    
    int responseCode = http.POST(jsonPayload);
    Serial.println("http posteado");
    if (responseCode > 0) {
        Serial.printf("Enviado (%s). Código: %d\n", sensorType, responseCode);
        String response = http.getString();
        Serial.println("[HTTP] Respuesta:");
        Serial.println(response);
    } else {
        Serial.printf("Fallo al enviar (%s): %s\n", sensorType, http.errorToString(responseCode).c_str());
    }

    http.end();
}

void MonitoringLocalDevice::handle(Command command){

}