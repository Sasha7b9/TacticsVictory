#pragma once


EVENT(E_MAP_CHANGED, MapChanged)
{

}


class Level : public Urho3D::Object
{
    OBJECT(Level);

public:
    Level(UContext *context = gContext);

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
    Level& operator=(const Level&)
    {
    };

    static Vector<Vector<float>> map;
};