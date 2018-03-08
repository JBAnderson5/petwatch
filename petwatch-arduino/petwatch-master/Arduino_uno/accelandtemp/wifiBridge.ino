#include <ESP8266WiFi.h>

const char* ssid = "iPhone";
const char* password = "rache1ha1e";

const char* host = "students.engr.scu.edu";
String url;

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
  WiFiClient client;
  const int httpPort = 80;
  if(!client.connect(host, httpPort)){
    Serial.println("connection failed");
    return;
  }

  url="/dogCollar/sendData.php";
  client.print(String("POST ") + url + " HTTP/1.1\r\n" + "HOST: " + host + "\r\n" + "prevTrans="+prevTrans  + "\r\n Connection: close\r\n\r\n");

  delay(500);

  while(client.available()){
    String line=client.readStringUntil('\r');
    Serial.print(line);
  }
}


void sendAccel(){
  String message=String("POST ")+url+ " HTTP/1.1\r\n"+ "HOST: "+host + "\r\n"+ "prevTrans="+ prevTrans+ "&dataType=accel";
  for(int i=0; i < accelIndex;i++){
    message+=String("&accel")+i+"="+aggMovement[i]+"&time"+i+"="+accelTime[i];
  }
  message+="\r\n Connection: close\r\n\r\n";
}

void sendTemp(){
  String message="POST "+url+ " HTTP/1.1\r\n"+ "HOST: "+host + "\r\n"+ "prevTrans="+ prevTrans+ "&dataType=temp";
  for(int i=0; i < storedIndex;i++){
    message+=String("&temp")+i+"="+avgTemp[i]+"&hum"+i+"="+avgHum[i]+"&HI"+i+"="+avgHI[i]+"&time"+i+"="+timeStamp[i];
  }
  message+="\r\n Connection: close\r\n\r\n";
}

