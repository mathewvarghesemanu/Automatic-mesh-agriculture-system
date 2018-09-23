#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "man";
const char* password = "firefox123";

void setup () {

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http1;  //Declare an object of class HTTPClient
    HTTPClient http2;  //Declare an object of class HTTPClient


    http1.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
    http2.begin("http://jsonplaceholder.typicode.com/users/1");  //Specify request destination
  
    
    int httpCode1 = http1.GET();                                                                  //Send the request
    int httpCode2 = http2.GET();
   
    if (httpCode1 > 0) { //Check the returning code

      String payload = http1.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    if (httpCode2 > 0) { //Check the returning code

      String payload = http2.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }

    
    http1.end();   //Close connection
    http2.end();   //Close connection


  }

  delay(30000);    //Send a request every 30 seconds

}
