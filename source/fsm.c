#include "fsm.h"
#include "order_handler.h"


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
          if (elev_get_button_signal(i,j)){
			  add_order(i, j, data);
          }
        }
      }
      time_diff = (clock() - start_time) * 1000/CLOCKS_PER_SEC;

  } while(time_diff < wait_time);

  remove_order(data->prev_floor, data);
  elev_set_door_open_lamp(0);

  data->curr_dir = idle_get_dir(data);
  if (data->curr_dir) {
	  elev_set_motor_direction(data->curr_dir);
  }
  else {
	  data->active_state = IDLE;
  }
}

fsm_data fsm_init() {
    fsm_data data;
    for (int i = 0; i < N_FLOORS; i++){
        for (int j = 0; j < N_BUTTONS; j++){
            data.orders[i][j] = 0;
        }
    }
	data.active_state = MOVING;
	data.prev_floor = 0;
	data.curr_dir = -1;
    elev_set_motor_direction(data.curr_dir);

    return data;

}

void fsm_evt_order(int floor, int button, fsm_data * data) {
	add_order(floor, button, data);
	switch (data->active_state) {
	case IDLE:
		if(floor != data->prev_floor){
			data->curr_dir = idle_get_dir(data);
			elev_set_motor_direction(data->curr_dir);
			data->active_state = MOVING;
		}
		else {
			data->active_state = DOOR_OPEN;
			door_timer(data);
		}
		break;
	case MOVING:
	case DOOR_OPEN:
		add_order(floor, button, data);
		break;
    }
}


void fsm_evt_floor_sensor(int floor, fsm_data * data) {
	data->prev_floor = floor;
	elev_set_floor_indicator(floor);
	switch (data->active_state) {
	case IDLE:
		break;
	case MOVING:
		if (check_for_stop(floor, data)) {
			elev_set_motor_direction(DIRN_STOP);
			data->active_state = DOOR_OPEN;
			door_timer(data);
		} else if (!check_for_orders(data)){
            data->active_state = IDLE;
            elev_set_motor_direction(DIRN_STOP);
        }else if (floor == 0 || floor == (N_FLOORS - 1)){
            data->curr_dir = -(data->curr_dir);
            elev_set_motor_direction(data->curr_dir);
        }


		break;
	case DOOR_OPEN:
        break;
    }
}

void fsm_evt_stop_button_pressed(fsm_data * data){
	elev_set_motor_direction(DIRN_STOP);
	if (elev_get_floor_sensor_signal() != -1) {
		data->active_state = DOOR_OPEN;
		door_timer(data);
	}
	else {
		while (elev_get_stop_signal());
		delete_all_orders(data);
		data->active_state = MOVING;
		elev_set_motor_direction(data->curr_dir);
	}
}
