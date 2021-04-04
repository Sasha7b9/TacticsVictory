// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Controls/Sliders/SliderInt_.h"
#include "GUI/Controls/Sliders/SliderWithTextAndButtons_.h"
#include "GUI/Menu/MenuStart/MenuOptions.h"


MenuOptions::MenuOptions() : WindowMenu()
{
    SetLayout(LM_VERTICAL, 0, IntRect(0, 0, 0, 0));

    SetName("Options menu");

    SharedPtr<Label> label(Label::Create("Options", true, 20));
    label->SetTextAlignment(HA_CENTER);
    AddChild(label);

#define CREATE_SWTAB(name, text, min, max, step, startIndex)                                  \
    name = new SliderWithTextAndButtons(this, text, min, max, step);                          \
    SubscribeToEvent(name, E_SLIDERINTCHANGED, URHO3D_HANDLER(MenuOptions, HandleOnSlider));  \
    name->SetValue(startIndex);

    CREATE_SWTAB(sliderBrightness, "Brightness", 0, 100, 1, TheSettings.GetIntValue("brightness"));

    CREATE_SWTAB(sliderVolume, "Volume", 0, 100, 1, TheSettings.GetIntValue("volume"));

    CREATE_SWTAB(sliderMaxOccluderTriangles, "Max occluder triangles", 0, 5000, 1,
        TheSettings.GetIntValue("max_occluder_triangles"));

    int width0 = TheSettings.GetIntValue("menu", "text", "width");
    int width1 = TheSettings.GetIntValue("menu", "ddlist", "width");

#define CREATE_DDLWTAB(name, text, num, itms, startIndex)                                       \
    name = DropDownListWithTextAndButton::Create(this, text, width0, width1, num, itms);        \
    SubscribeToEvent(name, E_ITEMSELECTED, URHO3D_HANDLER(MenuOptions, HandleItemSelected));    \
    name->SetSelection(startIndex);

    char *items1[] = {"Low", "Medium", "High"};
    CREATE_DDLWTAB(ddlTextureQuality, "Texture quality", 3, items1,
        (uint)TheSettings.GetIntValue("texture", "quality"));

    char *items2[] = {"x1", "x2", "x4", "x8", "x16", "x32"};
    CREATE_DDLWTAB(ddlTextureAnisotropy, "Texture anisotropy", 6, items2,
        (uint)TheSettings.GetIntValue("texture", "anisotropy"));

    char *items3[] = {"Low", "Medium", "High", "Max"};
    CREATE_DDLWTAB(ddlMaterialQuality, "Material quality", 4, items3,
        (uint)TheSettings.GetIntValue("material", "quality"));

    char *items4[] = {"Off", "On"};
    CREATE_DDLWTAB(ddlShadowsEnabled, "Shadows", 2, items4,
        (uint)TheSettings.GetIntValue("shadow", "draw"));

    CREATE_DDLWTAB(ddlSpecularLighting, "Specular lighting", 2, items4,
        (uint)TheSettings.GetIntValue("lighting", "specular"));

    CREATE_DDLWTAB(ddlDynamicInstancing, "Dynamic instancing", 2, items4, TheRenderer->GetDynamicInstancing() ? 1U : 0U);

    int itemSizes[9] = {64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    shadowMapSizes.Push(PODVector<int>(itemSizes, sizeof(itemSizes) / sizeof(int)));
    
    char *items6[] = {"64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384"};
    CREATE_DDLWTAB(ddlShadowMapSize, "Shadow map size", 9, items6,
        (uint)TheSettings.GetIntValue("shadow", "map_size"));

    char *items7[] = {"low 16bit", "low 24bit", "high 16bit", "high 24bit"};
    CREATE_DDLWTAB(ddlShadowQuality, "Shadow quality", 4, items7, static_cast<uint>(TheRenderer->GetShadowQuality()));
 
    SharedPtr<UIElement> layout(CreateChild<UIElement>());
    layout->SetAlignment(HA_CENTER, VA_TOP);

    buttonClose = new ButtonT(0, "Close", 100);
    SubscribeToEvent(buttonClose, E_RELEASED, URHO3D_HANDLER(MenuOptions, HandleButtonRelease));
    layout->AddChild(buttonClose);
    AddChild(layout);
    layout->SetMinHeight(buttonClose->GetHeight());

    SetMinSize(GetWidth(), GetHeight());

    buttonClose->SetPosition(GetWidth() / 2 - buttonClose->GetWidth() / 2, buttonClose->GetPosition().y_);

    buttons.Push(buttonClose);
}


void MenuOptions::HandleItemSelected(StringHash, VariantMap& eventData)
{
    DropDownListWithTextAndButton *ddList = dynamic_cast<DropDownListWithTextAndButton*>(eventData[ItemSelected::P_ELEMENT].GetPtr());
    int index = eventData[ItemSelected::P_SELECTION].GetInt();

    if(ddList == ddlTextureQuality)
    {
        TheRenderer->SetTextureQuality((MaterialQuality)index);
        TheSettings.SetInt("texture", "quality", index);
    }
    else if(ddList == ddlTextureAnisotropy)
    {
        TheRenderer->SetTextureAnisotropy(index + 1);
        TheSettings.SetInt("texture", "anisotropy", index);
    }
    else if(ddList == ddlMaterialQuality)
    {
        TheRenderer->SetMaterialQuality((MaterialQuality)index);
        TheSettings.SetInt("material", "quality", index);
    }
    else if(ddList == ddlShadowsEnabled)
    {
        TheRenderer->SetDrawShadows(index == 1);
        TheSettings.SetInt("shadow", "draw", index);
    }
    else if(ddList == ddlSpecularLighting)
    {
        TheRenderer->SetSpecularLighting(index == 1);
        TheSettings.SetInt("lighting", "specular", index);
    }
    else if(ddList == ddlShadowMapSize)
    {
        TheRenderer->SetShadowMapSize(shadowMapSizes[(uint)index]);
        TheSettings.SetInt("shadow", "map_size", index);
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
    SliderWithTextAndButtons *slider = (SliderWithTextAndButtons *)eventData[SliderIntChanged::P_ELEMENT].GetPtr();
    int value = eventData[SliderIntChanged::P_VALUE].GetInt();

    if(slider == sliderMaxOccluderTriangles)
    {
        TheRenderer->SetMaxOccluderTriangles(value);
        TheSettings.SetInt("max_occluder_triangles", value);
    }
    else if (slider == sliderBrightness)
    {
        TheSettings.SetInt("brightness", value);
    }
    else if (slider == sliderVolume)
    {
        TheSettings.SetInt("volume", value);
    }
}


void MenuOptions::HandleButtonRelease(StringHash, VariantMap&)
{
    SendEventClose();
}
