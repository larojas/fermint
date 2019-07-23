
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

#include "oled.h"

// Singleton (naive), statically initialized.
static U8G2_SSD1327_MIDAS_128X128_F_4W_HW_SPI u8g2(
    U8G2_R0, OLED_CS_PIN, OLED_DC_PIN, OLED_RESET_PIN);

#ifdef OLED_DEBUG_ENABLE
char OLED_DEBUG_STR[OLED_DEBUG_STR_SZ];
#endif // OLED_DEBUG_ENABLE


Oled::Oled()
  : pitch_(10), row_(0), col_(0), debug_(false)
{
  OLED_DEBUG_STR[0] = '\0';
}

void Oled::begin() {
  u8g2.begin();
}

void Oled::clear(bool clearDisplay) {
  u8g2.clearBuffer();
  if (clearDisplay) show();
}

void Oled::print_at(const char* str, uint8_t x, uint8_t y) {
  u8g2.drawStr(x, y, str);
  col_ = x;
  row_ = y;
}

void Oled::print(const char* str) {
  u8g2.drawStr(col_, row_, str);
}

void Oled::print_next(const char* str) {
  row_ += pitch_;
  print(str);
}



void Oled::set_font(OledFont font) {
  switch(font) {
  case FONT_SMALL:
    u8g2.setFont(u8g2_font_t0_11_tr);
    break;
  case FONT_BIG:
    u8g2.setFont(u8g2_font_crox3h_tr);
    break;
  case FONT_AXIS:
    u8g2.setFont(u8g2_font_profont10_mn);
    break;
  case FONT_BIGNUM:
    u8g2.setFont(u8g2_font_7x14_mn);
    break;
  }
  pitch_ = u8g2.getAscent() - u8g2.getDescent();
  mode(OLED_WHITE);
}

uint8_t Oled::get_font_height() {
  return pitch_;
}


void Oled::vline(uint8_t x, uint8_t y, uint8_t len) {
  u8g2.drawVLine(x, y, len);
}

void Oled::hline(uint8_t x, uint8_t y, uint8_t len) {
  u8g2.drawHLine(x, y, len);
}

void Oled::line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
  u8g2.drawLine(x1, y1, x2, y2);
}


void Oled::set_pixel(uint8_t x, uint8_t y) {
  u8g2.drawPixel(x, y);
}

void Oled::mode(OledColor color) {
  u8g2.setDrawColor(color);
}

void Oled::show() {
  if (debug_) {
    set_font(FONT_SMALL);
    mode(OLED_WHITE);
    print_at(OLED_DEBUG_STR, 0, 128);
  }
  u8g2.sendBuffer();
}

void Oled::debug_display(bool enable) {
  debug_ = enable;
}
