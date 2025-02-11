#include "component_artillery.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "game/entity/component/component_rigid_body.h"
#include "game/entity/entity_cannonball.h"
#include "game/game.h"
#include "util/log.h"
#include "util/map.h"

ArtilleryFireResponse
ComponentArtillery_fire(ComponentArtillery *component_artillery) {
  Log_trace("Firing artillery...");
  if (component_artillery->_currentCooldown > 0) {
    Log_trace("Artillery on cooldown");
    return ArtilleryFireResponseCooldown;
  }

  Log_trace("Artillery not on cooldown");

  ComponentPosition *component_position =
      component_artillery->_component_position;
  V pos = component_position->pos;
  V rot = ComponentPosition_get_rot(component_position);

  Log_trace("Creating cannonball...");
  Entity *entity_cannonball = EntityCannonball_new_ptr();

  HashMap_add(entity_cannonball->metadata, "fired_by",
              &component_artillery->base.entity_id);

  ComponentPosition *entity_cannonball_component_position =
      (ComponentPosition *)Entity_get_component(entity_cannonball,
                                                ComponentTypePosition);
  entity_cannonball_component_position->pos = pos;
  Log_trace("Cannonball created");

  Log_trace("Adding rigid body to cannonball...");
  ComponentRigidBody *entity_cannonball_component_rigid_body =
      (ComponentRigidBody *)Entity_get_component(entity_cannonball,
                                                 ComponentTypeRigidBody);
  ComponentRigidBody_push(entity_cannonball_component_rigid_body,
                          V_new(-cos(rot.y), 0.0f, -sin(rot.y)), 0.4f);
  Log_trace("Rigid body added to cannonball");
  Log_trace("Adding cannonball to game...");
  Game_add_entity(entity_cannonball);
  Log_trace("Cannonball added to game");

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
ComponentArtillery_new_ptr(Id entity_id, ComponentPosition *component_position,
                           int cooldown) {
  ComponentArtillery *component_artillery = malloc(sizeof(ComponentArtillery));

  component_artillery->base =
      Component_new(ComponentTypeArtillery, entity_id, ComponentArtillery_tick);

  component_artillery->_component_position = component_position;
  component_artillery->cooldown = cooldown;

  return component_artillery;
}