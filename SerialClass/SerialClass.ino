/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-button-toggle-led
 */

// constants won't change
const int HOUSE_BUTTON_PIN = 7; // Arduino pin connected to button's pin
const int HOUSE_LED_PIN    = 4; // Arduino pin connected to LED's pin

const int TOWER_BUTTON_PIN = 8;
const int TOWER_LED_PIN_1 = 2;
const int TOWER_LED_PIN_2 = 3;

// variables will change:
int ledStateHouse = LOW;     // the current state of LED
int lastButtonStateHouse;    // the previous state of button
int currentButtonStateHouse; // the current state of button

// variables will change:
int ledStateTower = LOW;     // the current state of LED
int lastButtonStateTower;    // the previous state of button
int currentButtonStateTower; // the current state of button

void setup() {
  Serial.begin(9600);                // initialize serial
  pinMode(HOUSE_BUTTON_PIN, INPUT_PULLUP); // set arduino pin to input pull-up mode
  pinMode(TOWER_BUTTON_PIN, INPUT_PULLUP);
  pinMode(HOUSE_LED_PIN, OUTPUT);          // set arduino pin to output mode
  pinMode(TOWER_LED_PIN_1, OUTPUT);
  pinMode(TOWER_LED_PIN_2, OUTPUT);

  currentButtonStateHouse = digitalRead(HOUSE_BUTTON_PIN);
  currentButtonStateTower = digitalRead(TOWER_BUTTON_PIN);
}

void loop() {
  house();
  tower();
}

void house(){
  lastButtonStateHouse    = currentButtonStateHouse;      // save the last state
  currentButtonStateHouse = digitalRead(HOUSE_BUTTON_PIN); // read new state

  if(lastButtonStateHouse == HIGH && currentButtonStateHouse == LOW) {
    Serial.println("The button is pressed");

    // toggle state of LED
    ledStateHouse = !ledStateHouse;

    // control LED arccoding to the toggled state
    digitalWrite(HOUSE_LED_PIN, ledStateHouse); 
  }
}

void tower(){
  lastButtonStateTower    = currentButtonStateTower;      // save the last state
  currentButtonStateTower = digitalRead(TOWER_BUTTON_PIN); // read new state

  if(lastButtonStateTower == HIGH && currentButtonStateTower == LOW) {
    Serial.println("The button is pressed");

    // toggle state of LED
    ledStateTower = !ledStateTower;

    // control LED arccoding to the toggled state
    digitalWrite(TOWER_LED_PIN_1, ledStateTower); 
    digitalWrite(TOWER_LED_PIN_2, ledStateTower); 
  }
}