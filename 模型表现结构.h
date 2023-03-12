#pragma once
#include<glm\glm.hpp>

using namespace std;
using namespace glm;

struct S材质 
{
	vec4 漫反射;
	vec3 自发光;
	vec3 环境光;
	float 光泽度;
	float 高光级别;
	float 不透明度;

	S材质() { ZeroMemory(this, sizeof(S材质)); }
	~S材质() {  };
};

struct S材质索引
{
	GLint 漫反射;
	GLint 自发光;
	GLint 环境光;
	GLint 光泽度;
	GLint 高光级别;
	GLint 不透明度;

	S材质索引() { ZeroMemory(this, sizeof(S材质索引)); }
	~S材质索引() {  };
};

struct S方向光源 
{
	vec4 颜色;
	vec3 方向;

	S方向光源() { ZeroMemory(this, sizeof(S方向光源)); }
	~S方向光源() {  };
};

struct S方向光源索引
{
	GLint 颜色;
	GLint 方向;

	S方向光源索引() { ZeroMemory(this, sizeof(S方向光源索引)); }
	~S方向光源索引() {  };
};