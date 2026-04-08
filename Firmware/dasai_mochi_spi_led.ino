#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>

// Dasai Mochi SPI wiring (ESP32-C3 Super Mini)
#define PIN_CLK   4   // SCK
#define PIN_MOSI  6   // D1 / MOSI
#define PIN_CS    7   // CS
#define PIN_DC    5   // D/C
#define PIN_RESET 3   // OLED reset

#ifndef LED_BUILTIN
#define LED_BUILTIN 8
#endif

const uint8_t PIN_LED = LED_BUILTIN;

U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(
  U8G2_R0,
  PIN_CS,
  PIN_DC,
  PIN_RESET
);

void drawStatus(const char* line1, const char* line2) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tf);
  u8g2.drawStr(0, 16, "Dasai Mochi SPI");
  u8g2.drawStr(0, 36, line1);
  u8g2.drawStr(0, 54, line2);
  u8g2.sendBuffer();
}

void setup() {
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);

  SPI.begin(PIN_CLK, -1, PIN_MOSI, PIN_CS);
  u8g2.begin();

  drawStatus("OLED init OK", "LED blink test");
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  drawStatus("LED: ON", "OLED should show text");
  delay(500);

  digitalWrite(PIN_LED, LOW);
  drawStatus("LED: OFF", "OLED should show text");
  delay(500);
}
