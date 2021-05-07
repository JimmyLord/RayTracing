#pragma once

#include "Core/Runnable.h"
#include "Math/Vector.h"

namespace fw
{
    class FWCore;
    class ImGuiManager;
}

class RayTracingRunnable : public fw::Runnable
{
public:
    RayTracingRunnable(fw::FWCore* pFramework);
    virtual ~RayTracingRunnable();

    void Init();
    virtual void StartFrame(float deltaTime);
    virtual void Update(float deltaTime);
    virtual void Draw();

    vec3 CalculatePixelColorForRay(ray r);
    void RenderFrame();

protected:
    fw::ImGuiManager* m_pImGuiManager;

    unsigned char* m_Pixels;
    GLuint m_TextureHandle;
    ivec2 m_TextureSize;

    vec2 m_ViewSize;
    float m_FocalLength;

    vec3 m_CameraPosition;

    // Temp light values.
    vec3 m_MaterialColor;
    vec3 m_LightColor;

    vec3 m_LightPos;
};
