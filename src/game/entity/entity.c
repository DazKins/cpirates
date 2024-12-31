#include "entity.h"

void Entity_tick(Entity *entity) {
  entity->_tickFunc(entity);
}