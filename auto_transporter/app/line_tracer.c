#include "line_tracer.h"

void line_tracer_config(void) {
  linemon_config();
  driver_config();
}

void line_tracer_run(void) {
  if( linemon_is_online() ) {
    driver_turn_left();
    driver_turn_right();
  } else {
    line_tracer_stop();
  }
}

void line_tracer_stop(void) {
  driver_stop();
}
