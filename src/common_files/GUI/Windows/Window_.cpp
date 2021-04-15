// 2021/04/15 15:05:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Windows/Window_.h"


WindowT::WindowT() : Control(TheContext)
{

}


void WindowT::HandlerResize(StringHash, VariantMap &)
{
    CallbackOnResize();
}
