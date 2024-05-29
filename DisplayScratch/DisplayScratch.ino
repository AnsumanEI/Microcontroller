#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_ADDRESS 0x3c

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH , SCREEN_HEIGHT , &Wire ,OLED_RESET);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
if(!display.begin(SSD1306_SWITCHCAPVCC,SCREEN_ADDRESS))
{
  Serial.println(F("FAILED ALLOCATION"));
  for(;;);
}
display.display();
delay(1000);
display.clearDisplay();

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("HELLO STARTED");
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println("Hello From Ansuman");
  delay(1000);

}
