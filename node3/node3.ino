#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN D4
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
float temp;
float Hum;
const char* ssid = "manu";
const char* password = "ambalathil1234";

void setup () {
  dht.begin();
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


HTTPClient http2;
http2.begin("http://jsonplaceholder.typicode.com/posts");
http2.addHeader("Content-Type", "application/x-www-form-urlencoded");
http2.POST("title=foo&body=bar&userId=1");
http2.writeToStream(&Serial);
http2.end();


void loop() {
  delay(delayMS);
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float Temp = event.temperature;

  dht.humidity().getEvent(&event);
  float Hum = event.relative_humidity;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;  //Declare an object of class HTTPClient

    http.begin("http://192.168.43.200:5000/node1?", Hum); //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
    Serial.println('a');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('b');
    }
    http.begin("http://192.168.43.200:5000/node2?", Temp); //Specify request destination
    httpCode = http.GET();                                                                  //Send the request
    Serial.println('c');
    if (httpCode > 0) { //Check the returning code

      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
      Serial.println('d');
    }

    http.end();   //Close connection

  }

  delay(3000);    //Send a request every 30 seconds

}
