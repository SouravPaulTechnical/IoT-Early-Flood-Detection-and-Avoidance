/*
IoT Early Flood Detection and Avoidance.
This is Reeceiver NodeMCU ESP8266 code from Arduino Uno.
This is code for accept data from Arduino and send them to ThingSpeak Cloud
Created by : Sourav Paul & Aditya Shee
---------------------------------------------------------------------------------------------------------
*/

/*Attached Library Files
---------------------------------------------------------------------------------------------------------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ThingSpeak.h>

WiFiClient client;

const char* ssid = "F62_HotSpot";                           // Your Network SSID
const char* password = "Sourav@120101";                    // Your Network Password

unsigned long myChannelNumber = 2143748;                   //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "XUFZ6AWYDADO3G2Q";          //Your Write API Key

int d,r;
float t,h,w,to;
void setup() {
  
  Serial.begin(9600);
  delay(1000);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(200);
    Serial.print("..");
  }
  ThingSpeak.begin(client);

}

void loop() {
    int del1, del2, del3, del4, del5, del6;
    if(Serial.available()>0){

      String data=Serial.readStringUntil('\n');
      del1=data.indexOf(",");
      del2=data.indexOf(",", del1+1);
      del3=data.indexOf(",", del2+1);
      del4=data.indexOf(",", del3+1);
      del5=data.indexOf(",", del4+1);
      del6=data.indexOf(",", del5+1);
      d=data.substring(del1+1,del2).toInt();
      t=data.substring(del2+1,del3).toFloat();
      h=data.substring(del3+1,del4).toFloat();
      w=data.substring(del4+1,del5).toFloat();
      to=data.substring(del5+1,del6).toFloat();
      r=data.substring(del6+1).toInt();

      ThingSpeak.writeField(myChannelNumber, 1, d, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber, 2, t, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber, 3, h, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber, 4, w, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber, 5, to, myWriteAPIKey);
      ThingSpeak.writeField(myChannelNumber, 6, r, myWriteAPIKey);
      delay(1000);

      Serial.print(d);
      Serial.print(",");
      Serial.print(t);
      Serial.print(",");
      Serial.print(h);
      Serial.print(",");
      Serial.print(w);
      Serial.print(",");
      Serial.print(to);
      Serial.print(",");
      Serial.print(r);
      Serial.println();
      delay(1000);
    }
    

}
