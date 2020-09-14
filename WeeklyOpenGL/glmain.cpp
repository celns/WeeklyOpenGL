#include "glwindow.h"


int main()
{
    GLWindow* glwindow = new GLWindow(800,600);
    glwindow->SetShader("../shader/coordinate_system.vs","../shader/coordinate_system.fs");
    glwindow->TickWindow();
    return 0;
}

#include <QtOpenGL/QtOpenGL>
