#include <Arduino.h>

#include <debug.h>

#include <settings.h>
#include <board.h>
#include <pulsefast.h>
#include <simulator.h>
#include <network.h>

void setup() {

  initSerial();

  initPins();

  buzzBeep();

  pulse_setup();

  networksetup();
  
  home_return();

}

void loop() {
  
  //ledFlash();
  //buzzBeep();

  pulse_refresh();

  home_return();
    
}

