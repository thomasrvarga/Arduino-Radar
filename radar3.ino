#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo radarServo;

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 6;

LiquidCrystal_I2C lcd(0x27, 16, 2);

int angle = 30;
int step = 2;        // degrees per step (smaller = smoother but slower)
bool sweepForward = true;

long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2;

  // Return 0 if out of range
  if (distance <= 0 || distance > 400) return 0;
  return distance;
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radarServo.attach(servoPin);
  radarServo.write(30);
  delay(500);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Radar Starting..");
  delay(1000);
  lcd.clear();
}

void loop() {
  radarServo.write(angle);
  delay(30); // let servo settle

  long distance = getDistance();

  // Send over serial: "angle,distance"
  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance);

  // Update LCD
  lcd.setCursor(0, 0);
  lcd.print("Angle: ");
  lcd.print(angle);
  lcd.print("   ");

  lcd.setCursor(0, 1);
  if (distance > 0 && distance < 50) {
    lcd.print("ALERT: ");
    lcd.print(distance);
    lcd.print("cm  ");
  } else if (distance > 0) {
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print("cm  ");
  } else {
    lcd.print("Out of range    ");
  }

  // Sweep logic (shifted window: 30 to 180)
  if (sweepForward) {
    angle += step;
    if (angle >= 180) {
      angle = 180;
      sweepForward = false;
    }
  } else {
    angle -= step;
    if (angle <= 30) {
      angle = 30;
      sweepForward = true;
    }
  }
}
