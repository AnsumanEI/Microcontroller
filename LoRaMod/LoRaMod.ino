#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

// LoRa pins
#define LORA_SCK 18
#define LORA_MISO 19
#define LORA_MOSI 23
#define LORA_CS 5 //chip select NSS
#define LORA_RST 14
#define LORA_IRQ 2 //digital io D101

// DHT sensor pin and type
#define DHTPIN 27
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize DHT sensor
  dht.begin();

  // Initialize LoRa
  SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setPins(LORA_CS, LORA_RST, LORA_IRQ);

  if (!LoRa.begin(865E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  // Read temperature and humidity from DHT sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed and exit early
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Display data on Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Prepare data to send
  String data = "Humidity: " + String(humidity) + " %\tTemperature: " + String(temperature) + " *C";

  // Send data via LoRa
  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();

  // Wait for a minute before sending again
  delay(600);
}
