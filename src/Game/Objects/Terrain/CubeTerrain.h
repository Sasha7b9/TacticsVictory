#pragma once


#include "SideCube.h"
#include "CornerCube.h"
#include "EdgeCube.h"


class Terrain;


class CubeTerrain : public Object
{
    URHO3D_OBJECT(CubeTerrain, Object);

public:
    CubeTerrain(Context *context = gContext);
    CubeTerrain(uint row, uint col, float height);  // Create cube with one

    void Create();

    void BuildVertexes(PODVector<float> &vertexes, PODVector<uint> &indexes);

    SideCube    sides[4];
    CornerCube  corners[4];
    EdgeCube    edges[2];

    uint row = 0;
    uint col = 0;
    uint layer = 0;
    bool underGround = false;

    static Terrain *terrain;

private:

    #define S_LEFT      0
    #define S_TOP       1
    #define S_RIGHT     2
    #define S_DOWN      3
    
    #define C_TOPLEFT   0
    #define C_TOPRIGHT  1
    #define C_DOWNRIGHT 2
    #define C_DOWNLEFT  3
    
    #define E_TOP       0
    #define E_DOWN      1


    PODVector<float> *vertexes = nullptr;

    CubeTerrain& operator=(const CubeTerrain&)
    {};

    void CreateEdges();
    void CreateEdgeTop();
    void CreateEdgeDown();

    void CreateSides();
    void CreateSideLeft();
    void CreateSideTop();
    void CreateSideRight();
    void CreateSideDown();

    void PushPoint(PointPlane &point);
};

/*                     Corner_0              Corner_1
                          |                    |                                                      
                          |   Edge_0           |                                                      
                          |     |              |                                                      
                          |     |              |                                                      
                          |     |              |                                                      
                          /-----+--------------/
                        /       |            / |                           /|\ Y
                      /         |          /   |                            |
                    /                    /     |                            |    -/| Z
                  /                  / |       |                            |    /
                 |----------------| /  |       |                            |   /
                 |                |    |       |                            |  /
                 |                |    |       |                            | /         
                 |                |    |       |                            |/----------+
                 |                |    |      /                                          X
                 |                |    |    /
                 |       |        |    |   /
                 |       |        |    | /
                 |       |        |  / |/
                 |-------+--------|/  \
                         |             \
                         |              \
                         |            Corner_2
                       Side_3
*/                       
