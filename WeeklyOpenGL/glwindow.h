#ifndef GLWINDOW_H
#define GLWINDOW_H

class GLFWwindow;
class Shader;

class GLWindow
{
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow* window);

public:
    GLWindow(int,int);
    int TickWindow();
    void SetShader(const char*,const char*);

private:
    int SCR_WIDTH;
    int SCR_HEIGHT;
    Shader* shader;
    int shaderProgram;
    const char* vsPath;
    const char* fsPath;

};

#endif // GLWINDOW_H
