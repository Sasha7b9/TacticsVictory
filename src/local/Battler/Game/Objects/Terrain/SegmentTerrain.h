#pragma once



class CubeTerrain;
class LayerTerrain;



class SegmentTerrain : public Object
{
    URHO3D_OBJECT(SegmentTerrain, Object);

public:

    enum
    {
        LEFT,
        TOP,
        RIGHT,
        BOTTOM
    };

    SegmentTerrain(Context *context = gContext);
    ~SegmentTerrain();
    void CreateFromVector(const Vector<Vector<float>> &level, uint row0, uint col0, uint numRows, uint numCols);
    void Build();
    void GetColumnCubes(uint row, uint col, PODVector<CubeTerrain*> &column);

    static const uint WIDTH = 10;
    static const uint HEIGHT = 10;
    SegmentTerrain* neighbours[4];      // Соседи соотвественно с четырёх сторон //-V122

private:
    Vector<SharedPtr<LayerTerrain>> ground;          // Height (0, 1, 2, 3, ...)
    Vector<SharedPtr<LayerTerrain>> underGround;     // Height [0, -1, -2, ...)


    void AddCube(const SharedPtr<CubeTerrain> &cube);
    void CreateLayers();

    DEFAULT_MEMBERS(SegmentTerrain);
};
