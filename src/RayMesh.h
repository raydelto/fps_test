#ifndef RAY_MESH_H
#define RAY_MESH_H
#include "MeshInterface.h"
#include <string>

class RayMesh : public MeshInterface
{
	virtual bool load(const std::string& filename);
	virtual const char* getName() const;
};

#endif
