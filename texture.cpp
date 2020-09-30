#include "stdafx.h"
#include "texture.h"
#include "math.h"
#include <iostream>
#include "scene.h"




// load ************************************a tiff image to pixel buffer
void texture::LoadTiff(char* fname) {
	TIFF* in = TIFFOpen(fname, "r");
	if (in == NULL) {
		cerr << fname << " could not be opened" << endl;
		return;
	}

	int width, height;
	TIFFGetField(in, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(in, TIFFTAG_IMAGELENGTH, &height);
	w = width;
	h = height;
	pix = new unsigned int[w * h];
	

	if (TIFFReadRGBAImageOriented(in, w, h, pix, ORIENTATION_LEFTTOP, 0) == 0) {
		cerr << "failed to load " << fname << endl;
	}
	cout << "imageLoaded-w,h:" << w <<" "<< h << endl;
	TIFFClose(in);
	
}