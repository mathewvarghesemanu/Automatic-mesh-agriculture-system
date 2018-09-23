#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            2

#define DHTTYPE           DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

const char* ssid = "manu";
const char* password = "ambalathil1234";

void setup () {
  sensor_t sensor;
  dht.begin();
  dht.humidity().getSensor(&sensor);
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  dht.temperature().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }

}

void loop() {
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);

  float t = event.temperature; // Gets the values of the temperature
  dht.humidity().getEvent(&event);
  float h = event.relative_humidity; // Gets the values of the humidity

  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http1;  //Declare an object of class HTTPClient

    http1.begin("http://192.168.43.200:5000/node1?dht=" + char(t)); //Specify request destination



    int httpCode1 = http1.GET();                                                                  //Send the request


    if (httpCode1 > 0) { //Check the returning code

      String payload = http1.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload

    }


    http1.end();   //Close connection


  }

  delay(30000);    //Send a request every 30 seconds

}
