#pragma once

#include "sensor.h"

#include "Adafruit_MAX31855.h"

#include "hw.h"

class MAX31855_Sensor : public Sensor {
 public:
  MAX31855_Sensor(uint16_t update_frequency, uint16_t accuracy, uint16_t precision, boolean calibrated) : Sensor(update_frequency, accuracy, precision, calibrated), _last_read(0) {};

  void begin();
  void handle();

  float temperatureC() { _mark_read(); return _temperatureC; };
  float temperatureF() { return (temperatureC() * 9/5) + 32; }

 private:
  Adafruit_MAX31855 _max31855 = Adafruit_MAX31855(MAX_CLK, MAX_CS, MAX_D0);
  unsigned long _last_read;

  float _temperatureC;
  float _temperatureF;
};
