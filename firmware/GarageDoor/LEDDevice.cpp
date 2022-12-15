#include "LEDDevice.hpp" 

LEDDevice::LEDDevice(int ledPin) : Service::LightBulb(){
  power=new Characteristic::On();                 // this is where we create the On Characterstic we had previously defined in setup().  Save this in the pointer created above, for use below
  this->ledPin=ledPin;                            // don't forget to store ledPin...
  pinMode(ledPin,OUTPUT);                         // ...and set the mode for ledPin to be an OUTPUT (standard Arduino function)
}

boolean LEDDevice::update(){            

    digitalWrite(ledPin,power->getNewVal());        // use a standard Arduino function to turn on/off ledPin based on the return of a call to power->getNewVal() (see below for more info)
   
    return(true);                                   // return true to indicate the update was successful (otherwise create code to return false if some reason you could not turn on the LED)
  
}