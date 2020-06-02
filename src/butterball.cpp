#include "butterball.h"

#include "config.h"

#include <multiball/app.h>
#include <multiball/homebus.h>

#include "display.h"

#ifdef USE_MAX6675
#include "sensors/max6675_sensor.h"

static MAX6675_Sensor max6675 = MAX6675_Sensor(60*1000, 0, 0, false);
#endif

#ifdef USE_MAX31855
#include "sensors/max31855_sensor.h"

static MAX31855_Sensor max31855 = MAX31855_Sensor(60*1000, 0, 0, false);
#endif

#include "sensors/bme280_sensor.h"

static BME280_Sensor bme280 = BME280_Sensor(60*1000, 0, 0, false);


void butterball_setup() {
#ifdef USE_MAX6675
  max6675.begin();
  Serial.println("[max6675]");
#endif

#ifdef USE_MAX31855
  max31855.begin();
  Serial.println("[max6675]");
#endif

  bme280.begin();

  display_begin();
  Serial.println("[display]");
}


static boolean butterball_air_update(char* buf, size_t buf_len) {
  snprintf(buf,
	   buf_len,
	   "{ \"id\": \"%s\", \"org.homebus.experimental.air-sensor\": { \"temperature\": %.1f, \"humidity\": %.1f, \"pressure\": %.1f } }",
	   homebus_uuid(),
#ifdef TEMPERATURE_ADJUSTMENT
	   bme280.temperature() + TEMPERATURE_ADJUSTMENT,
#else
	   bme280.temperature(),
#endif
	   bme280.humidity(), bme280.pressure());

#ifdef VERBOSE
  Serial.println(buf);
#endif

  return true;
}

static boolean butterball_high_temperature_update(char* buf, size_t buf_len) {
  snprintf(buf,
	   buf_len,
	   "{ \"id\": \"%s\", \"org.homebus.experimental.high-temperature-sensor\": { \"temperature\": %.1f }",
	   homebus_uuid(),
#ifdef USE_MAX6675
	   max6675.temperatureC());
#endif
#ifdef USE_MAX31855
	   max31855.temperatureC());
#endif

#ifdef VERBOSE
  Serial.println(buf);
#endif

  return true;
}

/*
 * we do this once at startup, and not again unless our IP address changes
 */
static boolean butterball_system_update(char* buf, size_t buf_len) {
  static IPAddress oldIP = IPAddress(0, 0, 0, 0);
  static String mac_address = WiFi.macAddress();
  IPAddress local = WiFi.localIP();

  if(oldIP == local)
    return false;

  snprintf(buf,
	   buf_len,
	   "{ \"id\": \"%s\", \"org.homebus.experimental.butterball-system\": { \"name\": \"%s\", \"build\": \"%s\", \"ip\": \"%d.%d.%d.%d\", \"mac_addr\": \"%s\" } }",
	   homebus_uuid(),
	   App.hostname().c_str(), App.build_info().c_str(), local[0], local[1], local[2], local[3], mac_address.c_str()
	   );

#ifdef VERBOSE
  Serial.println(buf);
#endif

  return true;
}

static boolean butterball_diagnostic_update(char* buf, size_t buf_len) {
  snprintf(buf, buf_len, "{ \"id\": \"%s\", \"org.homebus.experimental.butterball-diagnostic\": { \"freeheap\": %d, \"uptime\": %lu, \"rssi\": %d, \"reboots\": %d, \"wifi_failures\": %d } }",
	   homebus_uuid(),
	   ESP.getFreeHeap(), App.uptime()/1000, WiFi.RSSI(), App.boot_count(), App.wifi_failures());

#ifdef VERBOSE
  Serial.println(buf);
#endif

  return true;
}

void butterball_handle() {
  static unsigned long next_reading = 0;

  if(next_reading > millis())
    return;

  next_reading = millis() + UPDATE_DELAY;

  float high_temp;

  bme280.handle();

#ifdef USE_MAX6675
  max6675.handle();
  high_temp = max6675.temperatureC();
#endif
#ifdef USE_MAX31855
  max31855.handle();
  high_temp = max31855.current_temperatureC();
#endif

  Serial.printf("bme280 temp %f\n", bme280.temperature());
  Serial.printf("high temp temp %f\n", high_temp);

  display_update(high_temp*9.0/5 + 32);

  #define BUFFER_LENGTH 700
  char buffer[BUFFER_LENGTH + 1];

  if(butterball_air_update(buffer, BUFFER_LENGTH))
    homebus_publish_to("org.homebus.experimental.air-sensor", buffer);

  if(butterball_high_temperature_update(buffer, BUFFER_LENGTH))
    homebus_publish_to("org.homebus.experimental.high-temperature-sensor", buffer);

  if(butterball_system_update(buffer, BUFFER_LENGTH))
    homebus_publish_to("org.homebus.experimental.butterball-system", buffer);

  if(butterball_diagnostic_update(buffer, BUFFER_LENGTH))
    homebus_publish_to("org.homebus.experimental.butterball-diagnostic", buffer);
}
