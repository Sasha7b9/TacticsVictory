#include <stdafx.h>


#include "GlobalFunctions.h"


void SetWindowInCenterScreen(Window *window)
{
    window->SetPosition(gGraphics->GetWidth() / 2 - window->GetWidth() / 2, gGraphics->GetHeight() / 2 - window->GetHeight() / 2);
}
