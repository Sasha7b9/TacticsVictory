// 2021/04/05 22:40:36 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "stdafx.h"
#include "Graphics/Renderer_.h"


void RendererT::LoadSettings()
{
    static const int shadow_map_sizes[] = { 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384 };
    TheRenderer->SetShadowMapSize(shadow_map_sizes[TheSettings.GetInt("shadow", "map_size")]);

    TheRenderer->SetTextureQuality((MaterialQuality)TheSettings.GetInt("texture", "quality"));
    TheRenderer->SetTextureAnisotropy(TheSettings.GetInt("texture", "anisotropy"));
    TheRenderer->SetMaterialQuality((MaterialQuality)TheSettings.GetInt("material", "quality"));
    TheRenderer->SetDrawShadows(TheSettings.GetInt("shadow", "draw") == 1);
    TheRenderer->SetSpecularLighting(TheSettings.GetInt("lighting", "specular") == 1);
    TheRenderer->SetShadowQuality((ShadowQuality)TheSettings.GetInt("shadow", "quality"));
    TheRenderer->SetDynamicInstancing(TheSettings.GetInt("dynamic_instancing") == 1);
    TheRenderer->SetMaxOccluderTriangles(TheSettings.GetInt("max_occluder_triangles"));
}
