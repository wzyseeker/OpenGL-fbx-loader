#pragma once
#include<glm\glm.hpp>

using namespace std;
using namespace glm;

struct S���� 
{
	vec4 ������;
	vec3 �Է���;
	vec3 ������;
	float �����;
	float �߹⼶��;
	float ��͸����;

	S����() { ZeroMemory(this, sizeof(S����)); }
	~S����() {  };
};

struct S��������
{
	GLint ������;
	GLint �Է���;
	GLint ������;
	GLint �����;
	GLint �߹⼶��;
	GLint ��͸����;

	S��������() { ZeroMemory(this, sizeof(S��������)); }
	~S��������() {  };
};

struct S�����Դ 
{
	vec4 ��ɫ;
	vec3 ����;

	S�����Դ() { ZeroMemory(this, sizeof(S�����Դ)); }
	~S�����Դ() {  };
};

struct S�����Դ����
{
	GLint ��ɫ;
	GLint ����;

	S�����Դ����() { ZeroMemory(this, sizeof(S�����Դ����)); }
	~S�����Դ����() {  };
};