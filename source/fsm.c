#include "fsm.h"

bool check_for_stop(int floor, elev_button_type_t dir){
  return (orders[floor][2] || orders[floor][dir]);
}

void door_timer(){
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
