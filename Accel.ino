// accelerometer pins
#define LIS3DH_CLK 14   //blue SCL
#define LIS3DH_MISO 12  //yellow SDO
#define LIS3DH_MOSI 13  //green SDA
#define LIS3DH_CS 15    //blue CS

// global accelerometer variables
Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO,LIS3DH_CLK);


//TODO: fix physics


//stores the total movement of 5 minute intervals
int steps[12];
unsigned long accelTime[12];
int accelIndex;
float movement;
int stepCount;
bool isStepping;

void setupAccel(void){
    
    Wire.begin(14,13);
   if(! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start accelerometer");

    //while (1);
  }
  Serial.println("accelerometer found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  movement=0;
  prevAccel=0;
  accelIndex=0;
  stepCount=0;
  isStepping=false;
}

void totalAccel(){
  if(accelIndex==12)
    return;
  steps[accelIndex]=stepCount;
  accelTime[accelIndex]=millis();
  accelIndex++;
  stepCount=0;
  prevAccel=millis();
  
}


void measureAccel(){

 //Serial.print("a");
  lis.read();
  sensors_event_t event; 
  lis.getEvent(&event);

  //figure out physics
  movement= (event.acceleration.x*event.acceleration.x+event.acceleration.y*event.acceleration.y
  +event.acceleration.z+event.acceleration.z)/(9.8*9.8);
  //movement=float(.6)+random(0,2);
  //Serial.println(movement);
  if(isStepping){
    if(movement<1.5){
      isStepping=false;
      stepCount++;
      Serial.println("is this a step");
    }
  }
  else{
    if(movement>1.5){
      isStepping=true;
    }
  }
  
  if(millis()-prevAccel>1000*20UL)
    totalAccel(); 
}



