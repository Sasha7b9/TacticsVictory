// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "_GameObject.h"
#include "GUI/Cursor.h"
#include "Core/Math.h"



static uint creatorID = 0;



GameObject::GameObject(Context *context) : LogicComponent(context)
{
    deltaPos = Vector3::ZERO;
    id = ++creatorID;

    translator = new Translator();
}


GameObject::~GameObject()
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
        if(type == Unit)
        {
            contextMenu->Create(this);
        }
    }
    contextMenu->SetPosition(TheCursor->GetCursor()->GetPosition());
    TheUIRoot->AddChild(contextMenu);
    SubscribeToEvent(E_MOUSEBUTTONDOWN, URHO3D_HANDLER(GameObject, HandleOnMouseDown));
}


void GameObject::HandleOnMouseDown(StringHash, VariantMap&)
{
    if(!contextMenu->UnderCursor())
    {
        UnsubscribeFromEvent(E_MOUSEBUTTONDOWN);

        TheUIRoot->RemoveChild(contextMenu);
    }
}


char *GameObject::GetName()
{
    return name;
}


GameObject::Type GameObject::GetGameObjectType()
{
    return type;
}


void GameObject::SetSelected(bool selected_)
{
    selected = selected_;
}


bool GameObject::IsSelected()
{
    return selected;
}


uint GameObject::GetID()
{
    return id;
}


Vector3 GameObject::GetPosition()
{
    return node_->GetPosition() - deltaPos;
}


void GameObject::SetPosition(const Vector3& pos)
{
    node_->SetPosition(pos + deltaPos);
}


void GameObject::Normalize(float k)
{
    Vector3 pos = GetPosition();
    node_->SetPosition({0.0f, 0.0f, 0.0f});
    node_->SetScale(1.0f);

    BoundingBox box = modelObject->GetModel()->GetBoundingBox();

    Vector3 delta = box.max_ - box.min_;

    float divider = Math::Max(delta.x_, delta.y_, delta.z_);

    Vector3 scale = {k / divider, k / divider, k / divider};

    deltaPos.y_ = -box.min_.y_ / divider * k;
    deltaPos.z_ = -(box.max_.z_ + box.min_.z_) / 2.0f / divider * k;
    deltaPos.x_ = (box.max_.x_ + box.min_.x_) / 2.0f / divider * k;

    node_->SetScale(scale);

    SetPosition(pos);
}


Node* GameObject::GetNode()
{
    return node_;
}


void GameObject::SetCoord(const Coord& coord)
{
    SetPosition(coord.ToVector3());
}
