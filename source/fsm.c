#include "fsm.h"

void door_timer(fsm_data * data){
  elev_set_door_open_lamp(1);
  while (elev_get_stop_signal()) {
	  delete_all_orders(data);
  };
  int wait_time = 3000; //3000 ms = 3 sec
  clock_t start_time = clock();
  clock_t time_diff;
  do{
      for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
          if (elev_get_button(i,j,data)){
			  add_order(i, j);
          }
        }
      }
      int time_diff = (clock() - start_time) * 1000/CLOCKS_PER_SEC;

  } while(time_diff < wait_time);

  remove_order(data.prev_floor);
  elev_set_door_open_lamp(0);

  data.curr_dir = idle_get_dir(data);
  if (data.curr_dir) {
	  elev_set_motor_direction(data.curr_dir);
  }
  else {
	  data.active_state = state.IDLE;
  }
}

void fsm_init(fsm_data * data) {
	data.orders = {
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 },
		{ 0,0,0 }
	};
	data.active_state = IDLE;
	data.prev_floor = 0;
	data.curr_dir = 0;
}

int fsm_evt_order(int floor, elev_button_type_t dir, fsm_data * data) {
	add_order(floor, dir, data);
	switch (data.active_state) {
	case IDLE:
		if(floor != data.prev_floor){
			data.curr_dir = idle_get_dir(data);
			elev_set_motor_direction(data.curr_dir);
			data.active_state = MOVING;
		}
		else {
			data.active_state = DOOR_OPEN;
			door_timer(data);
		}
		break;
	case MOVING:
	case DOOR_OPEN:
		add_order(floor, dir, data);
		break;
}


void fsm_evt_floor_sensor(int floor, fsm_data * data) {
	data.prev_floor = floor;
	elev_set_floor_indicator(floor);
	switch (fsm_data.active_state) {
	case IDLE:
		break;
	case MOVING:
		if (check_for_stop(floor, data.dir)) {
			elev_set_motor_direction(DIRN_STOP);
			data.active_state = state.DOOR_OPEN;
			door_timer(data);
		}
		break;
	case DOOR_OPEN:
}

void fsm_evt_stop_button_pressed(fsm_data * data){
	elev_set_motor_direction(DIRN_STOP);
	if (elev_get_floor_sensor_signal() != -1) {
		data.active_state = state.DOOR_OPEN;
		door_timer(data);
	}
	else {
		data.active_state = state.STOPPED;
		while (elev_get_stop_signal);
		delete_all_orders(data);
		data.active_state = state.MOVING;
		elev_set_motor_direction(data.curr_dir);
	}
}
