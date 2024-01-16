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

DGL_Mesh* createRectMeshOption(float width, float height, int option) {
    // Save the half width and height values

    float size = 1.0f / 1.0f;
    float halfHeight = height / 2.0f;
    // Tell DGL that we are starting a new mesh
    DGL_Graphics_StartMesh();
    // All vertices will use this color
    // You could change it between adding vertices to interpolate colors across the mesh
    DGL_Color color = { 0.0f, 0.0f, 0.0f, 1.0f };
    // First triangle
    // Add a vertex at the bottom-left corner
    DGL_Vec2 pos = { 0.0f, -halfHeight };
    DGL_Vec2 uv = { 0.0f, size };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-left corner
    pos = (DGL_Vec2){ 0.0f, halfHeight };
    uv = (DGL_Vec2){ 0.0f, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-right corner
    pos = (DGL_Vec2){ 1.0f, halfHeight };
    uv = (DGL_Vec2){ size, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Second triangle
    // Add a vertex at the bottom-left corner
    pos = (DGL_Vec2){ 0.0f, -halfHeight };
    uv = (DGL_Vec2){ 0.0f, size };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the top-right corner
    pos = (DGL_Vec2){ 1.0f, halfHeight };
    uv = (DGL_Vec2){ size, 0.0f };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    // Add a vertex at the bottom-right corner
    pos = (DGL_Vec2){ 1.0f, -halfHeight };
    uv = (DGL_Vec2){ size, size };
    DGL_Graphics_AddVertex(&pos, &color, &uv);
    return DGL_Graphics_EndMesh();
}


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