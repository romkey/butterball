#include <Arduino.h>
#include <SPIFFS.h>

#include "config.h"

#include "butterball.h"

#include <multiball/app.h>
#include <multiball/homebus.h>
#include <multiball/bme280.h>

#include "hw.h"

MultiballApp App;
ButterballApp Butterball;

void setup() {
  const wifi_credential_t wifi_credentials[] = {
    { WIFI_SSID1, WIFI_PASSWORD1 },
    { WIFI_SSID2, WIFI_PASSWORD2 },
    { WIFI_SSID3, WIFI_PASSWORD3 }
  };

  delay(500);

  App.wifi_credentials(3, wifi_credentials);
  App.begin("butterball");

  homebus_configure("butterball", "", "Homebus", "1");
  homebus_setup();

  Butterball.begin();
  Serial.println("[butterball]");

  bme280_setup();
  Serial.println("[bme280]");
}

void loop() {
  Serial.println("app handle");
  App.handle();
  delay(500);

  Serial.println("butterball handle");
  Butterball.handle();
  delay(500);

  Serial.println("homebus handle");
  homebus_handle();
  delay(500);

  Serial.println("bme280 handle");
  bme280_handle();
  delay(500);
}
