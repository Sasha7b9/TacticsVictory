// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


URHO3D_EVENT(E_MAP_CHANGED, MapChanged)
{

}


class Level : public Object
{
    URHO3D_OBJECT(Level, Object);

public:
    Level(Context *context = TheContext);
    void Load(const char *fileName);
    void Load(MemoryBuffer &msg);
    bool Save(const String &fileName);
    Vector<Vector<float>> Create(int sizeZ, int sizeX);     // Create a new simpe level height == 0.0f; 
    Vector<Vector<float>> CreateRandom(uint numRows, uint numCols);
    Vector<Vector<float>> Get();                            // Return the last loaded or created level
    void Clear();
    uint GetWidthZ();
    uint GetHeightX();
    void SetMap(const Vector<Vector<float>> &map);

    static Vector<Vector<float>> map;
};
