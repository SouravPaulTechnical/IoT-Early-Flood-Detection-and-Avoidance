/*
IoT Early Flood Detection and Avoidance.
This is Arduino Sender Code To NodeMCU ESP8266.
This is also Arduino Uno code for accepting all the sensors data.
Created by : Sourav Paul & Aditya Shee
---------------------------------------------------------------------------------------------------------
*/

/*Attached Library Files
---------------------------------------------------------------------------------------------------------*/
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//Define Arduino Pins and Creating Objects

LiquidCrystal_I2C lcd(0x27,20,4);    // set the LCD address to 0x27 for a 20 chars and 4 line display

int trig=7;
int echo=6;
int safedistance;
int TimeMicro;
int Distance;

#define DHT11_PIN 2
#define DHTTYPE DHT11
#define buzzer 11
DHT dht(DHT11_PIN, DHTTYPE);

float t;
float h;
int X;
int Y;
float TIME = 0;
float FREQUENCY = 0;
float WATER = 0;
float TOTAL = 0;
float LS = 0;
const int input = A0;

/*Void Setup Function
-----------------------------------------------------------------------------------------------------------*/
void setup()
{

  Serial.begin(9600);
  lcd.init();                    // initialize the lcd 
 
  lcd.backlight();               // turn on LCD backlight

  pinMode(7,OUTPUT);             // trigger pin for ultrasonic sensor
  pinMode(6,INPUT);              // echo pin for ultrasonic sensor

  dht.begin();                   // function begin for DHT11 sensor

  pinMode(input,INPUT);          // pinmode for water flow sensor

  pinMode(5, INPUT);             // pinmode for rain sensor module


}

/* void loop function
-----------------------------------------------------------------------------------------------------------*/
void loop()
{

  /*function body for ultrasonic sensor*/

  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  TimeMicro=pulseIn(echo,HIGH);
  Distance=TimeMicro/29/2;
  safedistance=Distance;

  /*logic for buzzer*/

  if(safedistance<=20){
    digitalWrite(buzzer,HIGH);
  }
  else{
    digitalWrite(buzzer,LOW);
  }

  /*logic to print data to LCD display*/
  
  lcd.setCursor(0, 0);
  lcd.print("W.Lev=");
  lcd.print(Distance);
  lcd.print("cm");
  delay(2000);

  /*logic for DHT11 sensor*/
  
  h = dht.readHumidity();
  t = dht.readTemperature();
  lcd.setCursor(11, 0);
  lcd.print("Tem=");
  lcd.print(t);
  lcd.setCursor(0, 1);
  lcd.print("Hum=");
  lcd.print(h);
  lcd.print("%");
  delay(2000);

  /*logic for water flow sensor*/
  
  X = pulseIn(input, HIGH);
  Y = pulseIn(input, LOW);
  TIME = X + Y;
  FREQUENCY = 1000000/TIME;
  WATER = FREQUENCY/7.5;
  LS = WATER/60;
  if(FREQUENCY >= 0)
    {
      if(isinf(FREQUENCY))
        {
          lcd.clear();
          lcd.setCursor(0,2);
          lcd.print("VOL:0.0");
          lcd.setCursor(0,3);
          lcd.print("TOTAL:");
          lcd.print(TOTAL);
          lcd.print("L");
        }
      else
        {
          TOTAL = TOTAL + LS;
          lcd.clear();
          lcd.setCursor(0,2);
          lcd.print("VOL:");
          lcd.print(WATER);
          lcd.print("L/M");
          lcd.setCursor(0,3);
          lcd.print("TOTAL:");
          lcd.print(TOTAL);
          lcd.print("L");
        }
    }
delay(2000);

  /*logic for rain sensor module*/

int rain = digitalRead(5);

if(rain==0)
{
  lcd.setCursor(11, 1);
  lcd.print("RAIN");
   delay(1000);
}
else if(rain==1)
{
  lcd.setCursor(11, 1);
  lcd.print("NO RAIN");
   delay(1000);
}

/*logic for serial monitor printing in Arduino IDE*/

Serial.print(",");
Serial.print(Distance);
Serial.print(",");
Serial.print(t);
Serial.print(",");
Serial.print(h);
Serial.print(",");
Serial.print(WATER);
Serial.print(",");
Serial.print(TOTAL);
Serial.print(",");
Serial.print(rain);
Serial.println();
delay(1000);
  
}


