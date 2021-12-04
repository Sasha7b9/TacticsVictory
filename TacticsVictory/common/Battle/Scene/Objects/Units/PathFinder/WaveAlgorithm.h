// 2021/12/4 11:09:12 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{

class WaveAlgorithm : public Thread
{
public:
    WaveAlgorithm();
    virtual ~WaveAlgorithm();

    void SetSize(uint numRows, uint numCols);
    bool PathIsFound();
    Array<Point2D> GetPath();
    virtual void ThreadFunction();

private:
    typedef Array<Point2D> Wave;
    Array<Array<int>> cells;
    float heightStart = 0.0f;
    uint numRows = 0;
    uint numCols = 0;
    Array<Point2D> path;
    Point2D start;
    Point2D end;
    bool pathIsFound = true;

    void SetCell(Wave &wave, uint row, uint col, int numWave);
    void FindPath();

    void StartFind(Point2D start, Point2D end);
    void NextWave(Array<Wave> &waves);
    bool Contain(const Wave &wave, const Point2D &coord);
    void AddPrevWave(Array<Point2D> &path);

public:

    const Array<String<>>& GetPathString()
    {
        static Array<String<>> vect;
        vect.SetElementCount(10);
        return vect;
    }

    uint GetUINT()
    {
        return 5;
    }
};

}