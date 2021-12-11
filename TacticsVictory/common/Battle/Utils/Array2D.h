// 2021/12/10 23:14:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    template <typename T>
    class Array2D
    {
    public:
        void SetDimensions(int numCols, int numRows);
        int GetNumberRows() const { return array.GetElementCount(); }
        int GetNumberColumns() const { return GetNumberRows() > 0 ? array[0].GetElementCount() : 0; }
        void Fill(T value);
        T &At(int col, int row) { return array[row][col]; }
    private:
        Array<Array<T>> array;
    };
}
