#include <stdafx.h>
#include "PanelMain.h"
#include "Settings.h"
#include "GUI/Widgets/TabWidget.h"


using namespace Pi;


PanelMain::PanelMain() 
    : PanelGUI(SET::GUI::MAIN::SIZE()),
    Singleton<PanelMain>(ThePanelMain) {

    SetMovementMutator(Point2D((float)SET::GUI::MAIN::VIEW::X(), (float)SET::GUI::MAIN::VIEW::Y()),
        Point2D((float)SET::GUI::MAIN::VIEW::X(), (float)SET::WINDOW::SIZE().y),
        Vector2D(0.0f, SET::GUI::PANEL::SPEED()));

    AppendNewSubnode(TheTabWidgetMainPanel = new TabWidgetMainPanel(this));
}

PanelMain::~PanelMain() {
    SAFE_DELETE(TheTabWidgetMainPanel);
}

void PanelMain::HandleHideShow(Widget *, const WidgetEventData *) {
    Toggle();
}