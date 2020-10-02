#pragma once
#include <tiffio.h>

class texture
{
public:
	unsigned int* pix; // pixel array
	int w, h,id;
	
	void LoadTiff(char* fname);
	int getPixelIndex(int u, int v);

};

