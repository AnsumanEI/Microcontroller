
#include <Wire.h>
#include <MPU9250_asukiaaa.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "OnePlus";
const char* password = "719622Aa";
const char* serverName = "http://192.168.21.105:3000/data"; // Replace with your server's IP and port
const char* apiKey = "L4ZA2L24TO09SB81";

MPU9250_asukiaaa myIMU;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  myIMU.setWire(&Wire);
  myIMU.beginAccel();
  myIMU.beginGyro();
  myIMU.beginMag();
}

void loop() {
  myIMU.accelUpdate();
  myIMU.gyroUpdate();
  myIMU.magUpdate();

  float accelX = myIMU.accelX();
  float accelY = myIMU.accelY();
  float accelZ = myIMU.accelZ();

  float gyroX = myIMU.gyroX();
  float gyroY = myIMU.gyroY();
  float gyroZ = myIMU.gyroZ();

  // Send data to local server
  String postDataLocal = "{\"accelX\":" + String(accelX) + ",\"accelY\":" + String(accelY) + ",\"accelZ\":" + String(accelZ) +
                    ",\"gyroX\":" + String(gyroX) + ",\"gyroY\":" + String(gyroY) + ",\"gyroZ\":" + String(gyroZ) 
                    ;

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient httpLocal;
    httpLocal.begin(serverName);
    httpLocal.addHeader("Content-Type", "application/json");
    int httpResponseCodeLocal = httpLocal.POST(postDataLocal);

    if (httpResponseCodeLocal > 0) {
      Serial.print("Local server response code: ");
      Serial.println(httpResponseCodeLocal);
    } else {
      Serial.print("Error on sending data to local server: ");
      Serial.println(httpResponseCodeLocal);
    }
    httpLocal.end();
  } else {
    Serial.println("WiFi not connected");
  }

  // Send data to ThingSpeak
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient httpThingSpeak;
    String url = "http://api.thingspeak.com/update?api_key=" + String(apiKey) +
                 "&field1=" + String(accelX) + "&field2=" + String(accelY) + "&field3=" + String(accelZ) +
                 "&field4=" + String(gyroX) + "&field5=" + String(gyroY) + "&field6=" + String(gyroZ) 
                 ;

    httpThingSpeak.begin(url);
    int httpResponseCodeThingSpeak = httpThingSpeak.GET();

    if (httpResponseCodeThingSpeak == 200) {
      Serial.println("Data sent to ThingSpeak");
    } else {
      Serial.print("Error on sending data to ThingSpeak: ");
      Serial.println(httpResponseCodeThingSpeak);
    }
    httpThingSpeak.end();
  }

  delay(1000); 
}
