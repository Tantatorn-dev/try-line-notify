#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "LineNotify.h"

const String TOKEN = "vOhcPRrN8mnO7urMx5vxLy2NyZEb8NwyIQy2hYacBDb";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Your WIFI name","Your WIFI password");
  Serial.println("connecting...");

  WiFi.mode(WIFI_STA);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("connected ip:");
  Serial.print( WiFi.localIP());
  Serial.println();

}

void loop() {
  // put your main code here, to run repeatedly:
  sendMessage(TOKEN,"Your message");
  delay(5000);
}
