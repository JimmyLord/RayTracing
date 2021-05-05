#pragma once

#include "Core/Runnable.h"

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

protected:
    fw::ImGuiManager* m_pImGuiManager;
};
