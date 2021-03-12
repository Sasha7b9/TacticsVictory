// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "Core/Structures_.h"


class WaveAlgorithm : public Thread, public Object
{
    URHO3D_OBJECT(WaveAlgorithm, Object);

public:
    WaveAlgorithm(Context *);
    virtual ~WaveAlgorithm();
    static void RegisterObject();

    void SetSize(uint numRows, uint numCols);
    void StartFind(Coord start, Coord end);
    bool PathIsFound();
    PODVector<Coord> GetPath();
    virtual void ThreadFunction();

private:
    typedef Vector<Coord> Wave;
    Vector<Vector<int>> cells;
    float heightStart = 0.0f;
    uint numRows = 0;
    uint numCols = 0;
    PODVector<Coord> path;
    Coord start;
    Coord end;
    bool pathIsFound = true;

    bool Contain(const Wave &wave, const Coord &coord);
    void NextWave(Vector<Wave> &waves);
    void SetCell(Wave &wave, uint row, uint col, int numWave);
    void AddPrevWave(PODVector<Coord> &path);
    void FindPath();

    static void RegisterInAS();

public:
    CScriptArray* GetPathUINT()
    {
        static PODVector<uint> vect;
        vect.Clear();
        for (uint i = 0; i < 10; i++)
        {
            vect.Push(i);
        }

        return VectorToArray<uint>(vect, "Array<uint>");
    }
    const PODVector<String>& GetPathString()
    {
        static PODVector<String> vect;
        vect.Resize(10);
        return vect;
    }

    uint GetUINT()
    {
        return 5;
    }
};


#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4505)
#endif

/*
static CScriptArray* WaveAlgorithmGetUINT(WaveAlgorithm *wave)
{
    return VectorToArray<uint>(wave->GetPathUINT(), "Array<uint>");
}
*/

static CScriptArray* WaveAlgorithmGetString(WaveAlgorithm *wave)
{
    return VectorToArray<String>(wave->GetPathString(), "Array<String>");
}

#ifdef WIN32
#pragma warning(pop)
#endif
