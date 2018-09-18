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


struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
};

class Mesh: public MeshInterface
{
public:

	 Mesh();
	~Mesh();

	virtual bool load(const std::string& filename);
	virtual void draw();
	virtual const char* getName() const;


private:

	void initBuffers();

	bool mLoaded;
	std::vector<Vertex> mVertices;
	GLuint mVBO, mVAO;
};
#endif //MESH_H
