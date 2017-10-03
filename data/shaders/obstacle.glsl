#version 330

#ifdef VERTEX_SHADER

layout(location= 0) in vec3 position;
uniform mat4 mvpMatrix;

uniform mat4 mvMatrix;
out vec3 vertex_position;

#ifdef USE_TEXCOORD
    layout(location= 1) in vec2 texcoord;
    out vec2 vertex_texcoord;
#endif

#ifdef USE_NORMAL
    layout(location= 2) in vec3 normal;
    uniform mat4 normalMatrix;
    out vec3 vertex_normal;
#endif

#ifdef USE_COLOR
    layout(location= 3) in vec4 color;
    out vec4 vertex_color;
#endif


void main( )
{
    gl_Position= mvpMatrix * vec4(position, 1);

    vertex_position= vec3(mvMatrix * vec4(position, 1));

#ifdef USE_TEXCOORD
    vertex_texcoord= texcoord;
#endif

#ifdef USE_NORMAL
    vertex_normal= mat3(normalMatrix) * normal;
#endif

#ifdef USE_COLOR
    vertex_color= color;
#endif
}
#endif


#ifdef FRAGMENT_SHADER

#ifdef USE_TEXCOORD
    in vec2 vertex_texcoord;
    uniform sampler2D diffuse_color;
#endif

#ifdef USE_ALPHATEST
    uniform float alpha_min= 0.3;
#endif

in vec3 vertex_position;

#ifdef USE_NORMAL
    in vec3 vertex_normal;
#endif

#ifdef USE_COLOR
    in vec4 vertex_color;
#endif

#ifdef USE_LIGHT
uniform vec3 light;
uniform vec4 light_color;
#endif

uniform vec4 mesh_color;

out vec4 fragment_color;
uniform vec3 lightSource1;
uniform vec3 lightDir1;
uniform vec3 lightSource2;
uniform vec3 lightDir2;


void main( )
{
    vec4 color= mesh_color;
    color= color * texture(diffuse_color, vertex_texcoord);


    vec3 normal= vec3(0, 0, 1);
    float cos_theta = 0.2 * normal.z;// normal.z;

    float d1 = length(lightSource1 - vertex_position.xyz);
    float a1 = 2.5 / d1;
    float angle1 = dot(normalize(-(lightSource1 - vertex_position.xyz)), normalize(lightDir1));
    float spotAttenuation1 = 0.0f;
    if(angle1 >= 0.8)
        spotAttenuation1 = pow(angle1, 2);
    float att1 = a1 * spotAttenuation1;

    float d2 = length(lightSource2 - vertex_position.xyz);
    float a2 = 2.5 / d2;
    float angle2 = dot(normalize(-(lightSource2 - vertex_position.xyz)), normalize(lightDir2));
    float spotAttenuation2 = 0.0f;
    if(angle2 >= 0.8)
        spotAttenuation2 = pow(angle2, 2);
    float att2 = a2 * spotAttenuation2;

    color.rgb= color.rgb * cos_theta * max(max(att1, att2), 0.5);

    fragment_color= color;
}
#endif
