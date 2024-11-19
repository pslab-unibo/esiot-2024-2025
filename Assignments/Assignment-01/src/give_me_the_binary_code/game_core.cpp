#include "game_core.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "user_console.h"
#include <avr/sleep.h>

/* target number to convert */
unsigned int numberToConvert;

/* current max time that can be used to input the sequence */
long max_time_to_convert;

/* current max time to display the sequence */
long max_time_to_display_sequence;

/* difficulty level */
int difficulty_level;

/* difficulty scaling factor */
double difficulty_scaling_factor = 1.5;

/* the score */
long score = 0;

/* current game state */
int game_state;

/* time in which the game entered in the game state */
long entered_state_time;

/* how long it the game is in current state */
long current_time_in_state;

/* =========== procedures about game state ======== */


void change_game_state(int new_state){
  game_state = new_state;
  entered_state_time = millis();
}

void update_game_state_time(){
  current_time_in_state = millis() - entered_state_time;
}

void check_difficulty_level(){
  int new_difficulty_level = read_difficulty_level();
  if (new_difficulty_level != difficulty_level){
    difficulty_level = new_difficulty_level;
    display_new_difficulty_level(difficulty_level);  
  } 
}

void game_intro(){
  reset_led_board();   
  display_welcome_msg();
  reset_pulsing();
  reset_player_input();
  change_game_state(GAME_WAIT_TO_START);
}

void game_wait_to_start(){
  if (current_time_in_state < MAX_IDLE_TIME){
    go_on_pulsing();
    check_difficulty_level();
    if (player_input_started()){
      change_game_state(GAME_INIT);
    }
  } else {
    change_game_state(GAME_SLEEP);
  }
}

void game_sleep(){
  log("Going to sleep..");
  reset_pulsing();
  sleep_console();
  delay(500);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
  sleep_disable();
  resume_console();   
  change_game_state(GAME_INTRO);
}

void game_init(){
  reset_pulsing();
  difficulty_level = read_difficulty_level();
  difficulty_scaling_factor = 1.0 + difficulty_level*0.1;
  log(String("Scaling F: ") + difficulty_scaling_factor);
  
  display_go_message();  
  /* here we can delay, since we do not need reactivity */
  delay(1000);

  score = 0;  
  max_time_to_convert = T1_TIME;
  srandom(1);
  change_game_state(GAME_LOOP_GENERATE_AND_SHOW_NUMBER);
}

void game_loop_generate_and_show_sequence(){
  turn_all_leds_off();
  numberToConvert = random(15);
  display_num_to_convert(numberToConvert);
  reset_player_input();
  log("Waiting for player input");
  change_game_state(GAME_LOOP_WAITING_PLAYER_SEQUENCE);
}

void change_to_game_over(){
  display_game_over(score);  
  change_game_state(GAME_OVER);
}

void game_loop_waiting_player_sequence(){
  
  for (int i = 0; i < NUM_INPUT_POS; i++){
    if (hasBeenPressed(i)){
      turn_on_led(i);
    } 
  }

  if (current_time_in_state >= max_time_to_convert){
    log("Player input timeout");    

    unsigned short currentComposedNum = 0;    
    for (int i = 0; i < NUM_INPUT_POS; i++){
      currentComposedNum *= 2;
      if (hasBeenPressed(i)){
        currentComposedNum++;
      } else {
      }
    }

    log(String("composed number: ") + currentComposedNum);
    log(String("target number: ") + numberToConvert);
 
    /* checking */ 

    if (currentComposedNum != numberToConvert){
      display_binary_wrong(currentComposedNum);
      /* here we can delay, since we do not need reactivity */
      delay(1000);
      change_to_game_over();
    } else {
      score++;
      max_time_to_convert /= difficulty_scaling_factor;
      display_binary_ok(score);
      /* here we can delay, since we do not need reactivity */
      delay(1000);
      change_game_state(GAME_LOOP_GENERATE_AND_SHOW_NUMBER);
    }
  }
}

void game_over(){
  if (current_time_in_state > TIME_IN_GAME_OVER){
     change_game_state(GAME_INTRO);
  }
}

