#pragma once

#include "math.h"
#include "memory.h"
#include <SDL3/SDL.h>

typedef struct {
  SDL_Renderer *renderer;
  memory_arena memory;
  v2 screenCenter;
} game_renderer;

#define PIXELS_PER_METER 60
#define METERS_PER_PIXEL (1.0f / PIXELS_PER_METER)

void
RenderFrame(game_renderer *renderer);

void
ClearScreen(game_renderer *renderer, v4 color);

void
DrawLine(game_renderer *renderer, v2 from, v2 to, v4 color, f32 width);

void
DrawCircle(game_renderer *renderer, v2 position, f32 radius, v4 color);

void
DrawRect(game_renderer *renderer, rect rect, v4 color);

void
DrawCrosshair(game_renderer *renderer, v2 position, f32 dim, v4 color);

rect
RendererGetSurfaceRect(game_renderer *renderer);
