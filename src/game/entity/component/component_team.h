#ifndef COMPONENT_TEAM_H
#define COMPONENT_TEAM_H

#include "game/entity/component/component.h"

typedef enum {
  TeamRed,
  TeamBlue,
} Team;

typedef struct {
  Component base;
  Team team;
} ComponentTeam;

ComponentTeam *ComponentTeam_new_ptr(Id entity_id, Team team);

#endif // !COMPONENT_TEAM_H 