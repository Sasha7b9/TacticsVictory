#include <stdafx.h>


#include "TargetDetected.h"


TargetDetected::TargetDetected(Context* context) :
    Component(context)
{

}

void TargetDetected::OnNodeSet(Node *node)
{
    if(node)
    {
        SubscribeToEvent(node, Urho3D::E_NODECOLLISIONSTART, HANDLER(TargetDetected, HandleNodeCollision));
    }
}

void TargetDetected::HandleNodeCollision(StringHash, VariantMap&)
{
    static int num = 0;
    LOGINFOF("Node collision %d", num++);
}
