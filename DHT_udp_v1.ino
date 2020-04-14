#include "DHT.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h" 
//IPAddress : 192.168.0.170
IPAddress ClientIP_1(192,168,0,121);
#define udp_port 90
WiFiUDP udp;
char ssid[] = "TP-Link_5F54";
char pass[] = "xxx";
char packetBuffer[255]; // char buffer to hold incoming packet

DHT dht;

void setup()
{
  Serial.begin(115200);
  WiFi.disconnect(true);
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
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");

  dht.setup(D4); // data pin 2
}

void loop()
{
  //delay(dht.getMinimumSamplingPeriod());

  byte humidity = dht.getHumidity();
  byte temperature = dht.getTemperature();
    udp.beginPacket(ClientIP_1,udp_port);
    udp.write(35);
    udp.write(humidity);
    udp.write(temperature);
    udp.endPacket();
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity);
  Serial.print("\t\t");
  Serial.print(temperature);
  Serial.print("\t\t");
  Serial.println(dht.toFahrenheit(temperature), 1);
  delay(2000);
}

