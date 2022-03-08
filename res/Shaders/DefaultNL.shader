#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aText;
layout(location = 2) in vec3 aNormal;

out vec2 TexCoords;

uniform mat4 u_VP;
uniform mat4 u_M;

void main()
{
    vec3 FragPos = vec3(u_M * vec4(aPos, 1.0));
    vec3 Normal = mat3(transpose(inverse(u_M))) * aNormal;
    TexCoords = aText;
    gl_Position = u_VP * vec4(FragPos, 1.0);
}

#shader fragment
#version 330 core
out vec4 FragColor;

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

in vec2 TexCoords;

uniform Material material;
uniform vec3 ambient;

void main()
{
    vec3 ambient = ambient * texture(material.diffuse, TexCoords).rgb;

    //diffuse
    vec3 diffuse = texture(material.diffuse, TexCoords).rgb;

    //specular
    float spec = material.shininess;
    vec3 specular = spec * texture(material.specular, TexCoords).rgb;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}