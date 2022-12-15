#include "LEDDevice.hpp"

void setup() {
  Serial.begin(115200);

  // HomeSpan setup
  homeSpan.begin(Category::Lighting,"Garage Door");
  new SpanAccessory();

  // Accessory Information Service
  new Service::AccessoryInformation();
  new Characteristic::Identify();
  new Characteristic::Model("ESP32 Dev Board");
  new Characteristic::FirmwareRevision("0.1"); 

  new LEDDevice(16);
}

void loop() {
  // put your main code here, to run repeatedly:
  homeSpan.poll();
}
