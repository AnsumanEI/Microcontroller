#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
int ledpin = 5;
const char* ssid = "OnePlus";
const char* password = "719622Aa";
int invalidcount =0;
ESP8266WebServer server(80);

String loginPage = "<html>\
                    <body>\
                      <h1>Login</h1>\
                      <form action='/login' method='post'>\
                        Username: <input type='text' name='username'><br>\
                        Password: <input type='password' name='password'><br>\
                        <input type='submit' value='Login'>\
                      </form>\
                    </body>\
                    </html>";

String controlPage = "<html>\
                      <body>\
                        <h1>LED Control</h1>\
                        <form action='/control' method='post'>\
                          <input type='submit' name='LED' value='OF1'>\
                          <input type='submit' name='LED' value='ON1'>\
                        </form>\
                      </body>\
                      </html>";
String invalidcred = "<html>\
                      <body>\
                        <h1>Invalid Cred</h1>\
                        <form action='/invalidcred' method='delete'>\
                          <input type='submit' name='INVC' value='IC'>\
                        </form>\
                      </body>\
                      </html>";

const char* correctUsername = "1";
const char* correctPassword = "1";

void handleRoot() {
  server.send(200, "text/html", loginPage);
}

void handleLogin() {
  if (server.method() == HTTP_POST) {
    String username = server.arg("username");
    String password = server.arg("password");

    if (username == correctUsername && password == correctPassword && invalidcount<3) {
      server.send(200, "text/html", controlPage);
    } else {
      server.send(401, "text/html", "<html><body>Invalid credentials</body></html>");
      invalidcount+=1;
      if (invalidcount<=3) {
      server.send(302 , "text/html" , loginPage);
      }
      else{
        server.send(401 ,"text/html" , invalidcred);
      }
      
    }
  } else {
    server.send(405, "text/html", "<html><body>Method Not Allowed</body></html>");
  }
}

void handleControl() {
  if (server.method() == HTTP_POST) {
    String ledState = server.arg("LED");

    if (ledState == "ON1") {
      digitalWrite(ledpin, HIGH);
      server.send(200, "text/html", "<html><body>LED is ON</body></html>");
    } else if (ledState == "OF1") {
      digitalWrite(ledpin, LOW);
      server.send(200, "text/html", "<html><body>LED is OFF</body></html>");
    } else {
      server.send(400, "text/html", "<html><body>Bad Request</body></html>");
    }
  } else {
    server.send(405, "text/html", "<html><body>Method Not Allowed</body></html>");
  }
}

void invalidcontrol()
{
  if(invalidcount >= 3)
  {
    server.send(400 , "text/html" , "<html> <h1>You have exceeded the maximum attempts , the server will disconnect in 5 seconds</h1></html>");
    WiFi.disconnect();
  }
  else {

  }
}

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
WiFi.mode(WIFI_STA);
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
  server.on("/invalidcred" , invalidcontrol);
  server.on("/control", handleControl);
  

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}