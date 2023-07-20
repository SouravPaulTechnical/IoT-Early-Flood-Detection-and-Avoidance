#include <SoftwareSerial.h>
#include <stdlib.h>

SoftwareSerial soft(2, 3); // RX, TX
void setup() {
  /* Initial bauderate of ESp when you purchase from market is 115200 */
  Serial.begin(115200);  /* Here you should give current baudrate of ESP */
  soft.begin(115200);  

     soft.print("***VER:");
  delay(2000);
soft.println("AT+RST");
 delay(1000);
}


void loop() {
soft.println("AT+GMR");

delay(3000);
soft.println("AT+CWMODE=3");

delay(3000);
soft.println("AT+UART_DEF=9600,8,1,0,0");  /* Here you should give expected baudrate of ESp */

delay(3000);
Serial.println("Done");
while(1);
   
}
void printresponse()
{
  while (soft.available()>0) {
    Serial.println(soft.readString());
  }
}
