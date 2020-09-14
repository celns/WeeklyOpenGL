#include "glwindow.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



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
        //positions        //colors         //texture coords
        0.5f,0.5f,0.0f,    1.0f,0.0f,0.0f,  1.0f,1.0f,
        0.5f,-0.5f,0.0f,    0.0f,1.0f,0.0f,  1.0f,0.0f,
        -0.5f,-0.5f,0.0f,   0.0f,0.0f,1.0f,  0.0f, 0.0f,
        -0.5f,0.5f,0.0f,     1.0f,1.0f,0.0f,  0.0f, 1.0f
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

    //顶点属性
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    //颜色属性
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //纹理颜色
    glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //载入并创建纹理
    unsigned int texture1, texture2;
    //texture1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    //设置texture的wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置texture的filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //载入图片，创建texture并生成mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../Textures/container.jpg",&width,&height,&nrChannels,0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout<<"Failed to load texture"<<endl;
    }
    stbi_image_free(data);

    //texture2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    //设置texture的wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //设置texture的filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("../Textures/awesomeface.png",&width, &height, &nrChannels, 0);
    if(data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout<<"Failed to load texture"<<endl;
    }
    stbi_image_free(data);

    shader->Use();
    //glUniform1i(glGetUniformLocation(shader->ID, "texture1"), 0);

    shader->SetInt("texture2", 1);
    shader->SetInt("texture2", 1);

    //渲染循环
    while(!glfwWindowShouldClose(window))
    {
        //处理输入
        processInput(window);

        //渲染指令
        glClearColor(0.2f,0.2f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //texture绑定
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //激活shader
        shader->Use();

        //transformations
        //initialize matrix
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f),glm::vec3(1.f, 0.f,0.f));
        view = glm::translate(view, glm::vec3(0.0f, 0.f, -3.f));
        projection = glm::perspective(glm::radians(45.f), (float)SCR_WIDTH/(float)SCR_HEIGHT, 0.1f, 100.f);
        //定位uniformLocation
        unsigned int modeLoc = glGetUniformLocation(shader->ID, "model");
        unsigned int viewLoc = glGetUniformLocation(shader->ID, "view");
        //传值到shader
        glUniformMatrix4fv(modeLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        shader->SetMat4("projection", projection);


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



