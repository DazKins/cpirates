#ifndef GAME_RENDER_H
#define GAME_RENDER_H

#include "game/game.h"
#include "render/render_context.h"
#include "util/map.h"

int GameRenderer_init();
void GameRenderer_render(RenderContext *render_context);

extern HashMap GameRenderer_entity_renderers;

#endif // !GAME_RENDER_H
