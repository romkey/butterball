#pragma once

#include <multiball/app.h>

#include "max31855_sensor.h"

class ButterballApp : public MultiballApp {
public:
  void begin();
  void handle();

  float high_temperatureC() { return _max31855.temperatureC(); };
  float high_temperatureF() { return _max31855.temperatureF(); };

  boolean has_environmental();
  boolean has_tvoc();

private:
  MAX31855_Sensor _max31855 = MAX31855_Sensor(60*1000, 0, 0, false);
};

extern ButterballApp BApp;
