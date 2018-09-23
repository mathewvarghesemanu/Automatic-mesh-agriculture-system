#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>


int motorpin = D4;
 int flag = 0;


ESP8266WebServer server(80);

const char* ssid = "manu";
const char* password =  "ambalathil1234";

IPAddress ip(192, 168, 43, 57); //set static ip
IPAddress gateway(192, 168, 43, 1); //set getteway
IPAddress subnet(255, 255, 255, 0);//set subnet


void setup() {
  pinMode(motorpin, OUTPUT);
  digitalWrite(motorpin, LOW);
  Serial.begin(115200);
  WiFi.begin(ssid, password);  //Connect to the WiFi network

  while (WiFi.status() != WL_CONNECTED) {  //Wait for connection

    delay(500);
    Serial.println("Waiting to connect...");
    // WiFi.config(ip, gateway, subnet);
  }

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP

  server.on("/", handleBody); //Associate the handler function to the path

  server.begin(); //Start the server
  Serial.println("Server listening");

}

void loop() {

  server.handleClient(); //Handling of incoming requests

}

void handleBody() { //Handler for the body path

  if (server.hasArg("mode") == false) { //Check if body received

    server.send(200, "text/plain", "Body not received");
    return;

  }

  String message = "Body received:\n";
  message += server.arg("mode");
  message += "\n";
 
  if (server.arg("mode") == "1")
  {flag = 1;
    digitalWrite(motorpin, HIGH);
  }
  else
  {flag = 0;
    digitalWrite(motorpin, LOW);
  }
  server.send(200, "text/plain", message);
  Serial.println(message);
}
