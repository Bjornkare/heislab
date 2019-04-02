#include "order_hander.h"


void add_order(int floor, elev_button_type_t button, fsm_data * data){
  orders[floor][button] = 1;
  elev_set_button_lamp(button, floor, 1);
}

/*
  Delete all orders on a floor
*/
void remove_order(int floor, fsm_data * data){
  &orders[floor][button] = 0;
  orders[floor][2] = 0;

  elev_set_button_lamp(button, floor, 0);
  elev_set_button_lamp(BUTTON_CMD, floor, 0);
}


bool check_for_stop(int floor, elev_button_type_t dir){
  return (orders[floor][2] || orders[floor][dir]);
}

int get_orders_floor
    


int check_for_orders(fsm_data * data){
  for (int i = 0; i < N_FLOORS; i++){
    for (int j = 0; j < N_BUTTONS; j++){
      if (&data.orders[i][j])
}
