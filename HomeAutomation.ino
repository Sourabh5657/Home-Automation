#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// WiFi credentials
#define WIFI_SSID "Your_WiFi_SSID"
#define WIFI_PASS "Your_WiFi_Password"

// Blynk authorization token
char auth[] = "Your_Blynk_Auth_Token";

// Pin definitions
const int trigPin = D6;    // Ultrasonic trigger
const int echoPin = D7;    // Ultrasonic echo
const int buzzPin = D8;    // Buzzer
const int LED1 = RX;       // Indicator LED
const int flameSensorPin = A0; // MQ2 analog pin (or digital, adjust if needed)
const int ldrPin = A0;     // LDR analog pin (if different, set accordingly)
const int irSensorPin = D5; // IR sensor pin (change as per your wiring)

const int relayPin = D1;   // Relay pin controlling an appliance
const int manualSwitchPin = D2; // Manual switch input pin

// Variables for manual switch debounce
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 200;
bool lastSwitchState = HIGH;
bool relayState = LOW;

BlynkTimer timer;

// Function to measure distance using ultrasonic sensor
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2; // Distance in cm
  return distance;
}

// Function to check sensors and update states
void checkSensors() {
  // Intruder detection with ultrasonic sensor
  long distance = measureDistance();
  if (distance > 0 && distance <= 10) {  // Adjust threshold as needed
    digitalWrite(buzzPin, HIGH);
    digitalWrite(LED1, HIGH);
    Blynk.notify("Alert! Intruder detected.");
  } else {
    digitalWrite(buzzPin, LOW);
    digitalWrite(LED1, LOW);
  }

  // Fire detection using flame sensor (MQ2)
  int flameValue = analogRead(flameSensorPin);  // Analog read
  if (flameValue > 400) { // Adjust threshold as per calibration
    digitalWrite(buzzPin, HIGH);
    digitalWrite(LED1, HIGH);
    Blynk.notify("Alert! Fire detected.");
  }

  // Automatic light control based on LDR (day/night)
  int lightLevel = analogRead(ldrPin);
  if (lightLevel < 300) { // Dark condition threshold (adjust)
    digitalWrite(relayPin, HIGH); // Turn ON bulb
    relayState = HIGH;
    Blynk.virtualWrite(V1, 1);
  } else {
    digitalWrite(relayPin, LOW); // Turn OFF bulb
    relayState = LOW;
    Blynk.virtualWrite(V1, 0);
  }
}

// Blynk widget to control relay manually (virtual pin V0)
BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(relayPin, pinValue);
  relayState = pinValue;
}

// Check physical manual switch and toggle relay
void checkManualSwitch() {
  bool currentState = digitalRead(manualSwitchPin);
  if (currentState != lastSwitchState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentState != relayState) {
      relayState = currentState;
      digitalWrite(relayPin, relayState);
      Blynk.virtualWrite(V0, relayState);  // Sync Blynk button
    }
  }
  lastSwitchState = currentState;
}

void setup() {
  Serial.begin(115200);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzPin, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(relayPin, OUTPUT);
  pinMode(manualSwitchPin, INPUT_PULLUP);

  digitalWrite(relayPin, LOW);
  digitalWrite(buzzPin, LOW);
  digitalWrite(LED1, LOW);

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Blynk.begin(auth, WIFI_SSID, WIFI_PASS);

  // Timer to run checkSensors every 1 second
  timer.setInterval(1000L, checkSensors);
}

void loop() {
  Blynk.run();
  timer.run();
  checkManualSwitch();
}
