#ifndef COMPONENT_LIFETIME_H
#define COMPONENT_LIFETIME_H

#include "game/entity/component/component.h"

typedef struct {
  Component base;
  int remaining_ticks; // Number of game ticks remaining before entity is
                       // destroyed
} ComponentLifetime;

ComponentLifetime *ComponentLifetime_new_ptr(Id entity_id, int lifetime_ticks);

#endif // !COMPONENT_LIFETIME_H