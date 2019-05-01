#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "LineNotify.h"

const String TOKEN = "vOhcPRrN8mnO7urMx5vxLy2NyZEb8NwyIQy2hYacBDb";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("CE-ESL","ceeslonly");
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
  sendMessage(TOKEN,"Hello");
  delay(5000);
}

void Line_Notify(String message) {
  String msg = String("message=") + message;

  axTLS::WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;
  }

  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Authorization: Bearer " + String(TOKEN) + "\r\n";
  req += "Content-Length: " + String(msg.length()) + "\r\n";
  req += "\r\n";
  req +=  msg;

  client.print(req);

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }

  Serial.println();
  Serial.println("closing connection");
}