#include "Scene/Objects/_TGameObject.h"


Vector<GameObject *> GameObject::storage;


GameObject::GameObject()
{
    storage.Push(this);
}
