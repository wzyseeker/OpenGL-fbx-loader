
#version 400 core

layout( location = 0 ) in vec4 vPosition;
out vec4 gl_Position;

void
main()
{
    gl_Position = vPosition;
}
