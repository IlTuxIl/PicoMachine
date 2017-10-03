#version 330

#ifdef VERTEX_SHADER

layout(location= 0) in vec3 position;
uniform mat4 mvpMatrix;

uniform mat4 mvMatrix;
out vec3 vertex_position;

layout(location= 1) in vec2 texcoord;
out vec2 vertex_texcoord;

layout(location= 2) in vec3 normal;
uniform mat4 normalMatrix;
out vec3 vertex_normal;

void main( )
{
    gl_Position= mvpMatrix * vec4(position, 1);
    vertex_position= vec3(mvMatrix * vec4(position, 1));
    vertex_texcoord= texcoord;
    vertex_normal= mat3(normalMatrix) * normal;
}
#endif


#ifdef FRAGMENT_SHADER

in vec2 vertex_texcoord;
uniform sampler2D diffuse_color;
in vec3 vertex_position;
in vec3 vertex_normal;

uniform vec3 lightSource1;
uniform vec3 lightSource2;

uniform vec3 lightDir1;
uniform vec3 lightDir2;

uniform vec4 mesh_color;
out vec4 fragment_color;

void main( )
{
    vec4 color= mesh_color;

    color = color * texture(diffuse_color, vertex_texcoord);
    vec4 maxIllum = color * 1.2f;
    vec3 normal= vec3(0, 0, 1);
    normal= normalize(vertex_normal);
    vec3 t= normalize(dFdx(vertex_position));
    vec3 b= normalize(dFdy(vertex_position));
    normal= normalize(cross(t, b));

    float cos_theta= 0.25 * normal.z;
    float d1 = length(lightSource1 - vertex_position.xyz);
    float d2 = length(lightSource2 - vertex_position.xyz);
    float a1 = 2.5 / d1;
    float a2 = 2.5 / d2;

    float angle1 = dot(normalize(-(lightSource1 - vertex_position.xyz)), normalize(lightDir1));
    float angle2 = dot(normalize(-(lightSource2 - vertex_position.xyz)), normalize(lightDir2));

    float spotAttenuation1 = 0.0f;
    float spotAttenuation2 = 0.0f;

    if(angle1 >= 0.8){
		spotAttenuation1 = pow(angle1, 2);
	}
    if(angle2 >= 0.8){
        spotAttenuation2 = pow(angle2, 2);
	}
    float att1 = a1 * spotAttenuation1;
    float att2 = a2 * spotAttenuation2;
    float attenuation = max(att1, att2);
    color = min(color * cos_theta * max(attenuation, 0.5), maxIllum);
    fragment_color = color;
}
#endif
