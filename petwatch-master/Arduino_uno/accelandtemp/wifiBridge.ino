
//green pin 5
//blue pin 4

void setupWifi(){
  Wire.begin();
  prevTrans=0;
}

void sendAccel(){

  Wire.beginTransmission(8);
  Wire.write("accel");

  Wire.write(accelIndex);
/*

  for(int i=0;i<accelIndex;i++){
    Wire.write(aggMovement, sizeof(aggMovement));
    Wire.write(&accelTime[i]);
    aggMovement[i]=0;
    accelTime[i]=0;
  }

  */
  byte result= Wire.endTransmission();
  accelIndex=0;
  Serial.println("sent accel data");
  Serial.println(result);

}

void sendTemp(){

  Wire.beginTransmission(8);
  Wire.write("temp");

  Wire.write(storedIndex);
  /*
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

  */
  Wire.endTransmission();
  storedIndex=0;
  Serial.println("sent temp data");
}

void sendFloat(float genfloat){
  Wire.write((int)genfloat>>24);
  Wire.write((int) genfloat>>16);
  Wire.write((int) genfloat>>8);
  Wire.write((int) genfloat);
}

