// Libraries that will be used
#include <Stepper.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

// Pins setup
int stepper_1 = 11;
int stepper_2 = 10;
int stepper_3 = 9;
int stepper_4 = 8;

int rs = 2;
int en = 3;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;

int vibration_in = 12;

int left_button = 40;
int center_butotn = 38;
int right_button = 36;

// Instances of stepper and lcd
int STEPS = 200; // 360º/1.8º
Stepper motor = (STEPS, stepper_1, stepper_2, stepper_3, stepper_4);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// States of buttons and vibratino sensor
int left_button_state;
int center_button_state;
int right_button_state;

int vibration;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
