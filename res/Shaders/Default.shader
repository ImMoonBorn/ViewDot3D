#shader vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aText;
layout(location = 2) in vec3 aNormal;

out vec3 FragPos;
out vec2 TexCoords;
out vec3 Normal;

uniform mat4 u_VP;
uniform mat4 u_M;

void main()
{
    FragPos = vec3(u_M * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(u_M))) * aNormal;
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

struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float lineer;
    float quadratic;
};

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;

uniform Material material;
uniform Light light;
uniform vec3 u_CameraPos;

void main()
{
    //ambient
    vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

    //specular
    vec3 viewDir = normalize(u_CameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

    //attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.lineer * distance + light.quadratic * (distance * distance));

    diffuse *= attenuation;
    specular *= attenuation;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}