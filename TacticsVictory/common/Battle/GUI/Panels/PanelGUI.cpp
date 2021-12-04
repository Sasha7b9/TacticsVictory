// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include <stdafx.h>
#include "PanelGUI.h"
#include "GUI/Widgets/Button.h"
#include "GUI/Mutators/MovementMutator.h"
#include "Settings.h"
#include "Sounds/SoundPlayer.h"


using namespace Pi;


PanelGUI::PanelGUI(const Vector2D &size) 
    : DrawingWidget(size) {

    Clear();

    EndScene();
}

PanelGUI::~PanelGUI() {

}

void PanelGUI::Preprocess() {
    //GetRootWidget()->AddMovingWidget(this);
}

void PanelGUI::SetMovementMutator(Point2D posShow, Point2D posHide, Vector2D speed) {
    Mutator *mutator = GetFirstMutator();
    while (mutator) {
        if (mutator->GetMutatorType() == kMutatorMovement) {
            static_cast<MovementMutator*>(mutator)->SetParameters(posShow, posHide, speed);
            break;
        }
        mutator = mutator->Next();
    }
    if (!mutator) {
        MovementMutator *_mutator = new MovementMutator(posShow, posHide, speed);
        _mutator->SetMutatorState(0);
        AddMutator(_mutator);
    }
}

void PanelGUI::Toggle() {
    TheSoundPlayer->Play(kMovePanel);
    Mutator *mutator = GetFirstMutator();
    while (mutator) {
        if (mutator->GetMutatorType() == kMutatorMovement) {
            static_cast<MovementMutator*>(mutator)->Toggle();
            break;
        }
        mutator = mutator->Next();
    }
}

void PanelGUI::Clear() {
    SetColorBackground(K::black);
    DrawingWidget::Clear();
    SetColorBrush(K::cyan);
    DrawRectangle({ 0.0f, 0.0f }, { GetWidgetSize().x - 1, GetWidgetSize().y - 1 });
}
