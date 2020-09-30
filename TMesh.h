#pragma once

#include "V3.h"
#include "M33.h"
#include "ppc.h"
#include "framebuffer.h"

class TMesh {
public:
	int onFlag;
	V3 *verts;
	V3 *colors;
	V3 *normals;
	int vertsN;
	unsigned int *tris;
	int trisN;
	TMesh() : verts(0), vertsN(0), tris(0), trisN(0), colors(0), normals(0), onFlag(1) {};
	void SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1);
	void Allocate(int _vertsN, int _trisN);
	void DrawCubeQuadFaces(FrameBuffer *fb, PPC *ppc, unsigned int color);
	void DrawWireFrame(FrameBuffer *fb, PPC *ppc, unsigned int color);
	void LoadBin(char *fname);
	V3 GetCenter();
	void SetCenter(V3 center);
	void Translate(V3 tv);
	void Rotate(V3 aO, V3 aDir, float theta);
	void RenderFilled(FrameBuffer *fb, PPC *ppc);
	V3 SetEEQ(V3 v0, V3 v1, V3 v2);
	M33 SetEEQs(V3 pv0, V3 pv1, V3 pv2);
	M33 SetSSIM(V3 pv0, V3 pv1, V3 pv2);
};