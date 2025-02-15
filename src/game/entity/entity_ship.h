#ifndef ENTITY_SHIP_H
#define ENTITY_SHIP_H

#include "game/entity/entity.h"
#include "game/entity/component/component_team.h"

Entity *EntityShip_new_ptr(Team team);

#endif // !ENTITY_SHIP_H