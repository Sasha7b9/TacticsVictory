// 2021/12/10 23:14:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace Pi
{
    template <typename T>
    class Array2D
    {
    public:
        void SetDimensions(int numRows, int numCols);
        void Fill(T value);
        T *operator[](uint i) { return array[i]; }
    private:
        Array<Array<T>> array;
    };
}
