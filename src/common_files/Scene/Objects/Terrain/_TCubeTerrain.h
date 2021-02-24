/* (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by */
#pragma once
#include "Scene/Objects/Terrain/_TCornerCube.h"


class SideCube;
class EdgeCube;
class PointPlane;
class PlaneCube;
class TTerrain;


class CubeTerrain : public Object
{
    URHO3D_OBJECT(CubeTerrain, Object);

public:

    struct SIDE { enum E {
        LEFT = 0,
        TOP = 1,
        RIGHT = 2,
        DOWN = 3
    }; };

    enum CORNER
    {
        C_TOPLEFT = 0,
        C_TOPRIGHT = 1,
        C_DOWNRIGHT = 2,
        C_DOWNLEFT = 3
    };

    struct EDGE { enum E {
        TOP = 0,
        DOWN = 1
    }; };

public:
    CubeTerrain(Context *context = TheContext);
    CubeTerrain(uint row, uint col, float height);  // Create cube with one
    void Create();
    void BuildVertexes(PODVector<float> &vertexes, PODVector<uint> &indexes);
    Vector3& GetEdgeCoord(EDGE::E edge, CORNER corner);

    SharedPtr<SideCube>     sides[4];
    SharedPtr<CornerCube>   corners[4];
    SharedPtr<EdgeCube>     edges[2];
    uint row = 0;
    uint col = 0;
    uint layer = 0;
    bool underGround = false;
    static TTerrain *terrain;

private:

    PODVector<float> *vertexes = nullptr; //-V122
    PODVector<uint>  *indexes = nullptr; //-V122

    void CreateEdges();
    void CreateEdgeTop();
    void CreateEdgeDown();
    void CreateSides();
    void CreateSideLeft();
    void CreateSideTop();
    void CreateSideRight();
    void CreateSideDown();
    SharedPtr<SideCube> CreateSide(SIDE::E side, float anotherHeight);
    void PushPoint(const PointPlane &point);
    void BuildPlaneVerexes(const PlaneCube &plane);
    float CalculateHeight() const;
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
