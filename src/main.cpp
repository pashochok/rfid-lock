#include <Arduino.h>
#include <Servo.h>
Servo myServo;
unsigned long previousMillis = 0;
unsigned long pinMillis = 0;

constexpr uint8_t SERVO_PIN   = 2;
const unsigned long interval = 2000;
void updateServo(uint32_t currentMillis);
void updateLed(uint32_t currentMillis);

void setup() {
  myServo.attach(SERVO_PIN);
  myServo.write(0);  // встановлюємо початкове положення серво
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  uint32_t currentMillis = millis();
updateServo(currentMillis);
updateLed(currentMillis);
}

void updateServo(uint32_t currentMillis) {
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    int currentAngle = myServo.read();
    int newAngle = (currentAngle == 0) ? 90 : 0;  // перемикаємо між 0 та 90 градусами
    if (newAngle != currentAngle) {
       myServo.write(newAngle);
    }
   
  }
 
}

void updateLed(uint32_t currentMillis) {
  if (currentMillis - pinMillis >= 300) {
    pinMillis = currentMillis;
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  }
}

