#include "component.h"

#include <stdio.h>

Component Component_new(ComponentType type,
                        void (*tick_func)(Component *component)) {
  Component component;
  component.type = type;
  component._tick_func = tick_func;
  return component;
}

void Component_tick(Component *component) {
  if (component->_tick_func != NULL) {
    component->_tick_func(component);
  }
}
