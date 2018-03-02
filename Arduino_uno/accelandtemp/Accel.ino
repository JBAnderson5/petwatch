// accelerometer pins
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
#define LIS3DH_CS 10

// global accelerometer variables
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
float totalMovement=0;

void setupAccel(void){
   if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start accelerometer");
    while (1);
  }
  Serial.println("accelerometer found!");

   lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
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
