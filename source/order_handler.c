#include "order_handler.h"

int idle_get_dir(fsm_data * data) {
    if (data->curr_dir == 1){ //Prioritize orders above elevator
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

    }else if (data->curr_dir == -1){
        for (int i = 0; i < data->prev_floor; i++){
          if (get_orders_floor(i, data)){
	          return -1; //downwards
          }
		  for (int i = data->prev_floor; i < N_FLOORS; i++) {
			  if (get_orders_floor(i, data) && get_orders_floor(i, data) != data->prev_floor) {
				  return 1; //upwards
        }
    }
    return 0;
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
  return (data->orders[floor][2] || data->orders[floor][data->curr_dir]);
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
