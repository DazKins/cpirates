#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "game/entity/component/component.h"
#include "math/v.h"

typedef struct {
  Component base;

  V pos;
  V _rot;
} ComponentPosition;

ComponentPosition *ComponentPosition_new_ptr();
void ComponentPosition_set_rot(ComponentPosition *component_position, V rot);
V ComponentPosition_get_rot(ComponentPosition *component_position);

#endif // !POSITION_COMPONENT_H