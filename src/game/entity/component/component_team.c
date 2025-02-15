#include "component_team.h"

#include <stdlib.h>

void ComponentTeam_tick(Component *component) {}

ComponentTeam *ComponentTeam_new_ptr(Id entity_id, Team team) {
  ComponentTeam *component_team = malloc(sizeof(ComponentTeam));

  component_team->base =
      Component_new(ComponentTypeTeam, entity_id, ComponentTeam_tick);
  component_team->team = team;

  return component_team;
}