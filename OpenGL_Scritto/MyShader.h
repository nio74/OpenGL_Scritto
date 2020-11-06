#pragma once
#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class MyShader
{
public:

	unsigned int ID;

	MyShader(const char* vertexPath, const char* fragmentPath);

	// usare lo shader
	void use();

	//utility

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;
	void checkCompileErrors(unsigned int shader, std::string type);

};

