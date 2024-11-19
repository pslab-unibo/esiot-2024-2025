/*********
 * 
 * USER CONSOLE
 * 
 * This module implements the user console,
 * containing the buttons for interacting
 * with the user as well as the console
 * to output the messages.
 * 
 */
#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__
#include "Arduino.h" 

#define NUM_INPUT_POS 4
#define LAST_POS 3

#define NO_SELECTION -1
#define DIFFICULTY_LEVELS 4

/* Output management */

void init_player_console();
void sleep_console();
void resume_console();

void display_welcome_msg();
void display_go_message();
void display_num_to_convert(unsigned int num);
void display_new_difficulty_level(int level);
void display_binary_ok(int score);
void display_binary_wrong(unsigned int wrongNum);
void display_game_over(int score);

/* Input Management */

/* read the difficulty level */
int read_difficulty_level();

/* check if the player started the game */
bool player_input_started();

/* reset the input, at each interation */
void reset_player_input();

bool hasBeenPressed(int index);

/* for testing */
void test_player_input();

/* for debugging */
void log(const String& msg);
 
#endif
