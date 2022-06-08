#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <glad\glad.h> //for OpenGL functions


class Shader
{
	unsigned int ID;
public:
	Shader(const char* vs_file, const char* fs_file);
	~Shader();
	void use(); 
	unsigned int get_ID() const;

};

