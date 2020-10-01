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
	FrameBuffer* fb1, *fb3;
	PPC* ppc, *ppc3;
	PPC* ppc1;
	TMesh* tmeshes;
	int tmeshesN;
	texture *t1;
	//int texesN;
	float vf;
	Scene();
	void DBG();
	void NewButton();
	void Render();
	void Render(FrameBuffer* fb, PPC* ppc, texture* t1);
};

extern Scene *scene;