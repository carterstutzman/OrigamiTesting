#pragma once
#include <DGL.h>




typedef struct {
	DGL_Texture* t1;//front
	DGL_Texture* t2;//right
	DGL_Texture* t3;//rear
	DGL_Texture* t4;//left
	DGL_Texture* t5;//bottom
	DGL_Texture* t6;//top

	DGL_Mesh* mesh;

	float angle;
	float dir;

	float width;
	float height;

} Room;



Room* createRoom(DGL_Texture* front, DGL_Texture* right, DGL_Texture* rear, DGL_Texture* left, DGL_Texture* floor, DGL_Texture* ceiling);
void drawRoom(Room* r);
void rotateRoom(Room* r, float angle);
void stepRoom(Room* r);