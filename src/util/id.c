#include "id.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "util/tim3.h"

Id Id_new() {
  Id id;

  id._0 = get_time_ns();
  id._1 = ((uint64_t)arc4random() << 32) | arc4random();

  return id;
}

char *Id_to_string(Id id) {
  char *str = malloc(33);
  sprintf(str, "%016llx-%016llx", id._0, id._1);
  return str;
}

int Id_eq(Id a, Id b) { return a._0 == b._0 && a._1 == b._1; }
