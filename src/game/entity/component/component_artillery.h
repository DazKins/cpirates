#ifndef COMPONENT_ARTILLERY_H
#define COMPONENT_ARTILLERY_H

#include "game/entity/component/component.h"
#include "game/entity/component/component_position.h"
#include "math/v.h"

typedef enum {
  ArtilleryFireResponseSuccess,
  ArtilleryFireResponseCooldown,
} ArtilleryFireResponse;

typedef struct {
  Component base;

  ComponentPosition *_component_position;
  int _currentCooldown;

  int cooldown;
} ComponentArtillery;

ComponentArtillery *
ComponentArtillery_new_ptr(Id entity_id, ComponentPosition *component_position,
                           int cooldown);

ArtilleryFireResponse
ComponentArtillery_fire(ComponentArtillery *component_artillery, V direction);

#endif // !COMPONENT_ARTILLERY_H