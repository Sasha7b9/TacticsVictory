// 2021/12/10 23:14:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Array2D.h"


using namespace Pi;

template void Array2D<int>::SetDimensions(int, int);
template void Array2D<int>::Fill(int);


template <typename T>
void Array2D<T>::SetDimensions(int numRows, int numCols)
{
    array.SetElementCount(numRows);

    for (auto &row : array)
    {
        row.SetElementCount(numCols);
    }
}


template <typename T>
void Array2D<T>::Fill(T value)
{
    for (auto &row : array)
    {
        for (auto &cell : row)
        {
            cell = value;
        }
    }
}
