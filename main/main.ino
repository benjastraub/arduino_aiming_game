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

// States of buttons and vibration sensor
int left_button_state;
int center_button_state;
int right_button_state;

int vibration;

// Constants
const float gear_diameter = 1.2;
const float gear_radius = gear_diameter / 2;
const float distance_per_step = pow(gear_radius, 2.0) * 3.14;
const int total_length = 180;
String regions[] = {"Arica", "Tarapaca", "Antofagasta", "Atacama", "Coquimbo", "Valparaiso", "Metropolitana", "O'Higgins", "Maule", "Biobio", "Araucania", "Los Rios", "Los lagos", "Aysen", "Magallanes"};

// Variables
long selected_region = [];
int region_selection_pos = 0;
bool region_selected = false;
bool data_converted = false;
bool first_position = false;

// Data

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
