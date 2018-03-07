#include <Wire.h>

//green pin 5
//blue pin 4
String recieveType;


void recieveEvent(int howMany){
  recieveType="";
  while(Wire.available()){
    recieveType+=Wire.read();
    if(recieveType=="accel"){
      recieveAccel();
      return;
    }
    else if(recieveType=="temp"){
      recieveTemp();
      return;
    }
  }
}

void setupReciever(){
  Wire.begin(8);
  Wire.onReceive(recieveEvent);
  Serial.println("Reciever setup");
}


void recieveAccel(){
  int index=Wire.read();
  Serial.println(recieveType);
  Serial.println(index);
}

void recieveTemp(){
  int index=Wire.read();
  Serial.println(recieveType);
  Serial.println(index);
}

