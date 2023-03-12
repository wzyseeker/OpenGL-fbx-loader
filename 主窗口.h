#pragma once
#include<glad/glad.h>
#include<GLFW\glfw3.h>
#include<Windows.h>
#include<sstream>
#include"fbx��̬�ļ�����.h"
#include"�������.h"
#include"�������.h"

class C������
{
public:
	int ���ڿ� = 0;
	int ���ڸ� = 0;
	GLFWwindow* ���� = 0;
    string �������� = "fbx loader";

    float aspect = 0.0f;

    GLuint  VAOs = 0;
    GLuint  Buffers = 0;

    GLuint base_prog = 0;
    S�����Դ �����Դ;
    S���� ����;
    mat4 ������� = mat4(1.0f);
    mat4 �۲���� = mat4(1.0f);
    mat4 ͶӰ���� = mat4(1.0f);
    vec3 ���λ�� = vec3(0.0f, 0.0f, 0.0f);
    vec3 ������ = vec3(0.0f, 0.0f, 0.0f);
    vec3 �Ϸ��� = vec3(0.0f, 0.0f, 0.0f);
    unsigned int m_appStartTime = 0;

    mat4* �����任;

    struct S������ɫ������
    {
        S�����Դ���� dlight;
        S�������� mat;
        GLint projview;
        GLint world;
        GLint eyeposw;
        GLint tex;
        GLint bonetransform;
        GLint worldinv;
        GLint bonetransformindex;
        GLint influence;
        GLint bonecount;

        S������ɫ������()
        {
            projview = -1;
            world = -1;
            eyeposw = -1;
            tex = -1;
            bonetransform = -1;
            worldinv = -1;
            bonetransformindex = -1;
            influence = -1;
            bonecount = -1;
        }

    } ������ɫ������;

    S���� ����;
    C��̬����* ��̬���� = 0;
    C������Դ* ������Դ = 0;
    C�����˳����* ��� = 0;

    void ���㿪��״̬();
    static void ��갴�����(GLFWwindow* ����, int ����, int ����, int ģʽ);
    static void �������(GLFWwindow* ����, int ����, int ɨ��ģʽ, int ����, int ģʽ);
    static void ���λ�ü��(GLFWwindow* ����, double λ��x, double λ��y);
    static void ��껬�ּ��(GLFWwindow* ����, double ƫ��x, double ƫ��y);

    int ��ʼ��();
    void ��ʾ(float dt);
    void �ͷ�();
    int ������ɫ��(wstring filepath, GLuint prog, GLenum type);
    int ���ӳ���(GLuint program);
	int ������();
    float ��ȡʱ��仯();

};