#include "order_handler.h"

int idle_get_dir(fsm_data * data) {
  switch(data->curr_dir){
  case 0: //Currently no direction set, default to checking above current position
  case 1: //Current direction upwards
    for (int i = data->prev_floor + 1; i < N_FLOORS; i++){
      if (get_orders_floor(i, data)){
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
    for (int i = data->prev_floor + 1; i < N_FLOORS; i++){
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


int check_for_stop(int floor, fsm_data * data){
  if (floor == 0 || floor == N_FLOORS -1){
    for (int i = 0; i < 3; i++){
      if (data->orders[floor][i]){
	return 1;
      }
    }
    
  } else {
    
    if (data->curr_dir == 1){
      for(int i = floor + 1; i < N_FLOORS; i++){
	if (data->orders[i][0] || data->orders[i][2]){
	  return (data->orders[floor][2] || data->orders[floor][0]);
	}
      }
    }
    else{
      if (data->curr_dir == -1){
	for(int i = 0; i < floor; i++){
	  if (data->orders[i][1] || data->orders[i][2]){
	    return (data->orders[floor][2] || data->orders[floor][1]);
	  }
	}
      }
    } 
  }
  return (data->orders[floor][0] || data->orders[floor][1] || data->orders[floor][2]);
}


int check_for_orders(fsm_data * data){
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j < N_BUTTONS; j++){
      if (data->orders[i][j] == 1){
	return 1;
      }
    }
  }
  return 0;
}


int get_orders_floor(int floor, fsm_data * data){
  for (int i = 0; i < N_BUTTONS; i++){
    if (data->orders[floor][i]) {
      return 1;
    }
  }
  return 0;
}
