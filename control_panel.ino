/*	Brian Hooper
	7/9/18

	Emulates a keyboard matrix using an Arduino Feather 32u4
	to provide input to a computer */

#include <Keyboard.h>

// Number of milliseconds to waiting in between checking for input
#define KEY_DELAY 5

// Input and output pins
int inputs[] = {18, 19, 20, 21, 22, 23};
int outputs[] = {5, 6, 9, 10, 11};

// For rotary encoder
int PIN_ENCODER_A = 15;
int PIN_ENCODER_B = 16;

// Each button indexes this array and retrieves its unique system shortcut
char shortcuts[30][3] = {
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, 'M'}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}, 
  {KEY_LEFT_GUI, KEY_LEFT_SHIFT, ' '}
  };

// Dimensions
const int width = sizeof(outputs) / sizeof(int);
const int height = sizeof(inputs) / sizeof(int);
const int keyLength = sizeof(shortcuts[0]) / sizeof(char);

/*
	Start serial connection, set pinMode
*/
void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  for(int i = 0; i < width; i++) {
    pinMode(inputs[i], INPUT);
    pinMode(outputs[i], OUTPUT);
  }
  pinMode(PIN_ENCODER_A, INPUT_PULLUP);
  pinMode(PIN_ENCODER_B, INPUT_PULLUP);
}

/*
	Envoke keyboard when a button is pressed
*/
void buttonPress(int button) {
  Serial.println("Key : " + String(button));
  String keyPress = "";
  for(int i = 0; i < keyLength; i++) {
    keyPress += shortcuts[button][i];
    Keyboard.press(shortcuts[button][i]);
  }
  Serial.println("\"" + keyPress + "\"");
  Keyboard.releaseAll();
}

/*
	Read a button and act if it was pressed
*/
void readPin(int i, int j) {
  int button = width * i + j;
  if (digitalRead(inputs[j]) == HIGH) {
    buttonPress(button);
  } 
  delay(KEY_DELAY);
}

/*
	Power on a single output pin, 
	then check all inputs
	param i index of outputs array
*/
void power(int i) {
  digitalWrite(outputs[i], HIGH);
  for(int j = 0; j < height; j++) {
    readPin(i, j);
  }
  digitalWrite(outputs[i], LOW);
}

/*
	Iteratively power on each output pin
*/
void cycleOutputs() {
  for(int i = 0; i < width; i++) {
    power(i);
  }
}

/**
  Main loop
*/
void loop() {
  cycleOutputs();
}