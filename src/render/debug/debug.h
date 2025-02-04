#ifndef RENDER_DEBUG_H
#define RENDER_DEBUG_H

#include "math/obb.h"
#include "math/v.h"

void DebugRender_point(V v, float size);
void DebugRender_obb(OBB obb);

#endif // !RENDER_DEBUG_H