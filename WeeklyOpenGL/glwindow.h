#ifndef GLWINDOW_H
#define GLWINDOW_H

class GLFWwindow;
class Shader;
class Camera;

class GLWindow
{
private:
    void processInput(GLFWwindow* window);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_callback(GLWindow* window, double xpos, double ypos);
    void scroo_callback(GLWindow* window, double xoffset, double yoffset);

public:
    GLWindow(int,int);
    int InitWindow();
    void BindCallback(GLWindow* callback);
    int TickWindow();
    void SetShader(const char*,const char*);



private:
    int SCR_WIDTH;
    int SCR_HEIGHT;
    GLFWwindow* window;
    Shader* shader;
    int shaderProgram;
    const char* vsPath;
    const char* fsPath;
    Camera* camera;
    float lastX;
    float lastY;
    float deltaTime;
    float lastFrame;
    bool firstMouse;

};

#endif // GLWINDOW_H
