#pragma once
#include <GL/glew.h>
#include <iostream>

#define ASSERT(x) if (!(x)) __debugbreak();
 
#define GLCall(x) GLClearError();\
x;\
ASSERT(GLLogCall());\


static void GLClearError()
{
	while(glGetError() != GL_NO_ERROR); 
}

static bool GLLogCall()
{
	while(GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] ( " << error << " )\n";
		return false;
	}
	return true;
}
