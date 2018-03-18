// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

unsigned long Time;
unsigned long prevTemp;
unsigned long prevAccel;
unsigned long prevTrans;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Time=millis();
  Serial.begin(9600);
  setupAccel();
  setupTemp();
  setupWifi();

  for(int i=0;i<20;i++){
    measureTemp();
    measureAccel();
  }

  sendInfo();
//  sendTemp();
}




void loop() {

  
  Time=millis();

  //check temperature every minute
  if(Time-prevTemp>1000*10UL)
    measureTemp();

  measureAccel();
  //Serial.println();
  if(Time-prevTrans>1000*60UL)
    sendInfo();
 
  delay(200); 
  
}





