#include "rotateroom.h"
#include "graphicsutils.h"
#include <stdlib.h>
#include <math.h>
#define PI 3.141592f


Room* createRoom(DGL_Texture* front, DGL_Texture* right, DGL_Texture* rear, DGL_Texture* left, DGL_Texture* floor, DGL_Texture* ceiling) {
	Room* r = (Room*)malloc(sizeof(Room));
	if (r != NULL) {
		r->angle = 0.0f;
		r->dir = 0.0f;
		r->t1 = front;
		r->t2 = right;
		r->t3 = rear;
		r->t4 = left;
		r->t5 = floor;
		r->t6 = ceiling;
		r->mesh = createRectMesh(1.0f, 1.0f);
		r->width = 1920.0f;
		r->height = 1080.0f/2.0f;
	}
	return r;
}

void rotateRoom(Room* r, float angle) {
	r->angle += angle;
	while (r->angle > 360.0f) {
		r->angle -= 360.0f;
	}
	while (r->angle < 0.0f) {
		r->angle += 360.0f;
	}
}

void stepRoom(Room* r) {
	if (r->dir != 0) {
		rotateRoom(r, r->dir*1.0f);
		if ((int)roundf(r->angle) % 90 == 0) {
			//printf("%f\n", r->angle);
			r->dir = 0;
			r->angle = roundf(r->angle);
		}
	}
}


void drawRoom(Room* r) {
	DGL_Graphics_SetShaderMode(DGL_PSM_TEXTURE, DGL_VSM_DEFAULT);
	float c = cosf(r->angle * (PI / 180.0f));
	float s = sinf(r->angle * (PI / 180.0f));

	float ct = cosf(r->angle * (PI / 180.0f));
	float st = sinf(r->angle * (PI / 180.0f));




	//draw front
	DGL_Mat4 matrix = {
		r->width * (c),     0.0f,       0.0f,     (-s * (r->width / 2.0f)),
		0.0f,       r->height,     0.0f,     0.0f,
		0.0f,       0.0f,       0.0f,     0.0f,
		(1.0f * st) * ct,       0.0f,       0.0f,     1.0f,
	};

	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_SetTexture(r->t1);
	if (r->angle < 90 || r->angle > 270) DGL_Graphics_DrawMesh(r->mesh, DGL_DM_TRIANGLELIST);
	


	//draw the right wall
	c = cosf(( - 90 + r->angle) * (PI / 180.0f));
	s = sinf(( - 90 + r->angle) * (PI / 180.0f));

	matrix = (DGL_Mat4){
		r->width * (c),     0.0f,       0.0f,     (-s * (r->width / 2.0f)),
		0.0f,       r->height,     0.0f,     0.0f,
		0.0f,       0.0f,       0.0f,     0.0f,
		(-1.0f * st) * ct,       0.0f,       0.0f,     1.0f,
	};


	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_SetTexture(r->t2);
	if (r->angle > 0.0f && r-> angle < 180.0f) DGL_Graphics_DrawMesh(r->mesh, DGL_DM_TRIANGLELIST);
	


	//draw the rear wall
	c = cosf((-180 + r->angle) * (PI / 180.0f));
	s = sinf((-180 + r->angle) * (PI / 180.0f));
	matrix = (DGL_Mat4){
		r->width* (c),     0.0f,       0.0f,     (-s * (r->width / 2.0f)),
		0.0f,       r->height,     0.0f,     0.0f,
		0.0f,       0.0f,       0.0f,     0.0f,
		(1.0f * st) * ct,       0.0f,       0.0f,     1.0f,
	};


	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_SetTexture(r->t3);
	if (r->angle > 90.0f && r->angle < 270.0f) DGL_Graphics_DrawMesh(r->mesh, DGL_DM_TRIANGLELIST);
	
	//draw the left wall;
	c = cosf((-270 + r->angle) * (PI / 180.0f));
	s = sinf((-270 + r->angle) * (PI / 180.0f));
	matrix = (DGL_Mat4){
		r->width* (c),     0.0f,       0.0f,     (-s * (r->width/2.0f)),
		0.0f,       r->height,     0.0f,     0.0f,
		0.0f,       0.0f,       0.0f,     0.0f,
		(-1.0f * st) * ct,       0.0f,       0.0f,     1.0f,
	};


	DGL_Graphics_SetCB_TransformMatrix(&matrix);
	DGL_Graphics_SetTexture(r->t4);
	if (r->angle > 180.0f && r-> angle < 360.0f) DGL_Graphics_DrawMesh(r->mesh, DGL_DM_TRIANGLELIST);
}









