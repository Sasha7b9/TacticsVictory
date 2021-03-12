// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/ButtonSwitch_.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/SliderInt_.h"
#include "GUI/Controls/SliderWithTextAndButtons_.h"
#include "GUI/Menu/MenuOptions.h"
#include "Utils/Settings.h"
#include "Utils/SettingsTypes.h"


MenuOptions::MenuOptions(Context *context) : WindowMenu(context)
{
    SET_VERTICAL_LAYOUT_0_6(this);
    SetName("Options menu");

    SharedPtr<Label> label(Label::Create("Options", true, 20));
    AddChild(label);

#define CREATE_SWTAB(name, text, min, max, step, startIndex)                                  \
    name = new SliderWithTextAndButtons(this, text, min, max, step);                         \
    SubscribeToEvent(name, E_SLIDERINTCHANGED, URHO3D_HANDLER(MenuOptions, HandleOnSlider));  \
    name->SetValue(startIndex);

    CREATE_SWTAB(sliderBrightness, "Brightness", 0, 100, 1, TheSet->GetInt(TV_BRIGHTNESS));

    CREATE_SWTAB(sliderVolume, "Volume", 0, 100, 1, TheSet->GetInt(TV_VOLUME));

    CREATE_SWTAB(sliderMaxOccluderTriangles, "Max occluder triangles", 0, 5000, 1, TheSet->GetInt(TV_MAX_OCCLUDER_TRIANGLES));

    int width0 = SET::MENU::TEXT::WIDTH;
    int width1 = SET::MENU::DDLIST::WIDTH;

#define CREATE_DDLWTAB(name, text, num, itms, startIndex)   \
    name = DropDownListWithTextAndButton::Create(this, text, width0, width1, num, itms);  \
    SubscribeToEvent(name, E_ITEMSELECTED, URHO3D_HANDLER(MenuOptions, HandleItemSelected));     \
    name->SetSelection(startIndex);

    char *items1[] = {"Low", "Medium", "High"};
    CREATE_DDLWTAB(ddlTextureQuality, "Texture quality", 3, items1, (uint)TheSet->GetInt(TV_TEXTURE_QUALITY));

    char *items2[] = {"x1", "x2", "x4", "x8", "x16", "x32"};
    CREATE_DDLWTAB(ddlTextureAnisotropy, "Texture anisotropy", 6, items2, (uint)TheSet->GetInt(TV_TEXTURE_ANISOTROPY));

    char *items3[] = {"Low", "Medium", "High", "Max"};
    CREATE_DDLWTAB(ddlMaterialQuality, "Material quality", 4, items3, (uint)TheSet->GetInt(TV_MATERIAL_QUALITY)); //-V112

    char *items4[] = {"Off", "On"};
    CREATE_DDLWTAB(ddlShadowsEnabled, "Shadows", 2, items4, (uint)TheSet->GetInt(TV_SHADOW_DRAW));

    CREATE_DDLWTAB(ddlSpecularLighting, "Specular lighting", 2, items4, (uint)TheSet->GetInt(TV_SPECULAR_LIGHTING));

    CREATE_DDLWTAB(ddlDynamicInstancing, "Dynamic instancing", 2, items4, TheRenderer->GetDynamicInstancing() ? 1U : 0U);

    int itemSizes[9] = {64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    shadowMapSizes.Push(PODVector<int>(itemSizes, sizeof(itemSizes) / sizeof(int)));
    
    char *items6[] = {"64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384"};
    CREATE_DDLWTAB(ddlShadowMapSize, "Shadow map size", 9, items6, (uint)TheSet->GetInt(TV_SHADOW_MAP_SIZE));

    char *items7[] = {"low 16bit", "low 24bit", "high 16bit", "high 24bit"};
    CREATE_DDLWTAB(ddlShadowQuality, "Shadow quality", 4, items7, static_cast<uint>(TheRenderer->GetShadowQuality())); //-V112
 
    SharedPtr<UIElement> layout(CreateChild<UIElement>());
    layout->SetAlignment(HA_CENTER, VA_TOP);

    buttonClose = new TButton(0, "Close", 100);
    SubscribeToEvent(buttonClose, E_RELEASED, URHO3D_HANDLER(MenuOptions, HandleButtonRelease));
    layout->AddChild(buttonClose);
    AddChild(layout);
    layout->SetMinHeight(buttonClose->GetHeight());

    SetMinSize(GetWidth(), GetHeight());

    buttonClose->SetPosition(GetWidth() / 2 - buttonClose->GetWidth() / 2, buttonClose->GetPosition().y_);

    buttons.Push(buttonClose);
    
    int x = GetWidth() - label->GetWidth() / 2;
    int y = label->GetPosition().y_;
    label->SetPosition(x, y);
}


void MenuOptions::RegisterObject()
{
    Context *context = TheContext;

    context->RegisterFactory<MenuOptions>("UI");

    URHO3D_COPY_BASE_ATTRIBUTES(WindowMenu);
}


void MenuOptions::HandleItemSelected(StringHash, VariantMap& eventData)
{
    DropDownListWithTextAndButton *ddList = dynamic_cast<DropDownListWithTextAndButton*>(eventData[ItemSelected::P_ELEMENT].GetPtr());
    int index = eventData[ItemSelected::P_SELECTION].GetInt();

    if(ddList == ddlTextureQuality)
    {
        TheRenderer->SetTextureQuality((MaterialQuality)index);
        TheSet->SetInt(TV_TEXTURE_QUALITY, index);
    }
    else if(ddList == ddlTextureAnisotropy)
    {
        TheRenderer->SetTextureAnisotropy(index + 1);
        TheSet->SetInt(TV_TEXTURE_ANISOTROPY, index);
    }
    else if(ddList == ddlMaterialQuality)
    {
        TheRenderer->SetMaterialQuality((MaterialQuality)index);
        TheSet->SetInt(TV_MATERIAL_QUALITY, index);
    }
    else if(ddList == ddlShadowsEnabled)
    {
        TheRenderer->SetDrawShadows(index == 1);
        TheSet->SetInt(TV_SHADOW_DRAW, index);
    }
    else if(ddList == ddlSpecularLighting)
    {
        TheRenderer->SetSpecularLighting(index == 1);
        TheSet->SetInt(TV_SPECULAR_LIGHTING, index);
    }
    else if(ddList == ddlShadowMapSize)
    {
        TheRenderer->SetShadowMapSize(shadowMapSizes[(uint)index]);
        TheSet->SetInt(TV_SHADOW_MAP_SIZE, index);
    }
    else if(ddList == ddlShadowQuality)
    {
        TheRenderer->SetShadowQuality((ShadowQuality)index);
    }
    else if(ddList == ddlDynamicInstancing)
    {
        TheRenderer->SetDynamicInstancing(index == 1);
    }
}


void MenuOptions::HandleOnSlider(StringHash, VariantMap& eventData)
{
    SliderWithTextAndButtons *slider = dynamic_cast<SliderWithTextAndButtons*>(eventData[SliderIntChanged::P_ELEMENT].GetPtr());
    int value = eventData[SliderIntChanged::P_VALUE].GetInt();

    if(slider == sliderMaxOccluderTriangles)
    {
        TheRenderer->SetMaxOccluderTriangles(value);
        TheSet->SetInt(TV_MAX_OCCLUDER_TRIANGLES, value);
    }
    else if (slider == sliderBrightness)
    {
        TheSet->SetInt(TV_BRIGHTNESS, value);
    }
    else if (slider == sliderVolume)
    {
        TheSet->SetInt(TV_VOLUME, value);
    }
}


void MenuOptions::HandleButtonRelease(StringHash, VariantMap&)
{
    SendEventClose();
}
