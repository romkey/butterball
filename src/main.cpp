#include <Arduino.h>
#include <SPIFFS.h>

#include "config.h"

#include "butterball.h"

#include <multiball/app.h>
#include <multiball/homebus.h>

#include "hw.h"

MultiballApp App;

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

  butterball_setup();
  Serial.println("[butterball]");
}

void loop() {
  Serial.println("app handle");
  App.handle();
  delay(500);

  Serial.println("butterball handle");
  butterball_handle();
  delay(500);
}
