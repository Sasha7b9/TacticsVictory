// 2021/02/17 16:49:37 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by 
#include "stdafx.h"


SharedPtr<Tank> SScene::CreateTank()
{
    return STank::Create(Tank::Type::Small);
}


void SScene::RegisterObject(Context *context)
{
    context->RegisterFactory<SScene>();
}
