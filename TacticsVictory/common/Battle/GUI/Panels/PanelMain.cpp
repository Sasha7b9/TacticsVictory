// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "PanelMain.h"
#include "Settings.h"
#include "GUI/Widgets/TabWidget.h"


using namespace Pi;


PanelMain *PanelMain::self = nullptr;


PanelMain::PanelMain()
    : PanelGUI(SET::GUI::MAIN::SIZE()),
    Singleton<PanelMain>(PanelMain::self)
{

    SetMovementMutator(Point2D((float)SET::GUI::MAIN::VIEW::X(), (float)SET::GUI::MAIN::VIEW::Y()),
        Point2D((float)SET::GUI::MAIN::VIEW::X(), (float)SET::WINDOW::SIZE().y),
        Vector2D(0.0f, SET::GUI::PANEL::SPEED()));

    AppendNewSubnode(new TabWidgetMainPanel(this));
}

PanelMain::~PanelMain()
{
    SAFE_DELETE(TabWidgetMainPanel::self);
}

void PanelMain::HandleHideShow(Widget *, const WidgetEventData *)
{
    Toggle();
}