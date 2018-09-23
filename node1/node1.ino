///DHT

#include <DHT.h>
#define DHTTYPE DHT11
#define DHTPIN  2



#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "manu";
const char* password = "ambalathil1234";
DHT dht(DHTPIN, DHTTYPE, 11);
float humidity, temp_f;
String webString="";



 


void setup () {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
    dht.begin();  

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient
  gettemperature();
  webString="Temperature: "+String((int)temp_f)+" F"; 
  
    http.begin("http://192.168.43.200:5000/node1?Hum=5");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println('a');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('b');
    }


     gettemperature();           // read sensor
    webString="Humidity: "+String((int)humidity)+"%";
    

    http.end();   //Close connection

  }

  delay(3000);    //Send a request every 30 seconds

}
