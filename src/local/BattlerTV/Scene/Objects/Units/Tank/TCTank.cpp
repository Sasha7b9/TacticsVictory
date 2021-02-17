// 2021/02/17 15:45:38 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"


void CTank::RegisterObject(Context *context)
{
    context->RegisterFactory<CTank>();
}
