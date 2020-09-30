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
	FrameBuffer* fb3;
	PPC* ppc;
	PPC* ppc3;
	TMesh* tmeshes;
	int tmeshesN;
	texture *texes;
	int texesN;
	float vf;

	Scene();
	void DBG();
	void NewButton();
	void Render();
	void Render(FrameBuffer* fb, PPC* ppc);
};

extern Scene *scene;