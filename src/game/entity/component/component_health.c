#include "component_health.h"

#include <stdlib.h>

void ComponentHealth_tick(Component *component) {
  // No tick behavior needed for health component
}

ComponentHealth *ComponentHealth_new_ptr(Id entity_id, int max_health) {
  ComponentHealth *component_health = malloc(sizeof(ComponentHealth));
  
  component_health->base = Component_new(ComponentTypeHealth, entity_id, ComponentHealth_tick);
  component_health->max_health = max_health;
  component_health->health = max_health;
  
  return component_health;
}

void ComponentHealth_damage(ComponentHealth *component_health, int damage) {
  component_health->health -= damage;
  if (component_health->health < 0) {
    component_health->health = 0;
  }
}

void ComponentHealth_heal(ComponentHealth *component_health, int heal_amount) {
  component_health->health += heal_amount;
  if (component_health->health > component_health->max_health) {
    component_health->health = component_health->max_health;
  }
}

int ComponentHealth_get_health(ComponentHealth *component_health) {
  return component_health->health;
}

int ComponentHealth_get_max_health(ComponentHealth *component_health) {
  return component_health->max_health;
} 