#include "fsm.h"
#include "io.h"
#include "channels.h"
#include "stdio.h"

bool check_for_stop(int floor, int dir){
  int dir_index;
  if (dir == -1){
    int index = 2;
   }
  else dir_index = dir;
  return (orders[floor][0] || orders[floor][dir_index]);
}
