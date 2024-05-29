#include <Wifi.h>

const char* ssid = "OnePlus" ;
const char* password = "719622Aa";

WifiServer server(80);

int led1 = 5 ;
int led2 = 6;
void setup()
{
  Serial.begin(115200);
  pinmode(led1 , OUTPUT);
  pinmode(led2 , OUTPUT);

  delay(20);
  Serial.println("Connecting to");
  Serial.println(ssid);

  WiFi.begin(ssid,password);

  while(WiFi.status()!=WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("wifi connected.");
  Serial.println("IP:");
  Serial.println(WiFi.localIP());

  server.begin();

}

void loop()
{
  
}