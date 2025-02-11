#include "config.h"

#include <stdlib.h>

int Config_debug = 0;
int Config_trace = 0;

void Config_init() {
  if (getenv("DEBUG") != NULL) {
    Config_debug = 1;
  }

  if (getenv("TRACE") != NULL) {
    Config_trace = 1;
  }
}