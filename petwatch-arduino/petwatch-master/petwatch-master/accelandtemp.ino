// Basic demo for accelerometer readings from Adafruit LIS3DH

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

// accelerometer pins
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

//temperature pin
#define DHTPIN 2
#define DHTTYPE DHT22

// global accelerometer variables
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
float totalMovement=0;

//global temperature variables
DHT dht(DHTPIN, DHTTYPE);
float avgTemp;
float avgHum;
float avgHI;
float Temps[5];
float Hums[5];
float HIs[5];
int index;



#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

void setup(void) {
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);
  setupAccel();
  setupTemp();
}

void setupAccel(void){
   if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start accelerometer");
    while (1);
  }
  Serial.println("accelerometer found!");

   lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
}

void setupTemp(){

  dht.begin();
  index=0;
}

void loop() {
  
  //measureAccel();
  measureTemp();
  Serial.println();
 
  delay(200); 
}

void measureAccel(){
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);

  //figure out physics
  float movement= abs(event.acceleration.x) + abs(event.acceleration.y) + abs(event.acceleration.z) - 9.8;
  Serial.println(movement);
  totalMovement+=movement;
  
}

void calculateTemps(){
  avgTemp=0;
  avgHum=0;
  avgHI=0;
  for (int i = 0; i<5;i++){
    avgTemp+=Temps[i];
    avgHum+=Hums[i];
    avgHI+=HIs[i];
  }

  avgTemp/=5;
  avgHum/=5;
  avgHI/=5;

  Serial.println(avgTemp);
  Serial.println(avgHum);
  Serial.println(avgHI);
}

//runs every minute
void measureTemp(){
  float h = dht.readHumidity();
  float f = dht.readTemperature(true);

  if(isnan(h)||isnan(f)){
    Serial.println("Falied to read temp sensor");
  }
  else{
    float hif = dht.computeHeatIndex(f,h);
    Temps[index]=f;
    Hums[index]=h;
    HIs[index]=hif;
    Serial.println(hif);

    
  }
  if(index==4){
    calculateTemps();
  }
  
  index = (index+1)%5;
}



