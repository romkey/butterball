#include <Arduino.h>
#include <SPIFFS.h>

#include "config.h"

#include "butterball.h"

#include <multiball/app.h>
#include <multiball/homebus.h>
#include <multiball/bme280.h>

#include "hw.h"

void setup() {
  const wifi_credential_t wifi_credentials[] = {
    { WIFI_SSID1, WIFI_PASSWORD1 },
    { WIFI_SSID2, WIFI_PASSWORD2 },
    { WIFI_SSID3, WIFI_PASSWORD3 }
  };

  delay(500);

  BApp.wifi_credentials(3, wifi_credentials);
  BApp.begin();

  homebus_configure("butterball", "", "Homebus", "1");
  homebus_setup();

  Serial.println("[butterball]");
}

void loop() {
  BApp.handle();

  homebus_handle();

  bme280_handle();
}
