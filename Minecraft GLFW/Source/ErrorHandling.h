#pragma once
#include <GL/glew.h>
#include <iostream>

#include "Utility/Mexception.h"

#define CONSOLEMSG(x) std::cerr << x << std::endl;

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
		std::cerr << "[OpenGL Error] ( " << error << " )\n";
		return false;
	}
	return true;
}
