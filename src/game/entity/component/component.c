#include "component.h"

#include <stdio.h>

void Component_tick(Component *component) { component->_tick_func(component); }
