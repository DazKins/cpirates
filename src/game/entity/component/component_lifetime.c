#include "component_lifetime.h"
#include "game/game.h"
#include <stdlib.h>

void ComponentLifetime_tick(Component *component) {
  ComponentLifetime *lifetime = (ComponentLifetime *)component;
  lifetime->remaining_ticks--;

  if (lifetime->remaining_ticks <= 0) {
    Game_mark_entity_for_deletion(component->entity_id);
  }
}

ComponentLifetime *ComponentLifetime_new_ptr(Id entity_id, int lifetime_ticks) {
  ComponentLifetime *component_lifetime = malloc(sizeof(ComponentLifetime));

  component_lifetime->base =
      Component_new(ComponentTypeLifetime, entity_id, ComponentLifetime_tick);
  component_lifetime->remaining_ticks = lifetime_ticks;

  return component_lifetime;
}