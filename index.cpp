#include <Servo.h>
#include <Keypad.h>
#include <EEPROM.h>


// Servo motor object
Servo motor;

// No. Of Rows and Columns
const byte ROWS = 4;
const byte COLS = 4;


// Array to represent keypad
char haxkeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Connections in arduino
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

// Create Keypad Object
Keypad customKeypad = Keypad(makeKeymap(haxkeys), rowPins, colPins, ROWS, COLS);


// Password char Array
String password = "123456";

// keypad value
String keypad = "";



// LED_BUILDIN blink controller
bool blinkBuildInLED = false;

void setup() {
  Serial.begin(9600);
  motor.attach(A0);
  motor.write(0);
  pinMode(LED_BUILTIN, INPUT);
  clearEEPROM();
}



void loop() {
  char key = customKeypad.getKey();
  ledBlinker();
  if (key) {
   
    if (keyPressCheck(key)) {
      unlock(true);
    } else {
      Serial.println(keypad);
    }
  }
}


bool keyPressCheck(char ch) {
  if (ch == '#') {
    keypad = "";
    unlock(false);
    // clearEEPROM();
    return false;
  }
  if (ch == '*') {
    return (keypad.equals(password));
  }
  keypad = keypad + ch;
  return false;
}

void unlock(bool unlock) {
  if (unlock) {
  
    Serial.println("unlock");
    motor.write(180);
    clearEEPROM();
  } else {
   
    motor.write(0);
  }
}

void ledBlinker() {
  if(!blinkBuildInLED) return;
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
}

void clearEEPROM() {
  Serial.println("Wait while we clear your EEPROM");
  blinkBuildInLED = true;
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
  blinkBuildInLED = false;
  Serial.println("You are good to go! \n");
  return;
}
