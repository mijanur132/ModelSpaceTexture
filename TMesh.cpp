#include "stdafx.h"

#include <fstream>
#include <iostream>

#include "M33.h"
#include "TMesh.h"
#include "AABB.h"

using namespace std;


void TMesh::Allocate(int _vertsN, int _trisN) {

	vertsN = _vertsN;
	trisN = _trisN;
	verts = new V3[vertsN];
	textureSTpair = new V3[vertsN];
	colors = new V3[vertsN];
	normals = new V3[vertsN];
	tris = new unsigned int[trisN * 3];
}

void TMesh::InitTexture()
{
	for (int i = 0; i < vertsN; i++)
	{
		textureSTpair[i] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}


}

void TMesh::info() {

	for (int i = 0; i < trisN; i++)
	{
		cout << "vertices of triangle: " << i << " are: " << endl;
		cout<<"vertice ID: "<<tris[3 * i] << ", vertice:" << verts[tris[3 * i]] << ", textureRSpair:" << textureSTpair[tris[3 * i]] << endl;
		cout << "vertice ID: " << tris[3 * i+1] << ", vertice:" << verts[tris[3 * i+1]] << ", textureRSpair:" << textureSTpair[tris[3 * i+1]] << endl;
		cout << "vertice ID: " << tris[3 * i+2] << ", vertice:" << verts[tris[3 * i+2]] << ", textureRSpair:" << textureSTpair[tris[3 * i+2]] << endl;
	}

}

void TMesh::SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);



	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color0);
		colors[vi+4].SetFromColor(color1);
	}

	int vi = 0;
	verts[vi] = cc + V3(-sideLength / 2.0f, +sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(-sideLength / 2.0f, -sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, -sideLength / 2.0f, +sideLength / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength / 2.0f, +sideLength / 2.0f, +sideLength / 2.0f);
	vi++;

	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength);
	vi++;

	int tri = 0;
	tris[3 * tri + 0] = 0;
	tris[3 * tri + 1] = 1;
	tris[3 * tri + 2] = 2;
	tri++;
	tris[3 * tri + 0] = 2;
	tris[3 * tri + 1] = 3;
	tris[3 * tri + 2] = 0;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 7;
	tris[3 * tri + 1] = 6;
	tris[3 * tri + 2] = 5;
	tri++;
	tris[3 * tri + 0] = 5;
	tris[3 * tri + 1] = 4;
	tris[3 * tri + 2] = 7;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 1;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 4;
	tris[3 * tri + 1] = 0;
	tris[3 * tri + 2] = 3;
	tri++;
	tris[3 * tri + 0] = 3;
	tris[3 * tri + 1] = 7;
	tris[3 * tri + 2] = 4;
	tri++;
	tris[3 * tri + 0] = 1;
	tris[3 * tri + 1] = 5;
	tris[3 * tri + 2] = 6;
	tri++;
	tris[3 * tri + 0] = 6;
	tris[3 * tri + 1] = 2;
	tris[3 * tri + 2] = 1;
	tri++;

}

