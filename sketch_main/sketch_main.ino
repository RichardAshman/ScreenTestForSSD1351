// Screen dimensions
#define SCREEN_WIDTH  128
#define SCREEN_HEIGHT 128

// Pins
// #define SCLK_PIN 2 // USE 13
// #define MOSI_PIN 3 // USE 11
#define DC_PIN   4
#define CS_PIN   5
#define RST_PIN  6

#define BUTTON_1_PIN 8
#define BUTTON_2_PIN 9

// Color definitions
#define	BLACK           0x0000
#define	RED             0xF800
#define	GREEN           0x07E0
#define WHITE           0xFFFF

// What can be displayed
#define LINE_CLOSED 1
#define UP_TRAIN_ON_LINE 2
#define DOWN_TRAIN_APPROACHING 3

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>

bool button1Pressed = false;
bool button2Pressed = false;
uint16_t currentImageDisplayed = 0;

// Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN); // Slower
Adafruit_SSD1351 tft = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN); // for UNO thats sclk = 13 and sid = 11

void setup() {
  pinMode(BUTTON_1_PIN, INPUT_PULLUP);
  pinMode(BUTTON_2_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  tft.begin();
  tft.fillRect(0, 0, 128, 128, BLACK);
}

void loop() {
  updateButtonState();

  if (button1Pressed && !button2Pressed && currentImageDisplayed != UP_TRAIN_ON_LINE) {
    upTrainOnLine();
  } else if (!button1Pressed && button2Pressed && currentImageDisplayed != DOWN_TRAIN_APPROACHING) {
    downTrainApproaching();
  } else if (!button1Pressed && !button2Pressed && currentImageDisplayed != LINE_CLOSED) {
    lineClosed();
  }
}

void updateButtonState() {
  button1Pressed = digitalRead(BUTTON_1_PIN) == LOW;
  button2Pressed = digitalRead(BUTTON_2_PIN) == LOW;
}

void lineClosed() {
  currentImageDisplayed = LINE_CLOSED;
  tft.fillScreen(WHITE);
  drawtext("LINE", BLACK, 30, 30, 3);
  drawtext("CLOSED", BLACK, 12, 75, 3);
}

void upTrainOnLine() {
  currentImageDisplayed = UP_TRAIN_ON_LINE;
  tft.fillScreen(GREEN);
  drawtext("UP", BLACK, 50, 10, 3);
  drawtext("TRAIN", BLACK, 20, 40, 3);
  drawtext("ON", BLACK, 50, 70, 3);
  drawtext("LINE", BLACK, 32, 100, 3);
}

void downTrainApproaching() {
  currentImageDisplayed = DOWN_TRAIN_APPROACHING;
  tft.fillScreen(RED);
  drawtext("DOWN", BLACK, 25, 25, 3);
  drawtext("TRAIN", BLACK, 20, 55, 3);
  drawtext("APP", BLACK, 2, 88, 2); // APPROACHING is split up for fewer px between the letters
  drawtext("ROACH", BLACK, 37, 88, 2);
  drawtext("I", BLACK, 94, 88, 2);
  drawtext("NG", BLACK, 103, 88, 2);
}

void drawtext(char *text, uint16_t color, uint16_t startX, uint16_t endX, uint8_t size) {
  tft.setTextSize(size);
  tft.setCursor(startX, endX);
  tft.setTextColor(color);
  tft.print(text);
}
