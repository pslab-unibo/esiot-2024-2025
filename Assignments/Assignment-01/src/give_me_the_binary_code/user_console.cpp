#include "user_console.h"
#include "Arduino.h"
#include "config.h"

#include <EnableInterrupt.h>
#include <LiquidCrystal_I2C.h> 

#define BOUNCING_TIME 100
#define __DEBUG__

LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 

uint8_t inputPins[] = {BUT01_PIN, BUT02_PIN, BUT03_PIN, BUT04_PIN};
bool buttonPressed[] = { false, false, false, false };

/* used for debouncing */
long lastButtonPressedTimeStamps[NUM_INPUT_POS];

void button_handler(int i);
void button_handler_0(){ button_handler(0); }
void button_handler_1(){ button_handler(1); }
void button_handler_2(){ button_handler(2); }
void button_handler_3(){ button_handler(3); }

void (*button_handlers[4])() = { button_handler_0, button_handler_1, button_handler_2, button_handler_3 };

void button_handler(int i){
  long ts = millis();
  if (ts - lastButtonPressedTimeStamps[i] > BOUNCING_TIME){
    lastButtonPressedTimeStamps[i] = ts;
    int status = digitalRead(inputPins[i]);
    if (status == HIGH && !buttonPressed[i]) { 
        buttonPressed[i] = true;
    }
  }
}

void init_player_console(){
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    pinMode(inputPins[i], INPUT);  
    enableInterrupt(inputPins[i], button_handlers[i], CHANGE);       
  }
  lcd.init();
  lcd.backlight();
}

/* Output management */

void display_welcome_msg(){
  lcd.clear();
  lcd.setCursor(1, 0); 
  lcd.print("Welcome to GMB!");
  lcd.setCursor(1, 2); 
  lcd.print("Press B1 to Start");
}

void display_go_message(){
  lcd.clear();
  lcd.setCursor(1, 1); 
  lcd.print("Go!");
}

void display_num_to_convert(unsigned int num){
  lcd.clear();
  lcd.setCursor(1, 1); 
  lcd.print(num);
}

void display_binary_ok(int score){
  lcd.clear();
  lcd.setCursor(1, 1); 
  lcd.print(String("GOOD! Score: ") + score);
}

void display_binary_wrong(unsigned int wrongNum){
  lcd.clear();
  lcd.setCursor(1, 1); 
  lcd.print(String(wrongNum) + " is WRONG");
}

void display_new_difficulty_level(int level){
  lcd.setCursor(1, 3); 
  lcd.print("Difficulty Level: "+String(level));
}

void display_game_over(int score){
  lcd.clear();
  lcd.setCursor(1, 1); 
  lcd.print("Game Over");
  lcd.setCursor(1, 2); 
  lcd.print(String("Final Score: ") + score);
}

/* Input management  */

void reset_player_input(){
  long ts = millis();
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    buttonPressed[i] = false;      
    lastButtonPressedTimeStamps[i] = ts;    
  }
  delay(BOUNCING_TIME);
  log("input reset");
}

bool hasBeenPressed(int index){
  return buttonPressed[index]; 
}

int read_difficulty_level(){
  double value = analogRead(POT_PIN);
  double valueMapped = ((((double)value) + 1.0)*((double)DIFFICULTY_LEVELS))/1024.0; 
  int trunc = (int) valueMapped;
  if (valueMapped > ((double)trunc)){
    trunc++;
  }
  return trunc;
}

bool player_input_started(){
  if (buttonPressed[0]){
    return true;
  } else {
    return false;
  }
}

/* for sleep management */

void sleep_console(){
  lcd.noDisplay();
  lcd.noBacklight();
}

void resume_console(){
  lcd.display();
  lcd.backlight();
}

/* aux */

void log(const String& msg){
  #ifdef __DEBUG__
  Serial.println(msg);
  #endif
}


void test_player_input(){
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    if (buttonPressed[i]) {
      Serial.println(String("button ") + i + " pressed"); 
      buttonPressed[i] = false;   
    }
  }
  // int value = analogRead(POT_PIN);
  // Serial.println(value);
}


