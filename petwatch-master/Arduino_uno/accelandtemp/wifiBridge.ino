
void setupWifi(){
  Wire.begin();
  prevTrans=0;
}

void sendAccel(){

  Wire.beginTransmission(8);
  Wire.write("accel");

  for(int i=0;i<accelIndex;i++){
    Wire.write(aggMovement, sizeof(aggMovement));
    Wire.write(&accelTime[i]);
    aggMovement[i]=0;
    accelTime[i]=0;
  }
  Wire.endTransmission();
  accelIndex=0;
}

void sendTemp(){

  Wire.beginTransmission(8);
  Wire.write("temp");
  for(int i=0;i<storedIndex;i++){
    Wire.write(avgTemp[i]);
    Wire.write(avgHum[i]);
    Wire.write(avgHI[i]);
    Wire.write(timeStamp[i]);
    avgTemp[i]=0;
    avgHum[i]=0;
    avgHI[i]=0;
    timeStamp[i]=0;
  }
  Wire.endTransmission();
  storedIndex=0;
}

