#include "HomeSpan.h" 

struct LEDDevice : Service::LightBulb {               // First we create a derived class from the HomeSpan LightBulb Service

  int ledPin;                                       // this variable stores the pin number defined for this LED
  SpanCharacteristic *power;                        // here we create a generic pointer to a SpanCharacteristic named "power" that we will use below

  // Next we define the constructor for DEV_LED.  Note that it takes one argument, ledPin,
  // which specifies the pin to which the LED is attached.
  
  LEDDevice(int ledPin);

  // Finally, we over-ride the default update() method with instructions that actually turn on/off the LED.  Note update() returns type boolean

  boolean update();
};
