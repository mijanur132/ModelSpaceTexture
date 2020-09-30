
#include "stdafx.h"

#include <fstream>
#include <iostream>
#include<vector>

#include "TMesh.h"

using namespace std;


void TMesh::Allocate(int _vertsN, int _trisN) {

	vertsN = _vertsN;
	trisN = _trisN;
	verts = new V3[vertsN];
	colors = new V3[vertsN];
	normals = new V3[vertsN];
	tris = new unsigned int[trisN * 3];
}

void TMesh::SetToCube(V3 cc, float sideLength, unsigned int color0, unsigned int color1) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);

	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color0);
		colors[vi + 4].SetFromColor(color1);
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

void TMesh::SetToAABBQuad(V3 cc, V3 sideLength, unsigned int color0, unsigned int color1) {

	vertsN = 8;
	trisN = 6 * 2;
	Allocate(vertsN, trisN);

	for (int vi = 0; vi < 4; vi++) {
		colors[vi].SetFromColor(color0);
		colors[vi + 4].SetFromColor(color1);
	}

	int vi = 0;
	verts[vi] = cc + V3(-sideLength.xyz[0] / 2.0f, +sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;
	verts[vi] = cc + V3(-sideLength.xyz[0] / 2.0f, -sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength.xyz[0] / 2.0f, -sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;
	verts[vi] = cc + V3(+sideLength.xyz[0] / 2.0f, +sideLength.xyz[1] / 2.0f, +sideLength.xyz[2] / 2.0f);
	vi++;

	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
	vi++;
	verts[vi] = verts[vi - 4] + V3(0.0f, 0.0f, -sideLength.xyz[2]);
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

void TMesh::DrawCubeQuadFaces(FrameBuffer* fb, PPC* ppc, unsigned int color) {

	V3 c0;
	c0.SetFromColor(color);
	for (int si = 0; si < 4; si++) {
		fb->Draw3DSegment(verts[si], verts[(si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[4 + si], verts[4 + (si + 1) % 4], ppc, c0, c0);
		fb->Draw3DSegment(verts[si], verts[si + 4], ppc, c0, c0);
	}

}

void TMesh::DrawWireFrame(FrameBuffer* fb, PPC* ppc, unsigned int color) {

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

/****   
This function calculates sidedness of a point p(x,y,z), with repsect to a triangle.
The V3 a[3] is the parameters in the following equation calculated from the triangle 
vertices in "GetSidedNessParam()" function

return etemp(x,y,z) which hold the values for the point with each triangle edges. All must be same sign (+ prob.)
to have the point within the triangle

*****/

//p1
//........p3
//p2
//E(x3,y3)=x3*(y2-y1)-y3(x2-x1)-(x1y2-y1x2)
//=x3*a[0]-y3*a[1]+a[2]
V3 TMesh::CalcSidedNessE(V3 a[3], V3 p)
{
	V3 etemp;
	for (int i = 0; i < 3; i++)
	{
		etemp[i] = p.xyz[0] * a[i].xyz[0] - p.xyz[1] * a[i].xyz[1] - a[i][2];
	}
	return etemp;
}


/*
Calculates parameters V3 a[0] required by the function "CalcSidedNessE(V3 a[3], V3 p)".
input: 3 vertices and a pointer for the parameter storage vecctor V3 a[3]
output v3 a[3]

in reality I did not use this funciton. I found barrycentric technique to be more easy to use. 

*/


void TMesh::GetSidedNessParam(V3 pa, V3 pb, V3 pc, V3 a[3])
{	
	
	for (int i = 0; i < 3; i++)
	{
		float x1, x2, y1, y2, x3, y3;
		V3 p1, p2, p3;
		if (i==0)
		{
			p1 = pa;
			p2 = pb;
			p3 = pc;
		}
		if (i == 1)
		{
			p1 = pb;
			p2 = pc;
			p3 = pa;
		}
		if (i == 3)
		{
			p1 = pc;
			p2 = pa;
			p3 = pb;
		}

		
		x1 = p1.xyz[0];
		x2 = p2.xyz[0];
		x3 = p3.xyz[0];

		y1 = p1.xyz[1];
		y2 = p2.xyz[1];
		y3 = p3.xyz[1];

		a[i].xyz[0] = y2 - y1;
		a[i].xyz[1] = x2 - x1;
		a[i].xyz[2] = x1 * y2 - x2 * y1;
		float etemp;
		
		V3 p = p3;
		etemp = p.xyz[0] * a[i].xyz[0] - p.xyz[1] * a[i].xyz[1] - a[i][2];
		if (etemp < 0)
		{
			a[i].xyz[0] = -1 * a[i].xyz[0];
			a[i].xyz[1] = -1*a[i].xyz[1];
			a[i].xyz[2] = -1 * a[i].xyz[2];
		}
		
	}
	
}

/*
Create and return the bounding box of the triangle defined by the points pa, pb and pc.
checks for min and max value in all x,y and z direction from the points pa, pb and pc
return center, each side length, leftmost, topmost, rightmost and bottommost points

*/


void TMesh::GetTriangleAABBparam(V3 pa, V3 pb, V3 pc, V3& center, V3& sideL, V3& leftMost, V3& topMost, V3 &rightMost, V3 &bottomMost)
{
	V3 minV(100000.0f, 10000.0f, 100000.0f);
	V3 maxV(-100000.0f, -100000.0f, -100000.0f);
	V3 trs[3];
	trs[0] = pa;
	trs[1] = pb;
	trs[2] = pc;
	V3 minN(0,0,0), maxN(0,0,0);

	for (int vi = 0; vi < 3; vi++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (trs[vi].xyz[j] < minV.xyz[j])
			{
				minV.xyz[j] = trs[vi].xyz[j];
				minN.xyz[j] = vi;
			}
			if (trs[vi].xyz[j] > maxV.xyz[j])
			{
				maxV.xyz[j] = trs[vi].xyz[j];
				maxN.xyz[j] = vi;
			}
		}
		for (int j = 0; j < 3; j++)
		{
			center.xyz[j] = (minV.xyz[j] + maxV.xyz[j]) / 2.0f;
			sideL.xyz[j] = fabs(minV.xyz[j] - maxV.xyz[j]);
		}
		
	}
	
	int temp = minN.xyz[0];
	leftMost = trs[temp];
	temp = maxN.xyz[0];
	rightMost = trs[temp];
	temp = minN.xyz[1];
	topMost = trs[temp];
	temp = maxN.xyz[1];
	bottomMost = trs[temp];

	
}

/*

calculate area of a triangle defined by point p1,p2 and p3 using cross product rules

*/

float TMesh::CalcArea(V3 p1, V3 p2, V3 p3)
{
	float area= ((p1.xyz[0] * (p2.xyz[1] - p3.xyz[1]) + p2.xyz[0] * (p3.xyz[1] - p1.xyz[1]) + p3.xyz[0] * (p1.xyz[1] - p2.xyz[1])) / 2.0f);
	return area;
}

/*
c
 \
|		w	\
	\			\
  u	 D *		-	-	b
|				/
	/	v	/

|		/
a

 some point P=ua+vb+wc

*/

/*

Gives barrycentric co-ordinates of a point p with respect to a triangle with point a,b and c
Refer to the graph above for understanding u,v and w
calculates area of the whole triangle and sub triangles formed by the point and two triangle points and find ratios
returns
barycentric parameters u,b,w 
0<u,v,w<1 for the point within the triangle. 0 means on the line. 
*/

void TMesh::GetBarryCentric(V3 a, V3 b, V3 c, V3 p, V3& uvw)
{
	float area_abc = CalcArea(a, b, c)+0.01f;
	float area_cap = CalcArea(c, a, p);
	float area_abp = CalcArea(a, b , p);
	float area_bcp = CalcArea(b, c, p);
	
	uvw.xyz[0] = area_cap / area_abc;
	uvw.xyz[1] = area_abp / area_abc;
	uvw.xyz[2] = area_bcp / area_abc;

}

/*

filled the Triangle Mesh with barrycentric colors wrt to vertices.
steps:

get a triangle
project the vertices into camera frame
determine the AABB for the triangle in the camera frame (not the original one)
loop through all the points in the AABB and determine wether inside or not
if inside check/update z buffer;
if new point is closer to us, update the color
*/

void TMesh::TriangleFillTexture(FrameBuffer* fb, PPC* ppc, texture* t1, int tri)
{
	V3 pa = verts[tris[3 * tri + 0]];
	V3 pb = verts[tris[3 * tri + 1]];
	V3 pc = verts[tris[3 * tri + 2]];

	V3 V0(0.0f, 0.0f, 0.0f), V1(0.0f, 0.0f, 0.0f), V2(0.0f, 0.0f, 0.0f);

	ppc->Project(pa, V0);
	ppc->Project(pb, V1);
	ppc->Project(pc, V2);

	V3 center(0.0f, 0.0f, 0.0f), sideL(0.0f, 0.0f, 0.0f), leftP(0.0f, 0.0f, 0.0f), rightP(0.0f, 0.0f, 0.0f), topP(0.0f, 0.0f, 0.0f), bottomP(0.0f, 0.0f, 0.0f);


	GetTriangleAABBparam(V0, V1, V2, center, sideL, leftP, topP, rightP, bottomP);
	//cout << "pas: " << pa << " " << pb << " " << pc << endl;
	//cout <<"Vs"<< V0 << " " << V1 << " " << V2 << endl;
	vector<V3> insidePoints = TriangleGetInsidePoints(fb, leftP, rightP, topP, bottomP, sideL, V0, V1, V2);	
	//ColorInsidePointsSS(fb,insidePoints,pa,pb,pc,V0,V1,V2,t1,ppc);
	ColorInsidePointsMS(fb, insidePoints, pa, pb, pc, V0, V1, V2, t1);
	cout << "returned1 "<< endl;
}

void TMesh::ColorInsidePointsSS(FrameBuffer* fb,vector<V3> insidePoints, V3 pa, V3 pb, V3 pc, V3 V0, V3 V1, V3 V2,texture* t1, PPC* ppc)
{
	int count = 0;
	for (int i = 0; i < insidePoints.size(); i++)
	{
		int pxI = insidePoints[i][0];
		int pyI = insidePoints[i][1];
		V3 insidePointsUP = ppc->UnProject(insidePoints[i]);
		int px = insidePointsUP[0];
		int py = insidePointsUP[1];
		int pz = insidePointsUP[2];
		
		//cout << "insidePointsNP:" << insidePoints[i] << endl;
		//cout << "insidePointsuP:" << insidePointsUP << endl;
		//cout << "pa, pb and pc:" << pa << " " << pb << " " << pc << endl;		
		int pxSS = (px - pa[0]) / (pc[0] - pa[0])*t1->w;
		int pySS = (py - pa[1]) / (pc[1] - pa[1]) * t1->h;
		//cout << "pxSS,pySS:" << pxSS << " " << pySS << endl;
		if (pxSS < 0 || pySS < 0|| pxSS> t1->w || pySS> t1->h)
		{
		}
		else {

			unsigned int color_uvw = t1->pix[pxSS + pySS * t1->w];
			fb->Set(pxI, pyI, color_uvw);
		}
	}
}

void TMesh::ColorInsidePointsMS(FrameBuffer* fb, vector<V3> insidePoints, V3 pa, V3 pb, V3 pc, V3 V0, V3 V1, V3 V2, texture* t1)
{
	for (int i = 0; i < insidePoints.size(); i++)
	{
		int px = insidePoints[i][0];
		int py = insidePoints[i][1];
		int pxSS = (px - V0[0]) / (V2[0] - V0[0]) * t1->w;
		int pySS = (py - V0[1]) / (V2[1] - V0[1]) * t1->h;
		unsigned int color_uvw = t1->pix[pxSS + pySS * t1->w];
		fb->Set(px, py, color_uvw);
	}
}



vector<V3> TMesh::TriangleGetInsidePoints(FrameBuffer* fb, V3 leftP, V3 rightP, V3 topP, V3 bottomP, V3 sideL, V3 V0, V3 V1, V3 V2)
{
	float delta = 0.5f;
	vector<V3> insidePoints;
	for (int j = topP.xyz[1] + delta; j <= bottomP.xyz[1] - delta; j++)
	{
		for (int i = leftP.xyz[0] + delta; i <= rightP.xyz[0] - delta; i++)
		{
			
			float mul = 1.0f;
			float tempZ = leftP.xyz[2] + (i - leftP.xyz[0]) * sideL.xyz[2] * mul / (sideL.xyz[0] + 0.01f);
			float tempZ2 = topP.xyz[2] + (j - topP.xyz[1]) * sideL.xyz[2] * mul / (sideL.xyz[1] + 0.01f);
			float zfinal = (tempZ + tempZ2) / 2.0f;

			V3 uvw(0, 0, 0);
			GetBarryCentric(V0, V1, V2, V3(i, j, 0), uvw);

			if (uvw.xyz[0] >= 0 && uvw.xyz[1] >= 0 && uvw.xyz[2] >= 0 && uvw.xyz[0] < 1 && uvw.xyz[1] < 1 && uvw.xyz[2] < 1)
			{
				if (!fb->Farther(i, j, zfinal))
				{			
					V3 in(i, j, zfinal);
					insidePoints.push_back(in);					
					

				}

			}

		}		

	}
	return insidePoints;
}

void TMesh::DrawFilledFrameTexture(FrameBuffer* fb, PPC* ppc, texture *t1) 
{
	
	for (int tri = 0; tri <2; tri++) 
	{
		//TriangleFillTexture(fb, ppc, t1, tri);
		
		
		V3 pa = verts[tris[3 * tri + 0]];
		V3 pb = verts[tris[3 * tri + 1]];
		V3 pc = verts[tris[3 * tri + 2]];
		
		V3 V0(0.0f, 0.0f, 0.0f), V1(0.0f,0.0f,0.0f), V2(0.0f, 0.0f, 0.0f);

		ppc->Project(pa,V0);
		ppc->Project(pb,V1);
		ppc->Project(pc,V2);

		V3 center(0.0f, 0.0f, 0.0f), sideL(0.0f, 0.0f, 0.0f), leftP(0.0f, 0.0f, 0.0f), rightP(0.0f, 0.0f, 0.0f), topP(0.0f, 0.0f, 0.0f), bottomP(0.0f, 0.0f, 0.0f);
		

		GetTriangleAABBparam(V0, V1, V2, center, sideL,leftP, topP,rightP, bottomP);
		cout<< "|" << pa << " " << pb << " " << pc << endl;

		cout << V0<<" "<<V1<<" "<<V2 << endl;
		cout << "topBLR" << topP << bottomP << leftP << rightP << endl;
		float delta = 1.0f;
		
	
		for (int j = topP.xyz[1] + delta; j <= bottomP.xyz[1] - delta; j++)
		{
			for (int i = leftP.xyz[0] - delta; i <= rightP.xyz[0] + delta; i++)
			{
				//cout << "i,j:" << i << "," << j << endl;
				

				float mul = 1.0f;
				float tempZ = leftP.xyz[2] + (i - leftP.xyz[0]) * sideL.xyz[2]*mul/ (sideL.xyz[0]+0.01f);
				float tempZ2 = topP.xyz[2] + (j - topP.xyz[1]) * sideL.xyz[2]*mul / (sideL.xyz[1]+0.01f);
				float zfinal = (tempZ + tempZ2) / 2.0f;			

				V3 uvw(0, 0, 0);
				GetBarryCentric(V0, V1, V2, V3(i, j, 0), uvw);
				
					
				if (uvw.xyz[0] >= 0 && uvw.xyz[1] >= 0 && uvw.xyz[2] >= 0 && uvw.xyz[0] <= 1 && uvw.xyz[1] <=1 && uvw.xyz[2] <=1)
				{	
					if (!fb->Farther(i, j, zfinal))
					{
					
						int texI, texJ;					
						
					//	V3 ii = ppc->UnProject(V3(i, j, zfinal));

						texI = (i - (leftP.xyz[0])) / sideL[0] * t1->w;
						texJ = (j - (topP.xyz[1])) / sideL[1] * t1->h;

					//	cout <<"ii:"<< ii <<","<<tt<<","<<ll<<","<<rr<<","<<bb<< endl;
					//	texI = (ii[0]-ll[0])/60* t1->w;
						//texJ = (ii[1]-tt[1])/60 * t1->h;
					//	cout <<texI<< ","<<texJ<<endl;

						//texI = (i - (V0[0])) / (V2[0]-V0[0]) * t1->w;
						//texJ = (j - (V0[1])) / (V2[1] - V0[1]) * t1->h;
						int pixIJ = texI + texJ * t1->w;
						if (pixIJ<0 || pixIJ>(t1->w* t1->h))
						{
							cout << "**********************Problem: pixel seeking beyond image corodinate:" << pixIJ << " **************************" << endl;
						}
						unsigned int color_uvw = t1->pix[pixIJ];

						if (tri == 0)
						{
							fb->Set(i, j, color_uvw);

						}
						else {

						fb->Set(i, j, 0xFFFF0000);
					}
						
					}

				}		
				
			}
			//cerr << endl;
			//cerr << endl;

		}
		

	}
	cout << endl;
	
}



void TMesh::DrawFilledFrame(FrameBuffer* fb, PPC* ppc, unsigned int color)
{

	for (int tri = 0; tri < trisN; tri++)
	{

		V3 pa = verts[tris[3 * tri + 0]];
		V3 pb = verts[tris[3 * tri + 1]];
		V3 pc = verts[tris[3 * tri + 2]];
		V3 c0 = colors[tris[3 * tri + 0]];
		V3 c1 = colors[tris[3 * tri + 1]];
		V3 c2 = colors[tris[3 * tri + 2]];
		V3 V0(0.0f, 0.0f, 0.0f), V1(0.0f, 0.0f, 0.0f), V2(0.0f, 0.0f, 0.0f);

		ppc->Project(pa, V0);
		ppc->Project(pb, V1);
		ppc->Project(pc, V2);

		V3 center(0.0f, 0.0f, 0.0f), sideL(0.0f, 0.0f, 0.0f), leftP(0.0f, 0.0f, 0.0f), rightP(0.0f, 0.0f, 0.0f), topP(0.0f, 0.0f, 0.0f), bottomP(0.0f, 0.0f, 0.0f);


		GetTriangleAABBparam(V0, V1, V2, center, sideL, leftP, topP, rightP, bottomP);


		float delta = 0.5f;


		for (int i = leftP.xyz[0] - delta; i <= rightP.xyz[0] + delta; i++)
		{
			for (int j = topP.xyz[1] - delta; j <= bottomP.xyz[1] + delta; j++)
			{
				float mul = 1.0f;
				float tempZ = leftP.xyz[2] + (i - leftP.xyz[0]) * sideL.xyz[2] * mul / (sideL.xyz[0] + 0.01f);
				float tempZ2 = topP.xyz[2] + (j - topP.xyz[1]) * sideL.xyz[2] * mul / (sideL.xyz[1] + 0.01f);
				float zfinal = (tempZ + tempZ2) / 2.0f;

				V3 uvw(0, 0, 0);
				GetBarryCentric(V0, V1, V2, V3(i, j, 0), uvw);


				V3 color_uvw = c0 * uvw.xyz[0] + c1 * uvw.xyz[1] + c2 * uvw.xyz[2];

				if (uvw.xyz[0] >= 0 && uvw.xyz[1] >= 0 && uvw.xyz[2] >= 0 && uvw.xyz[0] < 1 && uvw.xyz[1] < 1 && uvw.xyz[2] < 1)
				{
					if (!fb->Farther(i, j, zfinal)) {

						fb->Set(i, j, color_uvw.GetColor());
					}
				}


			}

		}


	}

}


void TMesh::GetAABBParam(V3 &center, V3& sideL) {
	
	V3 minV(100000.0f, 10000.0f, 100000.0f);
	V3 maxV(-100000.0f, -100000.0f, -100000.0f);
	
	for (int vi = 0; vi < vertsN; vi++) 
	{
		for (int j = 0; j < 3; j++)
		{
			if (verts[vi].xyz[j] < minV.xyz[j])
			{
				minV.xyz[j] = verts[vi].xyz[j];
			}
			if (verts[vi].xyz[j] > maxV.xyz[j])
			{
				maxV.xyz[j] = verts[vi].xyz[j];
			}
		}
		for (int j = 0; j < 3; j++)
		{
			center.xyz[j] = (minV.xyz[j] + maxV.xyz[j])/2.0f;
			sideL.xyz[j] = fabs(minV.xyz[j] - maxV.xyz[j]);

		}
		

	}
	

}

void TMesh::LoadBin(char* fname) {

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
	float* tcs = 0; // don't have texture coordinates for now
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

float TMesh::GetSL()
{
	return(fabs((GetCenter()[0] - verts[0][0]))) * 2;
}

void TMesh::Translate(V3 tv) {

	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] + tv;
	}

}

void TMesh::Scale(float scf) {
	V3 oldCenter = GetCenter();
	SetCenter(V3(0.0f, 0.0f, 0.0f));
	
	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi] * scf;
		
	}
	SetCenter(oldCenter);
	

}


void TMesh::SetCenter(V3 center) {

	V3 currCenter = GetCenter();
	Translate(center - currCenter);
	

}


void TMesh::Rotate(V3 a0, V3 adir, float angle) {
	for (int vi = 0; vi < vertsN; vi++) {
		verts[vi] = verts[vi].RotateThisPointAboutArbitraryAxis(a0,adir, angle);
	}
	


}

