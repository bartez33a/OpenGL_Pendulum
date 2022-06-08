#pragma once

#include <glad\glad.h>
#include <iostream>

class VBO
{
	GLuint ID;
public:
	//Constructor for Vertex buffer object
	VBO(float *vertices, unsigned int vertices_size);
	//Destructor deletes buffer
	~VBO();
	void BindBuffer();
	void UnbindBuffer();
	void SetAttributes(int location, int attribSize, int stride, int offset);
};

