// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "FileSystem/ConfigurationFile_.h"
#include "GUI/Controls/DropDownListWithTextAndButton_.h"
#include "GUI/Controls/Buttons/ButtonSwitch_.h"
#include "GUI/Controls/Sliders/SliderInt_.h"
#include "GUI/Controls/Sliders/SliderWithTextAndButtons_.h"
#include "GUI/Menu/PageOptions.h"


PageOptions::PageOptions() : MenuPage()
{
    SetLayout(LM_VERTICAL, 0, IntRect(0, 0, 0, 0));

    SetName("Options menu");

    SharedPtr<Label> label(Label::Create("Options", 20));
    label->SetAlignment(HA_CENTER, VA_CENTER);
    label->SetTextAlignment(HA_CENTER);
    AddChild(label);

#define CREATE_SWTAB(name, text, min, max, step, startIndex)                                  \
    name = new SliderWithTextAndButtons(this, text, min, max, step);                          \
    SubscribeToEvent(name, E_SLIDERINTCHANGED, URHO3D_HANDLER(PageOptions, HandleOnSlider));  \
    name->SetValue(startIndex);

    CREATE_SWTAB(sliderBrightness, "Brightness", 0, 100, 1, TheSettings.GetInt("brightness"));

    CREATE_SWTAB(sliderVolume, "Volume", 0, 100, 1, TheSettings.GetInt("volume"));

    CREATE_SWTAB(sliderMaxOccluderTriangles, "Max occluder triangles", 0, 5000, 1,
        TheSettings.GetInt("max_occluder_triangles"));

    int width0 = TheSettings.GetInt("menu", "text", "width");
    int width1 = TheSettings.GetInt("menu", "ddlist", "width");

#define CREATE_DDLWTAB(name, text, num, itms, startIndex)                                       \
    name = DropDownListWithTextAndButton::Create(this, text, width0, width1, num, itms);        \
    SubscribeToEvent(name, E_ITEMSELECTED, URHO3D_HANDLER(PageOptions, HandleItemSelected));    \
    name->SetSelection(startIndex);

    char *items0[] = { "Off", "On" };
    CREATE_DDLWTAB(ddlFullScreen, "Full screen", 2, items0,
        (uint)TheSettings.GetInt("full_screen"));

    char *items1[] = { "Low", "Medium", "High" };
    CREATE_DDLWTAB(ddlTextureQuality, "Texture quality", 3, items1,
        (uint)TheSettings.GetInt("texture", "quality"));

    char *items2[] = {"x1", "x2", "x4", "x8", "x16", "x32"};
    CREATE_DDLWTAB(ddlTextureAnisotropy, "Texture anisotropy", 6, items2,
        (uint)TheSettings.GetInt("texture", "anisotropy"));

    char *items3[] = {"Low", "Medium", "High", "Max"};
    CREATE_DDLWTAB(ddlMaterialQuality, "Material quality", 4, items3,
        (uint)TheSettings.GetInt("material", "quality"));

    char *items4[] = {"Off", "On"};
    CREATE_DDLWTAB(ddlShadowsEnabled, "Shadows", 2, items4,
        (uint)TheSettings.GetInt("shadow", "draw"));

    CREATE_DDLWTAB(ddlSpecularLighting, "Specular lighting", 2, items4,
        (uint)TheSettings.GetInt("lighting", "specular"));

    CREATE_DDLWTAB(ddlDynamicInstancing, "Dynamic instancing", 2, items4,
        (uint)TheSettings.GetInt("dynamic_instancing"));

    char *items6[] = {"64", "128", "256", "512", "1024", "2048", "4096", "8192", "16384"};
    CREATE_DDLWTAB(ddlShadowMapSize, "Shadow map size", 9, items6,
        (uint)TheSettings.GetInt("shadow", "map_size"));

    char *items7[] = {"low 16bit", "low 24bit", "high 16bit", "high 24bit"};
    CREATE_DDLWTAB(ddlShadowQuality, "Shadow quality", 4, items7,
        (uint)TheSettings.GetInt("shadow", "quality"));
 
    SharedPtr<UIElement> layout(CreateChild<UIElement>());
    layout->SetAlignment(HA_CENTER, VA_TOP);

    buttonClose = new ButtonT(0, "Close", 100);
    SubscribeToEvent(buttonClose, E_RELEASED, URHO3D_HANDLER(PageOptions, HandleButtonRelease));
    layout->AddChild(buttonClose);
    AddChild(layout);
    layout->SetMinHeight(buttonClose->GetHeight());

    SetMinSize(GetWidth() + 15, GetHeight() + 50);

    buttonClose->SetPosition(GetWidth() / 2 - buttonClose->GetWidth() / 2, buttonClose->GetPosition().y_);

    buttons.Push(buttonClose);
}


void PageOptions::HandleItemSelected(StringHash, VariantMap& eventData)
{
    DropDownListWithTextAndButton *ddList = (DropDownListWithTextAndButton *)eventData[ItemSelected::P_ELEMENT].GetPtr();
    int index = eventData[ItemSelected::P_SELECTION].GetInt();

    if (ddList == ddlFullScreen)
    {
        TheSettings.SetInt(index, "full_screen");
    }
    else if(ddList == ddlTextureQuality)
    {
        TheSettings.SetInt(index, "texture", "quality");
    }
    else if(ddList == ddlTextureAnisotropy)
    {
        TheSettings.SetInt(index, "texture", "anisotropy");
    }
    else if(ddList == ddlMaterialQuality)
    {
        TheSettings.SetInt(index, "material", "quality");
    }
    else if(ddList == ddlShadowsEnabled)
    {
        TheSettings.SetInt(index, "shadow", "draw");
    }
    else if(ddList == ddlSpecularLighting)
    {
        TheSettings.SetInt(index, "lighting", "specular");
    }
    else if(ddList == ddlShadowMapSize)
    {
        TheSettings.SetInt(index, "shadow", "map_size");
    }
    else if(ddList == ddlShadowQuality)
    {
        TheSettings.SetInt(index, "shadow", "quality");
    }
    else if(ddList == ddlDynamicInstancing)
    {
        TheSettings.SetInt(index, "dynamic_instancing");
    }
}


void PageOptions::HandleOnSlider(StringHash, VariantMap& eventData)
{
    SliderWithTextAndButtons *slider = (SliderWithTextAndButtons *)eventData[SliderIntChanged::P_ELEMENT].GetPtr();
    int value = eventData[SliderIntChanged::P_VALUE].GetInt();

    if(slider == sliderMaxOccluderTriangles)
    {
        TheSettings.SetInt(value, "max_occluder_triangles");
    }
    else if (slider == sliderBrightness)
    {
        TheSettings.SetInt(value, "brightness");
    }
    else if (slider == sliderVolume)
    {
        TheSettings.SetInt(value, "volume");
    }
}


void PageOptions::HandleButtonRelease(StringHash, VariantMap&)
{
    SendEventClose();
}
