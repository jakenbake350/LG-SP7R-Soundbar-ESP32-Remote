#include <Arduino.h>
#define DECODE_NEC
#include <IRremote.hpp>

// Pin definitions
#define IR_SEND_PIN 4  // IR LED on GPIO 4

// Button GPIO pins (using INPUT_PULLUP, active LOW)
#define BTN_POWER 13
#define BTN_INPUT 12
#define BTN_SPEAKER_LEVEL 27
#define BTN_EQ 26
#define BTN_MENU 25
#define BTN_SETTINGS 33

// Deep sleep settings
#define SLEEP_TIMEOUT_MS 10000  // Sleep after 10 seconds of inactivity
RTC_DATA_ATTR int bootCount = 0;

// Captured IR codes for LG SP7R soundbar (NEC protocol, address 0x2C)
struct ButtonMap {
  uint8_t pin;
  uint8_t address;
  uint8_t command;
  const char* name;
};

ButtonMap buttons[] = {
  {BTN_POWER,         0x2C, 0x1E, "Power"},
  {BTN_INPUT,         0x2C, 0x8A, "Input"},
  {BTN_SPEAKER_LEVEL, 0x2C, 0x98, "Speaker Level"},
  {BTN_EQ,            0x2C, 0x2F, "EQ Setting"},
  {BTN_MENU,          0x2C, 0xA3, "Menu"},
  {BTN_SETTINGS,      0x2C, 0xA5, "Settings"}
};

const int numButtons = sizeof(buttons) / sizeof(buttons[0]);
unsigned long lastActivityTime = 0;

void goToSleep() {
  Serial.println("\nNo activity. Going to deep sleep...");
  Serial.println("Press Power to wake up.");
  Serial.flush();

  // Wake up on Power button press
  esp_sleep_enable_ext0_wakeup((gpio_num_t)BTN_POWER, LOW);

  delay(100);
  esp_deep_sleep_start();
}

void sendIRCode(uint8_t address, uint8_t command, const char* name) {
  Serial.print("Sending: ");
  Serial.println(name);

  IrSender.sendNEC(address, command, 0);

  lastActivityTime = millis();
  delay(200);  // Debounce
}

void setup() {
  Serial.begin(115200);
  delay(500);

  bootCount++;
  Serial.println("\n========================================");
  Serial.println("  LG SP7R Mini Remote - ACTIVE");
  Serial.println("========================================");
  Serial.print("Boot #");
  Serial.println(bootCount);

  esp_sleep_wakeup_cause_t wakeup_reason = esp_sleep_get_wakeup_cause();
  if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println("Woke up from Power button");
  }

  // Initialize IR sender
  IrSender.begin(IR_SEND_PIN);
  Serial.print("IR LED ready on GPIO ");
  Serial.println(IR_SEND_PIN);

  // Configure button pins with internal pull-up
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }

  Serial.println("\n6-Button Layout:");
  Serial.println("  GPIO 13 = Power");
  Serial.println("  GPIO 12 = Input");
  Serial.println("  GPIO 27 = Speaker Level");
  Serial.println("  GPIO 26 = EQ Setting");
  Serial.println("  GPIO 25 = Menu");
  Serial.println("  GPIO 33 = Settings");
  Serial.println("\nReady! Press any button...\n");

  lastActivityTime = millis();
}

void loop() {
  // Check each button
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttons[i].pin) == LOW) {
      sendIRCode(buttons[i].address, buttons[i].command, buttons[i].name);

      // Wait for button release
      while (digitalRead(buttons[i].pin) == LOW) {
        delay(10);
      }
    }
  }

  // Sleep after 10 seconds of inactivity
  if (millis() - lastActivityTime > SLEEP_TIMEOUT_MS) {
    goToSleep();
  }

  delay(50);
}