void TMesh::DrawCubeQuadFaces(FrameBuffer *fb, PPC *ppc, unsigned int color) {

	V3 c0;
	c0.SetFromColor(color);
	for (int si = 0; si < 4; si++) {
		fb->Draw3DSegment(verts[si], verts[(si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[4+si], verts[4 + (si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[si], verts[si + 4], ppc, c0, c0);
	}

}

void TMesh::DrawWireFrame(FrameBuffer *fb, PPC *ppc, unsigned int color) {
	//trisN = 2; //temp just to check one face of the cube for hw3 other wise delte this line.
	for (int tri = 0; tri < trisN; tri++) {
		V3 V0 = verts[tris[3 * tri + 0]];
		V3 V1 = verts[tris[3 * tri + 1]];
		V3 V2 = verts[tris[3 * tri + 2]];
		V3 c0 = colors[tris[3 * tri + 0]];
		V3 c1 = colors[tris[3 * tri + 1]];
		V3 c2 = colors[tris[3 * tri + 2]];
		fb->Draw3DSegment(V0, V1, ppc, c0, c1);
		fb->Draw3DSegment(V1, V2, ppc, c1, c2);
		fb->Draw3DSegment(V2, V0, ppc, c2, c0);
	}

}

void TMesh::LoadBin(char *fname) {

	ifstream ifs(fname, ios::binary);
	if (ifs.fail()) {
		cerr << "INFO: cannot open file: " << fname << endl;
		return;
	}

	ifs.read((char*)&vertsN, sizeof(int));
	char yn;
	ifs.read(&yn, 1); // always xyz
	if (yn != 'y') {
		cerr << "INTERNAL ERROR: there should always be vertex xyz data" << endl;
		return;
	}
	if (verts)
		delete verts;
	verts = new V3[vertsN];

	ifs.read(&yn, 1); // cols 3 floats
	if (colors)
		delete colors;
	colors = 0;
	if (yn == 'y') {
		colors = new V3[vertsN];
	}

	ifs.read(&yn, 1); // normals 3 floats
	if (normals)
		delete normals;
	normals = 0;
	if (yn == 'y') {
		normals = new V3[vertsN];
	}

	ifs.read(&yn, 1); // texture coordinates 2 floats
	float *tcs = 0; // don't have texture coordinates for now
	if (tcs)
		delete tcs;
	tcs = 0;
	if (yn == 'y') {
		tcs = new float[vertsN * 2];
	}

	ifs.read((char*)verts, vertsN * 3 * sizeof(float)); // load verts

	if (colors) {
		ifs.read((char*)colors, vertsN * 3 * sizeof(float)); // load cols
	}

	if (normals)
		ifs.read((char*)normals, vertsN * 3 * sizeof(float)); // load normals

	if (tcs)
		ifs.read((char*)tcs, vertsN * 2 * sizeof(float)); // load texture coordinates

	ifs.read((char*)&trisN, sizeof(int));
	if (tris)
		delete tris;
	tris = new unsigned int[trisN * 3];
	ifs.read((char*)tris, trisN * 3 * sizeof(unsigned int)); // read tiangles

	ifs.close();

	cerr << "INFO: loaded " << vertsN << " verts, " << trisN << " tris from " << endl << "      " << fname << endl;
	cerr << "      xyz " << ((colors) ? "rgb " : "") << ((normals) ? "nxnynz " : "") << ((tcs) ? "tcstct " : "") << endl;

}

V3 TMesh::GetCenter() {

	V3 ret(0.0f, 0.0f, 0.0f);
	for (int vi = 0; vi < vertsN; vi++) {
		ret = ret + verts[vi];
	}
	ret = ret / (float)vertsN;
	return ret;

}

void TMesh::Translate(V3 tv) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + tv;
	}

}

void TMesh::SetCenter(V3 center) {

	V3 currCenter = GetCenter();
	Translate(center - currCenter);

}



void TMesh::Rotate(V3 aO, V3 aDir, float theta) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi].RotatePoint(aO, aDir, theta);
	}

}

void TMesh::RenderFilled(FrameBuffer *fb, PPC *ppc) {

	V3 *pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	trisN = 2; //temp just to check one face of the cube for hw3 other wise delte this line.

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2]};
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		// if (!aabb.ClipWithFrame(fb->w, fb->h))
		//	continue;
		
		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;
		M33 cm;
		cm.SetColumn(0, colors[vinds[0]]);
		cm.SetColumn(1, colors[vinds[1]]);
		cm.SetColumn(2, colors[vinds[2]]);
		M33 cLEm;
		cLEm[0] = ssim * cm[0];
		cLEm[1] = ssim * cm[1];
		cLEm[2] = ssim * cm[2];
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				float currz = zLE * currPix;
				if (fb->Farther(u, v, currz))
					continue; // hidden
				V3 currColor = cLEm*currPix;
				fb->Set(u, v, currColor.GetColor());
			}
		}

	}

	delete []pverts;

}

V3 TMesh::SetEEQ(V3 v0, V3 v1, V3 v2) {

#if 0

	(x - x0) / (x1 - x0) = (y - y0) / (y1 - y0)
	(x - x0)*(y1 - y0) = (y - y0)*(x1 - x0);
	x*(y1 - y0) + y * (x0 - x1) + x0(y0 - y1) + y0(x1 - x0) = 0
	xA + yB + C = 0
#endif

	float x0, x1, y0, y1;
	x0 = v0[0];
	x1 = v1[0];
	y0 = v0[1];
	y1 = v1[1];
	V3 ret;
	ret[0] = y1 - y0;
	ret[1] = x0 - x1;
//	ret[2] = x0*(y0 - y1) + y0*(x1 - x0);
	ret[2] = -x0*y1 + y0*x1;
	V3 v2p(v2); v2p[2] = 1.0f;

	if (ret*v2p < 0.0f) // ret * v2p = Au+Bv+C
		ret = ret * -1.0f;

	return ret;

}

M33 TMesh::SetEEQs(V3 pv0, V3 pv1, V3 pv2) {

	M33 ret;
	V3 pvs[3];
	pvs[0] = pv0;
	pvs[1] = pv1;
	pvs[2] = pv2;
	for (int ei = 0; ei < 3; ei++) {
		ret[ei] = SetEEQ(pvs[ei], pvs[(ei + 1) % 3], pvs[(ei + 2) % 3]);
	}
	return ret;
}

