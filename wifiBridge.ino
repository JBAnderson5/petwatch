#include <ESP8266WiFi.h>

const char* ssid = "JB's iPhone";
const char* password = "getwrecked";

const char* host = "students.engr.scu.edu";
String url="/~janders2/initialConn.php";
WiFiClient client;
const int httpPort=80;

void setupWifi(){
  prevTrans=Time;

  //connect to wifi
  WiFi.begin(ssid,password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());


  //send initial ack to server

  if(!client.connect(host, httpPort)){
    Serial.println("connection failed");
    return;
  }

  String data=initialData(0,0);
  
  sendPacket(data);
  
  delay(500);

  recievePacket();
 
       Serial.println();
       /*
       Serial.println("disconnecting.");
       client.stop();
       */
       
}

void sendInfo(){
  prevTrans=Time;
  
  if(WiFi.status()!=WL_CONNECTED){
    Serial.println("wifi disconnected");
    
  }
  if(!client.connected()){
    Serial.println("client disconnected");
    while(!client.connect(host, httpPort)){
      Serial.println("connection failed");
      return;
    }
    {
      Serial.println("client reconnected");
    }
  }
  String data=initialData(1,1)+accelData()+tempData();

  sendPacket(data);

  delay(500);
  
  recievePacket();
  
  //add delay between sending accel and temp data
  //make sure tcp connection
  //check phone connection- may be problem with phone queing mechanism
  //may perform data aggregation
  //use sleep mode to conserve energy
  //buy esp 32 feather board for future
  
  
}

/*
 * returns a string with the initial data set for our data packet
 * the two variables set indicate if we are sending our data from the sensors or not (1 for yes, 0 for no)
 */
String initialData(int accel,int temp){
  String data=String("prevTrans=")+ prevTrans;

  if(accel){
    data+="&accelData=1";
  }
  else{
    data+="&accelData=0";
  }
  if(temp){
    data+="&tempData=1";
  }
  else{
    data+="&tempData=0";
  }
  return data;
}



String accelData(){
  //Serial.println("packaging accel data");
  
  String data=String("&accelIndex=")+accelIndex;
  for(int i=0; i < accelIndex;i++){
    data+=String("&accel[")+i+"]="+steps[i]+"&atime["+i+"]="+accelTime[i];
  }
  accelIndex=0;
  
  return data;

  
}

String tempData(){
  //Serial.println("packaging temp data");
  
  String data= String("&tempIndex=")+storedIndex;
  for(int i=0; i < storedIndex;i++){
    data+=String("&temp[")+i+"]="+avgTemp[i]+"&hum["+i+"]="+avgHum[i]+"&HI["+i+"]="+avgHI[i]+"&ttime["+i+"]="+timeStamp[i];
  }
  storedIndex=0;
  
  return data;
  
}

void recievePacket(){
  while(client.available()){
    String line=client.readStringUntil('\r');
    //Serial.print(line);
  }
  Serial.println("done reading");
}

void sendPacket(String data){
  String message=String("POST ") + url + " HTTP/1.1\r\n" + "HOST: " + host + "\r\n" 
  +"Accept: *" + "/"+"*\r\n"+ "Content-Length: "+data.length()+"\r\n" 
   + "Content-Type: application/x-www-form-urlencoded\r\n"+"\r\n"  + data+ "\r\n\r\n";
   client.print(message);
   Serial.println(message);
  
}


