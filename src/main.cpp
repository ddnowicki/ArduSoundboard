#include <Adafruit_MCP23X17.h>
#include <Arduino.h>

#include "pitches.hpp"

TaskHandle_t RestartByBtn;

Adafruit_MCP23X17 mcp;

#define BUZZER_PIN 19

int zeroMelody[] = {
  REST, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4,
  NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, REST,
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_G4, REST, NOTE_G4,
  NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_C5, NOTE_B4,
  NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_E5, NOTE_F5, NOTE_G5,
  NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_A4, NOTE_A4, REST, NOTE_A4, NOTE_A4, NOTE_G4, NOTE_A4, NOTE_G4, NOTE_G4, REST, NOTE_G4, NOTE_G4,
  NOTE_A4, NOTE_A4, NOTE_A4, REST, NOTE_A4, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_C5, REST,
  REST
};

int zeroDurations[] = {
  4, 2, 2, 2, 2, 2, 2, 2, 4,
  4, 8, 8, 4, 8, 8, 2, 2,
  4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8, 8, 8, 2, 8, 8,
  8, 8, 4, 4, 4, 1,
  4, 8, 8, 4, 8, 8, 1,
  4, 8, 8, 4, 8, 8, 4, 8, 8, 4, 8, 8,
  4, 8, 8, 4, 8, 8, 8, 8, 4, 4, 8, 8,
  8, 8, 8, 8, 4, 4, 8, 8, 4, 4, 8, 8,
  1
};



int oneMelody[] = {
  REST, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST, REST, NOTE_DS4,
  
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_G4, NOTE_B4, NOTE_E5,
  NOTE_DS5,   
  NOTE_D5, REST, REST, NOTE_DS4, 
  NOTE_E4, REST, NOTE_FS4, NOTE_G4, REST, NOTE_DS4,
  NOTE_E4, NOTE_FS4,  NOTE_G4, NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_B4,   
  
  NOTE_AS4, NOTE_A4, NOTE_G4, NOTE_E4, NOTE_D4, 
  NOTE_E4, REST,
  REST, NOTE_E5, NOTE_D5, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_E4,
  NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4,   
  NOTE_G4, NOTE_E4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_E4
};

int oneDurations[] = {
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  2, 16, 16, 16, 16, 
  2, 4, 8, 4,
  
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,
  1,   
  2, 4, 8, 8, 
  4, 8, 8, 4, 8, 8,
  8, 8,  8, 8, 8, 8, 8, 8,   
  
  2, 16, 16, 16, 16, 
  4, 4,
  4, 8, 8, 8, 8, 8, 8,
  16, 8, 16, 8, 16, 8, 16, 8,   
  16, 16, 16, 16, 16, 2
};

int twoMelody[] = {
  NOTE_E5, NOTE_D5, NOTE_A4, NOTE_F4,
  NOTE_E5, NOTE_D5, NOTE_A4, NOTE_F4,
  NOTE_C5, NOTE_AS4, NOTE_F4, NOTE_D4,
  NOTE_C5, NOTE_AS4, NOTE_F4, 
  NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_D4, NOTE_AS3
};

int twoDurations[] = {
  3, 5, 3, 3,
  3, 5, 3, 3,
  3, 5, 3, 3,
  3, 5, 2,
  3, 5, 3, 3, 1,
};

int threeMelody[] = {
  NOTE_B4, NOTE_B4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, 
  NOTE_E4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_D5, NOTE_C5, NOTE_B4

};

int threeDurations[] = {
  3, 3, 3, 3, 4, 3, 4, 
  5, 3, 3, 4, 3, 3, 3, 3, 4, 3
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
  delay(1000);
  for (;;) {
    delay(30);
    if (!mcp.digitalRead(6) && !cancellation) {
      cancellation = true;
      Serial.println("CANCELLATION");
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

  for (uint8_t i = 0; i < 7; i++) mcp.pinMode(i, INPUT_PULLUP);

  Serial.println("Looping...");
}

void playMelody(int melody[], int durations[], int size) {
  cancellation = false;
  for (int note = 0; note < size; note++) {
    if (cancellation) {
      Serial.println("LEAVING");
      cancellation = false;
      return;
    }
    int duration = 1000 / durations[note];
    tone(BUZZER_PIN, melody[note], duration);

    int pauseBetweenNotes = duration * 1.30;
    delay(pauseBetweenNotes);
    noTone(BUZZER_PIN);
  }
}


void loop() {
  for (uint8_t btn = 0; btn < 6; btn++) {
    if (!mcp.digitalRead(btn)) {
      Serial.print("\n " + (String)btn);
      if (btn == 0) {
        playMelody(zeroMelody, zeroDurations, sizeof(zeroMelody) / sizeof(int));
      } else if (btn == 1) {
        playMelody(oneMelody, oneDurations, sizeof(oneMelody) / sizeof(int));
      } else if (btn == 2) {
        playMelody(twoMelody, twoDurations, sizeof(twoMelody) / sizeof(int));
      } else if (btn == 3) {
        playMelody(threeMelody, threeDurations, sizeof(threeDurations) / sizeof(int));
      } else if (btn == 4) {
        playMelody(fourMelody, fourDurations, sizeof(fourDurations) / sizeof(int));
      } else if (btn == 5) {
        playMelody(fiveMelody, fiveDurations, sizeof(fiveDurations) / sizeof(int));
      }
    }
  }
  delay(30);
}