#ifndef MESH_INTERFACE_H
#define MESH_INTERFACE_H

#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec2 texCoords;
};

class MeshInterface
{
    public:
    	virtual bool load(const std::string& filename) = 0;
	    void draw();
		virtual const char* getName() const= 0;
	protected:
		std::vector<Vertex> mVertices;
		GLuint mVBO, mVAO;			
		void initBuffers();
};

#endif
