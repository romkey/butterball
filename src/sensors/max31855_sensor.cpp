#include "max31855_sensor.h"

#include "Adafruit_MAX31855.h"

#include "hw.h"

void MAX31855_Sensor::begin() {
  _max31855 = Adafruit_MAX31855(MAX_CLK, MAX_CS, MAX_D0);
}

void MAX31855_Sensor::handle() {
  if(millis() - _last_read > 1000) {
    _temperatureC = _max31855.readCelsius();
    _last_read = millis();
  }
}
