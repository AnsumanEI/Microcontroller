#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "OnePlus";
const char* password = "719622Aa";

WebServer server(80);

const int relayPin = 13;

void handleRoot() {
  server.send(200, "text/html", "<h1>You are connected</h1><p><a href=\"/on\"><button>ON</button></a> <a href=\"/off\"><button>OFF</button></a></p>");
}

void handleOn() {
  digitalWrite(relayPin, HIGH); 
  server.send(200, "text/html", "<h1>Bulb is ON</h1><p><a href=\"/\"><button>Home</button></a></p>");
}

void handleOff() {
  digitalWrite(relayPin, LOW);
  server.send(200, "text/html", "<h1>Bulb is OFF</h1><p><a href=\"/\"><button>Home</button></a></p>");
}

void setup() {
  Serial.begin(115200);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH); // Ensure relay is off initially

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  server.on("/", handleRoot);
  server.on("/on", handleOn);
  server.on("/off", handleOff);

  server.begin();
  Serial.print("HTTP server started , IP:");
  Serial.println(WiFi.localIP());

}

void loop() {
  server.handleClient();
}
