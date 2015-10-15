#pragma once


enum
{
    MenuEvent_MenuOptionsClose
};


class tvMenuOptions : public tvWindow
{
    OBJECT(tvMenuOptions)

public:
    tvMenuOptions(Context *context);

    static void RegisterObject(Context *context);

private:
    tvMenuOptions& operator=(const tvMenuOptions&) {};

    void HandleItemSelected(StringHash eventType, VariantMap& eventData);
    void HandleOnSlider(StringHash evenType, VariantMap& eventData);
    void HandleButtonRelease(StringHash eventType, VariantMap& eventData);
    void HandleHoverBegin(StringHash eventType, VariantMap& eventData);
    void HandleHoverEnd(StringHash eventType, VariantMap& eventData);

    HashMap<Slider*, uint> mapSlidersActions;

    SharedPtr<tvSliderWithTextAndButtons> sliderBrightness;
    SharedPtr<tvSliderWithTextAndButtons> sliderMaxOccluderTriangles;
    SharedPtr<tvSliderWithTextAndButtons> sliderVolume;

    SharedPtr<tvDropDownListWithTextAndButton> ddlLanguage;
    SharedPtr<tvDropDownListWithTextAndButton> ddlTextureQuality;
    SharedPtr<tvDropDownListWithTextAndButton> ddlMaterialQuality;
    SharedPtr<tvDropDownListWithTextAndButton> ddlTextureAnisotropy;
    SharedPtr<tvDropDownListWithTextAndButton> ddlShadowsEnabled;
    SharedPtr<tvDropDownListWithTextAndButton> ddlSpecularLighting;
    SharedPtr<tvDropDownListWithTextAndButton> ddlShadowMapSize;
    SharedPtr<tvDropDownListWithTextAndButton> ddlShadowQuality;
    SharedPtr<tvDropDownListWithTextAndButton> ddlDynamicInstancing;
    PODVector<int> shadowMapSizes;
    SharedPtr<tvButton> buttonClose;
    IntVector2 dragBeginPosition;
};