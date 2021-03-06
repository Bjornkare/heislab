#pragma once
#include <stdio.h>
#include "elev.h"
#include "fsm.h"


int main() {

    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    printf("Press STOP button to stop elevator and exit program.\n");

	fsm_data data = fsm_init();
	int floor;
	int button_signal;


    while (1) {
		floor = elev_get_floor_sensor_signal();
		if (floor != data.prev_floor && floor != -1) {
			fsm_evt_floor_sensor(floor, &data);
		}
		for (int i = 0; i < N_FLOORS; i++) {
			for (int j = 0; j < N_BUTTONS; j++) {
				button_signal = elev_get_button_signal(j, i);
				if (button_signal != data.orders[j][i] && button_signal == 1) {
					fsm_evt_order(i, j, &data);
				}
			}
		}
		if (elev_get_stop_signal()) {
			fsm_evt_stop_button_pressed(&data);
		}
    }

    return 0;
}
