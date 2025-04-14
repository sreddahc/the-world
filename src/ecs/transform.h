#pragma once


// Type definitions

typedef struct TW_Transform {
    int x;
    int y;
    float angle;
    float scale;
} TW_Transform;


// Function definitions

TW_Transform* TW_Position_Create( int x, int y );

void TW_Position_Update( TW_Transform* self, int x, int y );

void TW_Position_Free( TW_Transform* self );