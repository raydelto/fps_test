//-----------------------------------------------------------------------------
// Texture2D.h by Steve Jones 
// Copyright (c) 2015-2016 Game Institute. All Rights Reserved.
//
// Simple 2D texture class
//-----------------------------------------------------------------------------
#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "GL/glew.h"
#include <string>
using std::string;

class Texture2D
{
public:
	Texture2D();
	virtual ~Texture2D();

	bool loadTexture(const string& fileName, bool generateMipMaps = true);
	void bind(GLuint texUnit = 0);
	void unbind(GLuint texUnit = 0);

private:
	Texture2D(const Texture2D& rhs) {}
	Texture2D& operator = (const Texture2D& rhs) {}

	GLuint mTexture;
};
#endif //TEXTURE2D_H
