#ifndef COMPONENT_H
#define COMPONENT_H

typedef enum {
  ComponentTypePosition,
  ComponentTypeRigidBody,
} ComponentType;

typedef struct _component {
  ComponentType type;
  void (*_tick_func)(struct _component *component);
} Component;

void Component_tick(Component *component);

#endif // !COMPONENT_H