#ifndef POOLCLASSES_H_INCLUDED
#define POOLCLASSES_H_INCLUDED

#include <GL/glew.h>
#include <glm/glm.hpp>

class ball{
private:
	int slices;
	int stacks;
public:
	glm::vec3 *vertex;
	int vertexNum;
	glm::vec3 *normal;
	glm::vec2 *texcoord;

	ball(int slc, int stk);
	void ballMesh();
};

#endif // POOLCLASSES_H_INCLUDED
