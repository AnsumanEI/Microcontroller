const int sensorPin = 2; //D4
void setup() {
  Serial.begin(9600); 
  pinMode(sensorPin, INPUT); 
}

void loop() {
  int sensorValue = analogRead(sensorPin); 
  float voltage = sensorValue * (3.3 / 4095.0); 
  float ppm = (voltage - 0.4) * 2000.0; 
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  Serial.print(" - Voltage: ");
  Serial.print(voltage);
  Serial.print("V - CO Concentration: ");
  Serial.print(ppm);
  Serial.println(" ppm");

  delay(1000); 
}
