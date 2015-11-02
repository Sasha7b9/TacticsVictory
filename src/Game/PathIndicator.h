#pragma once


#include "Game/Path/PathWave.h"


class lPathIndicator
{
public:
    lPathIndicator();

    void SetVisible(bool visible);
    void SetInCurrentCursorPosition(Drawable *hitDrawable = 0, Vector3 *hitPos = 0);  // To establish the floating image in a cursor position

private:
    SharedPtr<DecalSet> decal;
    PathWave pathFinder;
};