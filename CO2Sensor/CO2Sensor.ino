
const int sensorPin = A0; // Analog input pin A0

void setup() {
  Serial.begin(115200);
  pinMode(sensorPin, INPUT);
}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue); // Print the sensor value to the serial monitor
  delay(1000);
}