// LE(u, v) = Au + Bv + c;

// LE(u + 1, v) = LE(u, v) + A;

M33 TMesh::SetSSIM(V3 pv0, V3 pv1, V3 pv2) {

	M33 ret;
	ret[0] = pv0;
	ret[1] = pv1;
	ret[2] = pv2;
	ret.SetColumn(2, V3(1.0f, 1.0f, 1.0f));
	return ret.Inverted();

}

void TMesh::MapTextureCorners2TriangleVerts(int tri, int whichHalf) {
	//whichHalf 0-->left/up side  1 for right/down side triangle
	//Z VALUE DOES NOT MATTER
	unsigned int vin[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
	if (whichHalf == 0)
	{
		textureSTpair[vin[0]] = V3(0,0, 1);
		textureSTpair[vin[1]] = V3(0, 1, 1);
		textureSTpair[vin[2]] = V3(1, 1, 1);
	}
	else {
	
		textureSTpair[vin[0]] = V3(1, 1, 1);
		textureSTpair[vin[1]] = V3(1, 0, 1);
		textureSTpair[vin[2]] = V3(0, 0, 1);
	
	}
}

void TMesh::RenderTexture(FrameBuffer* fb, PPC* ppc, texture* t1) {

	V3* pverts = new V3[vertsN];
	for (int vi = 0; vi < vertsN; vi++) {
		if (!ppc->Project(verts[vi], pverts[vi]))
			pverts[vi] = V3(FLT_MAX, FLT_MAX, FLT_MAX);
	}

	trisN = 1; //temp just to check one face of the cube for hw3 other wise delte this line.

	for (int tri = 0; tri < trisN; tri++) {
		unsigned int vinds[3] = { tris[3 * tri + 0], tris[3 * tri + 1], tris[3 * tri + 2] };
		if (
			pverts[vinds[0]][0] == FLT_MAX ||
			pverts[vinds[1]][0] == FLT_MAX ||
			pverts[vinds[2]][0] == FLT_MAX
			)
			continue;

		AABB aabb(pverts[vinds[0]]);
		aabb.AddPoint(pverts[vinds[1]]);
		aabb.AddPoint(pverts[vinds[2]]);
		// clipping
		// if (!aabb.ClipWithFrame(fb->w, fb->h))
		//	continue;

		int left = (int)(aabb.corners[0][0] + .5f);
		int right = (int)(aabb.corners[1][0] - .5f);
		int top = (int)(aabb.corners[0][1] + .5f);
		int bottom = (int)(aabb.corners[1][1] - .5f);

		M33 eeqsm = SetEEQs(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);
		M33 ssim = SetSSIM(pverts[vinds[0]], pverts[vinds[1]], pverts[vinds[2]]);

		V3 zv(pverts[vinds[0]][2], pverts[vinds[1]][2], pverts[vinds[2]][2]);
		V3 zLE = ssim * zv;

		cout <<verts[ vinds[0]]<<verts[ vinds[1]]<<verts[vinds[2]] << endl;

		V3 texS(textureSTpair[vinds[0]][0] , textureSTpair[vinds[1]][0] , textureSTpair[vinds[2]][0]);
		V3 texT(textureSTpair[vinds[0]][1], textureSTpair[vinds[1]][1], textureSTpair[vinds[2]][1]);
		V3 sLE = ssim * texS;
		V3 tLE = ssim * texT;
		cout << "texS and texT:" << endl;
		cout << texS << texT << endl;
		cout << "sLE and tLE" << endl;
		cout << sLE << tLE << endl;
		cout << top << " " << bottom << " " << left << " " << right << endl;
		for (int v = top; v <= bottom; v++) {
			for (int u = left; u <= right; u++) {
				V3 currPix(.5f + (float)u, .5f + (float)v, 1.0f);
				V3 sid = eeqsm * currPix;
				if (sid[0] < 0.0f || sid[1] < 0.0f || sid[2] < 0.0f)
					continue; // outside of triangle
				
				float currS = sLE * currPix*t1->w;
				float currT = tLE * currPix*t1->h;
				//cout << "j, i, T, s:" << v << "," << u << "," << currT << "," << currS << endl;
				int pixIJ = currS + currT * t1->w;
				unsigned int color_uvw = t1->pix[pixIJ];

				float currz = zLE * currPix;
				if (fb->Farther(u, v, currz))
					continue; // hidden
				
				fb->Set(u, v, color_uvw);
			}
		}

	}

	delete[]pverts;
}