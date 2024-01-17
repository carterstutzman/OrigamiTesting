#include "cube.h"
#include "graphicsutils.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#define SAMPLER DGL_TSM_LINEAR



Block* createBlock(DGL_Vec2 size, float depth,  DGL_Texture* tex1) {
	Block* blockPtr = (Block*)(malloc(sizeof(Block)));

	if (blockPtr != NULL) {
		blockPtr->size = size;
		blockPtr->depth = depth;

		blockPtr->frontmesh = createRectMeshOption(size.x, size.y, 0, 3.0f, 3.0f);
		blockPtr->leftmesh = createRectMeshOption(size.x, size.y, 1, 3.0f, 3.0f);
		blockPtr->rightmesh = createRectMeshOption(size.x, size.y, 2, 3.0f, 3.0f);
		blockPtr->topmesh = createRectMeshOption(size.x, size.y, 3, 3.0f, 3.0f);
		blockPtr->botmesh = createRectMeshOption(size.x, size.y, 4, 3.0f, 3.0f);


		blockPtr->fronttex = tex1;

	}

	return blockPtr;
}


void drawBlockFront(Block* block, float offx, float offy, float offz) {
	offz = 0.0f;
	DGL_Mat4 matrix;
	matrix = (DGL_Mat4){
		1.0f,        0,          0, offx,//all this works with 1.0 for depth
		0,        1.0f,        0, offy,
		0,        0,        1, 0,
		0,        0,        0, 1,
	};
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 1.0f / 3.0f, 1.0f / 3.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(block->fronttex);
	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_DrawMesh(block->frontmesh, DGL_DM_TRIANGLELIST);
}

void drawBlockBottom(Block* block, float offx, float offy, float offz) {
	offz = 0.0f;
	DGL_Mat4 matrix;
	//bot try
	matrix = (DGL_Mat4){
		1.0f,      0,         0, offx,
		0,          offy * 0,        0, offy - block->size.y / 2.0f,
		0,         0,                              1, 0,
		0,      -block->depth / 512.0f,             0, 1,
	};
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 1.0f / 3.0f, 2.0f / 3.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(block->fronttex);
	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	//if (offy > 0) {
	DGL_Graphics_DrawMesh(block->botmesh, DGL_DM_TRIANGLELIST);
	//}
}
void drawBlockTop(Block* block, float offx, float offy, float offz) {
	//offz = 0.0f;
	DGL_Mat4 matrix;
	offz;
	//top try
	matrix = (DGL_Mat4){
		1.0f ,      0,                              0, offx,
		0,          offy * 0,    0, offy + block->size.y / 2.0f,
		0,          0,                                  1, 0,
		0,      block->depth / 512.0f,                 0, 1,
	};


	DGL_Graphics_SetTexture(block->fronttex);
	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	//DGL_Vec2 offset = { offz, 0 };
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 1.0f / 3.0f, 0.0f / 3.0f });
	//DGL_Graphics_SetCB_TextureOffset(&offset);
	DGL_Graphics_DrawMesh(block->topmesh, DGL_DM_TRIANGLELIST);
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 0, 0 });

}

void drawBlockLeft(Block* block, float offx, float offy, float offz) {
	offz = 0.0f;
	DGL_Mat4 matrix;
	//right working
	matrix = (DGL_Mat4){
		0.0f,       0,          0, offx - block->size.x / 2.0f,
		0.0f,                    0.5f,            0, offy,
		0,                                 0,          1, 0,
		//-block->depth / 512.0f,  0,      0, 1,
		-block->depth / 512.0f,    0,                   0, 1,
	};
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 0.0f / 3.0f, 1.0f / 3.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(block->fronttex);
	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_DrawMesh(block->leftmesh, DGL_DM_TRIANGLELIST);
}

void drawBlockRight(Block* block, float offx, float offy, float offz) {
	offz = 0.0f;
	DGL_Mat4 matrix;
	//right working
	matrix = (DGL_Mat4){
		(-offx * block->depth) * 0.0f,     0,          0, offx + block->size.x / 2.0f,
		-offy * 0,                        0.5f,       0, offy,
		0,                                   0,          1, 0,
		//-block->depth / 512.0f,  0,           0, 1,
		block->depth / 512.0f,    0,       0, 1,
	};
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 2.0f / 3.0f, 1.0f / 3.0f });
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetTexture(block->fronttex);
	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_DrawMesh(block->rightmesh, DGL_DM_TRIANGLELIST);

}



