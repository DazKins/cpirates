#include "entity_ship.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/entity/component/component_artillery.h"
#include "game/entity/component/component_position.h"
#include "game/entity/component/component_rigid_body.h"

Entity *EntityShip_new_ptr() {
  Entity *entity = Entity_new_ptr(EntityTypeShip);

  ComponentPosition *component_position = ComponentPosition_new_ptr();
  Entity_add_component(entity, (Component *)component_position);

  ComponentRigidBody *component_rigid_body =
      ComponentRigidBody_new_ptr(component_position);
  Entity_add_component(entity, (Component *)component_rigid_body);

  ComponentArtillery *component_artillery =
      ComponentArtillery_new_ptr(component_position, 160);
  Entity_add_component(entity, (Component *)component_artillery);

  return entity;
}
