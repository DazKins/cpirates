#include "component_artillery.h"

#include <stdio.h>
#include <stdlib.h>

#include "game/entity/component/component_rigid_body.h"
#include "game/entity/entity_cannonball.h"
#include "game/game.h"

ArtilleryFireResponse
ComponentArtillery_fire(ComponentArtillery *component_artillery) {
  if (component_artillery->_currentCooldown > 0) {
    return ArtilleryFireResponseCooldown;
  }

  printf("firing...\n");

  ComponentPosition *component_position =
      component_artillery->_component_position;
  V pos = component_position->pos;

  Entity *entity_cannonball = EntityCannonball_new_ptr();
  ComponentPosition *entity_cannonball_component_position =
      (ComponentPosition *)Entity_get_component(entity_cannonball,
                                                ComponentTypePosition);
  entity_cannonball_component_position->pos = pos;

  ComponentRigidBody *entity_cannonball_component_rigid_body =
      (ComponentRigidBody *)Entity_get_component(entity_cannonball,
                                                 ComponentTypeRigidBody);
  ComponentRigidBody_push(entity_cannonball_component_rigid_body,
                          V_new(1.0f, 0.0f, 0.0f), 5.0f);

  Game_add_entity(entity_cannonball);

  component_artillery->_currentCooldown = component_artillery->cooldown;

  return ArtilleryFireResponseSuccess;
}

void ComponentArtillery_tick(Component *component) {
  ComponentArtillery *component_artillery = (ComponentArtillery *)component;

  if (component_artillery->_currentCooldown > 0) {
    component_artillery->_currentCooldown--;
  }
}

ComponentArtillery *
ComponentArtillery_new_ptr(ComponentPosition *component_position,
                           int cooldown) {
  ComponentArtillery *component_artillery = malloc(sizeof(ComponentArtillery));
  component_artillery->base.type = ComponentTypeArtillery;
  component_artillery->_component_position = component_position;
  component_artillery->base._tick_func = ComponentArtillery_tick;
  component_artillery->cooldown = cooldown;
  return component_artillery;
}