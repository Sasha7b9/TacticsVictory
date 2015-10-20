#include <stdafx.h>


#include "MenuConfirmExit.h"
#include "GUI/Elements/Button.h"
#include "GUI/Elements/Label.h"



lMenuConfirmExit::lMenuConfirmExit(Context *context) :
    lWindow(context)
{
    SetLayout(Urho3D::LM_VERTICAL, 0, IntRect(6, 6, 6, 6));
    SharedPtr<lLabel> label(lLabel::Create("Exit in OS?", 20));
    AddChild(label);

    SharedPtr<UIElement> layer(CreateChild<UIElement>());
    layer->SetLayout(Urho3D::LM_HORIZONTAL, 6, IntRect(6, 6, 6, 6));
    
    buttonOk = new lButton(layer, "Ok");
    buttonCancel = new lButton(layer, "Cancel");

    AddChild(layer);
}

void lMenuConfirmExit::RegisterObject(Context *context)
{
    context->RegisterFactory<lMenuConfirmExit>("UI");

    COPY_BASE_ATTRIBUTES(lWindow);
}