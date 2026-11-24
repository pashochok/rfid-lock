
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