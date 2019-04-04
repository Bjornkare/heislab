#include <stdio.h>
#include "io.h"
#include "channels.h"
#include "elev.h"
#include "stdio.h"

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
void add_order(int floor, int button, fsm_data * data);

/**
 *Remove all orders from a floor
 *@param[in] floor floornumber where orders should be deleted
 *@param[in] data pointer to the statemachine data struct
 */
void remove_order(int floor, fsm_data * data);

/**
 *Remove all orders from all floors
 *@param[in] data pointer to the statemachine data struct
 */
void delete_all_orders(fsm_data * data);

/**
 *When coming to floor, check if it has orders in current direction
 *@param[in] floor floornumber where orders should be deleted
 *@param[in] data pointer to the statemachine data struct
 *@return stop wheter or not the elevator should stop, 1 = stop, 0 = dont stop
 */
bool check_for_stop(int floor, fsm_data * data);

/**
 *@param[in] data pointer to the statemachine data struct
 */
int check_for_orders(fsm_data * data);


/**
 *Check which direction (if any) the elevator should go next
 *@param[in] data pointer to the statemachine data struct
 *@return 1 if elevator should go up, -1 if elevator should go down,
 * 0 if no orders on other floors
 */
int idle_get_dir(fsm_data * data);
