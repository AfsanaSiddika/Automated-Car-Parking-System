#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Define pin numbers for IR sensors and servo motors
#define inGateIRPin 2
#define outGateIRPin 3

#define slot1IRPin 4
#define slot2IRPin 5
#define servoInGatePin 9
#define servoOutGatePin 10

// Initialize the LCD with I2C address 0x27 (common I2C address for 16x2 LCDs)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // 16 columns and 2 rows

Servo servoInGate;
Servo servoOutGate;

void setup() {
  // Initialize the IR sensors and servo motors
  Serial.begin(9600);
  pinMode(inGateIRPin, INPUT);
  pinMode(outGateIRPin, INPUT);
  pinMode(slot1IRPin, INPUT);
  pinMode(slot2IRPin, INPUT);
  
  servoInGate.attach(servoInGatePin);
  servoOutGate.attach(servoOutGatePin);
  
  // Initialize LCD
  lcd.begin(16, 2);
  lcd.backlight();  // Turn on the LCD backlight
  lcd.clear();
  
  // Initial message on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Parking System");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
}

void loop() {
  // lcd.print("Afsana");
  // Serial.println("Afsanf");
  // Gate sensors detection logic
  // int l = digitalRead(inGateIRPin);
  // Serial.print(l);
  // Serial.print("   ");
  // int r = digitalRead(outGateIRPin);
  // Serial.println(r);
  if (digitalRead(inGateIRPin) == LOW) {  // Car detected for in-gate
    servoInGate.write(0);  // Close the in-gate
    delay(2000);  // Wait for 2 seconds before closing the gate
    servoInGate.write(90);  // Open the in-gate
  }

  if (digitalRead(outGateIRPin) == LOW) {  // Car detected for out-gate
    servoOutGate.write(0);  // Close the out-gate
    delay(2000);  // Wait for 2 seconds before closing the gate
    servoOutGate.write(90);  // Open the out-gate
  }

  // Update LCD with parking slot status
  lcd.clear();  // Clear the previous display

  // Slot 1 status
  lcd.setCursor(0, 0);
  if (digitalRead(slot1IRPin) == LOW) {  // Slot 1 occupied
    lcd.print("Slot 1: Filled");
  } else {
    lcd.print("Slot 1: Empty");
  }

  // Slot 2 status
  lcd.setCursor(0, 1);
  if (digitalRead(slot2IRPin) == LOW) {  // Slot 2 occupied
    lcd.print("Slot 2: Filled");
  } else {
    lcd.print("Slot 2: Empty");
  }

  delay(500);  // Small delay for stability
}