#ifndef POSITION_COMPONENT_H
#define POSITION_COMPONENT_H

#include "game/entity/component/component.h"
#include "math/v.h"

typedef struct {
  Component base;

  V pos;
  V rot;
} ComponentPosition;

ComponentPosition *ComponentPosition_new_ptr();

#endif // !POSITION_COMPONENT_H