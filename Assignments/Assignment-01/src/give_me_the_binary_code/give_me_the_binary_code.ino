/*
 * ESIOT a.y. 2024/2025
 *
 * ASSIGNMENT #1 - GIVE ME THE BINARY CODE!  
 * 
 * Author: A. Ricci
 * 
 */
#include "config.h"
#include "game_core.h"
#include "user_console.h" 
#include "led_board.h"

void setup() {
  init_player_console();
  init_led_board();
  reset_player_input();
  change_game_state(GAME_INTRO);
}

void loop(){ 
  update_game_state_time(); 
  switch (game_state) { 
  case GAME_INTRO:
    game_intro();
    break;
  case GAME_WAIT_TO_START:
    game_wait_to_start();
    break;
  case GAME_INIT:
    game_init();
    break;
  case GAME_LOOP_GENERATE_AND_SHOW_NUMBER:
    game_loop_generate_and_show_sequence();
    break;
  case GAME_LOOP_WAITING_PLAYER_SEQUENCE:
    game_loop_waiting_player_sequence();
    break;
  case GAME_OVER:
    game_over();
    break;
  case GAME_SLEEP:
    game_sleep();
    break;
  }
}

