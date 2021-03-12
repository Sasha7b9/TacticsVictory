// 2021/03/12 12:00:09 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Scene/Terrain/Level_.h"
#include "Scene/Terrain/SegmentTerrain_.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/StringUtils.h"


static bool IsCorrectSymbol(char symbol)
{
    if (symbol == '+')
    {
        return true;
    }
    if (symbol == '-')
    {
        return true;
    }
    if (symbol >= '0' && symbol <= '9')
    {
        return true;
    }
    return false;
}


static int PushToVector(const char *data, Vector<float> *vec)
{
    char buffer[20] = { 0 };

    int retValue = 0;

    while (IsCorrectSymbol(*data))
    {
        char add[2] = { *data, 0 };
        SU::Strcat(buffer, add);
        retValue++;
        data++;
    }

    float value = (float)atof(buffer);
    vec->Push(value);

    return retValue;
}


void Level::CreateFromVector(const Vector<Vector<float>> &lev)
{
    Clear();

    uint num_rows = lev.Size();

    for (uint row = 0; row < num_rows; row++)
    {
        Vector<LogicCell> layer;
        layer.Resize(lev[row].Size());
        level.Push(layer);

        uint num_cols = lev[row].Size();

        for (uint col = 0; col < num_cols; col++)
        {
            level[row][col].height = lev[row][col];
        }
    }
}


void Level::SetHeight(uint rowX, uint colZ, float height)
{
    level[rowX][colZ].height = height;
}


float Level::GetHeight(uint rowX, uint colZ) const
{
    if (colZ >= level[0].Size() || rowX >= level.Size())
    {
        return 0;
    }

    return level[rowX][colZ].height;
}


void Level::Load(const char *fileName)
{
    map.Clear();

    SharedPtr<File> fileRead;
    fileRead = new File(TheContext);

    fileRead->Open(fileName, FILE_READ);

    if (!fileRead->IsOpen())
    {
        fileRead->Open(GF::GetNameFile(fileName), FILE_READ);
    }

    if (fileRead->IsOpen())
    {
        String str = fileRead->ReadString();
        const char *data = str.CString();
        size_t sizeData = strlen(data);

        const char *end = data + sizeData;

        Vector<float> curString;

        while (data < end)
        {
            if (*data == '\n' || *data == 0x0d)
            {
                map.Push(curString);
                curString.Clear();
                data += 2;
                continue;
            }
            if (*data == ' ')
            {
                data++;
                continue;
            }
            if (IsCorrectSymbol(*data))
            {
                data += static_cast<uint64>(PushToVector(data, &curString));
            }
        }
    }
    else
    {
        LOGERROR("Can not load file");
    }

    fileRead->Close();

    uint numRows = map.Size();

    map.Resize((numRows / SegmentTerrain::WIDTH_Z) * SegmentTerrain::WIDTH_Z);


    uint numCols = map[0].Size();

    for (uint i = 0; i < map.Size(); i++)
    {
        map[i].Resize((numCols / SegmentTerrain::HEIGHT_X) * SegmentTerrain::HEIGHT_X);
    }
}


void Level::Load(MemoryBuffer &msg)
{
#define NAME_TEMP_FILE "level.tmp"

    SharedPtr<File> file(new File(TheContext));

    file->Open(NAME_TEMP_FILE, FILE_WRITE);

    uint height = msg.ReadUInt();
    uint width = msg.ReadUInt();

    for (uint row = 0; row < height; row++)
    {
        for (uint col = 0; col < width; col++)
        {
            String value = String(msg.ReadFloat()) + " ";

            file->Write(value.CString(), value.Length());
        }

        file->WriteByte(0x0d);
        file->WriteByte(0x0a);
    }

    file->Close();

    Load(NAME_TEMP_FILE);

    TheFileSystem->Delete(NAME_TEMP_FILE);
}


bool Level::Save(const String &fileName)
{
    SharedPtr<File> fileWrite(new File(TheContext));

    if (fileWrite->Open(fileName, FILE_WRITE))
    {
        for (uint row = 0; row < map.Size(); row++)
        {
            String line;
            for (uint col = 0; col < map[0].Size(); col++)
            {
                line += String(map[row][col]);
                if (col != map[0].Size() - 1)
                {
                    line += " ";
                }
            }
            fileWrite->WriteLine(line);
        }
        fileWrite->Close();
    }
    else
    {
        return false;
    }
    return true;
}


Vector<Vector<float>> Level::CreateRandom(uint numRows, uint numCols)
{
    map.Clear();

    int minHeight = 0;
    int maxHeight = 20;

    int maxDelta = 2;

    Vector<float> str;

    srand((uint)time(NULL)); //-V202

    SetRandomSeed(static_cast<uint>(rand()));

    str.Push(static_cast<float>(Math::RandomInt(minHeight, maxHeight)));

    for (uint col = 1; col < numCols; col++)
    {
        int min = Math::LimitBelow(static_cast<int>(str[col - 1]) - maxDelta, minHeight);
        int max = Math::LimitAbove(static_cast<int>(str[col - 1]) + maxDelta, maxHeight);

        str.Push(static_cast<float>(Math::RandomInt(min, max)));
    }

    map.Push(str);

    for (uint row = 1; row < numRows; row++)
    {
        str.Clear();

        int min = Math::LimitBelow(static_cast<int>(map[row - 1][0] - maxDelta), minHeight);
        int max = Math::LimitAbove(static_cast<int>(map[row - 1][0] + maxDelta), maxHeight);

        str.Push(static_cast<float>(Math::RandomInt(min, max)));

        for (uint col = 1; col < numCols; col++)
        {
            min = Math::LimitBelow(static_cast<int>(str[col - 1]) - maxDelta, minHeight);
            max = Math::LimitAbove(static_cast<int>(str[col - 1]) + maxDelta, maxHeight);

            int value = Math::RandomInt(min, max);

            while (value < map[row - 1][col] - maxDelta || value > map[row - 1][col] + maxDelta)
            {
                value = Math::RandomInt(min, max);
            }

            str.Push(static_cast<float>(value));
        }

        map.Push(str);
    }

    VariantMap eventData = GetEventDataMap();
    SendEvent(E_MAP_CHANGED, eventData);

    return map;
}
