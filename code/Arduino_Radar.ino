#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo radarServo;

const int trigPin  = 9;
const int echoPin  = 10;
const int servoPin = 6;

LiquidCrystal_I2C lcd(0x27, 16, 2);

// --- Tunable constants ---
const int DETECT_RANGE = 50;   // cm
const int SCAN_STEP    = 1;    // degrees per step
const int ANGLE_MIN    = 0;    // true servo start
const int ANGLE_MAX    = 180;  // true servo end
const int STEP_DELAY   = 20;   // ms between steps

// --- Sweep state ---
int angle = ANGLE_MIN;
bool sweepForward = true;

// --------------------------------------------------
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  long distance = duration * 0.034 / 2;
  if (distance <= 0 || distance > 400) return 0;
  return distance;
}

void updateLCD(int ang, long dist) {
  lcd.setCursor(0, 0);
  lcd.print("   SCANNING     ");

  lcd.setCursor(0, 1);
  if (dist > 0) {
    lcd.print("A:");
    lcd.print(ang);
    lcd.print(" D:");
    lcd.print(dist);
    lcd.print("cm   ");
  } else {
    lcd.print("No object       ");
  }
}

// --------------------------------------------------
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  radarServo.attach(servoPin);

  // Go directly to true 0 position
  radarServo.write(ANGLE_MIN);
  delay(1000);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Radar Starting..");
  delay(1000);
  lcd.clear();
}

// --------------------------------------------------
void loop() {
  radarServo.write(angle);
  delay(STEP_DELAY);

  long distance = getDistance();

  Serial.print(angle);
  Serial.print(",");
  Serial.println(distance);

  updateLCD(angle, distance);

  // Sweep 0 -> 180 -> 0
  if (sweepForward) {
    angle += SCAN_STEP;
    if (angle >= ANGLE_MAX) {
      angle = ANGLE_MAX;
      sweepForward = false;
    }
  } else {
    angle -= SCAN_STEP;
    if (angle <= ANGLE_MIN) {
      angle = ANGLE_MIN;
      sweepForward = true;
    }
  }
}
