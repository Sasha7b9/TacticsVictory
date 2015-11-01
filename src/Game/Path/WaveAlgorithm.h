#pragma once


#include "PathSegment.h"


class WaveAlgorithm
{
public:
    PODVector<Coord> GetPath(Coord start, Coord end);

    void CalculateWaves(Coord coord, int numWave);   // ���������� ������ ����� ������

    struct Cell
    {
        int numWave = 0;    // -1 ��� �� ��������, -2 - ������������ �������
        Coord parent;
    };

    Vector<Vector<Cell>> cells;
    Coord end;
    Coord start;
    float height = 0.0f;
};