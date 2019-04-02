#inclide <stdio.h>
#include <time.h>
#include "io.h"
#include "channels.h"
#include "stdio.h"
#include "elev.h"

typedef enum states{
  IDLE,
  MOVING_UP,
  MOVING_DOWN,
  DOOR_OPEN,
  STOPPED
} state;

enum events{
  FLOOR_SENSOR,
  STOP_BTN_PRESS,
  STOP_BTN_RELEASE,
  ORDER
} event;


/**
 * Initialize the state machine to a defined state
 */
void fsm_init();

/**
 * Event
 * Begin to complete any potential orders
 */
int fsm_evt_order(int *floor);

/**
 * Event
 * Reached a floor
 */
void fsm_evt_floor_sensor();

/**
 * Event
 * Stop button is pressed
 */
void fsm_evt_stop_button_pressed();

/**
 * Event
 * Stop button is released
 */
void fsm_evt_stop_button_released();

bool check_for_stop(int floor, tag_elev_motor_direction dir);

void door_timer();
