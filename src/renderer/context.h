#pragma once


// Type definitions

typedef struct TW_Position {
    int x;
    int y;
} TW_Position;


// Function definitions

TW_Position* TW_Position_Create( int x, int y );

void TW_Position_Update( TW_Position* self, int x, int y );

void TW_Position_Free( TW_Position* self );