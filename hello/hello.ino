#include <Servo.h>
byte xldr1 = A0;
byte xldr2 = A1;
byte yldr1 = A2;
byte yldr2 = A3;

int xled1 = 13;
int xled2 = 11;
int yled1 = 12;
int yled2 = 10;

int xp1, xp2;
int yp1, yp2;

byte xpin = 3;
byte ypin = 2;
Servo xservo, yservo;

int xangle = 0;
int yangle = 20;

int xlimithigh = 180;
int xlimitlow = 0;

int ylimithigh = 140;
int ylimitlow = 20;
int max1, max2, max3;
void setup() {
  xservo.attach(xpin);
  yservo.attach(ypin);

  xservo.write(xangle);
  yservo.write(yangle);

  pinMode(xled1, OUTPUT);
  pinMode(xled2, OUTPUT);
  pinMode(yled1, OUTPUT);
  pinMode(yled2, OUTPUT);
}

void loop() {
  xp1 = analogRead(xldr1);
  xp2 = analogRead(xldr2);

  yp1 = analogRead(yldr1);
  yp2 = analogRead(yldr2);

  max1 = max(xp1, xp2);
  max2 = max(yp1, yp2);
  max3 = max(max1, max2);

  // Vertical servo control
  if (xp1 < max3 && yp1 < max3) {
    if (yangle > ylimitlow) {
      yangle -= 1;
    }
    digitalWrite(yled2, HIGH);
    delay(30);
    digitalWrite(yled2, LOW);
    yservo.write(yangle);
  }

  if (xp2 < max3 && yp2 < max3) {
    if (yangle < ylimithigh) {
      yangle += 1;
    }
    digitalWrite(yled1, HIGH);
    delay(30);
    digitalWrite(yled1, LOW);
    yservo.write(yangle);
  }

  // Horizontal servo control
  if (xp1 < max3 && xp2 < max3) {
    if (xangle < xlimithigh) {
      xangle += 1;
    }
    digitalWrite(xled2, HIGH);
    delay(30);
    digitalWrite(xled2, LOW);
    xservo.write(xangle);
  }

  if (yp1 < max3 && yp2 < max3) {
    if (xangle > xlimitlow) {
      xangle -= 1;
    }
    digitalWrite(xled1, HIGH);
    delay(30);
    digitalWrite(xled1, LOW);
    xservo.write(xangle);
  }

  delay(15); 
}
