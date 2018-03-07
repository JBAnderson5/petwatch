#include <Wire.h>

void setupReciever(){
  Wire.begin(8);
  Wire.onReceive(receiveData);

}

void recieveData(){
  while(1<Wire.available()){
    
  }
}

