// accelerometer pins
#define LIS3DH_CLK 13   //blue SCL
#define LIS3DH_MISO 12  //yellow SDO
#define LIS3DH_MOSI 11  //green SDA
#define LIS3DH_CS 10    //blue CS

// global accelerometer variables
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);

//stores the total movement of 5 minute intervals
float aggMovement[12];
unsigned long accelTime[12];
int accelIndex;
float movement;

void setupAccel(void){
   if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start accelerometer");
    while (1);
  }
  Serial.println("accelerometer found!");

   lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  movement=0;
  prevAccel=0;
}

void totalAccel(){
  aggMovement[accelIndex]=movement;
  movement=0;
  
  accelTime[accelIndex]=Time;
  prevAccel=Time;
  Serial.println(aggMovement[accelIndex]);
  Serial.println(accelTime[accelIndex]);
  Serial.println();
  accelIndex++;
}


void measureAccel(){

 //Serial.print("a");
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);

  //figure out physics
  movement+= abs(event.acceleration.x) + abs(event.acceleration.y) + abs(event.acceleration.z) - 9.8;
  if(Time-prevAccel>1000*60UL)
    totalAccel();

  
}
