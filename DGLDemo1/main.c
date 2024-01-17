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



    //DGL_Mesh* mesh = createTriMesh(1.0f, 1.0f);
    //old origami
    //Triangle* t = createTriangle(0, DGL_Graphics_LoadTexture("./Assets/Paper/paper1.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"));
    //Triangle* t2 = createTriangle(0, DGL_Graphics_LoadTexture("./Assets/Paper/paper1.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"));


    //old origami
    //SmallSquare* s = createSmallSquare(DGL_Graphics_LoadTexture("./Assets/Paper/paper3.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"), 1);
    //SmallSquare* s2 = createSmallSquare(DGL_Graphics_LoadTexture("./Assets/Paper/paper3.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"), -1);
    //SmallSquare* s3 = createSmallSquare(DGL_Graphics_LoadTexture("./Assets/Paper/paper3.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"), -5);
    //SmallSquare* s4 = createSmallSquare(DGL_Graphics_LoadTexture("./Assets/Paper/paper3.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"), -3);
    //SmallSquare* temp;
    int flipy = 0;

    int running = TRUE;

    int test = 0;
    int angle = 0;

    int times = 0;


    //new origami (which we will use)
    PaperArray* p = createPaperArray(DGL_Graphics_LoadTexture("./Assets/Paper/paper2.png"), DGL_Graphics_LoadTexture("./Assets/Paper/paper1.png"));

    //room testing
    DGL_Texture* tex0 = DGL_Graphics_LoadTexture("./Assets/Paper/wall1.png");
    DGL_Texture* tex1 = DGL_Graphics_LoadTexture("./Assets/Paper/wall2.png");
    DGL_Texture* tex2 = DGL_Graphics_LoadTexture("./Assets/Paper/wall3.png");
    DGL_Texture* tex3 = DGL_Graphics_LoadTexture("./Assets/Paper/paper4.png");
    

    Room* r = createRoom(tex0, tex0, tex0, tex0, tex0, tex0);
    Room* r2 = createRoom(tex1, tex2, tex1, tex2, tex1, tex1);

    r2->width *= 5.0f;
    while (running)
    {
        DGL_System_FrameControl();
        DGL_System_Update();
        DGL_Graphics_StartDrawing();

        //if (test == 1) {
        //    //drawTriangle(t, 0.0f, 0.0f);
        //    drawSmallSquare(s, -226.0f, 226.0f * (flipy == 0));
        //    drawSmallSquare(s2, 226.0f, 226.0f * (flipy == 0));
        //
        //    drawSmallSquare(s3,-226.0f, -226.0f * (flipy == 0));
        //    drawSmallSquare(s4, 226.0f, -226.0f * (flipy == 0));
        //
        //
        //  DGL_Graphics_DrawMesh(mesh, DGL_DM_TRIANGLELIST);
        //  DGL_Graphics_FinishDrawing();
        //
        //    if (DGL_Input_KeyTriggered(VK_SPACE)) {
        //        //s->angle++;
        //        flipy = abs(flipy - 1);
        //    }
        //    
        //    if (DGL_Input_KeyTriggered('1')) {
        //        foldSmallSquare(s, 1, -0.10f);
        //    }
        //    if (DGL_Input_KeyTriggered('2')) {
        //        foldSmallSquare(s2, 1, -0.10f);
        //    }
        //    if (DGL_Input_KeyTriggered('3')) {
        //        foldSmallSquare(s3, 1, -0.10f);
        //    }
        //    if (DGL_Input_KeyTriggered('4')) {
        //        foldSmallSquare(s4, 1, -0.10f);
        //    }


            

        //    stepSmallSquare(s);
        //    stepSmallSquare(s2);
        //    stepSmallSquare(s3);
        //    stepSmallSquare(s4);
        //}
        if (test == 1) {
            drawRoom(r2);
            drawRoom(r);
            DGL_Graphics_FinishDrawing();
            if (DGL_Input_KeyTriggered(VK_RIGHT)) {
                //rotateRoom(r, 30.0f / 60.0f);
                r->dir = 1.0f;
                r2->dir = 1.0f;
            }
            if (DGL_Input_KeyTriggered(VK_LEFT)) {
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
            //7 2 4 3 3             wolf's face
            //1 1 7 7 5 3 4         makes another thing (face?
            //2 1 1 7 7 4 2         makes a backward facing bird?
            //7 7 3 3 1 5 0 4       makes a strange snake looking guy
            //0 1 1 5 5 6 5 3 3     makes a grave
            //7 7 5 5 1 1 3 3 2 4   makes a heart
            //1 1 2 5 5 7 7 6 3 3 7 makes a pinwheel
            drawPaperArray(p, angle);

            DGL_Graphics_FinishDrawing();
            if (DGL_Input_KeyTriggered(VK_DOWN)) {
                foldPaperArray(p, angle, 0);
                times++;
                
            }
            
            if (DGL_Input_KeyTriggered(VK_LEFT)) {
                angle++;
            }
            if (DGL_Input_KeyTriggered(VK_RIGHT)) {
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

        if (DGL_Input_KeyTriggered(VK_OEM_COMMA)) {
            test = 1;
            
        }
        if (DGL_Input_KeyTriggered(VK_OEM_PERIOD)) {
            test = 0;
        }

        if (!DGL_System_DoesWindowExist() || DGL_Input_KeyTriggered(VK_ESCAPE))
            running = FALSE;
    }

    DGL_System_Exit();

    return 0;
}