void drawBlock(Block* block, float offx, float offy, float offz, int front, int top, int bot, int left, int right) {
	//offz = 0.0f;
	DGL_Graphics_SetTextureSamplerData(SAMPLER, DGL_AM_WRAP);
	DGL_Graphics_SetCB_TextureOffset(&(DGL_Vec2) { 0, 0 });
	//top; bot; left; right;
	//have to do a convoluted ordering scheme (painters algorithm)
	//DGL_Color color = (DGL_Color){ 1.0f, 1.0f, 1.0f, 1.0f };
	//DGL_Graphics_SetCB_TintColor(&color);

	if (0 < offx && 0 > offy) {
		if (bot)   drawBlockBottom(block, offx, offy, offz);
		if (right) drawBlockRight(block, offx, offy, offz);
		if (left)  drawBlockLeft(block, offx, offy, offz);
		if (top)   drawBlockTop(block, offx, offy, offz);
	}
	if (0 > offx && 0 > offy) {
		if (bot)   drawBlockBottom(block, offx, offy, offz);
		if (left)  drawBlockLeft(block, offx, offy, offz);
		if (right) drawBlockRight(block, offx, offy, offz);
		if (top)   drawBlockTop(block, offx, offy, offz);
	}


	if (0 < offx && 0 < offy) {
		if (top)   drawBlockTop(block, offx, offy, offz);
		if (right) drawBlockRight(block, offx, offy, offz);
		if (left)  drawBlockLeft(block, offx, offy, offz);
		if (bot)   drawBlockBottom(block, offx, offy, offz);
	}
	if (0 > offx && 0 < offy) {
		if (top)   drawBlockTop(block, offx, offy, offz);
		if (left)  drawBlockLeft(block, offx, offy, offz);
		if (right) drawBlockRight(block, offx, offy, offz);
		if (bot)   drawBlockBottom(block, offx, offy, offz);
	}

	if ((-0.1f < offx && 0.1f > offx) && offy != 0) {
		if (top)   drawBlockTop(block, offx, offy, offz);
		if (bot)   drawBlockBottom(block, offx, offy, offz);
	}
	if (0 == offy && offx != 0) {
		if (left)  drawBlockLeft(block, offx, offy, offz);
		if (right) drawBlockRight(block, offx, offy, offz);
	}

	if (front) drawBlockFront(block, offx, offy, offz);


}







Layer* createLayer(DGL_Vec2 pos, DGL_Vec2 size, DGL_Vec2 offset, float depth, DGL_Mesh* mesh, DGL_Texture* toptex) {
	Layer* layer = (Layer*)(malloc(sizeof(Layer)));
	if (layer != NULL) {
		layer->pos = pos;
		layer->size = size;
		layer->offset = offset;
		layer->depth = depth;
		layer->mesh = mesh;
		layer->toptex = toptex;
	}
	return layer;
}

void drawLayer(Layer* layer) {
	DGL_Graphics_SetBlendMode(DGL_BM_BLEND);
	DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
	DGL_Graphics_SetTextureSamplerData(SAMPLER, DGL_AM_WRAP);
	DGL_Graphics_SetTexture(layer->toptex);

	DGL_Graphics_SetCB_TextureOffset(&layer->offset);
	DGL_Graphics_SetCB_TransformData(&layer->pos, &layer->size, 0.0f);
	//DGL_Color color = (DGL_Color){ 0.0f, 0.0f, 0.0f, 1.0f };
	//DGL_Graphics_SetCB_TintColor(&color);
	//DGL_Graphics_SetCB_Alpha(0.5f);

	DGL_Graphics_DrawMesh(layer->mesh, DGL_DM_TRIANGLELIST);


}

