#include "RayMesh.h"

const char* RayMesh::getName() const
{
    return "RAY";
}

bool RayMesh::load(const std::string& filename)
{
    const int STRIDE = 4;
    float vertices[] = {
        // positions         // texture coords
        0.5f,  0.5f, 2.0f,    1.0f, 1.0f,   // top right
        0.5f, -0.5f, 2.0f,    1.0f, 0.0f,   // bottom right
        -0.5f, -0.5f, 2.0f,   0.0f, 0.0f,   // bottom left
    };
    for(int i = 0 ; i < 3; i++)
    {
        glm::vec3 vertex;
        glm::vec2 uv;
        vertex.x = vertices[i + (i * STRIDE)];
        vertex.y = vertices[i + 1 +(i * STRIDE)];
        vertex.z = vertices[i + 2 +(i * STRIDE)];

        uv.s = vertices[i + 3 +(i * STRIDE)];
        uv.t = vertices[i + 4 +  (i * STRIDE)];

        Vertex meshVertex;
        meshVertex.position = vertex;
        meshVertex.texCoords = uv;

        mVertices.push_back(meshVertex);
    }
    initBuffers();
}
