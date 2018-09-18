//-----------------------------------------------------------------------------
// Mesh.h by Steve Jones 
// Copyright (c) 2015-2016 Game Institute. All Rights Reserved.
//
// Basic Mesh class
//-----------------------------------------------------------------------------
#ifndef MESH_H
#define MESH_H

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "MeshInterface.h"


struct Vertex;

class Mesh: public MeshInterface
{
public:

	 Mesh();
	~Mesh();

	virtual bool load(const std::string& filename);
	virtual const char* getName() const;

private:
	bool mLoaded;
};
#endif //MESH_H
