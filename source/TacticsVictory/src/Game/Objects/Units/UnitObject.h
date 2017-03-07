#pragma once
#include "Game/Objects/GameObject.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UnitObject : public GameObject
{
public:
    UnitObject(Context *context = gContext);
    virtual ~UnitObject();
    static void SetViewTargetView(bool view);
    virtual void SetSelected(bool selected);

protected:
    static bool viewTargetView;

private:
    Camera *cameraTarget = nullptr;                         // ������ ��� ���� ����� �� ������� ����
    SharedPtr<Texture2D> renderTexture;
    SharedPtr<RenderSurface> renderSurface;

    void HandlePostRenderUpdate(StringHash, VariantMap&);

    DEFAULT_MEMBERS(UnitObject);
};
