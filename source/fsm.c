#include "fsm.h"
#include "io.h"
#include "channels.h"
#include "elev.h"
#include "timer.h"
#include "stdio.h"

void door_timer(){
  elev_set_door_open_lamp(1);
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
  remove_order(floor);
  elev_set_door_open_lamp(0);
  if (fsm_data.curr_dir = idle_get_dir()) {
	  elev_set_motor_direction(fsm_data.curr_dir);
  }
  else {
	  fsm_data.active_orders = state.IDLE;
  }
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
	int curr_floor = 0;
	int curr_dir = 0;
}

int fsm_evt_order(int floor, elev_button_type_t dir) {
	add_order(floor, dir);
	switch (fsm_data.active_state) {
	case IDLE:
		if(floor != fsm_data.curr_floor){
			fsm_data.curr_dir = idle_get_dir()
			elev_set_motor_direction(fsm_data.curr_dir);
			fsm_data.active_state = MOVING;
		}
		else {
			fsm_data.active_state = DOOR_OPEN;
			door_timer();
		}
		break;
	case MOVING:
	case DOOR_OPEN:
		add_order(floor, dir);
		break;
	case STOPPED:
		break;
}


void fsm_evt_floor_sensor(int floor) {
	fsm_data.curr_floor = floor;
	elev_set_floor_indicator(floor);
	switch (fsm_data.active_state) {
	case IDLE:
		break;
	case MOVING:
		if (check_for_stop(floor, fsm_data.dir)) {
			elev_set_motor_direction(DIRN_STOP);
			active_state = state.DOOR_OPEN;
			door_timer();
		}
		break;
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
