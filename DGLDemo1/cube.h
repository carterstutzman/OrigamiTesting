#pragma once
#include "DGL.h"
#include "graphicsutils.h"

//This is a block shape, a 2D rectangle ya know but with the extra 3D bits on top left and right (and bottom?)
typedef struct {
	DGL_Vec2 size;
	float depth;
	DGL_Mesh* frontmesh;
	DGL_Mesh* leftmesh;
	DGL_Mesh* rightmesh;
	DGL_Mesh* topmesh;
	DGL_Mesh* botmesh;

	DGL_Texture* fronttex;

} Block;
//This is a regular flat texture, can be scrolled like a 
typedef struct {
	DGL_Vec2 pos;
	DGL_Vec2 size;
	DGL_Vec2 offset;
	float depth;
	DGL_Mesh* mesh;
	DGL_Texture* toptex;
} Layer;


void drawBlockTop(Block* block, float offx, float offy, float offz);
void drawBlockBottom(Block* block, float offx, float offy, float offz);
void drawBlockFront(Block* block, float offx, float offy, float offz);
void drawBlock(Block* block, float offx, float offy, float offz, int front, int top, int bot, int left, int right);

Block* createBlock(DGL_Vec2 size, float depth, DGL_Texture* tex1);



Layer* createLayer(DGL_Vec2 pos, DGL_Vec2 size, DGL_Vec2 offset, float depth, DGL_Mesh* mesh, DGL_Texture* toptex);
void drawLayer(Layer* layer);

void drawTilemap(char tilemap[][49], DGL_Vec2 off, int index, int index2, Block* block, TextureList* list);


//migrated
//TextureList* loadTextures(int bank, int len);
//void freeTextures(TextureList* list);