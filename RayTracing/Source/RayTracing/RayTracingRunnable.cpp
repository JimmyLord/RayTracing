#include "PCH.h"

#include "../../Libraries/imgui/imgui.h"
#include "RayTracingRunnable.h"
#include "UI/ImGuiManager.h"

RayTracingRunnable::RayTracingRunnable(fw::FWCore* pFramework)
    : Runnable( pFramework )
{
    m_pImGuiManager = nullptr;
}

RayTracingRunnable::~RayTracingRunnable()
{
}

void RayTracingRunnable::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( m_pFramework );
    m_pImGuiManager->Init();

    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );
}

void RayTracingRunnable::StartFrame(float deltaTime)
{
    m_pImGuiManager->StartFrame( deltaTime );
}

void RayTracingRunnable::Update(float deltaTime)
{
    ImGui::Begin( "Controls" );
    if( ImGui::Button( "Render Frame" ) )
    {
        // TODO:
    }
    ImGui::End();
}

void RayTracingRunnable::Draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pImGuiManager->EndFrame();
}
