#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#include "pitches.hpp"


TaskHandle_t RestartByBtn;

Adafruit_MCP23X17 mcp;

#define BUZZER_PIN 19

int threeMelody[] = {
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, 
  NOTE_E4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, 
  NOTE_E4, NOTE_B4, NOTE_E4, NOTE_E4, NOTE_E4, NOTE_E4, 
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, 
  NOTE_E4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4

};

int threeDurations[] = {
  3, 3, 3, 3, 4, 3, 4, 
  5, 3, 3, 4, 3, 3, 3, 3, 4, 3, 4, 
  5, 4, 8, 8, 8, 8, 
  3, 3, 3, 3, 3, 4, 3, 4, 
  5, 3, 3, 4, 3, 3
};

int fourMelody[] = {
  NOTE_C4, REST, NOTE_E4, REST, NOTE_G4, NOTE_A4, NOTE_AS4,
  NOTE_C5, REST, NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST,
  NOTE_AS4, REST, NOTE_AS4, NOTE_C5, REST, NOTE_AS4, NOTE_A4, REST,
  REST,
  NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST, NOTE_AS4, REST, NOTE_E5,
  REST,

  NOTE_C5, REST, NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST,
  NOTE_AS4, REST, NOTE_AS4, NOTE_C5, REST, NOTE_AS4, NOTE_A4, REST,
  REST,
  NOTE_C5, REST, NOTE_AS4, REST, NOTE_A4, REST, NOTE_AS4, REST, NOTE_E4,
  REST,
};

int fourDurations[] = {
  4, 8, 4, 8, 4, 4, 4,
  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 8, 16, 8, 8, 16,
  4,
  8, 16, 8, 16, 8, 16, 8, 4, 8,
  4,

  8, 16, 8, 16, 8, 16, 8, 16,
  8, 16, 8, 8, 16, 8, 8, 16,
  4,
  8, 16, 8, 16, 8, 16, 8, 4, 8,
  1
};


int fiveMelody[] = {NOTE_C4,  NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
                    NOTE_C4,  NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
                    NOTE_C4,  NOTE_C4,

                    NOTE_C5,  NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_AS4,
                    NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4};

int fiveDurations[] = {4, 8, 4, 4, 4, 2, 4, 8, 4, 4, 4, 2, 4, 8,

                       4, 4, 4, 4, 4, 4, 8, 4, 4, 4, 2};

bool cancellation = false;

void RestartByBtnCode(void* parameter) {
  for (;;) {
    if (!mcp.digitalRead(7)) {
      cancellation = true;
    }
    delay(30);
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

  for (uint8_t i = 0; i < 7; i++) mcp.pinMode(i, INPUT_PULLUP);

  Serial.println("Looping...");
}

void loop() {
  for (uint8_t btn = 0; btn < 6; btn++) {
    if (!mcp.digitalRead(btn)) {
      Serial.print("Button " + (String)btn);
      if (btn == 3) {
        int size = sizeof(threeMelody) / sizeof(int);

        for (int note = 0; note < size; note++) {
          int duration = 1000 / threeDurations[note];
          tone(BUZZER_PIN, threeMelody[note], duration);

          int pauseBetweenNotes = duration * 1.30;
          delay(pauseBetweenNotes);
          if (cancellation) {
            cancellation = false;
            return;
          }
          noTone(BUZZER_PIN);

        }
      } else if (btn == 4) {
        int size = sizeof(fourMelody) / sizeof(int);

        for (int note = 0; note < size; note++) {
          int duration = 1000 / fourDurations[note];
          tone(BUZZER_PIN, fourMelody[note], duration);

          int pauseBetweenNotes = duration * 1.30;
          delay(pauseBetweenNotes);
          if (cancellation) {
            cancellation = false;
            return;
          }
          noTone(BUZZER_PIN);
        }
      } else if (btn == 5) {
        int size = sizeof(fiveDurations) / sizeof(int);

        for (int note = 0; note < size; note++) {
          int duration = 1000 / fiveDurations[note];
          tone(BUZZER_PIN, fiveMelody[note], duration);

          int pauseBetweenNotes = duration * 1.30;
          delay(pauseBetweenNotes);

          if (cancellation) {
            cancellation = false;
            return;
          }
          noTone(BUZZER_PIN);
        }
      }
    }
  }
  delay(30);
}