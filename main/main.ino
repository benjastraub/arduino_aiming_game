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

int Reset = 42;

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
String levels[8][2] = {{"",""},{"Rindes la PSU?", ""}, {"Postulas a la", "universidad?"}, {"Tu postulacion", "es valida?"}, {"Eres", "seleccionado?"}, {"Te matriculas", " en la U?"}, {"Es universidad", "del CRUCH?"}, {"Es en la PUC?", ""}};
String name_levels[8][2] = {{"", ""}, {"Rendicion", ""}, {"Postulacion", ""}, {"Postulaicion", "valida"}, {"Seleccion", ""}, {"Matriculacion", ""}, {"Matriculacion", "CRUCH"}, {"Matriculacion", "PUC"}};
// Variables
long selected_region[8];
int region_selection_pos = 0;
bool region_selected = false;
bool data_converted = false;
bool first_position = false;
int round_counter = 0;

// Data
long region_1[8] = {100, 84, 57, 81, 89, 88, 91, 3};
long region_2[8] = {100, 87, 66, 81, 85, 85, 90, 2};
long region_3[8] = {100, 87, 64, 76, 90, 86, 89, 2};
long region_4[8] = {100, 86, 53, 88, 81, 83, 90, 3};
long region_5[8] = {100, 87, 57, 87, 82, 86, 77, 2};
long region_6[8] = {100, 86, 53, 88, 81, 77, 72, 9};
long region_7[8] = {100, 88, 54, 86, 76, 81, 89, 4};
long region_8[8] = {100, 90, 61, 84, 80, 81, 82, 1};
long region_9[8] = {100, 84, 58, 85, 85, 81, 86, 2};
long region_10[8] = {100, 85, 53, 85, 81, 84, 88, 3};
long region_11[8] = {100, 82, 48, 87, 81, 86, 76, 2};
long region_12[8] = {100, 86, 63, 77, 87, 89, 87, 3};
long region_13[8] = {100, 88, 55, 90, 80, 79, 52, 23};
long region_14[8] = {100, 85, 52, 86, 75, 81, 94, 1};
long region_15[8] = {100, 89, 62, 79, 87, 84, 96, 1};

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
  digitalWrite(Reset, HIGH);
  delay(200); 
  pinMode(Reset, OUTPUT); 
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
        Serial.println("Derecha");
      } else if (left_button_state == HIGH && region_selection_pos > 0){
        delay(500);
        region_selection_pos = --region_selection_pos;
        two_liner2("Elige la region", regions[region_selection_pos]);
        Serial.println("Izquierda");
      } else if (center_button_state == HIGH){
        delay(500);
        two_liner2("Elegiste", regions[region_selection_pos]);
        select_region(region_selection_pos);
        region_selected = true;
        round_counter = 0;
        Serial.println("Seleccionar");
      }
    }
  }
  // loop for the eight steps
  if (region_selected == true && round_counter < 7){
      Serial.println("En el loop de los turnos!");
      Serial.print("Loop "); Serial.println(round_counter);
      bailout:
      round_counter = round_counter + 1;
      int pos1 = selected_region[round_counter - 1];
      int pos2 = selected_region[round_counter];
      Serial.print(pos1); Serial.print(" "); Serial.println(pos2);
      two_liner2(levels[round_counter][0], levels[round_counter][1]);
      Serial.print(levels[round_counter][0]); Serial.println(levels[round_counter][1]);
      motor.step(-1 * calculate_step(pos1, pos2));
      delay(1000);
      for (int j = 5; j > 0; j--){
        two_liner2("Tiempo restante", String(j));
        Serial.println("Tiempo "); Serial.println(j);
        for (int k = 0; k < 100; k++){
          vibration = digitalRead(vibration_in);
          delay(10);
          if (vibration == 1){
            Serial.println("Pasaste");
            lcd.clear();
            two_liner("Pasaste","",1000);
            if (round_counter == 7){
              two_liner("Entraste a la PUC","",1000);
              two_liner("Eres del", String(map(selected_region[round_counter + 1], total_length, 0 , 0, 100)) + "%",1000);
              motor.step(calculate_step(selected_region[round_counter], 0));
              digitalWrite(Reset, LOW);
            } else{
                goto bailout;
            }
          } else{
            continue;
          }
        }
        if (vibration == 0 && j == 1){
          two_liner("Perdiste","",1000); 
          two_liner("Llegaste a", "", 1000);
          two_liner(name_levels[round_counter][0], name_levels[round_counter][1], 1000);
          two_liner("Eres del", String(map(selected_region[round_counter], total_length, 0 , 0, 100)) + "%", 1000);
          motor.step(calculate_step(selected_region[round_counter],0));
          digitalWrite(Reset, LOW);
        }
      }
  }
}
