// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Game/Path/TWaveAlgorithm_.h"


class PathIndicator
{
public:
    PathIndicator();

    void Init();
    void Update();
    void Enable(bool enable);
    void SetStartPosition(const Coord &start);
    void Stop();

    PODVector<Coord> &GetPath();

private:
    WaveAlgorithm pathFinder;
    bool enabled = false;
    Coord start;
    PODVector<Coord> path;
};
