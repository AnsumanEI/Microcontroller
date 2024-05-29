
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server(80);

const char* ssid = "OnePlus";
const char* password = "719622Aa";

const int ledpin = 5;
unsigned long prevmilli = 0;
const long interval = 1000 ;

void handleRoot() {
  server.send(200, "text/html", "<h1>Hello from Ansuman!</h1>");
  Serial.println("handleRoot function called");
  
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
pinMode(ledpin, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot); // When the root URL is used, the handleRoot function is called
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle incoming requests from the clients
  unsigned long currentmilli = millis();
  if(currentmilli - prevmilli >= interval)
  {
    prevmilli = currentmilli;
    digitalWrite(ledpin,!digitalRead(ledpin));
  }
}
