#include "component_position.h"

#include <stdlib.h>

void ComponentPosition_tick(Component *component) {}

ComponentPosition *ComponentPosition_new_ptr() {
  ComponentPosition *component_position = malloc(sizeof(ComponentPosition));
  component_position->base.type = ComponentTypePosition;
  component_position->base._tick_func = ComponentPosition_tick;
  component_position->pos = V_0;
  return component_position;
}
