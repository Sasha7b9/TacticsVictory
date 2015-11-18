#pragma once


class Landscape
{
public:
    Landscape();

    void CreateFromVector(Vector<Vector<float>> &level);

    void SaveToFile(char *nameFile);

private:
};
