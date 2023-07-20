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

const char* ssid = "F62_HotSpot";                           // Your Network SSID
const char* password = "Sourav@120101";                    // Your Network Password

WiFiClient client;

unsigned long myChannelNumber = 2143748;                   //Your Channel Number (Without Brackets)
const char * myWriteAPIKey = "XUFZ6AWYDADO3G2Q";          //Your Write API Key

int d,r;
float t,h,w,to;
void setup() {
  
  Serial.begin(9600);
  delay(10);
  // Connect to WiFi network
  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);

}

void loop() {
  
    if(Serial.available()>0){

      String data=Serial.readStringUntil('\n');
      d=data.substring(0,2).toInt();
      t=data.substring(3,8).toFloat();
      h=data.substring(9,14).toFloat();
      w=data.substring(15,18).toFloat();
      to=data.substring(19,26).toFloat();
      r=data.substring(27).toInt();
      
      Serial.println(d);
      Serial.println(t);
      Serial.println(h);
      Serial.println(w);
      Serial.println(to);
      Serial.println(r);
      delay(1000);
    }
    ThingSpeak.writeField(myChannelNumber,1,d,myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber,2,t,myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber,3,h,myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber,4,w,myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber,5,to,myWriteAPIKey);
    ThingSpeak.writeField(myChannelNumber,6,r,myWriteAPIKey);
    delay(1000);

}
