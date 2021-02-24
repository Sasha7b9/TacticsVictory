// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Game/Path/TWaveAlgorithm_.h"


class PathIndicator
{
public:
    PathIndicator();
    ~PathIndicator();

    void Update();
    void Enable();
    void Disable();
    void SetStartPosition(const Coord &start);

    PODVector<Coord> &GetPath();

private:
    WaveAlgorithm pathFinder;
    bool enabled = false;
    Coord start;
    PODVector<Coord> path;
};
