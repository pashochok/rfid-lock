#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(10, 9);  // SS, RST

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  rfid.PCD_DumpVersionToSerial();  // має показати версію чипа, наприклад 0x92
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  Serial.print("UID:");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();
  rfid.PICC_HaltA();
}