#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Create an instance of the sensor with a unique ID
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

// Create an instance of the display
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Define the I2C address for the OLED display
#define SCREEN_ADDRESS 0x3C

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for serial port to be available

  

  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed")); //flash memory stored
    for (;;);//infinite loop to stop execution 
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
}

void loop() {
 

  display.clearDisplay(); // Clear the display buffer
    display.setTextSize(1);      // Normal 1:1 pixel scale
    display.setTextColor(SSD1306_WHITE); // Draw white text
    display.setCursor(0, 0);     // Start at top-left corner
    display.print("Pressure: ");
    display.print(pressure);
    display.println(" hPa");

    // Calculate and display altitude
    float seaLevelPressure = 1013.25;
    float altitude = bmp.pressureToAltitude(seaLevelPressure, event.pressure);
    display.print("Altitude: ");
    display.print(altitude);
    display.println(" m");

    // Read and display temperature
    float temperature;
    bmp.getTemperature(&temperature);
    display.print("Temperature: ");
    display.print(temperature);
    display.println(" *C");

    display.display(); // Show the display buffer on the screen
  } else {
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Sensor error");
    display.display();
  }

  delay(2000); // Delay for 2 seconds before the next reading
}

