#ifndef COMPONENT_HEALTH_H
#define COMPONENT_HEALTH_H

#include "game/entity/component/component.h"

typedef struct {
  Component base;
  int health;
  int max_health;
} ComponentHealth;

ComponentHealth *ComponentHealth_new_ptr(Id entity_id, int max_health);
void ComponentHealth_damage(ComponentHealth *component_health, int damage);
void ComponentHealth_heal(ComponentHealth *component_health, int heal_amount);
int ComponentHealth_get_health(ComponentHealth *component_health);
int ComponentHealth_get_max_health(ComponentHealth *component_health);

#endif // !COMPONENT_HEALTH_H 