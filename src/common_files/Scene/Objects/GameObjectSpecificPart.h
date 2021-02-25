// 2021/02/25 21:04:41 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once

/*
    В потомках хранятся специфические для клиента и сервера параметры
*/

class GameObjectSpecificPart : public Object
{
    URHO3D_OBJECT(GameObjectSpecificPart, Object);

protected:

    GameObjectSpecificPart();
};
