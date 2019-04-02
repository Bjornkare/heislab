#include "fsm.h"
#include "io.h"
#include "channels.h"
#include "elev.h"
#include "timer.h"
#include "stdio.h"



void fsm_init() {
	fsm_data.orders = {
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }
	};
	fsm_data.active_state = IDLE;
	int last_floor = 0;
}

int fsm_evt_order(int floor, elev_button_type_t dir) {
	switch (active_state) {
	case IDLE:
		if (last_floor != floor) {
			add_order(floor, dir, orders);
			set_motor_direction()
		}
	}
}


void fsm_evt_floor_sensor(int floor) {
	last_floor = floor;
	elev_set_floor_indicator(floor);
	switch (active_state) {
	case IDLE:
		break;
	case MOVING_UP:
		if (check_for_stop(floor, DIRN_UP)) {
			remove_order(floor, DIRN_UP, orders)
			elev_set_motor_direction(DIRN_STOP);
			elev_set_door_open_lamp(1);
			active_state = state.DOOR_OPEN;
			door_timer();
		}
		break;
	case MOVING_DOWN:
		if (check_for_stop(floor, DIRN_DOWN)) {
			remove_order(floor, DIRN_DOWN, orders);
			elev_set_motor_direction(DIRN_STOP);
			elev_set_door_open_lamp(1);
			active_state = state.DOOR_OPEN;
			door_timer();
		}
		break;
	}
	case DOOR_OPEN:
	case STOPPED:
		break;
}

bool check_for_stop(int floor, int dir){
  int dir_index;
  if (dir == -1){
    int index = 2;
   }
  else dir_index = dir;
  return (orders[floor][0] || orders[floor][dir_index]);
}
