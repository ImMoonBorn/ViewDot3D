#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;

uniform mat4 u_VP;
uniform mat4 u_M;

void main()
{
    gl_Position = u_VP * u_M * vec4(aPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0);
}