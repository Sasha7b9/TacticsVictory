#include <stdafx.h>


#include "MovingObject.h"


lMovingObject::lMovingObject() : lObject()
{
    JSONFile file(gContext);

    JSONValue valueTank;
    valueTank.Set("number", 1);

    file.GetRoot().Set("model", valueTank);

    File writeFile(gContext);
    writeFile.Open("tank", Urho3D::FILE_WRITE);
    file.Save(writeFile);
}
