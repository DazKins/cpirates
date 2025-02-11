#include "component_position.h"

#include <math.h>
#include <stdlib.h>

void ComponentPosition_tick(Component *component) {}

void ComponentPosition_set_rot(ComponentPosition *component_position, V rot) {
  component_position->_rot = V_wrap(rot, 0, 2 * M_PI);
}

V ComponentPosition_get_rot(ComponentPosition *component_position) {
  return component_position->_rot;
}

ComponentPosition *ComponentPosition_new_ptr(Id entity_id) {
  ComponentPosition *component_position = malloc(sizeof(ComponentPosition));

  component_position->base =
      Component_new(ComponentTypePosition, entity_id, ComponentPosition_tick);

  component_position->pos = V_0;
  component_position->_rot = V_0;
  return component_position;
}
