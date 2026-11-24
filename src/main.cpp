// #include <Arduino.h>
// #include <SPI.h>
// #include <MFRC522.h>

// MFRC522 rfid(10, 9);  // SS, RST

// void setup() {
//   Serial.begin(9600);
//   SPI.begin();
//   rfid.PCD_Init();
//   rfid.PCD_DumpVersionToSerial();  // має показати версію чипа, наприклад 0x92
// }

// void loop() {
//   if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
//   Serial.print("UID:");
//   for (byte i = 0; i < rfid.uid.size; i++) {
//     Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(rfid.uid.uidByte[i], HEX);
//   }
//   Serial.println();
//   rfid.PICC_HaltA();
// }
// #include <Arduino.h>
// #include <LiquidCrystal.h>

// LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);  // RS, E, D4, D5, D6, D7

// void setup() {
//   lcd.begin(16, 2);
//   lcd.print("Hello, Pavlo!");
// }

// void loop() {
//   lcd.setCursor(0, 1);
//   lcd.print(millis() / 1000);
// }



// constexpr uint8_t ROW_PINS[4] = {6, 7, 8, 9};
// constexpr uint8_t COL_PINS[3] = {5, 4, 3};

// const uint8_t pins[8] = {2, 3, 4, 5, 6, 7, 8, 9};

// void setup() {
//   Serial.begin(9600);
//   for (uint8_t p : pins) pinMode(p, INPUT_PULLUP);
//   Serial.println("Press keys one by one");
// }

// void loop() {
//   for (uint8_t i = 0; i < 8; i++) {
//     pinMode(pins[i], OUTPUT);       // "опускаємо" один вивід у LOW
//     digitalWrite(pins[i], LOW);
//     for (uint8_t j = i + 1; j < 8; j++) {
//       if (digitalRead(pins[j]) == LOW) {  // натиснута кнопка замкнула i та j
//         Serial.print("keypad pin ");
//         Serial.print(i + 1);
//         Serial.print(" + ");
//         Serial.println(j + 1);
//         delay(300);
//       }
//     }
//     pinMode(pins[i], INPUT_PULLUP);  // повертаємо назад
//   }
// }
// #include <Arduino.h>
// #include <Servo.h>
// Servo myServo;
// unsigned long previousMillis = 0;
// unsigned long pinMillis = 0;

// constexpr uint8_t SERVO_PIN   = 2;
// const unsigned long interval = 2000;
// void updateServo(uint32_t currentMillis);
// void updateLed(uint32_t currentMillis);

// void setup() {
//   myServo.attach(SERVO_PIN);
//   myServo.write(0);  // встановлюємо початкове положення серво
//   pinMode(LED_BUILTIN, OUTPUT);
// }

// void loop() {
//   uint32_t currentMillis = millis();
// updateServo(currentMillis);
// updateLed(currentMillis);
// }

// void updateServo(uint32_t currentMillis) {
//   if (currentMillis - previousMillis >= interval) {
//     previousMillis = currentMillis;
//     int currentAngle = myServo.read();
//     int newAngle = (currentAngle == 0) ? 90 : 0;  // перемикаємо між 0 та 90 градусами
//     if (newAngle != currentAngle) {
//        myServo.write(newAngle);
//     }
   
//   }
 
// }

// void updateLed(uint32_t currentMillis) {
//   if (currentMillis - pinMillis >= 300) {
//     pinMillis = currentMillis;
//     digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
//   }
// }


#include <Arduino.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire wire(4, 3, 5);  // DAT, CLK, RST
RtcDS1302<ThreeWire> rtc(wire);
unsigned long previousMillis = 0;

void setup() {
  Serial.begin(9600);
  rtc.Begin();
  rtc.SetIsWriteProtected(false);
  rtc.SetIsRunning(true);
  RtcDateTime compiled(__DATE__, __TIME__);  // час збірки прошивки
  if (!rtc.IsDateTimeValid() || rtc.GetDateTime() < compiled) {
    rtc.SetDateTime(compiled);
  }
}

void loop() {
  uint32_t currentMillis = millis();
  RtcDateTime now = rtc.GetDateTime();
  int seconds = now.Second();
  char buffer[20];
  if(currentMillis - previousMillis >= 1000) {
    previousMillis = currentMillis;
    snprintf(buffer, sizeof(buffer), "%04u-%02u-%02u %02u:%02u:%02u",
           now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), seconds);
    Serial.println(buffer);
  }
}