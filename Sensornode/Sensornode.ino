#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN D4
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
int inputpin = A0;
int Moist;
float temp;
float Hum;
const char* ssid = "manu";
const char* password = "ambalathil1234";

void setup () {
  dht.begin();
  pinMode(inputpin, INPUT);
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(1000);
    Serial.print("Connecting..");

  }
  delayMS = sensor.min_delay / 1000;
}

void loop() {
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float Temp = event.temperature;

  dht.humidity().getEvent(&event);
  float Hum = event.relative_humidity;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("http://192.168.43.200:5000/node1?Hum="+ String(Hum)); //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println('a');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('b');
    }
    http.begin("http://192.168.43.200:5000/node2?Temp="+ String(Temp)); //Specify request destination
    httpCode = http.GET();                                                                  //Send the request
    Serial.println('c');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('d');
    }
    Moist = analogRead(inputpin);
    http.begin("http://192.168.43.200:5000/node3?Mois="+ String(Moist)); //Specify request destination
    httpCode = http.GET();                                                                  //Send the request
    Serial.println('e');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);             //Print the response payload
      Serial.println('b');
    }
    http.end();   //Close connection

  }

  delay(3000);    //Send a request every 30 seconds

}
