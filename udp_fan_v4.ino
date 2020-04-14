/*
 control fan motor outdoor 
 esp8266 ,data 4 byte
 D4 pwm 25Hz ,ssr 20a
*/

#include "ESP8266WiFi.h"
#include "WiFiUdp.h" 
//IPAddress : 192.168.0.121
#define udp_port 90
WiFiUDP udp;

char ssid[] = "TP-Link_5F54";
char pass[] = "xxx";

char packetBuffer[255]; // char buffer to hold incoming packet
uint16_t umotor = 0;
float umotorf = 0.0;
uint16_t umotortt = 0;
int timeout = 0;
void setup()
{
Serial.begin(115200);
pinMode(D4, OUTPUT);
//pinMode(LED_BUILTIN, OUTPUT);
WiFi.disconnect(true);
WiFi.mode(WIFI_STA);
WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED)
  {
   Serial.println("Connecting AccessPoint " + String(ssid));
   delay(2000);
  }

udp.begin(udp_port);
Serial.println("---------------------------------------------");
Serial.println("Connect " + String(ssid) + " !!!!!!");
Serial.print("IPAddress : ");
Serial.println(WiFi.localIP());
Serial.println("Udp Port : " + String(udp_port));
Serial.println("---------------------------------------------");
delay(2000);
}
void loop()
{
int buffer = udp.parsePacket();
if(buffer>0)
{
  //digitalWrite(LED_BUILTIN, LOW);
  //11 00 FF 03
  int len = udp.read(packetBuffer, 5);
  if(packetBuffer[0] == 34){
    umotor = ((packetBuffer[1] << 8) | packetBuffer[2]);
    //umotor = packetBuffer[1];
  }
      Serial.print(len);Serial.print("\t");
      Serial.print(packetBuffer[0],HEX);Serial.print("\t");
      Serial.print(packetBuffer[1],HEX);Serial.print("\t");
      Serial.print(packetBuffer[2],HEX);Serial.print("\t");
      Serial.print(packetBuffer[3],HEX);Serial.print("\t");
      Serial.print(packetBuffer[4],HEX);Serial.print("\t");
      Serial.println(umotor);
udp.flush();
timeout = 0;
}
else
{
  //digitalWrite(LED_BUILTIN, HIGH);
  timeout++;
  if(timeout > 500){//time 10 s
  //umotor = 0;// motor off
  }
}
//motor fan
umotorf = umotorf + (umotor - umotorf)*0.00124;//0.0000124
//umotorf = constrain(umotorf, 0, 1024);
umotortt = constrain(umotorf, 500, 40000);
//analogWriteFreq(50);//1  - 1000 Hz
//analogWrite(D12,umotorf);//D12
digitalWrite(D4, HIGH);
delayMicroseconds(umotortt);//1 - 19990
//delay(umotortt);
digitalWrite(D4, LOW);
//delay(umotortt);
delayMicroseconds(40000 - umotortt);//1 - 19990
}
