#include "../listener.h"


TW_L_Quit* TW_L_Quit_Create()
{
    TW_L_Quit* quitListener = malloc( sizeof( TW_L_Quit ) );
    quitListener->quit = false;
    return quitListener;
}


void TW_L_Quit_Free( TW_L_Quit* self )
{
    self->quit = false;
    free( self );
}


void TW_L_Quit_Check( TW_L_Quit* self, SDL_Event event )
{
    if( event.type == SDL_QUIT )
    {
        self->quit = true;
    }
}


//
void TW_L_Quit_Clear( TW_L_Quit* self )
{
    self->quit = false;
}