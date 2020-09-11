#include "glwindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"


GLWindow::GLWindow(int width, int height)
{
    SCR_WIDTH = width;
    SCR_HEIGHT = height;

}

int GLWindow::TickWindow()
{
    //glfw 初始化
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //mac环境下需要额外执行的配置
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);
#endif

    //创建glfw窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"OpenGLWindow",NULL,NULL);
    if(window == NULL)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);


    //载入全部OPENGL函数指针
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize GLAD"<<std::endl;
        return -1;
    }

    //LinkShader();
    shader = new Shader(vsPath,fsPath);

    //设置顶点数据
    float vertices[] = {
        0.5f,0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f
    };

    unsigned int indices[] = {
        0,1,3,
        1,2,3
    };



    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //绑定
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices),indices,GL_STATIC_DRAW);


    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);





    //渲染循环
    while(!glfwWindowShouldClose(window))
    {
        //处理输入
        processInput(window);

        //渲染指令
        glClearColor(0.2f,0.2f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //绘制三角形
//        glUseProgram(shaderProgram);
        shader->Use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6 , GL_UNSIGNED_INT, 0);


        //交换buffer
        glfwSwapBuffers(window);
        //拉取IO事件
        glfwPollEvents();
    }

    //释放资源
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);



    //终止glfw，释放资源
    glfwTerminate();
    return 0;

}

void GLWindow::processInput(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
        glfwSetWindowShouldClose(window,true);
}

//当窗口大小改变时，回调该函数
void GLWindow::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    //确保视口大小与新窗口匹配
    glViewport(0,0,width,height);
}

void GLWindow::SetShader(const char* VS,const char* FS)
{
    vsPath = VS;
    fsPath = FS;
}



