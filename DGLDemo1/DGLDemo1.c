//-------------------------------------------------------------------------------------------------
// file:    main.c
// author:  carter.stutzman
// brief:   demo dgl project
//
// Copyright © 2022 DigiPen, All rights reserved.
//-------------------------------------------------------------------------------------------------

#include "Resource.h"
#include "DGL.h"


DGL_Mesh* createMesh(float width, float height) {
    // Save the half width and height values
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    // Tell DGL that we are starting a new mesh
    DGL_Graphics_StartMesh();
    // All vertices will use this color
    // You could change it between adding vertices to interpolate colors across the mesh
    DGL_Color color = { 1.0f, 0.0f, 0.0f, 1.0f };
    // First triangle
    // Add a vertex at the bottom-left corner
    DGL_Vec2 pos = { -halfWidth, -halfHeight };
    DGL_Vec2 uv = { 0.0f, 1.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-left corner
    pos = { -halfWidth, halfHeight };
    uv = { 0.0f, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-right corner
    pos = { halfWidth, halfHeight };
    uv = { 1.0f, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Second triangle
    // Add a vertex at the bottom-left corner
    pos = { -halfWidth, -halfHeight };
    uv = { 0.0f, 1.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-right corner
    pos = { halfWidth, halfHeight };
    uv = { 1.0f, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the bottom-right corner
    pos = { halfWidth, -halfHeight };
    uv = { 1.0f, 1.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    return DGL_Graphics_EndMesh();
}


LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    int result;
    if (DGL_System_HandleWindowsMessage(message, wParam, lParam, &result))
        return result;

    switch (message)
    {
    case 0:
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    lpCmdLine;
    hPrevInstance;
    DGL_SysInitInfo initInfo;
    initInfo.mAppInstance = hInstance;
    initInfo.mClassStyle = CS_HREDRAW | CS_VREDRAW;
    initInfo.mMaxFrameRate = 60;
    initInfo.mShow = nCmdShow;
    initInfo.mWindowStyle = WS_EX_TOPMOST | WS_POPUP;// WS_OVERLAPPEDWINDOW;
    initInfo.mWindowTitle = "Origami";
    initInfo.mWindowHeight = 1080;
    initInfo.mWindowWidth = 1920;
    initInfo.mCreateConsole = FALSE;
    initInfo.pWindowsCallback = WndProc;
    initInfo.mWindowIcon = IDI_DGLDEMO1;
    HWND windowHandle = DGL_System_Init(&initInfo);
    if (windowHandle == NULL)
        return 1;
    DGL_Color color = { 0.1f, 0.1f, 0.1f, 1.0f };
    DGL_Graphics_SetBackgroundColor(&color);
    DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
    DGL_Mesh* mesh = createMesh(1.0f, 1.0f);
    int running = TRUE;
    DGL_Vec2 pos = { 0.0f, 0.0f };
    DGL_Vec2 scale = { 64.0f, 64.0f };
    while (running)
    {
        DGL_System_FrameControl();
        DGL_System_Update();

        DGL_Graphics_StartDrawing();

        



        DGL_Graphics_FinishDrawing();

        if (!DGL_System_DoesWindowExist() || DGL_Input_KeyTriggered(VK_ESCAPE))
            running = FALSE;
    }

    DGL_System_Exit();

    return 0;
}
