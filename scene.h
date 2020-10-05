#pragma once

#include "gui.h"
#include "framebuffer.h"
#include "ppc.h"
#include "TMesh.h"
#include "texture.h"



class Scene {
public:

	GUI *gui;
	FrameBuffer *fb;
	FrameBuffer* fb1, *fb2, *fb3, *fb4;
	PPC* ppc, *ppc3;
	PPC* ppc1;
	TMesh* tmeshes;
	int tmeshesN;
	texture *t1, *t2, *t3, *t4, *t5;
	//int texesN;
	float vf;
	Scene();
	void DBG();
	void NewButton();
	void Render();
	void Render(FrameBuffer* fb, PPC* ppc, texture* t1, TMesh* tmesh);
};

extern Scene *scene;