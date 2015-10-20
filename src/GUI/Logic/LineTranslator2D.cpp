#include <stdafx.h>


#include "LineTranslator2D.h"
#include "GUI/Logic/LineTranslator1D.h"


vLineTranslator2D::vLineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition) :
    Object(gContext)
{
    translatorX = new vLineTranslator1D(start.x_, finish.x_, speed, (vLineTranslator1D::State)startPosition);
    translatorY = new vLineTranslator1D(start.y_, finish.y_, speed, (vLineTranslator1D::State)startPosition);
}

void vLineTranslator2D::Toggle()
{
    translatorX->Toggle();
    translatorY->Toggle();
}

IntVector2 vLineTranslator2D::Update(float dT)
{
    return IntVector2(translatorX->Update(dT), translatorY->Update(dT));
}