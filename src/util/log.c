#include "log.h"

#include <stdio.h>

#include "config.h"

void Log(const char *message) { printf("%s\n", message); }

void Log_trace(const char *message) {
  if (Config_trace) {
    printf("%s\n", message);
  }
}
