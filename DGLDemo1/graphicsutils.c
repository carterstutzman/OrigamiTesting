#include "graphicsutils.h"
DGL_Mesh* createRectMesh(float width, float height) {
    // Save the half width and height values
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    float size = 1.0f / 1.0f;
    // Tell DGL that we are starting a new mesh
    DGL_Graphics_StartMesh();
    // All vertices will use this color
    // You could change it between adding vertices to interpolate colors across the mesh
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
    // Second triangle
    // Add a vertex at the bottom-left corner
    pos = (DGL_Vec2){ -halfWidth, -halfHeight };
    uv = (DGL_Vec2){ 0.0f, size };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-right corner
    pos = (DGL_Vec2){ halfWidth, halfHeight };
    uv = (DGL_Vec2){ size, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the bottom-right corner
    pos = (DGL_Vec2){ halfWidth, -halfHeight };
    uv = (DGL_Vec2){ size, size };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    return DGL_Graphics_EndMesh();
}
DGL_Mesh* createRectMeshOption(float width, float height, int dir, float cols, float rows) {
    DGL_Graphics_StartMesh();
    DGL_Color color = { 1.0f, 1.0f, 1.0f, 0.0f };
    float uWidth = 1.0f / cols;
    float vHeight = 1.0f / rows;

    if (dir == 0) {//center
        //bottom left, top left, top right, bottom right
        DGL_Vec2 pos = { -width / 2.0f, -height / 2.0f };
        DGL_Vec2 uv = { 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ -width / 2.0f, height / 2.0f };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, height / 2.0f
        };

        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ -width / 2.0f, -height / 2.0f };
        uv = (DGL_Vec2){ 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, height / 2.0f };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, -height / 2.0f };
        uv = (DGL_Vec2){ uWidth, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    if (dir == 1) {//left NOT USED IN PRACTICE, JUST INVERT RIGHT
        //bottom left, top left, top right,     second bottom left, top right bottom right
        DGL_Vec2 pos = { -width, -height };
        DGL_Vec2 uv = { 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ -width, height };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ 0.0f,  height };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        //second triangle
        pos = (DGL_Vec2){ -width, -height };
        uv = (DGL_Vec2){ 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ 0.0f, height };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ 0.0f, -height };
        uv = (DGL_Vec2){ uWidth, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }

    if (dir == 2) {//right
        //bottom left, top left, top right,     second bottom left, top right bottom right
        DGL_Vec2 pos = { width, -height };
        DGL_Vec2 uv = { uWidth, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width, height };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ 0.0f,  height };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        //second triangle
        pos = (DGL_Vec2){ width, -height };
        uv = (DGL_Vec2){ uWidth, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ 0.0f, height };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ 0.0f, -height };
        uv = (DGL_Vec2){ 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    if (dir == 3) {//bottom
        //bottom left, top left, top right,        second bottom left, top right bottom right
        DGL_Vec2 pos = { -width / 2.0f, 0.0f };
        DGL_Vec2 uv = { 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ -width / 2.0f, height };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, height };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        //second
        pos = (DGL_Vec2){ -width / 2.0f, 0.0f };
        uv = (DGL_Vec2){ 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, height };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, 0.0f };
        uv = (DGL_Vec2){ uWidth, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    if (dir == 4) {//top (seem on top)
        //bottom left, top left, top right,       second bottom left, top right bottom right
        DGL_Vec2 pos = { -width / 2.0f, -height };
        DGL_Vec2 uv = { 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ -width / 2.0f, 0.0f };
        uv = (DGL_Vec2){ 0.0f, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, 0.0f };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        //second
        pos = (DGL_Vec2){ -width / 2.0f, -height };
        uv = (DGL_Vec2){ 0.0f, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, 0.0f };
        uv = (DGL_Vec2){ uWidth, 0.0f };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
        pos = (DGL_Vec2){ width / 2.0f, -height };
        uv = (DGL_Vec2){ uWidth, vHeight };
        DGL_Graphics_AddVertex(&pos, &color, &uv);
    }
    return DGL_Graphics_EndMesh();
};

DGL_Mesh* createTriMesh(float width, float height) {
    // Save the half width and height values
    float halfWidth = width / 2.0f;
    float halfHeight = height / 2.0f;
    // Tell DGL that we are starting a new mesh
    DGL_Graphics_StartMesh();
    // All vertices will use this color
    // You could change it between adding vertices to interpolate colors across the mesh
    DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
    // First triangle
    // Add a vertex at the bottom-left corner
    DGL_Vec2 pos = { -halfWidth, 0.0f };
    DGL_Vec2 uv = { 0.0f, 1.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the bottom right
    pos = (DGL_Vec2){ halfWidth, 0.0f };
    uv = (DGL_Vec2){ 0.0f, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-middle 
    pos = (DGL_Vec2){ 0.0f, halfHeight };
    uv = (DGL_Vec2){ 0.5f, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    return DGL_Graphics_EndMesh();
}





TextureList* loadTextureList(int bank, int len) {

    TextureList* list = malloc(sizeof(TextureList));
    int num = 0;
    char path[26] = "";

    //'./Assets/Textures
    //.\Assets\Textures\00\00.png
    if (list != NULL) {
        for (int x = 0; x < len; x++) {
            //"./Assets/Textures/%i/%i.png"
            sprintf_s(path, 26, "./Assets/Textures/%i/%i.png", bank, x);
            //path[0] = '1';
            list->textures[x] = DGL_Graphics_LoadTexture(path);
            num++;
        }
        list->length = num;
        while (num < 64) {
            list->textures[num] = list->textures[0];
            num++;
        }
    }
    return list;

};

void freeTextureList(TextureList* list) {
    for (int i = 0; i < list->length; i++) {
        DGL_Graphics_FreeTexture(&list->textures[i]);
    }


}