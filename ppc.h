#pragma once

#include "v3.h"
#include"framebuffer.h"

class PPC {
public:
	V3 a, b, c, C;
	int w, h, pw, ph;
	PPC();
	PPC(float hfov, int _w, int _h);
	PPC(float hfov, int _w, int _h, int _pw, int _ph);
	int Project(V3 P, V3 &p);
	V3 UnProject(V3 p);
	void TranslateRightLeft(float tstep);
	void TranslateFrontBack(float tstep);
	void TranslateUpDown(float tstep);
	void Pan(float angle);
	void Tilt(float angle);
	void Roll(float angle);
	void ChangeFoculLength(float ScalingFactor);
	void SetInterpolated(PPC* ppc0, PPC* ppc1, int stepi, int stepsN);
	void PositionAndOrient(V3 C1, V3 L1, V3 vpv);
	V3 GetVD();
	float GetFocalLength();
	void load4mText(char* name);
	//void Visualize(FrameBuffer* vfb, PPC* vppc, float vf);
	//void Visualize(FrameBuffer* vfb, PPC* vppc, float vf, FrameBuffer* fb);
	//float GetF();
	//void SetPose(V3 newC, V3 lookAtPoint, V3 upGuidance);
	//void PanLeftRight(float rstep);
};