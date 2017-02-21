#pragma once


URHO3D_EVENT(E_MAP_CHANGED, MapChanged)
{

}


class Level : public Object
{
    URHO3D_OBJECT(Level, Object);

public:
    Level(Context *context = gContext);

    Vector<Vector<float>> Load(char *fileName);             // Load from file simple level (from height map)
    bool Save(String fileName);
    Vector<Vector<float>> Create(int sizeZ, int sizeX);     // Create a new simpe level height == 0.0f; 
    Vector<Vector<float>> CreateRandom(uint numRows, uint numCols);
    Vector<Vector<float>> Get();                            // Return the last loaded or created level
    void Clear();
    uint GetWidth();
    uint GetHeight();
    void SetMap(Vector<Vector<float>> map);

private:
    static Vector<Vector<float>> map;

    CONSTRUCTORS(Level, Object);
};