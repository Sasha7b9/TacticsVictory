#include <stdafx.h>


tvLineTranslator2D::tvLineTranslator2D(const IntVector2 &start, const IntVector2 &finish, float speed, State startPosition) :
    Object(gContext)
{
    translatorX = new tvLineTranslator1D(start.x_, finish.x_, speed, (tvLineTranslator1D::State)startPosition);
    translatorY = new tvLineTranslator1D(start.y_, finish.y_, speed, (tvLineTranslator1D::State)startPosition);
}

void tvLineTranslator2D::Toggle()
{
    translatorX->Toggle();
    translatorY->Toggle();
}

IntVector2 tvLineTranslator2D::Update(float dT)
{
    return IntVector2(translatorX->Update(dT), translatorY->Update(dT));
}