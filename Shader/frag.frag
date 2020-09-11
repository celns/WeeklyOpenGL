//uniform sampler2D qt_Texture0;
//varying vec4 qt_TexCoord0;

//void main(void)
//{
//    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
//}
#version 330 core
out vec4 FragColor

in vec4 vertexColor;

void main()
{
    FragColor = vertexColor;
}
