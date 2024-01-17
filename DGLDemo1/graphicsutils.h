#pragma once
#include "DGL.h"
#include <stdlib.h>
#include <stdio.h>
DGL_Mesh* createRectMesh(float width, float height);
DGL_Mesh* createRectMeshOption(float width, float height, int dir, float cols, float rows);
DGL_Mesh* createTriMesh(float width, float height);
DGL_Mesh* createRectMesh(float width, float height);


typedef struct {
	DGL_Texture* textures[64];
	int length;//after this is jsut copies of tex 0
} TextureList;
//texture loading
TextureList* loadTextureList(int bank, int len);

void freeTextureList(TextureList* list);
