#include <BluetoothSerial.h>
#include "DHT.h"

#define dhtPin 27
#define DHTTYPE DHT11

DHT dht(dhtPin, DHTTYPE);
BluetoothSerial SerialBT; 

void setup() {
  Serial.begin(115200);
  SerialBT.begin("DHT11"); 
  dht.begin();
}

void loop() {
 
  float temperature = dht.readTemperature(); // Read temperature value in 
  float humidity = dht.readHumidity(); // Read humidity value

  if (isnan(temperature) || isnan(humidity)) {
     Serial.println("Failed to read from DHT sensor!");
     SerialBT.println("Failed to read from DHT sensor!");
    return;
  } 
    SerialBT.print("Temperature: ");
    SerialBT.print(temperature);
    SerialBT.print(" °C\t");
    SerialBT.print("Humidity: ");
    SerialBT.print(humidity);
    SerialBT.println(" %");
    

    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print(" °C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

     delay(2000);
}