#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
 
const char* ssid = "hackathon";
const char* password = "fisat@2018";
const int httpsPort = 443;
const char* fingerprint = "5F F1 60 31 09 04 3E F2 90 D2 B0 8A 50 38 04 E8 37 9F BC 76";


void setup () {
 
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }
  WiFiClientSecure client;
  Serial.print("connecting to ");
  Serial.println(host);
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }
 
}
 
void loop() {
 
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
    HTTPClient http;  //Declare an object of class HTTPClient
 
      http.begin("https://us-central1-fisathackathon-7a617.cloudfunctions.net/createValuesGet?name=Object6&label=T"); //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println(httpCode);
    Serial.println(http.getString());
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('b');
    }
  
 
    http.end();   //Close connection
 
  }
 
  delay(3000);    //Send a request every 30 seconds
 
}
