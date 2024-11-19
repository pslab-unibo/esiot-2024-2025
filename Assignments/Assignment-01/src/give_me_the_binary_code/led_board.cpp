#include "Arduino.h"
#include "config.h"

uint8_t ledPin[] = {LED01_PIN, LED02_PIN, LED03_PIN, LED04_PIN};
uint8_t pulseIntensity = 0;
uint8_t pulseDelta = 5;

extern void log(const String& msg);

void init_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    pinMode(ledPin[i], OUTPUT);     
  }
  pinMode(LED_START, OUTPUT);     
}

void reset_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], LOW);     
  }
}

void test_led_board(){   
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], HIGH);     
    delay(500);
    digitalWrite(ledPin[i], LOW);     
  }
  for (int i = 0; i < 10; i++){
    analogWrite(LED_START, i*25);     
    delay(100);
  }
  for (int i = 9; i >= 0; i--){
    analogWrite(LED_START, i*25);     
    delay(100);
  }
}

void reset_pulsing() {
  pulseIntensity = 0;
  pulseDelta = 5;
  analogWrite(LED_START, pulseIntensity);   
}

void go_on_pulsing(){
  analogWrite(LED_START, pulseIntensity);   
  pulseIntensity = pulseIntensity + pulseDelta;
  if (pulseIntensity == 0 || pulseIntensity == 255) {
    pulseDelta = -pulseDelta ; 
  }     
  delay(15);                               
}

void turn_all_leds_off(){
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], LOW);     
  }
}

void turn_off_led(int index){
  digitalWrite(ledPin[index], LOW);     
}

void turn_on_led(int index){
  digitalWrite(ledPin[index], HIGH);     
}

