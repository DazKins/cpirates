#include "component_position.h"

#include <stdio.h>

void ComponentPosition_tick(Component *component) {}

ComponentPosition ComponentPosition_new() {
  ComponentPosition component_position = {};
  component_position.base.type = ComponentTypePosition;
  component_position.base._tick_func = ComponentPosition_tick;
  component_position.pos = V_0;
  return component_position;
}
