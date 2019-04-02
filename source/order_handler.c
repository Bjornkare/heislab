#include "order_hander.h"

int idle_get_dir(fsm_data * data) {
  if (data.curr_dir == 1){ //Prioritize orders above elevator
    for (int i = curr_floor; i < N_FLOORS; i++){
      if (get_orders_floor(i) && get_orders_floor(i) != data.curr_floor){
	return 1; //upwards
      }
    }
    
  } else if (data.curr_dir == -1){
    for (int i = 0; i < data.curr_floor; i++){
      if (get_orders_floor(i)){
	return -1; //downwards
      }
    }
    
  } else return 0; //No orders, or order only on current floor
}

void add_order(int floor, elev_button_type_t button, fsm_data * data){
  data.orders[floor][button] = 1;
  elev_set_button_lamp(button, floor, 1);
}

void remove_order(int floor, fsm_data * data){
  for (int i = 0; i < 3; i++){
    data.orders[floor][i] = 0;
    elev_set_button_lamp(i, floor, 0);
  }
}


bool check_for_stop(int floor, elev_button_type_t dir){
  return (orders[floor][2] || orders[floor][data.curr_dir]);
}

int get_orders_floor{}
    


int check_for_orders(fsm_data * data){
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j < N_BUTTONS; j++){
      if (&data.orders[i][j])
}
