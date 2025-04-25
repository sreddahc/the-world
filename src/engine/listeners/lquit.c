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