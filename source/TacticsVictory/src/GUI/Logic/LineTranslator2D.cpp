// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <stdafx.h>
#include "LineTranslator2D.h"
#include "GUI/Logic/LineTranslator1D.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LineTranslator2D::LineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition) :
    Object(gContext)
{
    translatorX = new LineTranslator1D(start.x_, finish.x_, speed, (LineTranslator1D::State)startPosition);
    translatorY = new LineTranslator1D(start.y_, finish.y_, speed, (LineTranslator1D::State)startPosition);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void LineTranslator2D::Toggle()
{
    translatorX->Toggle();
    translatorY->Toggle();
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
IntVector2 LineTranslator2D::Update(float dT)
{
    int x = translatorX->Update(dT);
    int y = translatorY->Update(dT);

    return IntVector2(x, y);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
LineTranslator2D::State LineTranslator2D::GetState()
{
    return (State)translatorX->GetState();
}
