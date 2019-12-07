#include "display.h"

#include <multiball/app.h>
#include "butterball.h"

#include <WiFi.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display;

void display_begin() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello, world!");
  display.print("Wifi ");
  display.println(WiFi.SSID());
  display.display();
}

void display_ip() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(App.hostname());
  display.println(App.ip_address());
  display.display();
}

void display_update() {
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(4);
  display.println((int)Butterball.high_temperatureF());
  display.display();
}
