#include "direction_changer.h"

void direction_changer_config(void) {
  linemon_config();
  driver_config();
}

bool direction_changer_is_changed(void) {
  return linemon_is_online();
}

void direction_changer_run(void) {
  timer_start(1000 * 1000);
  while( !timer_is_timedout() ) {
    driver_back();
  }
  timer_stop();
  timer_start(1000 * 1000);
  while( !timer_is_timedout() ) {
    driver_spin();
  }
  while( !direction_changer_is_changed() ) {
    driver_spin();
  }
}
