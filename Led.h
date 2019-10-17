#include <Arduino.h>
#ifndef LED_H
#define LED_H

class Led {
  
  private:
    byte pin;
  
  public:
    Led(byte pin);
    
    void init();
    void on();
    void off();
}; 

#endif
