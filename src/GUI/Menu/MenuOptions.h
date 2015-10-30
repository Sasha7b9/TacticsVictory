#pragma once


#include "GUI/Elements/Window.h"


enum
{
    MenuEvent_MenuOptionsClose
};


class lMenuOptions : public lWindow
{
    OBJECT(lMenuOptions)

public:
    lMenuOptions(Context *context = gContext);

    static void RegisterObject(Context *context = gContext);

private:
    lMenuOptions& operator=(const lMenuOptions&) {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleOnSlider(StringHash evenType, VariantMap& eventData);
    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);

    HashMap<Slider*, uint> mapSlidersActions;

    SharedPtr<lSliderWithTextAndButtons> sliderBrightness;
    SharedPtr<lSliderWithTextAndButtons> sliderMaxOccluderTriangles;
    SharedPtr<lSliderWithTextAndButtons> sliderVolume;

    SharedPtr<lDropDownListWithTextAndButton> ddlTextureQuality;
    SharedPtr<lDropDownListWithTextAndButton> ddlMaterialQuality;
    SharedPtr<lDropDownListWithTextAndButton> ddlTextureAnisotropy;
    SharedPtr<lDropDownListWithTextAndButton> ddlShadowsEnabled;
    SharedPtr<lDropDownListWithTextAndButton> ddlSpecularLighting;
    SharedPtr<lDropDownListWithTextAndButton> ddlShadowMapSize;
    SharedPtr<lDropDownListWithTextAndButton> ddlShadowQuality;
    SharedPtr<lDropDownListWithTextAndButton> ddlDynamicInstancing;
    PODVector<int> shadowMapSizes;
    SharedPtr<lButton> buttonClose;
    IntVector2 dragBeginPosition;
};