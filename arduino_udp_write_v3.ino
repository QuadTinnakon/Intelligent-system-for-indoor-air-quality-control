#include "ESP8266WiFi.h"
#include "WiFiUdp.h" 
//IPAddress : 192.168.0.121
IPAddress ClientIP_1(192,168,0,142);
 
#define udp_port 90
WiFiUDP udp;

char ssid[] = "TP-Link_5F54";
char pass[] = "xxx";

char packetBuffer[255]; // char buffer to hold incoming packet
byte umotor = 0;

void setup()
{
Serial.begin(115200);
pinMode(LED_BUILTIN, OUTPUT);
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
  if (Serial.available() >= 4) {
    ////11 00 FF 03
    digitalWrite(LED_BUILTIN, LOW);
    int inByte1 = Serial.read();
    int inByte2 = Serial.read();
    int inByte3 = Serial.read();
    int inByte4 = Serial.read();
    //Serial1.write(inByte);
    udp.beginPacket(ClientIP_1,udp_port);
    udp.write(inByte1);
    udp.write(inByte2);
    udp.write(inByte3);
    udp.write(inByte4);
    udp.endPacket();
  }
  int buffer = udp.parsePacket();
if(buffer>2)
{
  int len = udp.read(packetBuffer, 3);
  Serial.write(packetBuffer[0]);
  Serial.write(packetBuffer[1]);
  Serial.write(packetBuffer[2]);
       //Serial.print(len);Serial.print("\t");
      //Serial.print(packetBuffer[0],DEC);Serial.print("\t");
      //Serial.print(packetBuffer[1],DEC);Serial.print("\t");
      //Serial.print(packetBuffer[2],DEC);Serial.print("\t");
      //Serial.print(packetBuffer[3],DEC);Serial.print("\t");
      //Serial.print(packetBuffer[4],DEC);Serial.print("\t");
      //Serial.println(packetBuffer[5]);
   udp.flush();
}
 digitalWrite(LED_BUILTIN, HIGH);
}
