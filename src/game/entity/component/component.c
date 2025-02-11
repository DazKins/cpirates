#include "component.h"

#include <stdio.h>

#include "util/id.h"

Component Component_new(ComponentType type, Id entity_id,
                        void (*tick_func)(Component *component)) {
  Component component;
  component.type = type;
  component.entity_id = entity_id;
  component._tick_func = tick_func;
  return component;
}

void Component_tick(Component *component) {
  if (component->_tick_func != NULL) {
    component->_tick_func(component);
  }
}
