#pragma once
#include <string>

struct source;

class Shader
{
private:
	unsigned int mRendererID;
public:
	Shader(const std::string& vsPath, const std::string& fsPath);
	~Shader();

	void Bind();
	void Unbind();

	bool CompileShader(unsigned int type, const std::string& source);

	std::string ParseShader(const std::string& filePath);

	unsigned int CreateShader(std::string& vertexShader, std::string& fragmentShader);

	void Uniform(std::string name);
};