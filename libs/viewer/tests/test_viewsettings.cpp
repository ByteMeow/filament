/*
 * Copyright 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <viewer/ViewSettings.h>

#include <gtest/gtest.h>

namespace viewer = filament::viewer;

class ViewSettingsTest : public testing::Test {};

// Do not autogenerate the ImGui commmands
// However the struct members can (mostly) be referenced directly when calling ImGui commands

static const char* JSON_TEST_1 = R"TXT(
{
    "view": {
        "sampleCount": 1,
        "antiAliasing": "FXAA",
        "taa": {
            "enabled": false,
            "filterWidth": 1.0,
            "feedback": 0.04
        },
        "colorGrading": {
            "enabled": true,
            "quality": "MEDIUM",
            "toneMapping": "ACES_LEGACY",
            "temperature": 0,
            "tint": 0,
            "outRed": [1.0, 0.0, 0.0],
            "outGreen": [0.0, 1.0, 0.0],
            "outBlue": [0.0, 0.0, 1.0],
            "shadows": [1.0, 1.0, 1.0, 0.0],
            "midtones": [1.0, 1.0, 1.0, 0.0],
            "highlights": [1.0, 1.0, 1.0, 0.0],
            "ranges": [0.0, 0.333, 0.550, 1.0],
            "contrast": 1.0,
            "vibrance": 1.0,
            "saturation": 1.0,
            "slope": [1.0, 1.0, 1.0],
            "offset": [0.0, 0.0, 0.0],
            "power": [1.0, 1.0, 1.0],
            "gamma": [1.0, 1.0, 1.0],
            "midPoint": [1.0, 1.0, 1.0],
            "scale": [1.0, 1.0, 1.0],
            "linkedCurves": false
        },
        "ssao": {
            "enabled": false,
            "radius": 0.3,
            "power": 1.0,
            "bias": 0.0005,
            "resolution": 0.5,
            "intensity": 1.0,
            "quality": "LOW",
            "upsampling": "LOW",
            "minHorizonAngleRad": 0.0
        },
        "bloom": {
            "enabled": false,
            "strength": 0.10,
            "resolution": 360,
            "anamorphism": 1.0,
            "levels": 6,
            "blendMode": "ADD",
            "threshold": true,
            "highlight": 1000.0
        },
        "fog": {

        },
        "dof": {

        },
        "vignette": {

        },
        "dithering": "TEMPORAL",
        "renderQuality": {
            "hdrColorBuffer": "HIGH"
        },
        "dynamicLighting": {
            "zLightNear": 5,
            "zLightFar": 100,
        },
        "shadowType": "PCF",
        "postProcessingEnabled": true
    }
}
)TXT";

static const char* JSON_TEST_2 = R"TXT(
[
    {
        "group_name": "View",
        "group_members": [
            {
                "name": "Dithering",
            }

        ]
    },
    {

    }
]
)TXT";

static const char* foobar = R"TXT(

    float mIblIntensity = 30000.0f;
    float mIblRotation = 0.0f;
    float mSunlightIntensity = 100000.0f; // <-- This value is overridden when loading an IBL.
    filament::math::float3 mSunlightColor = filament::Color::toLinear<filament::ACCURATE>({ 0.98, 0.92, 0.89});
    filament::math::float3 mSunlightDirection = {0.6, -1.0, -0.8};
    bool mEnableWireframe = false;
    bool mEnableSunlight = true;
    bool mEnableVsm = false;
    bool mEnableShadows = true;
    int mShadowCascades = 1;
    bool mEnableContactShadows = false;
    std::array<float, 3> mSplitPositions = {0.25f, 0.50f, 0.75f};
    bool mEnableDithering = true;
    bool mEnableFxaa = true;
    bool mEnableMsaa = true;

    "ambientOcclusionOptions": {

    },
    "bloomOptions": {

    },
    "fogOptions": {

    },
    "temporalAntiAliasingOptions": {

    },

    "developer": false,
}
)TXT";

TEST_F(ViewSettingsTest, JsonTest) {

    viewer::Settings* settings1;
    ASSERT_TRUE(viewer::parseJson(JSON_TEST_1, strlen(JSON_TEST_1), &settings1));
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
