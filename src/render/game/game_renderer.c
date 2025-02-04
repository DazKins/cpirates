#include "game_renderer.h"

#include <stdio.h>

#include "game/entity/entity.h"
#include "render/debug/debug.h"
#include "render/game/entity/entity_renderer.h"
#include "render/model/model.h"
#include "render/model/model_builder.h"
#include "render/model/model_sea.h"
#include "render/model/model_ship.h"
#include "render/shader.h"
#include "render/texture.h"
#include "util/file.h"
#include "util/id.h"
#include "util/tim3.h"

Texture *texture;

#define MAX_ENTITY_RENDERERS 1000

HashMap GameRenderer_entity_renderers;

Model *model_sea;

int GameRenderer_init() {
  texture = malloc(sizeof(Texture));
  *texture = Texture_load_from_image("res/img/texture.png");

  GameRenderer_entity_renderers = HashMap_new(MAX_ENTITY_RENDERERS, sizeof(Id));

  model_sea = ModelSea_build();

  return 0;
}

void GameRenderer_render(RenderContext *render_context) {
  Texture_bind(texture);

  M camera_transform = Camera_get_transform(&Game_camera);
  MStack_push(&render_context->matrix_stack, camera_transform);

  RenderContext_render(render_context, model_sea);

  List entities = Game_get_entities();
  Iterator entities_iter = Iterator_new(&entities);
  while (Iterator_has_next(&entities_iter)) {
    Entity *entity = Iterator_next(&entities_iter);

    EntityRenderer *entity_renderer =
        HashMap_get(GameRenderer_entity_renderers, &entity->id);

    if (entity_renderer == NULL) {
      entity_renderer = EntityRenderer_new_ptr(entity);
      if (entity_renderer != NULL) {
        HashMap_add(GameRenderer_entity_renderers, &entity->id,
                    entity_renderer);
      }
    }

    if (entity_renderer != NULL) {
      EntityRenderer_render(entity_renderer, render_context);
    }
  }
}
