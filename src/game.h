#pragma once

#include "math.h"
#include "memory.h"
#include "random.h"
#include "renderer.h"
#include "type.h"

#if IS_BUILD_DEBUG
#include "string_builder.h"
#endif

typedef struct {
  b8 a : 1;
  b8 b : 1;
  b8 x : 1;
  b8 y : 1;

  b8 back : 1;
  b8 start : 1;
  b8 home : 1;

  b8 ls : 1;
  b8 rs : 1;

  b8 lb : 1;
  b8 rb : 1;

  // [-1, 1] math coordinates
  f32 lsX;
  // [-1, 1] math coordinates
  f32 lsY;
  // [-1, 1] math coordinates
  f32 rsX;
  // [-1, 1] math coordinates
  f32 rsY;

  // [0, 1] math coordinates
  f32 lt;
  // [0, 1] math coordinates
  f32 rt;
} game_controller;

static inline game_controller *
GameControllerGetKeyboard(game_controller *controllers, u32 controllerCount)
{
  debug_assert(controllerCount > 0);
  u32 index = 0;
  debug_assert(index < controllerCount);
  game_controller *controller = controllers + index;
  return controller;
}

static inline game_controller *
GameControllerGetGamepad(game_controller *controllers, u32 controllerCount, u32 index)
{
  debug_assert(controllerCount > 0);
  index += 1; // 0 is reserved for keyboard
  debug_assert(index < controllerCount);
  game_controller *controller = controllers + index;
  return controller;
}

typedef struct {
  f32 dt;                         // in seconds
  game_controller controllers[3]; // 1 keyboard + 2 controllers
} game_input;

typedef struct particle {
  v2 position;     // unit: m
  v2 velocity;     // unit: m/s
  v2 acceleration; // unit: m/s²
  f32 mass;        // unit: kg
  f32 invMass;     // computed from 1/mass
} particle;

typedef struct {
  b8 isInitialized : 1;

  memory_arena worldArena;

  random_series effectsEntropy;
  particle *particles;
  u32 particleCount;

  rect liquid;
} game_state;

typedef struct {
  void *permanentStorage;
  u64 permanentStorageSize;

  void *transientStorage;
  u64 transientStorageSize;
} game_memory;

typedef struct {
  b8 isInitialized : 1;
  memory_arena transientArena;
  string_builder *sb;
} transient_state;

typedef void (*pfnGameUpdateAndRender)(game_memory *memory, game_input *input, game_renderer *renderer);
void
GameUpdateAndRender(game_memory *memory, game_input *input, game_renderer *renderer);
