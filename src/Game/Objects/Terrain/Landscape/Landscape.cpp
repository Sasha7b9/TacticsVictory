#include <stdafx.h>


#include "Landscape.h"


Landscape::Landscape(Context *context) :
    Object(context)
{

}

void Landscape::CreateFromVector(Vector<Vector<float>> &level)
{
    URHO3D_LOGINFOF("1 %f", gTime->GetElapsedTime());
    uint height = SegmentLandscape::HEIGHT;
    uint width = SegmentLandscape::WIDTH;

    uint segmentsInZ = level.Size() / height + ((level.Size() % height) == 0 ? 0 : 1);
    uint segmentsInX = level[0].Size() / width + ((level.Size() % width) == 0 ? 0 : 1);

    uint allRows = level.Size();
    uint allCols = level[0].Size();

    segments.Resize(segmentsInZ);

    for(uint row0 = 0; row0 < allRows; row0 += height)
    {
        segments[row0 / height].Resize(segmentsInX);

        for(uint col0 = 0; col0 < allCols; col0 += width)
        {
            uint numRows = (row0 + height > allRows) ? (allRows - row0) : height;
            uint numCols = (col0 + width > allCols) ? (allCols - col0) : width;

            uint i = row0 / height;
            uint j = col0 / width;

            segments[i][j] = new SegmentLandscape();

            segments[i][j]->CreateFromVector(level, row0, col0, numRows, numCols);
        }
    }

    URHO3D_LOGINFOF("2 %f", gTime->GetElapsedTime());

    for(uint z = 0; z < segmentsInZ; z++)
    {
        for(uint x = 0; x < segmentsInX; x++)
        {
            SegmentLandscape *segment = segments[z][x];
            if(x > 0)
            {
                segment->neighbours[SegmentLandscape::LEFT] = segments[z][x - 1];
            }
            if(z > 0)
            {
                segment->neighbours[SegmentLandscape::TOP] = segments[z - 1][x];
            }
            if(x < segmentsInX - 1)
            {
                segment->neighbours[SegmentLandscape::RIGHT] = segments[z][x + 1];
            }
            if(z < segmentsInZ - 1)
            {
                segment->neighbours[SegmentLandscape::BOTTOM] = segments[z + 1][x];
            }
        }
    }

    URHO3D_LOGINFOF("3 %f", gTime->GetElapsedTime());
    for(auto row : segments)
    {
        for(SegmentLandscape* segment : row)
        {
            segment->Build();
        }
    }
    URHO3D_LOGINFOF("4 %f", gTime->GetElapsedTime());
}

void Landscape::SaveToFile(char * /*nameFile*/)
{

}
