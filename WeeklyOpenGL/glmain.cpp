#include "glwindow.h"


int main()
{
    GLWindow* glwindow = new GLWindow(800,600);
    glwindow->InitWindow();
    glwindow->BindCallback(glwindow);
    glwindow->SetShader("../shader/coordinate_system.vs","../shader/coordinate_system.fs");
    glwindow->TickWindow();
    return 0;
}

#include <QtOpenGL/QtOpenGL>
