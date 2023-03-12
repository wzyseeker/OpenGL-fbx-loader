#version 450 core

layout(location = 0) in vec3 vposition;
layout(location = 1) in vec3 vnormal;
layout(location = 2) in vec2 vtexuv;
layout(location = 3) in vec3 vboneweight;
layout(location = 4) in ivec4 vboneindex;
out vec4 gl_Position;
out vec3 fposw;
out vec3 fnormalw;
out vec2 ftexuv;

uniform mat4 projview;
uniform mat4 world;
layout(binding = 0) buffer Sbonetransform
{
    mat4 bonetransrom[];
};
uniform int bonetransformindex;
uniform float influence;
uniform int bonecount;
//uniform mat4 bonetransform[200];

int MAXBONENUM = 4;

void main()
{
    mat4 transform = mat4(0.0f);

    float bweight[4] = { vboneweight.x, vboneweight.y, vboneweight.z, 0.0f };
    bweight[3] = 1.0f - vboneweight.x - vboneweight.y - vboneweight.z;
    int bindex[4] = { vboneindex.x, vboneindex.y, vboneindex.z, vboneindex.w };

    for (int i = 0; i < MAXBONENUM; i++)
        transform += bweight[i] * ((1.0f - influence) * bonetransrom[bonetransformindex + bindex[i]] 
            + influence * bonetransrom[bonetransformindex + bindex[i] + bonecount]);

    //for (int i = 0; i < MAXBONENUM; i++)
    //    transform += bweight[i] * bonetransform[bindex[i]];
    
    fnormalw = mat3(world * transform) * vnormal;
    vec3 fposw = (world * transform * vec4(vposition, 1.0f)).xyz;
    gl_Position = projview * vec4(fposw, 1.0f);
    ftexuv = vtexuv;
}