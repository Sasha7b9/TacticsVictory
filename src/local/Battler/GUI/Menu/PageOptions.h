// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "GUI/Menu/MenuPage_.h"


enum
{
    MenuEvent_MenuOptionsClose
};


class PageOptions : public MenuPage
{
    URHO3D_OBJECT(PageOptions, MenuPage);

public:
    PageOptions();

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

    PODVector<int>     shadowMapSizes;
    SharedPtr<ButtonT> buttonClose;
    IntVector2         dragBeginPosition;
};
