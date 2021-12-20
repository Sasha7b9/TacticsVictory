// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Button.h"
#include "Settings.h"
#include "Utils/Math_.h"
#include "CursorGUI.h"


using namespace Pi;


ButtonSkin::ButtonSkin(TButton::Type type, pchar text, State state) 
   : DrawingWidget(SET::GUI::BUTTON::SIZE(type))
{
    ColorRGBA _colorBackground(SET::GUI::BUTTON::COLOR::BACKGROUND(type));
    ColorRGBA _colorBrush(SET::GUI::COLOR::BORDER());
    ColorRGBA colorText(1.0f, 1.0f, 1.0f);
    if (state == ButtonSkin::State::UnderMouse)
    {
        _colorBackground = Mathem::SetColorBrightness(_colorBackground, type == TButton::Type::Normal ? 0.2f : 0.3f);
    }
    else if (state == ButtonSkin::State::Pressed) {
        _colorBackground = Mathem::SetColorBrightness(_colorBackground, type == TButton::Type::Normal ? 0.4f : 0.6f);
        colorText = ColorRGBA(0.0f, 0.0f, 0.0f);
    }

    DrawSkin(type, _colorBackground, _colorBrush);

    TextWidget *textWidget = new TextWidget(SET::GUI::BUTTON::SIZE(type), text, "fonts/Techno28_14");

    textWidget->SetTextAlignment(TextAlignment::Center);
    textWidget->SetWidgetColor(colorText);
    textWidget->SetWidgetPosition(Point3D(0, 2, 0));

    if(type == TButton::Type::NameTab)
    {
        textWidget->SetWidgetPosition(Point3D(0, 4, 0));
    }

    AppendNewSubnode(textWidget);

    EndScene();
}

void ButtonSkin::DrawSkin(TButton::Type type, const ColorRGBA &_colorBackground, const ColorRGBA &colorBorder)
{
    SetColorBackground(_colorBackground);
    Clear();
    SetColorBrush(colorBorder);
    DrawRectangle({ 0.0f, 0.0f }, { SET::GUI::BUTTON::WIDTH(type) - 1.0f, SET::GUI::BUTTON::HEIGHT(type) - 1.0f });
}

TButton::TButton(Type type, const Vector2D &position, pchar text) 
    : Widget()
{

    buttonType = type;
    skins.AddElement(new ButtonSkin(type, text, ButtonSkin::State::Normal));
    skins.AddElement(new ButtonSkin(type, text, ButtonSkin::State::UnderMouse));
    skins.AddElement(new ButtonSkin(type, text, ButtonSkin::State::Pressed));
    AppendNewSubnode(skins[(int)ButtonSkin::State::Normal]);
    AppendNewSubnode(skins[(int)ButtonSkin::State::UnderMouse]);
    AppendNewSubnode(skins[(int)ButtonSkin::State::Pressed]);
    SetWidgetPosition(Point3D(position));
    SetState((uint)ButtonSkin::State::Normal);

    observer = new Observer<TButton, MouseObservable>(this, &TButton::HandleObserver);
    Mouse::self->AddObserver(observer);
}

TButton::~TButton()
{
    SAFE_DELETE(skins[(int)ButtonSkin::State::Normal]);
    SAFE_DELETE(skins[(int)ButtonSkin::State::UnderMouse]);
    SAFE_DELETE(skins[(int)ButtonSkin::State::Pressed]);
    SAFE_DELETE(observer);
}

void TButton::HandleObserver(MouseObservable *, uint)
{
    /*
    if (!Visible() || !Enabled()) 
    {
        return;
    }

    bool mouseOnButton = false;
    Widget *widget = GetFirstSubnode();
    while (widget) 
    {
        Point3D position = TheMouse->pos;
        Widget *detectingWidget = TheInterfaceMgr->DetectWidget(position);
        if (detectingWidget == widget) 
        {
            mouseOnButton = true;
            break;
        }
        widget = widget->Next();
    }

    if (!mouseOnButton) 
    {
        mouseOnButton = TheInterfaceMgr->DetectWidget(TheCursor->position) == this;
    }
    */

    Point3D pos = GetWorldPosition();
    bool mouseOnButton = Mathem::PointInRect(&(CursorGUI::self->position), pos.x, pos.y, (float)SET::GUI::BUTTON::WIDTH(buttonType), (float)SET::GUI::BUTTON::HEIGHT(buttonType));

    if (!mouseOnButton) 
    {
        if ((buttonType == TButton::Type::NameTab) && selected) 
        {
        } 
        else 
        {
            SetState((uint)ButtonSkin::State::Normal);
        }
        return;
    }
    if (buttonType == TButton::Type::Normal) 
    {
        SetState(Mouse::self->LeftIsPressed() ? (uint)ButtonSkin::State::Pressed : (uint)ButtonSkin::State::UnderMouse);
    } 
    else if (buttonType == TButton::Type::NameTab) 
    {
        SetState(selected ? (uint)ButtonSkin::State::Pressed : (uint)ButtonSkin::State::UnderMouse);
    }

    if (Mouse::self->LeftNowReleased())
    {
        if (buttonType == TButton::Type::NameTab) 
        {
            SetSelected(true);
        }
        SetState(buttonType == TButton::Type::NameTab ? (uint)ButtonSkin::State::Pressed : (uint)ButtonSkin::State::UnderMouse);
        this->selected = false;
        PostEvent(&eventData);
        Mouse::self->SetLeftReleased();
    }
}

void TButton::SetState(uint state) 
{
    Widget *widget = GetFirstSubnode();

    while (widget) 
    {
        Widget *node = widget;
        widget = widget->Next();
        RemoveSubnode(node);
    }

    AppendSubnode(skins[state]);
    Update();
    Invalidate();
}

void TButton::SetSelected(bool eSelected) 
{
    selected = eSelected;
    if (selected) 
    {
        SetState((uint)ButtonSkin::State::Pressed);
    } else 
    {
        SetState((uint)ButtonSkin::State::Normal);
    }
}
