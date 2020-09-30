#pragma once

#include "V3.h"
#include "ppc.h"
#include "framebuffer.h"
#include "texture.h"
#include<vector>

#include "M33.h"


class TMesh {
public:
	int onFlag;
	V3* verts;
	V3* colors;
	V3* normals;
	int vertsN;
	unsigned int* tris;
	int trisN;
	TMesh() : verts(0), vertsN(0), tris(0), trisN(0), colors(0), normals(0), onFlag(1) {};
	void SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1);
	void SetToAABBQuad(V3 cc, V3 sideLength, unsigned int color0, unsigned int color1);
	void Allocate(int _vertsN, int _trisN);
	void DrawCubeQuadFaces(FrameBuffer* fb, PPC* ppc, unsigned int color);
	void DrawWireFrame(FrameBuffer* fb, PPC* ppc, unsigned int color);
	void GetAABBParam(V3& center, V3& sideL);
	void GetSidedNessParam(V3 p1, V3 p2, V3 p3, V3 a[3]);
	V3 CalcSidedNessE(V3 a[3], V3 p);
	void GetTriangleAABBparam(V3 pa, V3 pb, V3 pc, V3& center, V3& sideL, V3& leftMost, V3& topMost, V3& rightMost, V3& bottomMost);
	void DrawFilledFrame(FrameBuffer* fb, PPC* ppc, unsigned int color);
	void DrawFilledFrameTexture(FrameBuffer* fb, PPC* ppc, texture* t1);
	void GetBarryCentric(V3 p1, V3 p2, V3 p3, V3 p, V3& uvw);
	float CalcArea(V3 p1, V3 p2, V3 p3);
	void LoadBin(char* fname);
	V3 GetCenter();
	float GetSL();
	void SetCenter(V3 center);
	void Translate(V3 tv);
	void Scale(float scf);
	void Rotate(V3 O, V3 adir, float angle);
	void TriangleFillTexture(FrameBuffer* fb, PPC* ppc, texture* t1, int TriangleNo);
	vector<V3> TriangleGetInsidePoints(FrameBuffer* fb, V3 leftP, V3 rightP, V3 topP, V3 bottomP, V3 sideL, V3 V0, V3 V1, V3 V2);
	void ColorInsidePointsSS(FrameBuffer* fb, vector<V3> insidePoints, V3 pa, V3 pb, V3 pc, V3 V1, V3 V2, V3 V3, texture* t1, PPC* ppc);
	void ColorInsidePointsMS(FrameBuffer* fb, vector<V3> insidePoints, V3 pa, V3 pb, V3 pc, V3 V1, V3 V2, V3 V3, texture* t1);
	void RenderFilled(FrameBuffer* fb, PPC* ppc);
	V3 SetEEQ(V3 v0, V3 v1, V3 v2);
	M33 SetEEQs(V3 pv0, V3 pv1, V3 pv2);
	M33 SetSSIM(V3 pv0, V3 pv1, V3 pv2);
};