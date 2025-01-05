#include "component_artillery.h"

#include <stdio.h>
#include <stdlib.h>

ArtilleryFireResponse
ComponentArtillery_fire(ComponentArtillery *component_artillery) {
  if (component_artillery->_currentCooldown > 0) {
    return ArtilleryFireResponseCooldown;
  }

  printf("firing...\n");

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