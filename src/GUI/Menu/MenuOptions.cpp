#include <stdafx.h>


#include "GUI/GUI.h"
#include "GUI/Elements/SliderInt.h"
#include "MenuOptions.h"


tvMenuOptions::tvMenuOptions(Context *context) :
    tvWindow(context)
{
    SetLayout(Urho3D::LM_VERTICAL, 0, IntRect(6, 6, 6, 6));
    SetName("Options menu");

    SharedPtr<tvLabel> label(tvLabel::Create("Options", 20));
    AddChild(label);

#define CREATE_SWTAB(name, text, min, max, startIndex)                                  \
    name = new tvSliderWithTextAndButtons(this, text, min, max);                        \
    SubscribeToEvent(name, E_SLIDERINTCHANGED, HANDLER(tvMenuOptions, HandleOnSlider)); \
    name->SetValue(startIndex);

    CREATE_SWTAB(sliderBrightness, "Brightness", 0, 100, gSet->GetInt(TV_BRIGHTNESS));

    CREATE_SWTAB(sliderVolume, "Volume", 0, 100, gSet->GetInt(TV_VOLUME));

    CREATE_SWTAB(sliderMaxOccluderTriangles, "Max occluder triangles", 0, 5000, gSet->GetInt(TV_MAX_OCCLUDER_TRIANGLES));

    int width0 = SET::MENU::TEXT::WIDTH;
    int width1 = SET::MENU::DDLIST::WIDTH;

#define CREATE_DDLWTAB(name, text, num, itms, startIndex)   \
    name = tvDropDownListWithTextAndButton::Create(this, text, width0, width1, num, itms);  \
    SubscribeToEvent(name, E_ITEMSELECTED, HANDLER(tvMenuOptions, HandleItemSelected));     \
    name->SetSelection(startIndex);

    char *items[] = { "English", "Russian" };
    CREATE_DDLWTAB(ddlLanguage, "Language", 2, items, (uint)gSet->GetInt(TV_LANGUAGE));

    char *items1[] = {"Low", "Medium", "High"};
    CREATE_DDLWTAB(ddlTextureQuality, "Texture quality", 3, items1, (uint)gSet->GetInt(TV_TEXTURE_QUALITY));

    char *items2[] = {"x1", "x2", "x4", "x8", "x16", "x32"};
    CREATE_DDLWTAB(ddlTextureAnisotropy, "Texture anisotropy", 6, items2, (uint)gSet->GetInt(TV_TEXTURE_ANISOTROPY));

    char *items3[] = {"Low", "Medium", "High", "Max"};
    CREATE_DDLWTAB(ddlMaterialQuality, "Material quality", 4, items3, (uint)gSet->GetInt(TV_MATERIAL_QUALITY));

    char *items4[] = {"Off", "On"};
    CREATE_DDLWTAB(ddlShadowsEnabled, "Shadows", 2, items4, (uint)gSet->GetInt(TV_SHADOW_DRAW));

    CREATE_DDLWTAB(ddlSpecularLighting, "Specular lighting", 2, items4, (uint)gSet->GetInt(TV_SPECULAR_LIGHTING));

    CREATE_DDLWTAB(ddlDynamicInstancing, "Dynamic instancing", 2, items4, gRenderer->GetDynamicInstancing() ? 1U : 0U);

    int itemSizes[9] = {64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    shadowMapSizes.Push(PODVector<int>(itemSizes, sizeof(itemSizes) / sizeof(int)));
    
    char *items6[] = {"64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384"};
    CREATE_DDLWTAB(ddlShadowMapSize, "Shadow map size", 9, items6, (uint)gSet->GetInt(TV_SHADOW_MAP_SIZE));

    char *items7[] = {"low 16bit", "low 24bit", "high 16bit", "high 24bit"};
    CREATE_DDLWTAB(ddlShadowQuality, "Shadow quality", 4, items7, (uint)gRenderer->GetShadowQuality());

    SharedPtr<UIElement> layout(CreateChild<UIElement>());
    layout->SetAlignment(Urho3D::HA_CENTER, Urho3D::VA_CENTER);

    buttonClose = new tvButton(0, "Close", 100);
    SubscribeToEvent(buttonClose, E_RELEASED, HANDLER(tvMenuOptions, HandleButtonRelease));
    SubscribeToEvent(buttonClose, E_HOVERBEGIN, HANDLER(tvMenuOptions, HandleHoverBegin));
    SubscribeToEvent(buttonClose, E_HOVEREND, HANDLER(tvMenuOptions, HandleHoverEnd));
    layout->AddChild(buttonClose);
    AddChild(layout);
    layout->SetMinHeight(buttonClose->GetHeight());

    SetMinSize(GetWidth(), GetHeight());

    buttonClose->SetPosition(GetWidth() / 2 - buttonClose->GetWidth() / 2, buttonClose->GetPosition().y_);

    mapButtonsActions[buttonClose] = MenuEvent_MenuOptionsClose;
    
    int x = GetWidth() - label->GetWidth() / 2;
    int y = label->GetPosition().y_;
    label->SetPosition(x, y);
}

void tvMenuOptions::RegisterObject(Context *context)
{
    context->RegisterFactory<tvMenuOptions>("UI");

    COPY_BASE_ATTRIBUTES(tvWindow);
}

void tvMenuOptions::HandleItemSelected(StringHash, VariantMap& eventData)
{
    tvDropDownListWithTextAndButton *ddList = (tvDropDownListWithTextAndButton*)eventData[Urho3D::ItemSelected::P_ELEMENT].GetPtr();
    int index = eventData[Urho3D::ItemSelected::P_SELECTION].GetInt();

    if(ddList == ddlLanguage)
    {
        gLocalization->SetLanguage(index == 0 ? "en" : "ru");
        tvLabel::ReloadLanguage();
        gSet->SetInt(TV_LANGUAGE, index);
    }
    else if(ddList == ddlTextureQuality)
    {
        gRenderer->SetTextureQuality(index);
        gSet->SetInt(TV_TEXTURE_QUALITY, index);
    }
    else if(ddList == ddlTextureAnisotropy)
    {
        gRenderer->SetTextureAnisotropy(index + 1);
        gSet->SetInt(TV_TEXTURE_ANISOTROPY, index);
    }
    else if(ddList == ddlMaterialQuality)
    {
        gRenderer->SetMaterialQuality(index);
        gSet->SetInt(TV_MATERIAL_QUALITY, index);
    }
    else if(ddList == ddlShadowsEnabled)
    {
        gRenderer->SetDrawShadows(index == 1);
        gSet->SetInt(TV_SHADOW_DRAW, index);
    }
    else if(ddList == ddlSpecularLighting)
    {
        gRenderer->SetSpecularLighting(index == 1);
        gSet->SetInt(TV_SPECULAR_LIGHTING, index);
    }
    else if(ddList == ddlShadowMapSize)
    {
        gRenderer->SetShadowMapSize(shadowMapSizes[(uint)index]);
        gSet->SetInt(TV_SHADOW_MAP_SIZE, index);
    }
    else if(ddList == ddlShadowQuality)
    {
        gRenderer->SetShadowQuality(index);
    }
    else if(ddList == ddlDynamicInstancing)
    {
        gRenderer->SetDynamicInstancing(index == 1);
    }
}

void tvMenuOptions::HandleOnSlider(StringHash, VariantMap& eventData)
{
    tvSliderWithTextAndButtons *slider = (tvSliderWithTextAndButtons*)eventData[SliderIntChanged::P_ELEMENT].GetPtr();
    int value = eventData[SliderIntChanged::P_VALUE].GetInt();

    if(slider == sliderMaxOccluderTriangles)
    {
        gRenderer->SetMaxOccluderTriangles(value);
        gSet->SetInt(TV_MAX_OCCLUDER_TRIANGLES, value);
    }
    else if (slider == sliderBrightness)
    {
        gSet->SetInt(TV_BRIGHTNESS, value);
    }
    else if (slider == sliderVolume)
    {
        gSet->SetInt(TV_VOLUME, value);
    }
}

void tvMenuOptions::HandleButtonRelease(StringHash, VariantMap& eventData)
{
    Button *button = (Button*)eventData[Urho3D::Released::P_ELEMENT].GetPtr();
    eventData = GetEventDataMap();
    eventData[MenuEvent::P_TYPE] = mapButtonsActions[button];
    SendEvent(E_MENU, eventData);
}

void tvMenuOptions::HandleHoverBegin(StringHash, VariantMap&)
{
    gCursor->SetSelected();
}

void tvMenuOptions::HandleHoverEnd(StringHash, VariantMap&)
{
    gCursor->SetNormal();
}
