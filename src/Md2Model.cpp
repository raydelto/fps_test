#include "Md2Model.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const char* Md2Model::getName() const
{
	return "MD2";
}

bool Md2Model::load(const std::string& filename)
{
	const char* fileName = filename.c_str();
	FILE *fp;
	int length;

	char *buffer;

	header *head;
	textindx *stPtr;

	frame *fra;
	positionVector *pntlst;
	mesh *triIndex, *bufIndexPtr;

	fp = fopen(fileName, "rb");
	fseek(fp, 0, SEEK_END);
	length = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buffer = (char *)malloc(length + 1);
	fread(buffer, sizeof(char), length, fp);

	head = (header *)buffer;
	mod = (modData *)malloc(sizeof(modData));

	mod->pointList = (positionVector *)malloc(sizeof(positionVector) * head->vNum * head->Number_Of_Frames);
	mod->numPoints = head->vNum;
	mod->numFrames = head->Number_Of_Frames;
	mod->frameSize = head->framesize;

	for (int count = 0; count < head->Number_Of_Frames; count++)
	{
		fra = (frame *)&buffer[head->offsetFrames + head->framesize * count];
		pntlst = (positionVector *)&mod->pointList[head->vNum * count];
		for (int count2 = 0; count2 < head->vNum; count2++)
		{
			pntlst[count2].point[0] =  fra->scale[0] * fra->fp[count2].v[0] + fra->translate[0];
			pntlst[count2].point[1] =  fra->scale[1] * fra->fp[count2].v[1] + fra->translate[1];
			pntlst[count2].point[2] = fra->scale[2] * fra->fp[count2].v[2] + fra->translate[2];
		}
	}

	mod->st = (textcoord *)malloc(sizeof(textcoord) * head->tNum);
	mod->numST = head->tNum;
	stPtr = (textindx *)&buffer[head->offsetTCoord];

	for (int count = 0; count < head->tNum; count++)
	{
		mod->st[count].s = (float)stPtr[count].s / (float)head->twidth;
		mod->st[count].t = (float)stPtr[count].t / (float)head->theight;
	}

	triIndex = (mesh *)malloc(sizeof(mesh) * head->fNum);
	mod->triIndx = triIndex;
	mod->numTriangles = head->fNum;
	bufIndexPtr = (mesh *)&buffer[head->offsetIndx];

	for (int count = 0; count < head->Number_Of_Frames; count++)
	{
		for (int count2 = 0; count2 < head->fNum; count2++)
		{
			triIndex[count2].meshIndex[0] = bufIndexPtr[count2].meshIndex[0];
			triIndex[count2].meshIndex[1] = bufIndexPtr[count2].meshIndex[1];
			triIndex[count2].meshIndex[2] = bufIndexPtr[count2].meshIndex[2];

			triIndex[count2].stIndex[0] = bufIndexPtr[count2].stIndex[0];
			triIndex[count2].stIndex[1] = bufIndexPtr[count2].stIndex[1];
			triIndex[count2].stIndex[2] = bufIndexPtr[count2].stIndex[2];
		}
	}

	mod->currentFrame = 1;
	mod->nextFrame = 2;
	mod->interpol = 0.0;

	fclose(fp);


	//Populating mVertices
	for (int index = 0; index < mod->numTriangles; index++)
	{
		glm::vec3 vertex;
		glm::vec2 uv;

		uv.s = mod->st[mod->triIndx[index].stIndex[0]].s;
		uv.t = mod->st[mod->triIndx[index].stIndex[0]].t;

		positionVector* frame = &mod->pointList[mod->numPoints * mod->currentFrame];
		vertex.x = frame[mod->triIndx[index].meshIndex[0]].point[0];
		vertex.y = frame[mod->triIndx[index].meshIndex[0]].point[1];
		vertex.z = frame[mod->triIndx[index].meshIndex[0]].point[2];

		Vertex meshVertex;
		meshVertex.position = vertex;
		meshVertex.texCoords = uv;

		mVertices.push_back(meshVertex);
	}
	InitBuffers();
	return true;
}

Md2Model::Md2Model(char *fileName)
{
	load(fileName);
}

void Md2Model::draw()
{
	// std::cout << "Drawing MD2 model" << std::endl;

	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVertices.size());
	glBindVertexArray(0);
}

void Md2Model::InitBuffers()
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)0);

	// Vertex Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));

	// unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);
}


