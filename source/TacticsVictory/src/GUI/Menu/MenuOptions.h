#pragma once
#include "GUI/Menu/WindowMenu.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum
{
    MenuEvent_MenuOptionsClose
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MenuOptions : public WindowMenu
{
    URHO3D_OBJECT(MenuOptions, WindowMenu);

public:
    MenuOptions(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleOnSlider(StringHash evenType, VariantMap& eventData);
    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    HashMap<Slider*, uint> mapSlidersActions;

    SharedPtr<SliderWithTextAndButtons> sliderBrightness;
    SharedPtr<SliderWithTextAndButtons> sliderMaxOccluderTriangles;
    SharedPtr<SliderWithTextAndButtons> sliderVolume;

    SharedPtr<DropDownListWithTextAndButton> ddlTextureQuality;
    SharedPtr<DropDownListWithTextAndButton> ddlMaterialQuality;
    SharedPtr<DropDownListWithTextAndButton> ddlTextureAnisotropy;
    SharedPtr<DropDownListWithTextAndButton> ddlShadowsEnabled;
    SharedPtr<DropDownListWithTextAndButton> ddlSpecularLighting;
    SharedPtr<DropDownListWithTextAndButton> ddlShadowMapSize;
    SharedPtr<DropDownListWithTextAndButton> ddlShadowQuality;
    SharedPtr<DropDownListWithTextAndButton> ddlDynamicInstancing;
    PODVector<int> shadowMapSizes;
    SharedPtr<ButtonRTS> buttonClose;
    IntVector2 dragBeginPosition;

    DEFAULT_MEMBERS(MenuOptions);
};
