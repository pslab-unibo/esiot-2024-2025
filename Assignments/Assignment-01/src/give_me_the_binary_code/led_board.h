/*********
 * 
 * LED BOARD
 * 
 * This module implements the Led Board,
 * containing the 4 leds.
 * 
 */
#ifndef __LED_BOARD__
#define __LED_BOARD__

#include "Arduino.h"

void init_led_board();
void reset_led_board();

void turn_all_leds_off();
void turn_off_led(int index);
void turn_on_led(int index);

void reset_pulsing();
void go_on_pulsing();

/* for testing */ 
void test_led_board();

#endif
