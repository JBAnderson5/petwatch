//temperature pin
#define DHTPIN 2 //green use pin 0 for prototype 1 and pin 2 for prototype 2
#define DHTTYPE DHT22


//TODO: fix stored index going over limit

//global temperature variables
DHT dht(DHTPIN, DHTTYPE);
//stores an average of the past five minutes. can store up to an hour's worth of data
float avgTemp [12];
float avgHum [12];
float avgHI [12];
unsigned long timeStamp [12];
int storedIndex;

//stores the temporary data to calculate the averages
float Temps[5];
float Hums[5];
float HIs[5];
int tempIndex;

void printTemps(){
  for(int i =0;i<12;i++){
    Serial.println(avgTemp[i]);
    Serial.println(avgHum[i]);
    Serial.println(avgHI[i]);
    Serial.println(timeStamp[i]);
    Serial.println();
  }
}

void setupTemp(){
  if(storedIndex==12)
      return;
  dht.begin();
  tempIndex=0;
  storedIndex=0;
  prevTemp=0;
}

void calculateTemps(){
  float temp=0;
  float hum=0;
  float hi=0;
  for (int i = 0; i<5;i++){
    temp+=Temps[i];
    hum+=Hums[i];
    hi+=HIs[i];
  }

  temp/=5;
  hum/=5;
  hi/=5;

  avgTemp[storedIndex] = temp;
  avgHum[storedIndex] = hum;
  avgHI[storedIndex] = hi;
  timeStamp[storedIndex] = millis();
  //if(storedIndex==11)
    //printTemps();
  storedIndex++;
}

//runs every minute
void measureTemp(){
  //Serial.print("t");
  prevTemp=Time;
  float hum = dht.readHumidity();
  float temp = dht.readTemperature(true);

  if(isnan(hum)||isnan(temp)){
    //Serial.println("Falied to read temp sensor");
    return;
  }
  else{
    float hi = dht.computeHeatIndex(temp,hum);
    Temps[tempIndex]=temp;
    Hums[tempIndex]=hum;
    HIs[tempIndex]=hi;
    
  }
  if(tempIndex==4){
    calculateTemps();
  }
  
  tempIndex = (tempIndex+1)%5;
}


