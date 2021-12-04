// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "CheckBox.h"
#include "Settings.h"


using namespace Pi;


CheckBoxSkin::CheckBoxSkin(pchar text, uint state, bool /*shadowed*/, bool /*checkded*/) : DrawingWidget(SET::GUI::CHECKBOX::SIZE())
{
    ColorRGBA _colorBackground(SET::GUI::COLOR::BACKGROUND());
    ColorRGBA colorBorder(SET::GUI::COLOR::BORDER());
    ColorRGBA colorFill(SET::GUI::COLOR::FILL());
    ColorRGBA colorCheck(SET::GUI::COLOR::CHECK());
    DrawSkin(_colorBackground, colorBorder, colorFill, colorCheck, state, text);
}

CheckBoxSkin::~CheckBoxSkin() {

}

void CheckBox::SetState(uint _state)
{
    this->state = _state;
}

void CheckBoxSkin::DrawSkin(const ColorRGBA &_colorBackground, const ColorRGBA &colorBorder, const ColorRGBA &colorFill, const ColorRGBA &colorCheck, uint state, pchar  /*text*/)
{
    SetColorBackground(_colorBackground);
    Clear();
    SetColorBrush(colorBorder);
    float x = SET::GUI::CHECKBOX::ZONE::X();
    float y = SET::GUI::CHECKBOX::ZONE::Y();
    float width = SET::GUI::CHECKBOX::ZONE::WIDTH();
    float heiht = SET::GUI::CHECKBOX::ZONE::HEIGHT();
    DrawRectangle({ x, y }, { width, heiht });
    SetColorBrush(colorFill);
    FillRegion(x + 1, y + 1, width - 2, heiht - 2);
    if (state == StateChecked) {
        SetColorBrush(colorCheck);
        DrawLine(x + width / 2, y + heiht - 3, x + 3, y + 3);
        DrawLine(x + width / 2, y + heiht - 3, x + width - 3, y + 3);
    }
}

CheckBox::CheckBox(TypeCheckBox type, const Vector2D & /*position*/, pchar text) 
    : Widget() {

    this->type = (uint)type;

    for (size_t skin = 0; skin < (size_t)CheckBoxSkin::NnumSkins; skin++) {
        for (size_t shadow = 0; shadow < 2; shadow++) {
            for (size_t check = 0; check < 2; check++) {
                skins[skin][shadow][check] = new CheckBoxSkin(text, (uint)skin, shadow == 0 ? false : true, check == 0 ? false : true);
            }
        }
    }
}

CheckBox::~CheckBox() {
    for (int skin = 0; skin < CheckBoxSkin::NnumSkins; skin++) {
        for (int shadow = 0; shadow < 2; shadow++) {
            for (size_t check = 0; check < 2; check++) {
                SAFE_DELETE(skins[skin][shadow][check]);
            }
        }
    }
}



