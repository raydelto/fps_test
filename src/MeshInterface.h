#ifndef MESH_INTERFACE_H
#define MESH_INTERFACE_H

#include <string>

class MeshInterface
{
    public:
    	virtual bool load(const std::string& filename) = 0;
	    virtual void draw() = 0;
		virtual const char* getName() const= 0;
};

#endif
