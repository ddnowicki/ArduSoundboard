#include <Adafruit_MCP23X17.h>
#include <Arduino.h>


TaskHandle_t RestartByBtn;

Adafruit_MCP23X17 mcp;

#define BUZZER_PIN 19

void RestartByBtnCode(void* parameter) {
  for (;;) {
    if (!mcp.digitalRead(7)) {
      Serial.println("Restarting...");
      ESP.restart();
    }
  }
}

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  xTaskCreatePinnedToCore(RestartByBtnCode, "RestartByBtn", 10000, NULL, 0,
                          &RestartByBtn, 0);

  Serial.begin(115200);
  Wire.begin();
  Serial.println("MCP23xxx Combo Test!");

  if (!mcp.begin_I2C(0x20)) ESP.restart();

  for (uint8_t i = 0; i < 8; i++) mcp.pinMode(i, INPUT_PULLUP);

  Serial.println("Looping...");

}

void loop() {}