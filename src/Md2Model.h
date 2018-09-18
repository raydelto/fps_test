#ifndef MD2_MODEL_H
#define MD2_MODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "MeshInterface.h"
#include <vector>

struct Vertex;

typedef struct
{
	int id;
	int version;
	int twidth;
	int theight;
	int framesize;
	int textures;
	int vNum;
	int tNum;
	int fNum;
	int numGLcmds;
	int Number_Of_Frames;
	int offsetSkins;
	int offsetTCoord;
	int offsetIndx;
	int offsetFrames;
	int offsetGLcmds;
	int offsetEnd;
} header;

typedef struct
{
	float s;
	float t;
} textcoord;

typedef struct
{
	short s;
	short t;
} textindx;

typedef struct
{
	unsigned char v[3];
	unsigned char normalIndex;
} framePoint_t;

typedef struct
{
	float scale[3];
	float translate[3];
	char name[16];
	framePoint_t fp[1];
} frame;

typedef struct
{
	unsigned short meshIndex[3];
	unsigned short stIndex[3];
} mesh;

typedef struct
{
	float point[3];
} positionVector;

typedef struct
{
	int numFrames;
	int numPoints;
	int numTriangles;
	int numST;
	int frameSize;
	int twidth;
	int theight;
	int currentFrame;
	int nextFrame;
	float interpol;
	mesh *triIndx;
	textcoord *st;
	positionVector *pointList;
	float x, y, z;
	float nextX, nextY, nextZ;
	float radius;
	float dist_to_player;
	int state;
	float speed;
} modData;

class Md2Model: public MeshInterface
{
  private:
	modData *mod;

  public:
	Md2Model(){};
	Md2Model(char *fileName);
	virtual bool load(const std::string& filename);	
	virtual const char* getName() const;
};

#endif
