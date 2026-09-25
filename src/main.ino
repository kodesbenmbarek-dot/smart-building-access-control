#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int BUTTON_PIN = 2;
const int LED_RED_PIN = 8;
const int LED_GREEN_PIN = 9;
const int DOOR_RELAY_PIN = 10;

bool accessGranted = false;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(DOOR_RELAY_PIN, OUTPUT);

  lcd.init();
  lcd.backlight();

  digitalWrite(LED_RED_PIN, HIGH);
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(DOOR_RELAY_PIN, LOW);

  lcd.setCursor(0, 0);
  lcd.print("Access Control");
  lcd.setCursor(0, 1);
  lcd.print("Status: LOCKED ");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    // Grant access
    digitalWrite(LED_RED_PIN, LOW);
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(DOOR_RELAY_PIN, HIGH);

    lcd.setCursor(0, 1);
    lcd.print("Status: ALLOWED");

    delay(3000); // Keep door open for 3 seconds

    // Lock again
    digitalWrite(LED_RED_PIN, HIGH);
    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(DOOR_RELAY_PIN, LOW);

    lcd.setCursor(0, 1);
    lcd.print("Status: LOCKED ");
  }
  delay(100);
}
