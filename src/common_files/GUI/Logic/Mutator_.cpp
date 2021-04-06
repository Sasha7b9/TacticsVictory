// 2021/04/06 12:10:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Logic/Mutator_.h"


Mutator::Mutator(UIElement *n) : Object(TheContext), node(n)
{

}


Mutator *Mutator::Empty()
{
    return nullptr;
}
