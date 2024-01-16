#pragma once
#include "graphicsutils.h"
#include "DGL.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


typedef struct {
	int angle;
	
	float stretchDiagonal;//for folding from point to base
	float stretchVertical;//for folding vertically in relation to screen
	float stretchHorizontal;//for folding horizontally in relation to screen
	
	DGL_Mesh* mesh;//triangular mesh with center along diagonal
	DGL_Texture* topTex;
	DGL_Texture* botTex;

} Triangle;//Component of paper (one fold)


typedef struct {
	Triangle* t1;
	Triangle* t2;
	int isFlipping;
	float flipSpeed;
	int isFlipped;
	int angle;


} SmallSquare;



typedef struct {
	int map[5][5];
	DGL_Texture* t1;
	DGL_Texture* t2;
	DGL_Mesh* sqMesh;

	DGL_Mesh* upLeft;
	DGL_Mesh* upRight;
	DGL_Mesh* downLeft;
	DGL_Mesh* downRight;


} PaperArray;





Triangle* createTriangle(int angle, DGL_Texture* topTex, DGL_Texture* botTex);
void drawTriangle(Triangle* t, int x, int y, int angle, int bias, float shadow);

SmallSquare* createSmallSquare(DGL_Texture* t1, DGL_Texture* t2, int angle);//add more params later
void drawSmallSquare(SmallSquare* s, float x, float y);
void foldSmallSquare(SmallSquare* s, int which, float much);
void stepSmallSquare(SmallSquare* s);




PaperArray* createPaperArray(DGL_Texture* t1, DGL_Texture* t2);
void drawPaperArray(PaperArray* p, int angle);
void foldPaperArray(PaperArray* p, int dir, int dist);
void resetPaperArray(PaperArray* p);