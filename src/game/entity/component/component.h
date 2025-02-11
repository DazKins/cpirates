#ifndef COMPONENT_H
#define COMPONENT_H

#include "util/id.h"

typedef enum {
  ComponentTypePosition,
  ComponentTypeRigidBody,
  ComponentTypeArtillery,
  ComponentTypeCollider,
} ComponentType;

typedef struct _component {
  ComponentType type;
  Id entity_id;
  void (*_tick_func)(struct _component *component);
} Component;

Component Component_new(ComponentType type, Id entity_id,
                        void (*tick_func)(Component *component));

void Component_tick(Component *component);

#endif // !COMPONENT_H