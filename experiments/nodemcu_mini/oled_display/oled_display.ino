#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0
Adafruit_SSD1306 OLED(OLED_RESET);

void setup() {
    OLED.begin();
    OLED.clearDisplay();

    // put text into buffer:
    OLED.setTextWrap(false);
    OLED.setTextSize(1);
    OLED.setTextColor(WHITE);
    OLED.setCursor(0, 0);
    OLED.println("Hello World");

    // display buffer:
    OLED.display();

    // make display scroll:
    OLED.startscrollleft(0x00, 0x0F);
}

void loop() {

}