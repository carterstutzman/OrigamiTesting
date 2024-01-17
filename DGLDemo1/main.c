//-------------------------------------------------------------------------------------------------
// file:    main.c
// author:  carter.stutzman
// brief:   demo dgl project
//
// Copyright © 2022 DigiPen, All rights reserved.
//-------------------------------------------------------------------------------------------------

#include "Resource.h"
#include "DGL.h"
#include "origraphics.h"
#include "rotateroom.h"
#include "cube.h"


int speed = 2;


LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT message, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
    int result;
    if (DGL_System_HandleWindowsMessage(message, wParam, lParam, &result))
        return result;

    //switch (message)
    //{
    //
    //default:
    //    return DefWindowProc(hWnd, message, wParam, lParam);
    //}
    return DefWindowProc(hWnd, message, wParam, lParam);
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
    initInfo.mCreateConsole = TRUE;
    initInfo.pWindowsCallback = WndProc;
    initInfo.mWindowIcon = IDI_DGLDEMO1;
    HWND windowHandle = DGL_System_Init(&initInfo);
    if (windowHandle == NULL)
        return 1;
    DGL_Color color = { 0.1f, 0.1f, 0.1f, 1.0f };
    DGL_Graphics_SetBackgroundColor(&color);
    DGL_Graphics_SetBlendMode(DGL_BM_BLEND);


    int running = TRUE;

    int test = 0;


    //new origami (which we will use)
    PaperArray* p = createPaperArray(DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper1.png"));

    //room testing
    DGL_Texture* tex0 = DGL_Graphics_LoadTexture("./Assets/Layers/00.png");
    DGL_Texture* tex1 = DGL_Graphics_LoadTexture("./Assets/Layers/frame.png");

    DGL_Texture* tex2 = DGL_Graphics_LoadTexture("./Assets/Paper/wall3.png");
    DGL_Texture* tex3 = DGL_Graphics_LoadTexture("./Assets/Paper/paper4.png");

    TextureList* list = loadTextureList(0, 1);

    Room* r = createRoom(tex1, tex1, tex1, tex1, tex1, tex1, 1.0f);

    Room* r2 = createRoom(tex0, tex0, tex0, tex0, tex0, tex0, 1.5f);


    r2->width *= 1.0f;

    Block* block = createBlock((DGL_Vec2) { 128.0f, 128.0f }, 0.5f, list->textures[0]);
    DGL_Vec2 pos = { 0.0f, 0.0f };
    int offx = 0;
    int offy = 0;

    int angle = 0;
    int times = 0;


    char MAP[49][49] = {
    "000000000000000000000000000000000000000000000000",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "000000000000000000000000000000000000000000000000",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "000000000000000000000000000000000000000000000000",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "000000000000000000000000000000000000000000000000",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "0..............................................0",
    "000000000000000000000000000000000000000000000000",
    };

    while (running)
    {
        DGL_System_FrameControl();
        DGL_System_Update();
        DGL_Graphics_StartDrawing();
        if (test == 2) {
            drawTilemap(MAP, pos, offx, offy, block, list);
            DGL_Graphics_FinishDrawing();
            if (DGL_Input_KeyDown('A')) {
                pos.x -= speed;
            }
            if (DGL_Input_KeyDown('D')) {
                pos.x += speed;
            }

            if (DGL_Input_KeyDown('W')) {
                pos.y -= speed;
            }
            if (DGL_Input_KeyDown('S')) {
                pos.y += speed;
            }

            offx = 0 + (int)(pos.x / 128.0f) * 1;
            offy = 0 + (int)((pos.y - 0.0f) / 128.0f) * 1;

        }

        if (test == 1) {
            DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 0.0f, 0.0f });
            drawRoom(r2);
            drawRoom(r);
            DGL_Graphics_FinishDrawing();
            if (DGL_Input_KeyTriggered('D')) {
                //rotateRoom(r, 30.0f / 60.0f);
                r->dir = 1.0f;
                r2->dir = 1.0f;
            }
            if (DGL_Input_KeyTriggered('A')) {
                //rotateRoom(r, -30.0f / 60.0f);
                r->dir = -1.0f;
                r2->dir = -1.0f;
            }
            if (DGL_Input_KeyTriggered(VK_SPACE)) {
                printf("%f\n", r->angle);
            }

            stepRoom(r);
            stepRoom(r2);


        }
        if (test == 0) {
            //old 5x5 tiles
            //7 2 4 3 3             wolf's face
            //1 1 7 7 5 3 4         makes another thing (face?
            //2 1 1 7 7 4 2         makes a backward facing bird?
            //7 7 3 3 1 5 0 4       makes a strange snake looking guy
            //0 1 1 5 5 6 5 3 3     makes a grave
            //7 7 5 5 1 1 3 3 2 4   makes a heart
            //1 1 2 5 5 7 7 6 3 3 7 makes a pinwheel


            //new 4 tile ones
            //7 1 1 3 5 4 6    paper plane/rocket
            //7 7 3 3 5 1 0 4  pinwheel
            drawPaperArray(p, angle);

            DGL_Graphics_FinishDrawing();
            if (DGL_Input_KeyTriggered('S')) {
                foldPaperArray(p, angle, 0);
                times++;
                
            }
            
            if (DGL_Input_KeyTriggered('A')) {
                angle++;
            }
            if (DGL_Input_KeyTriggered('D')) {
                angle--;
            }
            if (angle > 7) angle = 0;
            if (angle < 0) angle = 7;


            if (DGL_Input_KeyTriggered(VK_SPACE) || times >= 99) {
                printf("RESET\n");
                resetPaperArray(p);
                times = 0;
                angle = 0;
            }
        }

        if (DGL_Input_KeyTriggered(VK_OEM_PERIOD)) {
            test++;
            if (test > 2) { test = 2; }
        }
        if (DGL_Input_KeyTriggered(VK_OEM_COMMA)) {
            test--;
            if (test < 0) { test = 0; }
        }

        if (!DGL_System_DoesWindowExist() || DGL_Input_KeyTriggered(VK_ESCAPE))
            running = FALSE;
    }

    DGL_System_Exit();

    return 0;
}
