#include "max6675_sensor.h"

#include "hw.h"

void MAX6675_Sensor::begin() {
  _max6675.begin(MAX_CLK, MAX_CS, MAX_D0);
}

void MAX6675_Sensor::handle() {
  if(millis() - _last_read > 1000) {
    _temperatureC = _max6675.readCelsius();
    _temperatureF = _max6675.readFahrenheit();
    _last_read = millis();
  }
}
