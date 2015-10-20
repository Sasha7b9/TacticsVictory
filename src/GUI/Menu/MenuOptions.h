#pragma once


#include "GUI/Elements/Window.h"


enum
{
    MenuEvent_MenuOptionsClose
};


class vMenuOptions : public vWindow
{
    OBJECT(vMenuOptions)

public:
    vMenuOptions(Context *context);

    static void RegisterObject(Context *context);

private:
    vMenuOptions& operator=(const vMenuOptions&) {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleOnSlider(StringHash evenType, VariantMap& eventData);
    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    HashMap<Slider*, uint> mapSlidersActions;

    SharedPtr<vSliderWithTextAndButtons> sliderBrightness;
    SharedPtr<vSliderWithTextAndButtons> sliderMaxOccluderTriangles;
    SharedPtr<vSliderWithTextAndButtons> sliderVolume;

    SharedPtr<vDropDownListWithTextAndButton> ddlLanguage;
    SharedPtr<vDropDownListWithTextAndButton> ddlTextureQuality;
    SharedPtr<vDropDownListWithTextAndButton> ddlMaterialQuality;
    SharedPtr<vDropDownListWithTextAndButton> ddlTextureAnisotropy;
    SharedPtr<vDropDownListWithTextAndButton> ddlShadowsEnabled;
    SharedPtr<vDropDownListWithTextAndButton> ddlSpecularLighting;
    SharedPtr<vDropDownListWithTextAndButton> ddlShadowMapSize;
    SharedPtr<vDropDownListWithTextAndButton> ddlShadowQuality;
    SharedPtr<vDropDownListWithTextAndButton> ddlDynamicInstancing;
    PODVector<int> shadowMapSizes;
    SharedPtr<vButton> buttonClose;
    IntVector2 dragBeginPosition;
};