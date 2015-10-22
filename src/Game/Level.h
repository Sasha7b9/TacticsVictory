#pragma once


EVENT(E_MAP_CHANGED, MapChanged)
{

}


class lLevel : public Object
{
    OBJECT(lLevel);

public:
    lLevel(Context *context = gContext);

    Vector<Vector<float>> Load(char *fileName);             // Load from file simple level (from height map)
    Vector<Vector<float>> Create(int sizeZ, int sizeX);     // Create a new simpe level height == 0.0f; 
    Vector<Vector<float>> CreateRandom(int sizeZ, int sizeX);
    Vector<Vector<float>> Get();                            // Return the last loaded or created level
    void Clear();
    uint GetWidth();
    uint GetHeight();

private:
    lLevel& operator=(const lLevel&)
    {
    };

    static Vector<Vector<float> > map;
};