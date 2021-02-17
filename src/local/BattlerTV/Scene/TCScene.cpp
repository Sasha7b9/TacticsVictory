// 2021/02/17 13:13:02 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"


CScene::~CScene()
{
    SAFE_DELETE(TheWindowTarget);

    pathIndicator.Stop();
}
