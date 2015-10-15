#pragma once


class Level
{
public:
    Level();

    static Vector<Vector<float> > Load(char *fileName);             // Load from file simple level (from height map)
    static Vector<Vector<float> > Create(int sizeZ, int sizeX);     // Create a new simpe level height == 0.0f; 
    static Vector<Vector<float> > CreateRandom(int sizeZ, int sizeX);
    static Vector<Vector<float> > Get();                            // Return the last loaded or created level

private:
    static Vector<Vector<float> > map;
};