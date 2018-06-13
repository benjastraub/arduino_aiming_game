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

int reset_pin = 53;

// Instances of stepper and lcd
int STEPS = 200; // 360º/1.8º
Stepper motor(STEPS, stepper_1, stepper_2, stepper_3, stepper_4);
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);

// States of buttons and vibration sensor
int left_button_state;
int center_button_state;
int right_button_state;

int vibration;

// Constants
const float gear_diameter = 1.2;
const float gear_radius = gear_diameter / 2;
const float distance_per_step = (pow(gear_radius, 2.0) * 3.14);
const int total_length = 180;
String regions[] = {"Arica", "Tarapaca", "Antofagasta", "Atacama", "Coquimbo", "Valparaiso", "Metropolitana", "O'Higgins", "Maule", "Biobio", "Araucania", "Los Rios", "Los lagos", "Aysen", "Magallanes"};

// Variables
long selected_region[8];
int region_selection_pos = 0;
bool region_selected = false;
bool data_converted = false;
bool first_position = false;
int round_counter = 0;

// Data
long region_1[8] = {100, 84, 48, 39, 34, 30, 27, 1};
long region_2[8] = {100, 87, 58, 47, 40, 34, 30, 1};
long region_3[8] = {100, 87, 56, 43, 38, 33, 29, 1};
long region_4[8] = {100, 86, 45, 40, 32, 27, 24, 1};
long region_5[8] = {100, 87, 50, 43, 36, 30, 23, 0};
long region_6[8] = {100, 86, 46, 40, 33, 25, 18, 2};
long region_7[8] = {100, 88, 47, 41, 31, 25, 23, 1};
long region_8[8] = {100, 90, 55, 46, 37, 30, 24, 0};
long region_9[8] = {100, 84, 49, 41, 35, 28, 25, 0};
long region_10[8] = {100, 85, 44, 38, 31, 26, 23, 1};
long region_11[8] = {100, 82, 39, 34, 28, 24, 18, 0};
long region_12[8] = {100, 86, 54, 42, 36, 32, 28, 1};
long region_13[8] = {100, 88, 48, 43, 34, 27, 14, 3};
long region_14[8] = {100, 85, 44, 38, 28, 23, 22, 0};
long region_15[8] = {100, 89,	55,	44,	38, 32,	31,	0};

// function that returns steps to move from x1 to x2
int calculate_step(int x1, int x2){
  int distance = x2 - x1;
  int steps = STEPS * (distance / distance_per_step);
  return steps;
}

//function that writes two line messages and erase it after a given time
void two_liner(String line1, String line2, int delay_time){
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
  delay(delay_time);
  lcd.clear();
}

//function that writes two line messages and mantains it
void two_liner2(String line1, String line2){
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print(line1);
  lcd.setCursor(0,1);
  lcd.print(line2);
}

// function that prints an array
void print_array(long my_array[]){
  for(int i = 0; i < 8; i++) {
   Serial.println(my_array[i]);
  }
}

// function that select the region based on the index of the array regions wich ocntain the names
void select_region(int index){
  if (index == 0){
    for (int i = 0; i < 8; i++){
        selected_region[i] = region_15[i];
    }
  } else if (index == 1){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_1[i];
    }
  } else if (index == 2){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_2[i];
    }
  } else if (index == 3){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_3[i];
    }
  } else if (index == 4){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_4[i];
    }
  } else if (index == 5){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_5[i];
    }
  } else if (index == 6){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_13[i];
    }
  } else if (index == 7){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_6[i];
    }
  } else if (index == 8){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_7[i];
    }
  } else if (index == 9){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_8[i];
    }
  } else if (index == 10){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_9[i];
    }
  } else if (index == 11){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_14[i];
    }
  } else if (index == 12){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_10[i];
    }
  } else if (index == 13){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_11[i];
    }
  } else if (index == 14){
      for (int i = 0; i < 8; i++){
        selected_region[i] = region_12[i];
    }
  }
  print_array(int(select_region));
  convert_data(selected_region);
  print_array(int(select_region));
}

void convert_data(long data_array[8]){
    for (int i = 0; i < 8; i++){
        data_array[i] = map(data_array[i], 0 , 100, total_length, 0);
    }
}

void setup() {
  digitalWrite(reset_pin, HIGH);
  // Start of serial communication
  Serial.begin(9600);

  // Setup of lcd size
  lcd.begin(16,2);

  // Pinmodes
  pinMode(vibration_in, INPUT);
  pinMode(stepper_1, OUTPUT);
  pinMode(stepper_2, OUTPUT);
  pinMode(stepper_3, OUTPUT);
  pinMode(stepper_4, OUTPUT);
  pinMode(left_button, INPUT);
  pinMode(center_butotn, INPUT);
  pinMode(right_button, INPUT);
  pinMode(reset_pin, OUTPUT);

  // Setup of motor speed
  motor.setSpeed(20);
  round_counter = 0;
}

void loop() {
  // User select region
  if (region_selected == false){
    two_liner2("Elige la region", regions[0]);
  
    while (region_selected == false){
      left_button_state = digitalRead(left_button);
      center_button_state = digitalRead(center_butotn);
      right_button_state = digitalRead(right_button);

      if (right_button_state == HIGH && region_selection_pos < sizeof(regions)){
        delay(500);
        region_selection_pos = ++region_selection_pos;
        two_liner2("Elige la region", regions[region_selection_pos]);
      } else if (left_button_state == HIGH && region_selection_pos > 0){
        delay(500);
        region_selection_pos = --region_selection_pos;
        two_liner2("Elige la region", regions[region_selection_pos]);
      } else if (center_button_state == HIGH){
        delay(500);
        two_liner2("Elegiste", regions[region_selection_pos]);
        select_region(region_selection_pos);
        region_selected = true;
        round_counter = 0;
      }
    }
  }
  // loop for the eight steps
  if (region_selected == true && round_counter < 7){
      Serial.println("En el loop de los turnos!");
      Serial.print("Loop "); Serial.println(round_counter);
      round_counter = round_counter + 1;
      int pos1 = selected_region[round_counter];
      int pos2 = selected_region[round_counter + 1];
      Serial.print(pos1); Serial.print(" "); Serial.println(pos2);
      motor.step(-1 * calculate_step(pos1, pos2));
      delay(1000);
      for (int j = 15; j > 1; j--){
        two_liner2("Tiempo", String(j));
        vibration = digitalRead(vibration_in);
        delay(1000);
        if (vibration == 1){
          Serial.println("Pasaste");
          break;
        }
        if (vibration == 0 && j == 2){
          two_liner2("Perdiste","");
          delay(10000);
        }
      }
  }
}
