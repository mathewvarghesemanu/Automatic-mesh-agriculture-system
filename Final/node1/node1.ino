#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "manu";
const char* password = "ambalathil1234";

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
   char dhtvalue='5';
    http1.begin("http://192.168.43.200:5000/node1?Hum="+dhtvalue);  //Specify request destination
   
  
    
    int httpCode1 = http1.GET();                                                                  //Send the request

   
    if (httpCode1 > 0) { //Check the returning code

      String payload = http1.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }else{
      Serial.println("not working");
    }

    
    http1.end();   //Close connection
  

  }

  delay(30000);    //Send a request every 30 seconds

}
