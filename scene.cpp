#include "stdafx.h"
#include<sstream>
#include<iostream>
#include "scene.h"

#include "V3.h"
#include "M33.h"
#include   <chrono>
#include "ppc.h"
#include "TMesh.h"
#include <stdlib.h>

#include"texture.h"





Scene* scene;

using namespace std;


//hw2 submit

Scene::Scene()
{
	   	 
	gui = new GUI();
	gui->show();

	int u0 = 20;
	int v0 = 20;
	int h = 1000;
	int w = 1600;
	unsigned int col1 = 0xFFFF0000;

	fb = new FrameBuffer(u0, v0, w/2, h/2, -40);
	fb->label("SW frame buffer1");
	fb->show();
	fb->redraw();

	fb1 = new FrameBuffer(w/2, v0, w/2 , h/2 , -40);
	fb1->label("SW frame buffer2");
	fb1->show();
	fb1->redraw();

	gui->uiw->position(u0, v0 +550 );
	

	float hfov = 90.0f;
	ppc = new PPC(hfov, fb->w, fb->h);
	ppc1 = new PPC(hfov, fb1->w, fb1->h);
	
	
	Render(fb, ppc);
	
	fb->redraw();	   
	Fl::check();
}

void Scene:: Render(FrameBuffer* fb, PPC* ppc)
{
	fb->SetBGR(0xFFFFFFFF);
	fb->ClearZB();

	//ppc->Pan(10.0f);
	
	tmeshesN = 1;
	tmeshes = new TMesh[tmeshesN];

	V3 cc(0.0f, 0.0f, -150.0f);
	float sideLength = 60.0f;
	
	tmeshes[0].SetToCube(cc, sideLength, 0xFF0000FF, 0xFF000000);
	//tmeshes[0].Rotate(cc, V3(1, 0, 0), 90.0f);
	tmeshes[1].SetCenter(V3(0.0f, 0.0f, -140.0f));
	texture t1;
	texesN = 1;
	texes = new texture[1];
	t1.LoadTiff("checker.tiff");
	//tmeshes[0].LoadBin("geometry/teapot1K.bin");
	tmeshes[0].DrawFilledFrameTexture(fb, ppc,&t1);

	fb->redraw();
	Fl::check();	
}



void Scene::DBG() {
	V3 tcenter (0.0f, 0.0f, -200.0f);;
	float rotate = 0.0f;

	for (int i = 0; i < 360; i++)
	{
		fb1->SetBGR(0xFFFFFFFF);
		fb1->ClearZB();
		rotate = rotate + 5.0f;
		//tmeshes[0].SetToCube(tcenter, 60, 0xFF0000FF, 0xFF000000);
		tmeshes[0].Rotate(tcenter, V3(0, 1, 0), rotate);
		//tmeshes[0].DrawFilledFrameTexture(fb1, ppc1, &texes[0]);
		
		/*
		V3 uvw;
		ppc1->Project(V3(0.0f, 0.0f, 0.0f), uvw);

		float uv[2];
		uv[0] = uvw[0];
		uv[1] = uvw[1];
		fb1->DrawCircle(uv, 20, 0xFFFF0000, 0xFF0000FF);
		*/
		fb1->redraw();
		Fl::check();
		Sleep(100);
	}
	
}


void Scene::NewButton() {
	cerr << "INFO: pressed New Button" << endl;
}