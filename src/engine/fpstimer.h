#pragma once

#include <SDL2/SDL.h>

#define MILLISECONDS_IN_A_SEC 1000.f
#define FRAME_CAP 200000

typedef struct TW_FPSTimer {
    Uint64 ms;      // Milliseconds
    Uint64 frame;   // Frames
} TW_FPSTimer;

void TW_FPSTimer_Init( TW_FPSTimer* self );
void TW_FPSTimer_Update( TW_FPSTimer* self );
float TW_FPSTimer_GetFPS( TW_FPSTimer* self );
void TW_FPSTimer_Free( TW_FPSTimer* self );
