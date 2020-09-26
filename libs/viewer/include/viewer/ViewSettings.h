/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by mIcable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef VIEWER_VIEWSETTINGS_H
#define VIEWER_VIEWSETTINGS_H

#include <stddef.h>
#include <stdint.h>

#include <filament/ColorGrading.h>
#include <filament/View.h>

namespace filament {
namespace viewer {

struct Settings;

// ViewSettings* parseJson(const uint8_t* jsonChunk, cgltf_size size);
// void freeSettings(ViewSettings* settings);

bool parseJson(const char* jsonChunk, size_t size, Settings** out);

struct ColorGradingSettings {
    using QualityLevel = filament::ColorGrading::QualityLevel;
    using ToneMapping = filament::ColorGrading::ToneMapping;
    bool enabled = true;
    QualityLevel quality = QualityLevel::MEDIUM;
    ToneMapping toneMapping = ToneMapping::ACES_LEGACY;
    int temperature = 0;
    int tint = 0;
    math::float3 outRed{1.0f, 0.0f, 0.0f};
    math::float3 outGreen{0.0f, 1.0f, 0.0f};
    math::float3 outBlue{0.0f, 0.0f, 1.0f};
    math::float4 shadows{1.0f, 1.0f, 1.0f, 0.0f};
    math::float4 midtones{1.0f, 1.0f, 1.0f, 0.0f};
    math::float4 highlights{1.0f, 1.0f, 1.0f, 0.0f};
    math::float4 ranges{0.0f, 0.333f, 0.550f, 1.0f};
    float contrast = 1.0f;
    float vibrance = 1.0f;
    float saturation = 1.0f;
    math::float3 slope{1.0f};
    math::float3 offset{0.0f};
    math::float3 power{1.0f};
    math::float3 gamma{1.0f};
    math::float3 midPoint{1.0f};
    math::float3 scale{1.0f};
    bool linkedCurves = false;
};

struct DynamicLightingSettings {
    float zLightNear = 5;
    float zLightFar = 100;
};

struct ViewSettings {
    uint8_t sampleCount = 1;
    filament::View::AntiAliasing antiAliasing = filament::View::AntiAliasing::FXAA;
    filament::View::TemporalAntiAliasingOptions taa;
    ColorGradingSettings colorGrading;
    filament::View::AmbientOcclusionOptions ssao;
    filament::View::BloomOptions bloom;
    filament::View::FogOptions fog;
    filament::View::DepthOfFieldOptions dof;
    filament::View::VignetteOptions vignette;
    filament::View::Dithering dithering = filament::View::Dithering::TEMPORAL;
    filament::View::RenderQuality renderQuality;
    DynamicLightingSettings dynamicLighting;
    filament::View::ShadowType shadowType = filament::View::ShadowType::PCF;
    bool postProcessingEnabled = true;
};

struct Settings {
    ViewSettings view;
};

} // namespace viewer
} // namespace filament

#endif // VIEWER_SETTINGS_H
