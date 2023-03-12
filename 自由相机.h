#pragma once
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include"�������.h"

using namespace glm;

class C�������
{
public:
    void ���(mat4* �۲����, vec3 ��ʼ�Ϸ���, vec3 ��ʼǰ����, vec3 ��ʼ����, float ת��������, float �ƶ��ٶ�);
    C�������(S����* ����)
    {
        this->���� = ����;
    };
    ~C�������() {};

    vec3 ǰ���� = { 0.0f, 0.0f, 1.0f };
    vec3 �Ϸ��� = { 0.0f, 1.0f, 0.0f };
    vec3 �ҷ��� = { 1.0f, 0.0f, 0.0f };
    vec3 ������� = { 0.0f, 0.0f, 0.0f };
    S����* ����;

private:
    vec3 ����ǰ���� = { 0.0f, 0.0f, 0.0f };
    vec3 ������ = { 0.0f, 0.0f, 0.0f };

    float ת�������ȴ��� = 0;
    bool ��ʼ�� = 1;
};

class C�������
{
public:
    void ���(mat4* �۲����, vec3 ������, vec3 ����ǰ����, vec3 ��ʼ����, float ת��������, float �ƶ��ٶ�);
    C�������(S����* ����)
    {
        this->���� = ����;
    }
    ~C�������() {};

    vec3 ǰ���� = { 0.0f, 0.0f, 1.0f };
    vec3 �Ϸ��� = { 0.0f, 1.0f, 0.0f };
    vec3 �ҷ��� = { 1.0f, 0.0f, 0.0f };
    vec3 ������� = { 0.0f, 0.0f, 0.0f };
    S����* ����;

private:
    vec3 ������ = { 0.0f, 0.0f, 0.0f };
    vec3 ����ǰ���� = { 0.0f, 0.0f, 0.0f };
    vec3 �����ᴢ�� = { 0.0f, 0.0f, 0.0f };
    vec3 ������ǰ���� = { 0.0f, 0.0f, 0.0f };
    vec3 ��λ�����ᴢ�� = { 0.0f, 0.0f, 0.0f };
    vec3 ��ת���� = { 0.0f, 0.0f, 0.0f };
    vec3 ����ǰ���� = { 0.0f, 0.0f, 0.0f };
    float ת�������ȴ��� = 0;
    float ǰ�ؽǶ�cos = 0;
    float ǰ�ؽǶ�sin = 0;
    float ��ת�������� = 0;
    bool ��ʼ�� = 1;
};

class C�����˳����
{
public:
    void ���(mat4* �۲����);
    C�����˳����(S����* ����, float Phi, float Theta, float ��ʼ�뾶, float ת��������, float �ƶ��ٶ�, float ����������, vec3 ����)
    {
        this->���� = ����;
        this->Phi = Phi;
        this->Theta = Theta;
        this->�뾶 = ��ʼ�뾶;
        this->�ƶ��ٶ� = �ƶ��ٶ�;
        this->ת�������� = ת��������;
        this->������ = ����;
        this->���������� = ����������;
    }
    ~C�����˳����() {};

    vec3 ������� = { 0.0f, 0.0f, -40.0f };
    float Phi = 0;
    float Theta = 0;
    float �뾶 = 40;
    S����* ����;
    float �ƶ��ٶ� = 0;
    float ת�������� = 0;
    float ���������� = 0;

private:
    vec3 ������ = { 0.0f, 0.0f, 0.0f };
    vec3 ǰ���� = { 0.0f, 0.0f, 1.0f };
    vec3 �Ϸ��� = { 0.0f, 1.0f, 0.0f };
    vec3 �ҷ��� = { 1.0f, 0.0f, 0.0f };
    vec3 �ƶ����� = { 0.0f, 0.0f, 0.0f };
    float ��ת�� = 0;
    float ����� = 0;
    mat4 �任 = mat4(1.0f);
};