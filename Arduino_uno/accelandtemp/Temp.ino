//temperature pin
#define DHTPIN 2
#define DHTTYPE DHT22

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


void setupTemp(){

  dht.begin();
  tempIndex=0;
  storedIndex=0;
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
  timeStamp[storedIndex] = Time;
  storedIndex=(storedIndex+1)%12;
}

//runs every minute
void measureTemp(){
  float hum = dht.readHumidity();
  float temp = dht.readTemperature(true);

  if(isnan(h)||isnan(f)){
    Serial.println("Falied to read temp sensor");
  }
  else{
    float hi = dht.computeHeatIndex(f,h);
    Temps[tempIndex]=temp;
    Hums[tempIndex]=hum;
    HIs[tempIndex]=hi;
    
  }
  if(index==4){
    calculateTemps();
  }
  
  index = (index+1)%5;
}


