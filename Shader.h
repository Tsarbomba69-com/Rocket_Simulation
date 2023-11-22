#ifndef SHADER_H
#define SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include <string.h>
#include <string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<cerrno>

char* readFile(const char* filepath);
char* fail(FILE* file, char* buffer);

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);
};
#endif 