void drawTilemap(char tilemap[][49], DGL_Vec2 off, int index, int index2, Block* block, TextureList* list) {
	for (int y = 0; y <= 8; y++) {
		for (int x = 0; x <= 16; x++) {
			if (1) {//((16 - x) != 0 && (8 - y) != 0) {//if (x >= 0 && x < 48 && y >= 0 && y < 32) {

				//low left
				if (tilemap[index2 + (8 - y)][index - (16 - x)] != '.' && index2 + (8 - y) >= 0 && index2 + (8 - y) < 32 && index - (16 - x) >= 0 && index - (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 + (8 - y)][index - (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x - (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x - (8 - y) * block->size.y, 0.0f, 0, 1, 1, 1 || ((int)off.x % (int)block->size.x < 32) || (x != 16), ((int)off.x % (int)block->size.x > 1) || (x != 16));
				}
				//upper right
				if (tilemap[index2 - (8 - y)][index + (16 - x)] != '.' && index2 - (8 - y) >= 0 && index2 - (8 - y) < 32 && index + (16 - x) >= 0 && index + (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 - (8 - y)][index + (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x + (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x + (8 - y) * block->size.y, 0.0f, 0, 1, 1, 1 || ((int)off.x % (int)block->size.x < 32) || (x != 16), ((int)off.x % (int)block->size.x > 1) || (x != 16));
				}
				if (tilemap[index2 - (8 - y)][index - (16 - x)] != '.' && index2 - (8 - y) >= 0 && index2 - (8 - y) < 32 && index - (16 - x) >= 0 && index - (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 - (8 - y)][index - (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x - (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x + (8 - y) * block->size.y, 0.0f, 0, 1, 1, 1 || ((int)off.x % (int)block->size.x < 32) || (x != 16), ((int)off.x % (int)block->size.x > 1) || (x != 16));
				}
				if (tilemap[index2 + (8 - y)][index + (16 - x)] != '.' && index2 + (8 - y) >= 0 && index2 + (8 - y) < 32 && index + (16 - x) >= 0 && index + (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 + (8 - y)][index + (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x + (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x - (8 - y) * block->size.y, 0.0f, 0, 1, 1, 1 || ((int)off.x % (int)block->size.x < 32) || (x != 16), ((int)off.x % (int)block->size.x > 1) || (x != 16));
				}


			}
		}
	}

	for (int y = 0; y <= 8; y++) {
		for (int x = 0; x <= 16; x++) {
			if (1) {//((16 - x) != 0 && (8 - y) != 0) {//if (x >= 0 && x < 48 && y >= 0 && y < 32) {

				//low left
				if (tilemap[index2 + (8 - y)][index - (16 - x)] != '.' && index2 + (8 - y) >= 0 && index2 + (8 - y) < 32 && index - (16 - x) >= 0 && index - (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 + (8 - y)][index - (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x - (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x - (8 - y) * block->size.y, 0.0f, 1, 0, 0, 0, 0);
				}
				//upper right
				if (tilemap[index2 - (8 - y)][index + (16 - x)] != '.' && index2 - (8 - y) >= 0 && index2 - (8 - y) < 32 && index + (16 - x) >= 0 && index + (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 - (8 - y)][index + (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x + (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x + (8 - y) * block->size.y, 0.0f, 1, 0, 0, 0, 0);
				}
				if (tilemap[index2 - (8 - y)][index - (16 - x)] != '.' && index2 - (8 - y) >= 0 && index2 - (8 - y) < 32 && index - (16 - x) >= 0 && index - (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 - (8 - y)][index - (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x - (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x + (8 - y) * block->size.y, 0.0f, 1, 0, 0, 0, 0);
				}
				if (tilemap[index2 + (8 - y)][index + (16 - x)] != '.' && index2 + (8 - y) >= 0 && index2 + (8 - y) < 32 && index + (16 - x) >= 0 && index + (16 - x) < 48) {
					block->fronttex = list->textures[tilemap[index2 + (8 - y)][index + (16 - x)] - '0'];
					drawBlock(block, -(int)(off.x) % (int)block->size.x + (16 - x) * block->size.x, (int)(off.y) % (int)block->size.x - (8 - y) * block->size.y, 0.0f, 1, 0, 0, 0, 0);
				}
			}
		}
	}

	//for (int y = 0; y <= 16; y++) {
	//	for (int x = 0; x <= 32; x++) {
	//		DGL_Graphics_SetCB_Alpha(fabsf((y-8.0f) * (x-16.0f))/64.0f);
	//		block->fronttex = list->textures[7];
	//		drawBlock(block, -(int)(off.x) % (int)block->size.x + (x-16) * 64.0f, (int)(off.y) % (int)block->size.x + (y-8) * 64.0f, 0.0f, 1, 0, 0, 0, 0);
	//		
	//		DGL_Graphics_SetCB_Alpha(1.0f);
	//	}
	//}

}

