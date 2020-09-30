#include "stdafx.h"

#include "AABB.h"

AABB::AABB(V3 firstPoint) {

	corners[0] = corners[1] = firstPoint;

}

void AABB::AddPoint(V3 P) {

	for (int i = 0; i < 3; i++) {
		if (corners[0][i] > P[i])
			corners[0][i] = P[i];
		if (corners[1][i] < P[i])
			corners[1][i] = P[i];
	}

}