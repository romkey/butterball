#include "max31855_sensor.h"

#include "Adafruit_MAX31855.h"

#include "hw.h"

void MAX31855_Sensor::begin() {
  _max31855 = Adafruit_MAX31855(MAX_CLK, MAX_CS, MAX_D0);
}
