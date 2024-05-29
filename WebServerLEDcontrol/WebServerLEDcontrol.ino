
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <WebServer.h>
#else
#error "Board not found"
#endif
int ledpin = 18;
const char* ssid = "OnePlus";
const char* password = "719622Aa";
String exit1  ;

WebServer server(80);

// HTML pages with improved styling
String loginPage = "<html>\
<head>\
  <style>\
    body { font-family: Arial, sans-serif; text-align: center; background-color: #f2f2f2; }\
    h1 { color: #333; }\
    form { display: inline-block; margin-top: 20px; }\
    input[type='text'], input[type='password'] { padding: 10px; margin: 10px; border: 1px solid #ccc; border-radius: 4px; width: 200px; }\
    input[type='submit'] { padding: 10px 20px; border: 1px solid #ccc; border-radius: 4px; background-color: rgba(0, 123, 255, 0.5); color: white; cursor: pointer; transition: background-color 0.3s; }\
    input[type='submit']:hover { background-color: rgba(0, 123, 255, 0.7); }\
  </style>\
</head>\
<body>\
  <h1>Login</h1>\
  <form action='/login' method='post'>\
    <input type='text' name='username' placeholder='Username'><br>\
    <input type='password' name='password' placeholder='Password'><br>\
    <input type='submit' value='Login'>\
  </form>\
</body>\
</html>";

String controlPage = "<html>\
<head>\
  <style>\
    body { font-family: Arial, sans-serif; text-align: center; background-color: #f2f2f2; }\
    h1 { color: #333; }\
    .button { padding: 15px 30px; border: 1px solid #ccc; border-radius: 4px; background-color: rgba(0, 123, 255, 0.5); color: white; cursor: pointer; transition: background-color 0.3s; margin: 10px; }\
    .button:hover { background-color: rgba(0, 123, 255, 0.7); }\
  </style>\
  <script>\
    function updateLEDStatus() {\
      var xhr = new XMLHttpRequest();\
      xhr.open('GET', '/status', true);\
      xhr.onreadystatechange = function () {\
        if (xhr.readyState == 4 && xhr.status == 200) {\
          document.getElementById('led-status').innerText = xhr.responseText;\
        }\
      };\
      xhr.send();\
    }\
    setInterval(updateLEDStatus, 100);\
  </script>\
</head>\
<body onload='updateLEDStatus()'>\
  <h1>NATIONAL INSTITUTE OF TECHNOLOGY , ROURKELA</h1>\
  <div id='led-status'>Loading...</div>\
  <form action='/control' method='post'>\
    <input type='submit' name='LED' value='ON' class='button'>\
    <input type='submit' name='LED' value='OFF' class='button'>\
  </form>\
</body>\
</html>";

String incorrectCredentialsPage = "<html>\
<head>\
  <style>\
    body { font-family: Arial, sans-serif; text-align: center; background-color: #f2f2f2; }\
    h1 { color: #333; }\
    a { color: #007BFF; text-decoration: none; }\
    a:hover { text-decoration: underline; }\
  </style>\
</head>\
<body>\
  <h1>Login Failed</h1>\
  <p>Invalid username or password. Please try again.</p>\
  <a href='/'>Go back to login</a>\
</body>\
</html>";

// Correct username and password
const char* correctUsername = "admin";
const char* correctPassword = "password";

// Handle the root path, display the login page
void handleRoot() {
  server.send(200, "text/html", loginPage);
}

// Handle the login action
void handleLogin() {
  if (server.method() == HTTP_POST) {
    String username = server.arg("username");
    String password = server.arg("password");

    if (username == correctUsername && password == correctPassword) {
      server.send(200, "text/html", controlPage);
    } else {
      server.send(401, "text/html", incorrectCredentialsPage);
    }
  } else {
    server.send(405, "text/html", "<html><body>Method Not Allowed</body></html>");
  }
}

// Handle the control action, turn the LED on or off
void handleControl() {
  if (server.method() == HTTP_POST) {
    String ledState = server.arg("LED");

    if (ledState == "ON") {
      digitalWrite(ledpin, HIGH);
      server.send(200, "text/html", controlPage);
    } else if (ledState == "OFF") {
      digitalWrite(ledpin, LOW);
      server.send(200, "text/html", controlPage);
    } else {
      server.send(400, "text/html", "<html><body>Bad Request</body></html>");
    }
  } else {
    server.send(405, "text/html", "<html><body>Method Not Allowed</body></html>");
  }
}

// Handle the status request, send the current LED status
void handleStatus() {
  if (digitalRead(ledpin) == HIGH) {
    server.send(200, "text/plain", "LED is ON");
  } else {
    server.send(200, "text/plain", "LED is OFF");
  }
}

// Setup the ESP8266
void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  digitalWrite(ledpin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/login", handleLogin);
  server.on("/control", handleControl);
  server.on("/status", handleStatus);

  server.begin();
  Serial.println("HTTP server started");
}

// Main loop
void loop() {
  server.handleClient();
  if(Serial.available()>0)
  {
      WiFi.disconnect();
  }
}
