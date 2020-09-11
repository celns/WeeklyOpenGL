#ifndef SHADER_H
#define SHADER_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Shader
{
public:
    Shader(const char* vertexPath, const char* fragmentPath);
    void Use();
    void SetBool(const string &name, bool value) const;
    void SetInt(const string &name, int value) const;
    void SetFloat(const string &name, float value) const;
public:
    unsigned int ID;
private:
    string vertexCode;
    string fragmentCode;
    ifstream vShaderFile;
    ifstream fShaderFile;

private:
    void CheckCompileErrors(unsigned int shader, string type);
};

#endif // SHADER_H
