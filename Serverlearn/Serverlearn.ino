#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* username = "123456";
const char* password = "12345678";

WebServer server(80);
WebSocketsServer webs = WebSocketsServer(81);

String webpage_1 = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Transparent Hover Effect</title>
    <style>
        body {
            display: flex;
            justify-content: center;
            align-items: center;
            height: 100vh;
            margin: 0;
            background-color: #f0f0f0;
            font-family: Arial, sans-serif;
        }

        .random-number-container {
            padding: 20px;
            border: 2px solid #ccc;
            border-radius: 10px;
            background-color: rgba(255, 255, 255, 0.7);
            text-align: center;
            transition: background-color 0.3s, transform 0.3s;
        }

        .random-number-container:hover {
            background-color: rgba(255, 255, 255, 0.9);
            transform: scale(1.05);
        }

        .random-number {
            font-size: 2rem;
            color: #333;
        }
    </style>
</head>
<body>
    <div class="random-number-container">
        <div class="random-number">
            <h1>Random number is: <span id='rand'>-</span></h1>
        </div>
    </div>
    <p><button type ='button' id ='BTN_SEND_BACK'>SEND INFO TO ESP32</button></p>
    <script>
        var ws;
        document.getElementById('BTN_SEND_BACK').addEventListener('click',button_send_back);
        function init() {
            ws = new WebSocket('ws://' + window.location.hostname + ':81/');
            ws.onmessage = function(event) {
                processCommand(event);
            };
        }
        function button_send_back(){
          ws.send('Sending Plain text but we can send other things too');
        }
        function processCommand(event) {
            document.getElementById('rand').innerHTML = event.data;
        }
        window.onload = function(event) { // Corrected typo here
            init();
        };
    </script>
</body>
</html>
)";

int interval = 1000;
unsigned long prevmillis = 0;

void setup() {
    Serial.begin(9600);
    WiFi.begin(username, password);
    Serial.println("Connecting");

    while (WiFi.status() != WL_CONNECTED) {
      if(Serial.available()>0)
  {
    WiFi.disconnect();
    Serial.println("Force Stopped");
    return;
  }
        Serial.print(".");
        delay(500);
    }

    Serial.print("Connected to IP: ");
    Serial.println(WiFi.localIP());

    server.on("/", []() {
        server.send(200, "text/html", webpage_1);
    });

    server.begin();
    webs.begin();
}

void loop() {
  if(Serial.available()>0)
  {
    WiFi.disconnect();
  }
    server.handleClient();
    webs.loop();
    unsigned long currmillis = millis();
    if (currmillis - prevmillis > interval) {
        String str = String(random(100));
        int str_len = str.length() + 1;
        char char_array[str_len];
        str.toCharArray(char_array, str_len);
        webs.broadcastTXT(char_array); // This accepts only char array so we have to convert string into char array

        prevmillis = currmillis;
    }
}
