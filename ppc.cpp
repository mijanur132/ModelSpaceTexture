#include "stdafx.h"
#include <fstream>
#include "ppc.h"
#include <string>

#include <iostream>
#include "M33.h"

PPC::PPC(float hfov, int _w, int _h) {

	w = _w;
	h = _h;
	C = V3(0.0f, 0.0f, 0.0f);
	a = V3(1.0f, 0.0f, 0.0f);
	b = V3(0.0f, -1.0f, 0.0f);
	float hfovd = hfov / 180.0f * 3.14159236f;
	c = V3(-(float)w / 2.0f, (float)h / 2, -(float)w / (2 * tanf(hfovd / 2.0f)));

}

PPC::PPC() {

	w = 0;
	h = 0;
	C =V3(0,0,0);
	a = V3(0, 0, 0);
	b = V3(0, 0, 0);
	float hfovd =0;
	c = V3(0, 0, 0);
}

PPC::PPC(float hfov, int _w, int _h,int _pw, int _ph) {

	
	pw = _pw;
	ph = _ph;
	w = _w*pw;
	h = _h*ph;

	C = V3(0.0f, 0.0f, 0.0f);
	a = V3(1.0f, 0.0f, 0.0f);
	b = V3(0.0f, -1.0f, 0.0f);
	float hfovd = hfov / 180.0f * 3.14159236f;
	c = V3(-(float)w / 2.0f, (float)h / 2, -(float)w / (2 * tanf(hfovd / 2.0f)));

}

void PPC::load4mText(char* name) 
{
	ifstream newfile(name, std::ios_base::in); //open a file to perform read operation using file object
	string tp;
	int w, h;
	float hfov;
	if (newfile.is_open())
	{   
		int line = 0;
				
		float a;
		while (newfile >> a)
		{
			
			if (line == 0)
			{
				w = a;
				//cout << w << endl;
			}
			if (line == 1)
			{
				h = a;
				//cout << h << endl;
			}

			if (line == 2)
			{
				hfov = a;
				//cout << hfov << endl;
			}
			line++;
		}

		//getchar();
		(*this).w = w;
		(*this).h = h;
		(*this).C = V3(0.0f, 0.0f, 0.0f);
		(*this).a = V3(1.0f, 0.0f, 0.0f);
		(*this).b = V3(0.0f, -1.0f, 0.0f);
		float hfovd = hfov / 180.0f * 3.14159236f;
		(*this).c = V3(-(float)w / 2.0f, (float)h / 2, -(float)w / (2 * tanf(hfovd / 2.0f)));
		
	}

	cout <<"camera loaded: "<< w << h << hfov << endl;

	//getchar();


}

void PPC::Pan(float angle)
{ 
	V3 dv = (b * (-1.0f)).UnitVector();
	a = a.RotateThisVectorAboutDirection(dv, angle);
	c = c.RotateThisVectorAboutDirection(dv, angle);
}

void PPC::Tilt(float angle) {

	V3 dv = (a).UnitVector();
	b = b.RotateThisVectorAboutDirection(dv, angle);
	c = c.RotateThisVectorAboutDirection(dv, angle);

}

void PPC::Roll(float angle) {

	V3 dv = (a^b).UnitVector();
	a=a.RotateThisVectorAboutDirection(dv, angle);
	b = b.RotateThisVectorAboutDirection(dv, angle);
	c = c.RotateThisVectorAboutDirection(dv, angle);

}

void PPC::ChangeFoculLength(float scalingFactor) {

	V3 VD = (a ^ b).UnitVector();
	float fl = c * VD;
	float deltaFl = fl * (1.0f - scalingFactor);

	c = c + VD*deltaFl;

}

int PPC::Project(V3 P, V3 &p) {

	M33 M;
	M.SetColumn(0, a);
	M.SetColumn(1, b);
	M.SetColumn(2, c);
	V3 q = M.Inverted()*(P - C);
	float w = q[2];
	if (w <= 0.0f)
		return 0;

	p[0] = q[0] / q[2];
	p[1] = q[1] / q[2];
	p[2] = w;
	return 1;
}

V3 PPC::UnProject(V3 p) {

	V3 ret;

	ret = C + (a*p[0] + b*p[1] + c)*(p[2]);
	return ret;

}


void PPC::TranslateRightLeft(float tstep) {

	V3 rightDir = a.Normalized();
	C = C + rightDir*tstep;

}

void PPC::TranslateFrontBack(float tstep) {

	V3 tDir = (a^b).Normalized();
	C = C + tDir*tstep;

}

void PPC::TranslateUpDown(float tstep) {

	V3 upDir = b.Normalized()*(-1.0f);
	C = C + upDir * tstep;

}

// C1 is the new center, L1 is a point on the direction. So direction is (L1-C1) unit vector
//vpv is upvector, a is the (vd*upv).unitvector*a.length
//b is a*direct

void PPC::PositionAndOrient(V3 C1, V3 L1, V3 vpv) {

	V3 vd1 = (L1 - C1).UnitVector();
	V3 a1 = (vd1 ^ vpv).UnitVector() * a.Length();
	V3 b1 = (vd1 ^ a1).UnitVector() * b.Length();
	V3 c1 = vd1 * GetFocalLength() - b1 * ((float)h / 2.0f) - a1 * ((float)w / 2.0f);

	C = C1;
	a = a1;
	b = b1;
	c = c1;
	

}

V3 PPC::GetVD() {

	return (a ^ b).UnitVector();

}

float PPC::GetFocalLength() {

	return GetVD() * c;

}

void PPC::SetInterpolated(PPC* ppc0, PPC* ppc1, int stepi, int stepsN) {


	(*this) = *ppc0;

	float f = (float)stepi / (float)(stepsN - 1);
	V3 Ci = ppc0->C + (ppc1->C - ppc0->C) * f;

	V3 L0 = ppc0->C + ppc0->GetVD() * 100.0f;
	V3 L1 = ppc1->C + ppc1->GetVD() * 100.0f;
	V3 Li = L0 + (L1 - L0) * f;

	V3 vpv0 = ppc0->b * -1.0f;
	V3 vpv1 = ppc1->b * -1.0f;
	V3 vpvi = vpv0 + (vpv1 - vpv0) * f;

	PositionAndOrient(Ci, Li, vpvi);
	

}

