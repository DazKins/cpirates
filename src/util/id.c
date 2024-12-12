#include "id.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util/tim3.h"

Id Id_new() {
  Id id;

  id._0 = get_time_ns();
  id._1 = ((uint64_t)arc4random() << 32) | arc4random();

  return id;
}

char *Id_to_string(Id id) {
  char *str = malloc(33);
  sprintf(str, "%016lx-%016lx", id._0, id._1);
  return str;
}
