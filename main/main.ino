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
long region_1[8] = {5256, 4425, 2511, 2044, 1812, 1594, 1444, 37};
long region_2[8] = {9029, 7862, 5214, 4247, 3594, 3040, 2751, 57};
long region_3[8] = {4102, 3569, 2287, 1747, 1567, 1352, 1207, 21};
long region_4[8] = {12093, 10342, 5468, 4789, 3889, 3230, 2913, 77};
long region_5[8] = {31470, 27451, 15694, 13597, 11172, 9554, 7319, 149};
long region_6[8] = {14390, 12347, 6568, 5776, 4700, 3638, 2621, 227};
long region_7[8] = {17181, 15040, 8159, 7044, 5379, 4370, 3884, 148};
long region_8[8] = {35749, 32193, 19573, 16437, 13101, 10563, 8658, 90};
long region_9[8] = {15638, 13181, 7605, 6445, 5480, 4438, 3837, 77};
long region_10[8] = {12862, 10870, 5721, 4887, 3962, 3310, 2923, 97};
long region_11[8] = {1991, 1636, 783, 679, 552, 474, 358, 6};
long region_12[8] = {2821, 2439, 1530, 1176, 1021, 906, 789, 26};
long region_13[8] = {115149, 100861, 55189, 49552, 39689, 31311, 16194, 3664};
long region_14[8] = {6672, 5696, 2959, 2548, 1899, 1531, 1436, 21};
long region_15[8] = {4200, 3741, 2328, 1836, 1604, 1346, 1293, 12};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
