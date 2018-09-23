#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
int inputpin = A0;
const char* ssid = "manu";
const char* password = "ambalathil1234";
int inputvalue;
void setup () {

  pinMode(inputpin, INPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
    inputvalue = analogRead(inputpin);
    http.begin("http://192.168.43.200:5000/node1?",inputvalue);  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println('a');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('b');
    }

    http.end();   //Close connection

  }

  delay(3000);    //Send a request every 30 seconds

}
