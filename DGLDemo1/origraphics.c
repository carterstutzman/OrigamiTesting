#include "origraphics.h"
#include "graphicsutils.h"
#include "DGL.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define PI 3.141592f

DGL_Mesh* createTriMeshOption(float width, float height, int option) {
    // Save the half width and height values
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float size = 1.0f/1.0f;
    // Tell DGL that we are starting a new mesh
    DGL_Graphics_StartMesh();
    if (option == 0) {//Triangle upper left ya know
        DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
        // First triangle
        // Add a vertex at the bottom-left corner
        DGL_Vec2 pos = { -halfWidth, -halfHeight };
        DGL_Vec2 uv = { 0.0f, size };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the top-left corner
        pos = (DGL_Vec2){ -halfWidth, halfHeight };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the top-right corner
        pos = (DGL_Vec2){ halfWidth, halfHeight };
        uv = (DGL_Vec2){ size, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    if (option == 1) {//Triangle upper right ya know
        DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
        // First triangle
        // Add a vertex at the bottom-right corner
        DGL_Vec2 pos = {  halfWidth, -halfHeight };
        DGL_Vec2 uv = { size, size };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the top-left corner
        pos = (DGL_Vec2){ -halfWidth, halfHeight };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the top-right corner
        pos = (DGL_Vec2){ halfWidth, halfHeight };
        uv = (DGL_Vec2){ size, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }

    if (option == 2) {//Triangle lower left ya know
        DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
        // First triangle
        // Add a vertex at the bottom-left corner
        DGL_Vec2 pos = { -halfWidth, -halfHeight };
        DGL_Vec2 uv = { 0.0f, size };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the top-left corner
        pos = (DGL_Vec2){ -halfWidth, halfHeight };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the bottom-right corner
        pos = (DGL_Vec2){ halfWidth, -halfHeight };
        uv = (DGL_Vec2){ size, size };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    if (option == 3) {//Triangle lower right ya know
        DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
        // First triangle
        // Add a vertex at the bottom-left corner
        DGL_Vec2 pos = { -halfWidth, -halfHeight };
        DGL_Vec2 uv = { 0.0f, size };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the bottom right corner
        pos = (DGL_Vec2){  halfWidth,-halfHeight };
        uv = (DGL_Vec2){ size, size };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        // Add a vertex at the top-right corner
        pos = (DGL_Vec2){ halfWidth, halfHeight };
        uv = (DGL_Vec2){ size, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    return DGL_Graphics_EndMesh();
}


Triangle* createTriangle(int angle, DGL_Texture* topTex, DGL_Texture* botTex) {
    Triangle* t = (Triangle*)(malloc(sizeof(Triangle)));
    if (t) {
        t->angle = angle;
        t->stretchDiagonal = 1.0f;
        t->stretchVertical = 0.0f;
        t->stretchHorizontal = 1.0f;

        t->mesh = createTriMesh(640.0f, 640.0f);
        t->topTex = topTex;
        t->botTex = botTex;


    }
    return t;
}
void drawTriangle(Triangle* t, int x, int y, int angle, int bias, float shadow) {
    //float c = cosf((t->angle * 45.0f) * (PI / 180.0f));
    //float s = sinf((t->angle * 45.0f) * (PI / 180.0f));
    
    DGL_Vec2 pos = { x, y };
    DGL_Vec2 stretch = { 1.0f*bias,  1.0f* t->stretchDiagonal };

    DGL_Color col = { 0.0f, 0.0f, 0.0f, shadow};
    //DGL_Graphics_
    //DGL_Graphics_SetShaderMode(DGL_PSM_COLOR, DGL_VSM_DEFAULT);
    
    DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
    if (t->stretchDiagonal > 0) DGL_Graphics_SetTexture(t->topTex);
    else DGL_Graphics_SetTexture(t->botTex);

    DGL_Graphics_SetCB_TransformData(&pos, &stretch, (angle * 45.0f) * (PI/180.0f));
    //DGL_Graphics_SetCB_TintColor(&col);
    DGL_Graphics_SetCB_Alpha(1.0f);
    if (shadow != 1.0f) {
        DGL_Graphics_SetCB_Alpha(0.875f+(shadow + 1.0f) / 16.0f);
    }

    DGL_Graphics_DrawMesh(t->mesh, DGL_DM_TRIANGLELIST);
}

SmallSquare* createSmallSquare(DGL_Texture* t1, DGL_Texture* t2, int angle) {
    SmallSquare* s = (SmallSquare*)(malloc(sizeof(SmallSquare)));
    if (s) {
        s->t1 = createTriangle(0, t1, t2);
        s->t2 = createTriangle(4, t1, t2);
        s->angle = angle;

        s->isFlipping = 0;
        s->flipSpeed = 0.0f;
        s->isFlipped = 0;
    }
    return s;
}
void drawSmallSquare(SmallSquare* s, float x, float y) {
    //sorts by depth (which to draw on top)
    if (s->t2->stretchDiagonal < 0) {
        drawTriangle(s->t1, x, y, s->angle + 0, 1.0f, 1.0f);
        drawTriangle(s->t2, x, y, s->angle + 4, -1.0f, s->t1->stretchDiagonal);
    }
    else {
        drawTriangle(s->t2, x, y, s->angle + 4, -1.0f, s->t1->stretchDiagonal);
        drawTriangle(s->t1, x, y, s->angle + 0, 1.0f, 1.0f);   
    }
}
void foldSmallSquare(SmallSquare* s, int which, float much) {
    s->isFlipping = 1;
    if (s->isFlipped == 0) {
        s->flipSpeed = much;
    }
    if (s->isFlipped == 1) {
        s->flipSpeed = -much;
    }

}

void stepSmallSquare(SmallSquare* s) {
    if (s->isFlipping == 1) {
        s->t1->stretchDiagonal += s->flipSpeed * (0.1f + fabsf(s->t1->stretchDiagonal - 1.0f));
        if (s->t1->stretchDiagonal > 1.0f) {
            s->t1->stretchDiagonal = 1.0f;
            s->isFlipping = 0;
            s->flipSpeed = 0.0f;
            s->isFlipped = 0;

        }
        if (s->t1->stretchDiagonal < -1.0f) {
            s->t1->stretchDiagonal = -1.0f;
            s->isFlipping = 0;
            s->flipSpeed = 0.0f;
            s->isFlipped = 1;

        }
    }
}




//Below this line is what we'll use OK?
PaperArray* createPaperArray(DGL_Texture* t1, DGL_Texture* t2) {
    PaperArray* p = (PaperArray*)(malloc(sizeof(PaperArray)));
    if (p) {
        p->t1 = t1;
        p->t2 = t2;
        p->sqMesh = createRectMesh(128.0f, 128.0f);
        
        p->upLeft = createTriMeshOption(128.0f, 128.0f, 0);
        p->upRight = createTriMeshOption(128.0f, 128.0f, 1);
        p->downLeft = createTriMeshOption(128.0f, 128.0f, 2);
        p->downRight = createTriMeshOption(128.0f, 128.0f, 3);


        for (int a = 0; a < 5; a++) {
            for (int b = 0; b < 5; b++) {
                p->map[a][b] = 1;
            }
        }
    }
    return p;
}
void drawPaperArray(PaperArray* p, int angle) {
    DGL_Vec2 pos = { 0.0f, 0.0f };
    DGL_Vec2 scale = { 1.0f, 1.0f };
    DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
    
    //printf("%i\n", angle);

    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            if (p->map[y][x] != 0) {

                if (angle == 0) {
                    pos = (DGL_Vec2){ (x - 2) * 128.0f, -(y - 2) * 128.0f };
                }
                if (angle == 1) {//rotate left diagonal 45
                    pos = (DGL_Vec2){ (x - 2) * 90.0f + (y-2)*90.0f, (x - 2) * 90.0f - (y -2) * 90.0f,};
                }
                if (angle == 2) {//fully rotated 90 degrees to the left}
                    pos = (DGL_Vec2){ (y - 2) * 128.0f, (x - 2) * 128.0f };
                };
                if (angle == 3) {
                    pos = (DGL_Vec2){ -(x - 2) * 90.0f + (y - 2) * 90.0f, (x - 2) * 90.0f + (y - 2) * 90.0f };
                }
                if (angle == 4) {
                    pos = (DGL_Vec2){ -(x - 2) * 128.0f, (y - 2) * 128.0f };
                }
                if (angle == 5) {
                    pos = (DGL_Vec2){ -(x - 2) * 90.0f - (y - 2) * 90.0f, -(x - 2) * 90.0f + (y - 2) * 90.0f };
                }
                if (angle == 6) {
                    pos = (DGL_Vec2){ -(y - 2) * 128.0f, -(x - 2) * 128.0f };
                }
                if (angle == 7) {
                    pos = (DGL_Vec2){ (x - 2) * 90.0f - (y - 2) * 90.0f, -(x - 2) * 90.0f - (y - 2) * 90.0f };
                }
                DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2){ x*64.0f, y*64.0f });
                DGL_Graphics_SetCB_TransformData(&pos, &scale, (45.0f * angle) * (PI/180.0f));
                DGL_Graphics_SetCB_Alpha(1.0f);
                
                
                if (p->map[y][x] < 3) {
                    if (p->map[y][x] == 1) DGL_Graphics_SetTexture(p->t1);//Regular Face Up
                    if (p->map[y][x] == 2) DGL_Graphics_SetTexture(p->t2);//Regular Face Down
                    DGL_Graphics_DrawMesh(p->sqMesh, DGL_DM_TRIANGLELIST);
                }

                else if (p->map[y][x] >= 3 && p->map[y][x] < 11) {
                    
                    if (p->map[y][x] > 6) {
                        DGL_Graphics_SetTexture(p->t1);
                        DGL_Graphics_DrawMesh(p->sqMesh, DGL_DM_TRIANGLELIST);
                    }
                    DGL_Graphics_SetTexture(p->t2);
                    if (p->map[y][x] == 3 || p->map[y][x] == 7)  DGL_Graphics_DrawMesh(p->upLeft, DGL_DM_TRIANGLELIST);
                    if (p->map[y][x] == 4 || p->map[y][x] == 8)  DGL_Graphics_DrawMesh(p->upRight, DGL_DM_TRIANGLELIST);
                    if (p->map[y][x] == 5 || p->map[y][x] == 9)  DGL_Graphics_DrawMesh(p->downLeft, DGL_DM_TRIANGLELIST);
                    if (p->map[y][x] == 6 || p->map[y][x] == 10) DGL_Graphics_DrawMesh(p->downRight, DGL_DM_TRIANGLELIST);
                }
            }
        }
    }
}


void foldPaperArray(PaperArray* p, int dir, int dist) {//dir is direction UP, UPRIGHT, RIGHT, RIGHTDOWN, DOWN, DOWNLEFT, LEFT, UPLEFT, UP AGAIN 
    int flag = 0;
    int flag2 = 0;
    printf("%i ", dir);
    if (dir == 0) {//Folding the top side onto the bottom
        //printf("\n");
        for (int y = 0; y < 5; y++) {
            for (int x = 0; x < 5; x++) {
                //printf("%i ", p->map[y][x]);
                if (y != 4) {
                    switch (p->map[y][x]) {
                    case 0:
                        break;
                    case 1:
                        p->map[y][x] = 0;
                        p->map[y + 1][x] = 2;
                        flag = 1;
                        break;
                    case 2:
                        p->map[y][x] = 0;
                        p->map[y + 1][x] = 2;
                        flag = 1;
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        p->map[y][x] = 0;
                        if (p->map[y + 1][x] == 1) {
                            p->map[y + 1][x] = 7;
                        }
                        else { p->map[y + 1][x] = 2; }
                        flag = 1;
                        break;
                    case 6:
                        p->map[y][x] = 0;
                        if (p->map[y + 1][x] == 1) {
                            p->map[y + 1][x] = 8;
                        }
                        else { p->map[y + 1][x] = 2; }
                        flag = 1;
                        break;

                    default://7 8 9 10 
                        p->map[y][x] = 0;
                        p->map[y + 1][x] = 2;
                        flag = 1;
                        break;
                    }
                }
                //printf("\n");
            }
            if (flag) break;
        }
    }
    if (dir == 2) {//folding what was right to left
        //printf("\n");
        for (int x = 4; x > -1; x--) {
            for (int y = 0; y < 5; y++) {
                //printf("%i ", p->map[y][x]);
                if (x != 0) {
                    switch (p->map[y][x]) {
                    case 0:
                        break;
                    case 1:
                        p->map[y][x] = 0;
                        p->map[y][x - 1] = 2;
                        flag = 1;
                        break;
                    case 2:
                        p->map[y][x] = 0;
                        p->map[y][x - 1] = 2;
                        flag = 1;
                        break;
                    case 3:
                        p->map[y][x] = 0;
                        if (p->map[y][x - 1] == 1) {
                            p->map[y][x - 1] = 8;
                        }
                        else { p->map[y][x - 1] = 2; }
                        flag = 1;
                        break;
                    //case 4:
                    //    p->map[y][x] = 0;
                    //    if (p->map[y][x - 1] == 1) {
                    //        p->map[y][x - 1] = 10;
                    //    }
                    //    else { p->map[y][x - 1] = 2; }
                    //    flag = 1;
                    //    break;
                    //    break;
                    case 5:
                        p->map[y][x] = 0;
                        if (p->map[y][x - 1] == 1) {
                            p->map[y][x - 1] = 10;
                        }
                        else { p->map[y][x - 1] = 2; }
                        flag = 1;
                        break;
                    //case 6:
                    //    p->map[y][x] = 0;
                    //    if (p->map[y][x - 1] == 1) {
                    //        p->map[y][x - 1] = 8;
                    //    }
                    //    else { p->map[y][x - 1] = 2; }
                    //    flag = 1;
                    //    break;

                    default://7 8 9 10 
                        p->map[y][x] = 0;
                        p->map[y][x - 1] = 2;
                        break;
                    }

                }
                //printf("\n");
            }
            if (flag) break;
        }
    }

    if (dir == 4) {//folding what was bottom to top (idk how to describe this)
        //printf("\n");
        for (int y = 4; y > -1; y--) {
            for (int x = 0; x < 5; x++) {
                //printf("%i ", p->map[y][x]);
                if (y != 0) {
                    switch (p->map[y][x]) {
                    case 0:
                        break;
                    case 1:
                        p->map[y][x] = 0;
                        p->map[y - 1][x] = 2;
                        flag = 1;
                        break;
                    case 2:
                        p->map[y][x] = 0;
                        p->map[y - 1][x] = 2;
                        flag = 1;
                        break;
                    case 3:
                        p->map[y][x] = 0;
                        if (p->map[y - 1][x] == 1) {
                            p->map[y - 1][x] = 9;
                        }
                        else { p->map[y - 1][x] = 2; }
                        flag = 1;
                        break;
                    case 4:
                        p->map[y][x] = 0;
                        if (p->map[y - 1][x] == 1) {
                            p->map[y - 1][x] = 10;
                        }
                        else { p->map[y - 1][x] = 2; }
                        flag = 1;
                        break;
                        break;
                    case 5:
                        p->map[y][x] = 0;
                        if (p->map[y - 1][x] == 1) {
                            p->map[y - 1][x] = 7;
                        }
                        else { p->map[y - 1][x] = 2; }
                        flag = 1;
                        break;
                    case 6:
                        p->map[y][x] = 0;
                        if (p->map[y - 1][x] == 1) {
                            p->map[y - 1][x] = 8;
                        }
                        else { p->map[y - 1][x] = 2; }
                        flag = 1;
                        break;

                    default://7 8 9 10 
                        p->map[y][x] = 0;
                        p->map[y - 1][x] = 2;
                        break;
                    }

                }
                //printf("\n");
            }
            if (flag) break;
        }
    }

    if (dir == 6) {//folding what was right to left
        //printf("\n");
        for (int x = 0; x < 5; x++) {
            for (int y = 0; y < 5; y++) {
                //printf("%i ", p->map[y][x]);
                if (x != 4) {
                    switch (p->map[y][x]) {
                    case 0:
                        break;
                    case 1:
                        p->map[y][x] = 0;
                        p->map[y][x + 1] = 2;
                        flag = 1;
                        break;
                    case 2:
                        p->map[y][x] = 0;
                        p->map[y][x + 1] = 2;
                        flag = 1;
                        break;

                    //case 3:
                    //    p->map[y][x] = 0;
                    //    if (p->map[y][x + 1] == 1) {
                    //        p->map[y][x + 1] = 9;
                    //    }
                    //    else { p->map[y][x + 1] = 2; }
                    //    flag = 1;
                    //    break;
                    case 4:
                        p->map[y][x] = 0;
                        if (p->map[y][x + 1] == 1) {
                            p->map[y][x + 1] = 7;
                        }
                        else { p->map[y][x + 1] = 2; }
                        flag = 1;
                        break;
                        break;
                    //case 5:
                    //    p->map[y][x] = 0;
                    //    if (p->map[y][x + 1] == 1) {
                    //        p->map[y][x + 1] = 7;
                    //    }
                    //    else { p->map[y][x + 1] = 2; }
                    //    flag = 1;
                    //    break;
                    case 6:
                        p->map[y][x] = 0;
                        if (p->map[y][x + 1] == 1) {
                            p->map[y][x + 1] = 9;
                        }
                        else { p->map[y][x + 1] = 2; }
                        flag = 1;
                        break;


                    default://7 8 9 10 
                        p->map[y][x] = 0;
                        p->map[y][x + 1] = 2;
                        break;
                    }

                }
                //printf("\n");
            }
            if (flag) break;
        }
    }



    //Diagonals

    if (dir == 1) {//Upper Right Corner?
        for (int z = 0; z < 5; z++) {
            for (int w = 0; w <= z; w++) {
                if (z != 4) {
                    if (p->map[0 + w][4 - z + w] == 1 || p->map[0 + w][4 - z + w] == 2) {
                        p->map[0 + w][4 - z + w] = 0;
                        p->map[0 + w][4 - z + w] = 5;
                        flag = 1;
                    }
                    else if (p->map[0 + w][4 - z + w] == 5) {

                        p->map[0 + w][4 - z + w] = 0;

                        p->map[0 + w + 1][4 - z + w - 1] = 2;
                        if (p->map[0 + w + 0][4 - z + w - 1] != 5 || p->map[0 + w + 1][4 - z + w + 0] != 5) {
                            p->map[0 + w + 0][4 - z + w - 1] = 5;
                            p->map[0 + w + 1][4 - z + w + 0] = 5;
                        }
                        else {
                            p->map[0 + w + 2][4 - z + w - 2] = 2;
                        }
                        
                        flag = 1;
                    }
                    else if (p->map[0 + w][4 - z + w] >= 7) {
                        p->map[0 + w][4 - z + w] = 0;
                        p->map[0 + w + 1][4 - z + w - 1] = 2;
                    }
                }
            }
            if (flag) break;
        }
    }

    if (dir == 3) {//Lower Right (negative x, negative y) (start from 4, 4)  //works all right I think
        for (int z = 0; z < 5; z++) {
            for (int w = 0; w <= z; w++) {
                if (z != 4) {
                    if (p->map[4 - w][4 - z + w] == 1 || p->map[4 - w][4 - z + w] == 2) {
                        p->map[4 - w][4 - z + w] = 0;
                        p->map[4 - w][4 - z + w] = 3;
                        flag = 1;
                    }
                    else if (p->map[4 - w][4 - z + w] == 3) {

                        p->map[4 - w][4 - z + w] = 0;
                        p->map[4 - w - 1][4 - z + w - 1] = 2;
                        p->map[4 - w + 0][4 - z + w - 1] = 3;
                        p->map[4 - w - 1][4 - z + w + 0] = 3;
                        flag = 1;
                    }
                    else if (p->map[4 - w][4 - z + w] >= 7) {
                        p->map[4 - w][4 - z + w] = 0;
                        p->map[4 - w - 1][4 - z + w - 1] = 2;

                    }
                }
            }
            if (flag) break;
        }
    }
    if (dir == 5) {//Lower Left ( Start at [4][0] negative y, positive x //working except for  weird buffer overshoot

        for (int z = 0; z < 5; z++) {
            for (int w = 0; w <= z; w++) {
                //printf("Y: %i    X: %i\n", 4 - w, 0 + z + w);
                if (z != 4) {
                    if (p->map[4 + w - z][0 + w] == 1 || p->map[4 + w - z][0 + w] == 2) {
                        p->map[4 + w - z][0 + w] = 0;
                        p->map[4 + w - z][0 + w] = 4;
                        flag = 1;
                    }
                    else if (p->map[4 + w - z][0 + w] == 4) {

                        p->map[4 + w - z][0 + w] = 0;

                        p->map[4 + w - z - 1][0 + z + 1] = 2;
                        p->map[4 + w - z - 0][0 + z + 1] = 4;
                        p->map[4 + w - z - 1][0 + z + 0] = 4;
                        flag = 1;
                    }
                    else if (p->map[4 + w - z][0 + w] >= 7) {
                        p->map[4 + w - z][0 + w] = 0;
                        p->map[4 + w - z - 1][0 + z + 1] = 2;
                    }

                }
            }
            if (flag) break;
        }
    }

    if (dir == 7) {//Upper Left (Start at [0][0]) positive y, positive x
        for (int z = 0; z < 5; z++) {
            for (int w = 0; w <= z; w++) {
                if (z != 4) {
                    if (p->map[0 + z - w][0 + w] == 1 || p->map[0 + z - w][0 + w] == 2) {
                        p->map[0 + z - w][0 + w] = 0;
                        p->map[0 + z - w][0 + w] = 6;
                        flag = 1;
                    }
                    else if (p->map[0 + z - w][0 + w] == 6) {
                        
                        p->map[0 + z - w][0 + w] = 0;
                        p->map[0 + z - w + 1][0 + w + 1] = 2;
                        p->map[0 + z - w + 0][0 + w + 1] = 6;
                        p->map[0 + z - w + 1][0 + w + 0] = 6;
                        flag = 1;
                    }
                    else if (p->map[0 + z - w][0 + w] >= 7) {

                        p->map[0 + z - w][0 + w] = 0;
                        p->map[0 + z - w + 1][0 + w + 1] = 2;
                    }
                }
            }
            if (flag) break;
        }
    }


}

void resetPaperArray(PaperArray* p) {
    
    //crane
    p->map[0][0] = 6;
    p->map[0][1] = 5;
    p->map[0][2] = 0;
    p->map[0][3] = 0;
    p->map[0][4] = 0;

    p->map[1][0] = 1;
    p->map[1][1] = 2;
    p->map[1][2] = 5;
    p->map[1][3] = 0;
    p->map[1][4] = 0;

    p->map[2][0] = 2;
    p->map[2][1] = 2;
    p->map[2][2] = 2;
    p->map[2][3] = 0;
    p->map[2][4] = 0;



    //bull
    p->map[0][0] = 6;
    p->map[0][1] = 1;
    p->map[0][2] = 5;
    p->map[0][3] = 0;
    p->map[0][4] = 0;

    p->map[1][0] = 1;
    p->map[1][1] = 1;
    p->map[1][2] = 1;
    p->map[1][3] = 0;
    p->map[1][4] = 0;

    p->map[2][0] = 4;
    p->map[2][1] = 2;
    p->map[2][2] = 3;
    p->map[2][3] = 0;
    p->map[2][4] = 0;




    //test
    p->map[0][0] = 0;
    p->map[0][1] = 1;
    p->map[0][2] = 2;
    p->map[0][3] = 3;
    p->map[0][4] = 4;

    p->map[1][0] = 5;
    p->map[1][1] = 6;
    p->map[1][2] = 7;
    p->map[1][3] = 8;
    p->map[1][4] = 9;

    p->map[2][0] = 10;
    p->map[2][1] = 1;
    p->map[2][2] = 1;
    p->map[2][3] = 1;
    p->map[2][4] = 1;

    p->map[3][0] = 1;
    p->map[3][1] = 1;
    p->map[3][2] = 1;
    p->map[3][3] = 1;
    p->map[3][4] = 1;

    p->map[4][0] = 1;
    p->map[4][1] = 1;
    p->map[4][2] = 1;
    p->map[4][3] = 1;
    p->map[4][4] = 1;


    int num = 0;
    for (int y = 0; y < 5; y++) {
        for (int x = 0; x < 5; x++) {
            p->map[y][x] = 1;
            num++;
            if (num > 10) {
                num = 0;
            }
        }
    }

    






}

