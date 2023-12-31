#include "timer.h"

SYSTIM timer_start_count;
SYSTIM timer_timedout_count;
SYSTIM timer_current_count;

void timer_start(int delay_ms) {
  get_tim(&timer_start_count);
  timer_timedout_count
    = timer_start_count + (SYSTIM)delay_ms;
}

void timer_stop(void) {
  timer_start_count = (SYSTIM)0;
}

bool timer_is_started(void) {
  return ( timer_start_count > (SYSTIM)0 );
}

bool timer_is_timedout(void) {
  if( timer_start_count <= 0 ) {
    return false;
  }

  get_tim(&timer_current_count);
  if( timer_current_count
      >= timer_timedout_count ) {
    return true;
  } else {
    return false;
  }
}
