#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "io.h"
#include "channels.h"
#include "elev.h"

#ifndef fsm_data
#include "fsm.h"
#endif

/**
* @file
* @brief functions for adding, removing and checking current orders
*/


/**
 * Set index [floor][button] of order matrix to 1
 *@param[in] floor floornumber where orders should be added
 *@param[in] button which button on the floor. 0 =up, 1 = down and 2 = internal commmand
 *@param[in] data pointer to the statemachine data struct
 */
void oh_add_order(int floor, int button, fsm_data * data);

/**
 *Remove all orders from a floor
 *@param[in] floor floornumber where orders should be deleted
 *@param[in] data pointer to the statemachine data struct
 */
void oh_delete_order(int floor, fsm_data * data);

/**
 *Remove all orders from all floors
 *@param[in] data pointer to the statemachine data struct
 */
void oh_delete_all_orders(fsm_data * data);

/**
 *When coming to floor, check if it has orders in current direction
 *@param[in] floor floornumber where orders should be deleted
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if the elevator should stop, 0 = if not
 */
int oh_check_for_stop(int floor, fsm_data * data);

/**
 *Check if there are any current orders on any floor
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if there are orders, 0 if not
 */
int oh_check_for_orders(fsm_data * data);


/**
 *Check which direction (if any) the elevator should go next
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if elevator should go up, -1 if elevator should go down,
 * 0 if no orders on other floors
 */
int oh_get_direction(fsm_data * data);

/**
 *Check if there are any orders on a given floor
 *@param[in] floor floor to check orders on
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if there are orders on the floor, 0 if not
 */
int oh_get_orders_floor(int floor, fsm_data * data);

/**
 *Check if there are any orders below a given floor
 *@param[in] floor floor to check orders above
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if there are orders above floor, 0 if no orders above
 */
int oh_get_orders_above(int floor, fsm_data* data);

/**
 *Check if there are any orders below a given floor
 *@param[in] floor floor to check orders below
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if there are orders below floor, 0 if no orders below floor
 */
int oh_get_orders_below(int floor, fsm_data * data);
