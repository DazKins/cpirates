#ifndef COMPONENT_COLLIDER_H
#define COMPONENT_COLLIDER_H

#include "game/entity/component/component.h"
#include "game/entity/component/component_position.h"
#include "game/entity/entity.h"
#include "math/obb.h"

typedef struct {
  Component base;

  ComponentPosition *_component_position;
  void (*_on_collide_func)(Entity *entity, Entity *hit_entity);
  OBB _obb;

} ComponentCollider;

ComponentCollider *ComponentCollider_new_ptr(
    Id entity_id, ComponentPosition *component_position,
    void (*on_collide_func)(Entity *entity, Entity *hit_entity), OBB obb);

OBB ComponentCollider_get_obb(ComponentCollider *component_collider);
void ComponentCollider_on_collide(ComponentCollider *component_collider,
                                  Entity *entity, Entity *hit_entity);

#endif // !COMPONENT_COLLIDER_H