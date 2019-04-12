#include "order_handler.h"

int oh_get_direction(fsm_data * data) {
  int floor = data->prev_floor;
  switch(data->curr_dir){
  case 0: //Currently no direction set, default to checking above current position
  case 1: //Current direction upwards
    if (oh_get_orders_above(floor,data) || oh_get_orders_floor(floor,data)){
      return 1; //upwards
  }else if (oh_get_orders_below(floor,data)){
      return -1; //downwards
    }
    break;

  case -1: //Current direction downwards
    if (oh_get_orders_below(floor,data) || oh_get_orders_floor(floor,data)){
      return -1;
  }else if (oh_get_orders_above(floor,data)){
      return 1;
    }
    break;
  }

  return 0; //No order, or only orders on current floor
}


void oh_add_order(int floor, int button, fsm_data * data){
  data->orders[floor][button] = 1;
  elev_set_button_lamp(button, floor, 1);
}


void oh_delete_orders_floor(int floor, fsm_data * data){
  for (int i = 0; i < 3; i++){
    data->orders[floor][i] = 0;
    if (!((floor == 0 && i == 1) || (floor == 3 && i == 0))){
      elev_set_button_lamp(i, floor, 0);
    }
  }
}

void oh_delete_all_orders(fsm_data * data) {
  for (int i = 0; i < N_FLOORS; i++){
    oh_delete_order(i, data);
  }
}


int oh_check_for_stop(int floor, fsm_data * data){
  if (floor != 0 && floor != N_FLOORS -1) {
    if (data->curr_dir == 1){
      if (oh_get_orders_above(floor,data)){
	return (data->orders[floor][2] || data->orders[floor][0]);
      }
    }
    else if (data->curr_dir == -1){
      if (oh_get_orders_below(floor,data)){
	return (data->orders[floor][2] || data->orders[floor][1]);
      }
    }
  }
  return oh_get_orders_floor(floor,data);
}


int oh_check_for_orders(fsm_data * data){
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j < N_BUTTONS; j++){
      if (data->orders[i][j] == 1){
	return 1;
      }
    }
  }
  return 0;
}


int oh_get_orders_floor(int floor, fsm_data * data){
  for (int i = 0; i < N_BUTTONS; i++){
    if (data->orders[floor][i]) {
      return 1;
    }
  }
  return 0;
}

int oh_get_orders_above(int floor, fsm_data * data){
  for (int i = floor + 1; i < N_FLOORS; i++){
    if (oh_get_orders_floor(i,data)){
      return 1;
    }
  }
  return 0;
}

int oh_get_orders_below(int floor, fsm_data* data) {
  for (int i = 0; i < floor; i++){
    if (oh_get_orders_floor(i,data)){
	return 1;
      }
  }
  return 0;
}
