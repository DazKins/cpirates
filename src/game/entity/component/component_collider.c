#include "component_collider.h"

#include <stdlib.h>

ComponentCollider *
ComponentCollider_new_ptr(ComponentPosition *component_position,
                          void (*on_collide_func)(Entity *entity), OBB obb) {
  ComponentCollider *component_collider = malloc(sizeof(ComponentCollider));

  component_collider->base = Component_new(ComponentTypeCollider, NULL);

  component_collider->_component_position = component_position;
  component_collider->_on_collide_func = on_collide_func;
  component_collider->_obb = obb;

  return component_collider;
}

OBB ComponentCollider_get_obb(ComponentCollider *component_collider) {
  ComponentPosition *component_position = component_collider->_component_position;
  OBB obb = component_collider->_obb;
  
  // Rotate the OBB using the rotation value from ComponentPosition.
  // Here we assume 'rot' is a float (in radians) in ComponentPosition and we rotate about the Y-axis.
  V rot = ComponentPosition_get_rot(component_position);

  obb = OBB_rotate(obb, rot.x, V_new(1.0f, 0.0f, 0.0f));
  obb = OBB_rotate(obb, rot.y, V_new(0.0f, 1.0f, 0.0f));
  obb = OBB_rotate(obb, rot.z, V_new(0.0f, 0.0f, 1.0f));
  
  return OBB_translate(obb, component_position->pos);
}

void ComponentCollider_on_collide(ComponentCollider *component_collider,
                                  Entity *entity) {
  component_collider->_on_collide_func(entity);
}