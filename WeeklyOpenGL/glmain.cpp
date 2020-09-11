#include "glwindow.h"

int main()
{
    GLWindow* glwindow = new GLWindow(800,600);
    glwindow->SetShader("../shader/vert.vs","../shader/frag.fs");
    glwindow->TickWindow();
    return 0;
}

#include <QtOpenGL/QtOpenGL>
