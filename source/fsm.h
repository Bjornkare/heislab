 /**
 *@file
 *@brief Finite state machine that controls the elevator
 */
#pragma once

#include <stdio.h>
#include <time.h>
#include "io.h"
#include "channels.h"
#include "elev.h"

/**
 *Possible states for the state machine
 */
typedef enum states{
  IDLE,
  MOVING,
  DOOR_OPEN
} state;

/**
 * Struct for saving internal variables
 * active_state: the elevator's current state\n
 * curr_dir: The current direction of the elevator\n
 * prev_floor: The current or previously visited floor\n
 * orders: 2d array for keeping track of current orders\n
 * orders[i][j] = 1 if there is an order on floor i, button j
 */
typedef struct fsm_data{
  state active_state;
  int curr_dir;
  int prev_floor;
  int orders[N_FLOORS][N_BUTTONS];
} fsm_data;


/**
 * Initialize the state machine to a defined state
 * @return data: an initalized variable of the type fsm_data
 */
fsm_data fsm_init();

/**
 * Event \n
 * Recieve a new order, add it to the list
 * @param floor floor the order is on
 * @param data pointer to the fsm_data struct
 */
void fsm_evt_order(int floor, elev_button_type_t dir, fsm_data * data);

/**
 * Event \n
 * Reached a floor
 * @param floor index of reached floor
 * @param data pointer to the fsm_data struct
 */
void fsm_evt_floor_sensor(int floor, fsm_data * data);

/**
 * Event \n
 * Stop button is pressed
 * @param data pointer to the fsm_data struct
 */
void fsm_evt_stop_button_pressed(fsm_data * data);


/**
 * Keeps time of how long the door should stay open
 * @param data pointer to the fsm_data struct
 */
void fsm_door_timer(fsm_data * data);
