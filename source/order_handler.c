#include "order_handler.h"

int idle_get_dir(fsm_data * data) {
  switch(data->curr_dir){
  case 0: //Currently no direction set, default to checking above current position
  case 1: //Current direction upwards
    for (int i = data->prev_floor; i < N_FLOORS; i++){
      if (get_orders_floor(i, data) && get_orders_floor(i, data) != data->prev_floor){
	return 1; //upwards
      }
      for (int i = 0; i < data->prev_floor; i++){
	if (get_orders_floor(i, data)){
	  return -1; //downwards
	}
      }
    }
    break;
    
  case -1: //Current direction downwards
    //Check for orders below elevator
    for (int i = 0; i < data->prev_floor; i++){
      if (get_orders_floor(i, data)){
	return -1; //downwards
      }
    }
    //Check for orders above elevator
    for (int i = data->prev_floor; i < N_FLOORS; i++){
      if(get_orders_floor(i,data)){
	return 1; //upwards
      }
    }
  }
  return 0; //No order, or only orders on current floor
}


void add_order(int floor, int button, fsm_data * data){
  data->orders[floor][button] = 1;
  elev_set_button_lamp(button, floor, 1);
}


void remove_order(int floor, fsm_data * data){
  for (int i = 0; i < 3; i++){
    data->orders[floor][i] = 0;
    elev_set_button_lamp(i, floor, 0);
  }
}


void delete_all_orders(fsm_data * data) {
  for (int i = 0; i < N_FLOORS; i++){
    remove_order(i, data);
  }
}


bool check_for_stop(int floor, fsm_data * data){
  int button = (data->curr_dir == 1) ? 0 : 1;
  return (data->orders[floor][2] || data->orders[floor][button]);
}


int check_for_orders(fsm_data * data){
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j < N_BUTTONS; j++){
      if (data->orders[i][j]){
	return 1;
      }
    }
  }
  return 0;
}


bool get_orders_floor(int floor, fsm_data * data){
  for (int i = 0; i < N_BUTTONS; i++){
      if (data->orders[floor][i]) {
            return true;
        }
    }
    return false;
}
