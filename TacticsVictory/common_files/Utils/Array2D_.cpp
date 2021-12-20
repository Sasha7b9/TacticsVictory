// 2021/12/10 23:14:43 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Utils/Array2D_.h"


using namespace Pi;

template      Array2D<float>::Array2D(int, int);
template      Array2D<int>::Array2D(int, int);
template      Array2D<float>::Array2D(const Array2D<float> &);
template Array2D<float> &Array2D<float>::operator=(const Array2D<float> &);
template void Array2D<float>::SetDimensions(int, int);
template void Array2D<int>::SetDimensions(int, int);
template void Array2D<int>::Fill(int);


template <typename T>
Array2D<T>::Array2D(int sizeX, int sizeY)
{
    SetDimensions(sizeX, sizeY);
}


template <typename T>
Array2D<T>::Array2D(const Array2D &rhs)
{
    SetDimensions(rhs.GetNumberColumns(), rhs.GetNumberRows());

    for (int col = 0; col < GetNumberColumns(); col++)
    {
        for (int row = 0; row < GetNumberRows(); row++)
        {
            At(col, row) = rhs.At(col, row);
        }
    }
}


template <typename T>
Array2D<T> &Array2D<T>::operator=(const Array2D<T> &rhs)
{
    SetDimensions(rhs.GetNumberColumns(), rhs.GetNumberRows());

    for (int col = 0; col < GetNumberColumns(); col++)
    {
        for (int row = 0; row < GetNumberRows(); row++)
        {
            At(col, row) = rhs.At(col, row);
        }
    }

    return *this;
}


template <typename T>
void Array2D<T>::SetDimensions(int numCols, int numRows)
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
