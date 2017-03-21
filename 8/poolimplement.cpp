#include <stdio.h>
#include "poolclasses.h"
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <math.h>
#include <iostream>
using namespace std;

ball::ball(int slc, int stk){
	slices = slc;
	stacks = stk;
}

void ball::ballMesh(){
	vertexNum = 2 * (slices + 1) * stacks;
	vertex = (glm::vec3*)malloc(sizeof(glm::vec3)*vertexNum);
	normal = (glm::vec3*)malloc(sizeof(glm::vec3)*vertexNum);
	texcoord = (glm::vec2*)malloc(sizeof(glm::vec2)*vertexNum);
	float stepsk = M_PI/stacks;
	float stepsl = 2*M_PI/slices;
	float theta;
	float phi;

	for (int i = 0; i < stacks; i++) {
		theta = stepsk*i;
		for (int j = 0; j < slices; j++) {
			phi = stepsl*j;
		    glm::vec3 v1 = glm::vec3(sin(theta) * sin(phi), cos(theta), sin(theta) * cos(phi));
		    glm::vec3 v2 = glm::vec3(sin(theta + stepsk) * sin(phi), cos(theta + stepsk), sin(theta + stepsk) * cos(phi));
		    *(vertex++) = v1;
		    *(vertex++) = v2;
		    *(normal++) = v1;
		    *(normal++) = v2;
		    *(texcoord++) = glm::vec2(-(atan2(v1[0],v1[1])/M_PI+1.0)/2, -acos(v1[2])/M_PI);
		    *(texcoord++) = glm::vec2(-(atan2(v2[0],v2[1])/M_PI+1.0)/2, -acos(v2[2])/M_PI);
	  }
	}
	vertex = vertex - vertexNum;
	normal = normal - vertexNum;
	texcoord = texcoord - vertexNum;
}

GLuint setVBO(glm::vec3 *points, glm::vec3 *normals, glm::vec2 *texcoord, int vertexNum){
	GLuint vbo;
	cout<<"\nIn setVBO resources";
	int sizePoints = sizeof(glm::vec3)*vertexNum;
	int sizeTexcoord = sizeof(glm::vec2)*vertexNum;
	cout<<"In setVBO mid resources";
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizePoints*2+sizeTexcoord, NULL, GL_STATIC_DRAW);
	glBufferSubData( GL_ARRAY_BUFFER, 0, sizePoints, points );
	glBufferSubData( GL_ARRAY_BUFFER, sizePoints, sizePoints, normals);
	glBufferSubData( GL_ARRAY_BUFFER, 2*sizePoints, sizeTexcoord, texcoord);
	return vbo;
}
