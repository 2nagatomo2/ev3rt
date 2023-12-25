#include "app.h"
#include "util.h"
#include "porter.h"

void cyc0(intptr_t exinf) {
  act_tsk(MAIN_TASK);
}

void main_task(intptr_t unused) {
  porter_transport();
  ext_tsk();
}
