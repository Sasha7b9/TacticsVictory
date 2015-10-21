#include <stdafx.h>


#include "Level.h"
#include "Game/Objects/Terrain.h"


Vector<Vector<float> > vLevel::map;


vLevel::vLevel()
{

}

static bool IsCorrectSymbol(char symbol)
{
    if(symbol == '+')
    {
        return true;
    }
    if(symbol == '-')
    {
        return true;
    }
    if(symbol >= '0' && symbol <= '9')
    {
        return true;
    }
    return false;
}

static int PushToVector(const char *data, Vector<float> *vec)
{
    char buffer[20] = {0};

    int retValue = 0;

    while(IsCorrectSymbol(*data))
    {
        char add[2] = {*data, 0};
        strcat(buffer, add);
        retValue++;
        data++;
    }

    int value = atoi(buffer);
    vec->Push((float)value);

    return retValue;
}

Vector<Vector<float> > vLevel::Get()
{
    return map;
}

Vector<Vector<float> > vLevel::Load(char *fileName)
{
    SharedPtr<File> fileRead;
    fileRead = new File(gContext);
    if(fileRead->Open(fileName, Urho3D::FILE_READ))
    {
        String str = fileRead->ReadString();
        const char *data = str.CString();
        size_t sizeData = strlen(data);

        const char *end = data + sizeData;

        Vector<float> curString;

        while(data < end)
        {
            if(*data == 0x0d)
            {
                map.Push(curString);
                curString.Clear();
                data += 2;
                continue;
            }
            if(*data == ' ')
            {
                data++;
                continue;
            }
            if(IsCorrectSymbol(*data))
            {
                data += PushToVector(data, &curString);
            }
        }
        fileRead->Close();
    }

    uint numRows = map.Size();

    map.Resize((numRows / lTerrain::SIZE_BLOCK) * lTerrain::SIZE_BLOCK);


    uint numCols = map[0].Size();

    for (int i = 0; i < map.Size(); i++)
    {
        map[i].Resize((numCols / lTerrain::SIZE_BLOCK) * lTerrain::SIZE_BLOCK);
    }

    return map;
}

Vector<Vector<float> > vLevel::Create(int sizeZ, int sizeX)
{
    map.Clear();

    for (int x = 0; x < sizeX; x++)
    {
        Vector<float> str;
        for (int z = 0; z < sizeZ; z++)
        {
            str.Push(0.0f);
        }
        map.Push(str);
    }

    return map;
}

Vector<Vector<float> > vLevel::CreateRandom(int sizeZ, int sizeX)
{
    map.Clear();

    for (int x = 0; x < sizeX; x++)
    {
        Vector<float> str;

        for (int z = 0; z < sizeZ; z++)
        {
            str.Push((float)(int)Random(5.0f, 10.0f));
        }

        map.Push(str);
    }

    return map;
}