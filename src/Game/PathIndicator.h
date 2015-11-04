#pragma once


#include "Game/Path/PathWave.h"


class PathIndicator
{
public:
    PathIndicator();

    void Init();

    void SetVisible(bool visible);
    void SetInCurrentCursorPosition(UDrawable *hitDrawable = 0, Vector3 *hitPos = 0);  // To establish the floating image in a cursor position

private:
    PathWave pathFinder;
};