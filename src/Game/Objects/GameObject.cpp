#include <stdafx.h>


#include "GameObject.h"
#include "GUI/Elements/Cursor.h"


GameObject::GameObject(Context *context) 
    : LogicComponent(context)
{

}

void GameObject::Update(float)
{

}

void GameObject::EnableContextMenu()
{
    if(contextMenu == nullptr)
    {
        contextMenu = new ContextMenuUnit();
    }
    contextMenu->SetPosition(gCursor->GetCursor()->GetPosition());
    gUIRoot->AddChild(contextMenu);
    SubscribeToEvent(Urho3D::E_MOUSEBUTTONDOWN, URHO3D_HANDLER(GameObject, HandleOnMouseDown));
}

void GameObject::HandleOnMouseDown(StringHash, VariantMap&)
{
    if(!contextMenu->UnderCursor())
    {
        UnsubscribeFromEvent(Urho3D::E_MOUSEBUTTONDOWN);

        gUIRoot->RemoveChild(contextMenu);
    }
}
