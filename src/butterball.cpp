#include "butterball.h"

#include "config.h"

#include <multiball/app.h>
#include <multiball/homebus.h>
#include <multiball/bme280.h>

#include "max6675_sensor.h"
#include "max31855_sensor.h"

ButterballApp BApp;

void ButterballApp::begin() {
  MultiballApp::begin("butterball");

#if 0
  _max6675.begin();
  Serial.println("[max6675]");
#endif

  _max31855.begin();
  Serial.println("[max6675]");
}

void ButterballApp::handle() {
  static unsigned long next_reading = 0;

  if(next_reading > millis())
    return;

  Serial.printf("bme280 temp %f\n", bme280_current_temperature());
  Serial.printf("max318555 temp %f\n", _max31855.temperatureF());
}
