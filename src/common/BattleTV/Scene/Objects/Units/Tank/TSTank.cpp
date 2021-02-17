// 2021/02/17 15:56:57 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"


void STank::RegisterObject(Context *context)
{
    context->RegisterFactory<STank>();
}