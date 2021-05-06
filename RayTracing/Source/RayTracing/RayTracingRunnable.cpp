#include "PCH.h"

#include "../../Libraries/imgui/imgui.h"
#include "GL/GLExtensions.h"
#include "RayTracingRunnable.h"
#include "UI/ImGuiManager.h"

RayTracingRunnable::RayTracingRunnable(fw::FWCore* pFramework)
    : Runnable( pFramework )
{
    m_pImGuiManager = nullptr;

    m_Pixels = nullptr;
    m_TextureHandle = 0;
    m_TextureSize.Set( 512, 256 );

    m_ViewSize.Set( 4, 2 );
    m_FocalLength = 1;

    m_CameraPosition.Set( 0, 0, 0 );
}

RayTracingRunnable::~RayTracingRunnable()
{
    glDeleteTextures( 1, &m_TextureHandle );
    delete m_Pixels;

    delete m_pImGuiManager;
}

void RayTracingRunnable::Init()
{
    m_pImGuiManager = new fw::ImGuiManager( m_pFramework );
    m_pImGuiManager->Init();

    glClearColor( 0.0f, 0.0f, 0.2f, 1.0f );

    m_Pixels = new unsigned char[m_TextureSize.x*m_TextureSize.y*4];
    for( int y=0; y<m_TextureSize.y; y++ )
    {
        for( int x=0; x<m_TextureSize.x; x++ )
        {
            int baseIndex = y*m_TextureSize.x + x;
            int index = baseIndex * 4;

            m_Pixels[index+0] = 0;
            m_Pixels[index+1] = 0;
            m_Pixels[index+2] = 0;
            m_Pixels[index+3] = 255;
        }
    }

    glGenTextures( 1, &m_TextureHandle );
    glBindTexture( GL_TEXTURE_2D, m_TextureHandle );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_TextureSize.x, m_TextureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Pixels );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0 );
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
        RenderFrame();
    }
    ImGui::End();

    ImGui::Begin( "Render" );
    ImGui::Image( (ImTextureID)(uintptr_t)m_TextureHandle, ImVec2((float)m_TextureSize.x, (float)m_TextureSize.y), ImVec2(0,1), ImVec2(1,0) );
    ImGui::End();
}

void RayTracingRunnable::Draw()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    m_pImGuiManager->EndFrame();
}

vec3 RayTracingRunnable::CalculatePixelColorForRay(ray r)
{
    vec3 dir = r.dir.GetNormalized();

    // percH is 0 at bottom, 1 at top.
    float percH = (dir.y + 1.0f) * 0.5f;

    return (1.0f-percH)*vec3(1.0f, 1.0f, 1.0f) + percH*vec3(0.5f, 0.7f, 1.0f);
}

void RayTracingRunnable::RenderFrame()
{
    // Precalculate the lower left coordinate of our viewport.
    vec3 horizontal = vec3::Right()*m_ViewSize.x;
    vec3 vertical = vec3::Up()*m_ViewSize.y;
    vec3 viewportLL = m_CameraPosition - horizontal/2 - vertical/2 + vec3::In()*m_FocalLength;

    for( int y=0; y<m_TextureSize.y; y++ )
    {
        for( int x=0; x<m_TextureSize.x; x++ )
        {
            int baseIndex = y*m_TextureSize.x + x;
            int index = baseIndex * 4;

            float percX = x / (float)(m_TextureSize.x - 1);
            float percY = y / (float)(m_TextureSize.y - 1);

            vec3 dir = viewportLL + horizontal*percX + vertical*percY - m_CameraPosition;
            ray r( m_CameraPosition, dir );

            vec3 color = CalculatePixelColorForRay( r );

            m_Pixels[index+0] = (unsigned char)(color.x * 255);
            m_Pixels[index+1] = (unsigned char)(color.y * 255);
            m_Pixels[index+2] = (unsigned char)(color.z * 255);
            m_Pixels[index+3] = 255;
        }
    }

    glBindTexture( GL_TEXTURE_2D, m_TextureHandle );
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_TextureSize.x, m_TextureSize.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Pixels );
}
