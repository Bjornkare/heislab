#include "fsm.h"
#include "order_handler.h"


void fsm_door_timer(fsm_data * data){
  elev_set_motor_direction(0);
  elev_set_door_open_lamp(1);
  oh_delete_order(data->prev_floor, data);
  while (elev_get_stop_signal()) {
    oh_delete_all_orders(data);
  };
  int wait_time = 3000; //3000 ms = 3 sec
  clock_t start_time = clock();
  clock_t time_diff;
  do{
    for (int i = 0; i < N_FLOORS; i++){
      for (int j = 0; j < N_BUTTONS; j++){
	if ( !((i == 0 && j == 1) || (i == 3 && j == 0) || (i == data->prev_floor))){
	  if (elev_get_button_signal(j,i) && !data->orders[i][j]){
	    oh_add_order(i, j, data);
	  }
	}
      }
    }

    if(elev_get_stop_signal()){
      fsm_evt_stop_button_pressed(data);
      break;
    }

    time_diff = (clock() - start_time) * 1000/CLOCKS_PER_SEC;
  } while(time_diff < wait_time);

  oh_delete_order(data->prev_floor, data);
  elev_set_door_open_lamp(0);

  data->active_state = IDLE;

  if (oh_check_for_orders(data)) {
    data->curr_dir = oh_get_direction(data);
    if (data->curr_dir != 0) {
      data->active_state = MOVING;
      elev_set_motor_direction(data->curr_dir);
    }
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
  data.prev_floor = -1;
  data.curr_dir = -1;
  elev_set_motor_direction(data.curr_dir);

  while(elev_get_floor_sensor_signal() == -1);
  elev_set_motor_direction(0);
  data.prev_floor = elev_get_floor_sensor_signal();
  data.active_state = IDLE;
  elev_set_floor_indicator(data.prev_floor);

  return data;
}



void fsm_evt_order(int floor, elev_button_type_t dir, fsm_data * data) {
  oh_add_order(floor, dir, data);
  switch (data->active_state) {
  case IDLE:
    if(floor != data->prev_floor){
      if (floor > data->prev_floor){
	data->curr_dir = 1;
      }else{
	data->curr_dir = -1;
      }
      elev_set_motor_direction(data->curr_dir);
      data->active_state = MOVING;
    }
    else {
      data->active_state = DOOR_OPEN;
      fsm_door_timer(data);
    }
    break;
  case MOVING:
  case DOOR_OPEN:
    oh_add_order(floor, dir, data);
    break;
  }
}


void fsm_evt_floor_sensor(int floor, fsm_data * data) {
  data->prev_floor = floor;
  elev_set_floor_indicator(floor);
  switch (data->active_state) {
  case MOVING:
    if (oh_check_for_stop(floor, data)) {
      elev_set_motor_direction(DIRN_STOP);
      data->active_state = DOOR_OPEN;
      fsm_door_timer(data);
  } else if (!oh_check_for_orders(data)){
      data->active_state = IDLE;
      elev_set_motor_direction(DIRN_STOP);
    } else if (floor == 0 || floor == (N_FLOORS - 1)){
      data->curr_dir = -(data->curr_dir);
      elev_set_motor_direction(data->curr_dir);
    }
    break;
  case DOOR_OPEN:
  case IDLE:
    break;
  }
}

void fsm_evt_stop_button_pressed(fsm_data * data){
  elev_set_stop_lamp(1);
  elev_set_motor_direction(DIRN_STOP);

  if (elev_get_floor_sensor_signal() != -1) {
    data->active_state = DOOR_OPEN;
    elev_set_door_open_lamp(1);
    while (elev_get_stop_signal()); //Wait until stop button is released.
    elev_set_stop_lamp(0);
    fsm_door_timer(data);
  }
  else {
    while (elev_get_stop_signal()); //Wait until stop button is released.
    oh_delete_all_orders(data);
    elev_set_stop_lamp(0);
    data->active_state = IDLE;
    //elev_set_motor_direction(data->curr_dir); ??
  }
}
