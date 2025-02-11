#ifndef ID_H
#define ID_H

#include <stdint.h>

typedef struct {
  uint64_t _0;
  uint64_t _1;
} Id;

Id Id_new();

char *Id_to_string(Id id);

int Id_eq(Id a, Id b);

#endif // !ID_H