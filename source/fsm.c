#include "fsm.h"
#include "io.h"
#include "channels.h"
#include "elev.h"
#include "timer.h"
#include "stdio.h"

void door_timer(){
  int wait_time = 3000; //3000 ms = 3 sec
  clock_t start_time = clock();
  clock_t time_diff;
  do{
      if (elev_get_stop_signal()){
        break;
      }

      if ()

      time_diff = (clock() - start_time) * 1000/CLOCKS_PER_SEC;

  } while(time_diff < wait_time);
}

void add_order(int floor, elev_button_type_t button, int * orders){
  orders[floor][button] = 1;
  elev_set_button_lamp(button, floor, 1);
}

void remove_order(int floor, elev_button_type_t button, int * orders){
  &orders[floor][button] = 0;
  orders[floor][2] = 0;

  elev_set_button_lamp(button, floor, 0);
  elev_set_button_lamp(BUTTON_CMD, floor, 0);
}

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

bool check_for_stop(int floor, elev_button_type_t dir){
  return (orders[floor][2] || orders[floor][dir]);
}
