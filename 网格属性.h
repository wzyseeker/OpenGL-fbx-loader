#pragma once
#include<string>
#include<vector>
#include<map>
#include<glad/glad.h>
#include<SOIL2/SOIL2.h>
#include"ģ����������.h"
#include"ģ�ͱ��ֽṹ.h"
#include"������Դ.h"

using namespace std;
using namespace glm;

struct Sʰȡ���
{
	uint �Ƿ�ʰȡ;
	float ����;

	Sʰȡ���() {
		�Ƿ�ʰȡ = 0;
		���� = 0;
	}
	~Sʰȡ���() {};
};

//��������----------------------------------------------------------------
class C��������
{
public:
	struct S��Χ��
	{
		vec3 ����ǰλ��;
		vec3 �����;
		UINT ����;

		S��Χ��()
		{
			ZeroMemory(this, sizeof(S��Χ��));
		};
		~S��Χ��() {};
	};

	struct S����
	{
		wstring ��������;
		UINT ��ʼ����;
		UINT ��������;
		mat4 �任;
		UINT ��������;
		UINT ����ͼ����;
		S���� ����;
		UINT ��Χ������;
		GLuint ��Χ��;
		GLuint ʰȡ���;
		GLuint ��Χ��;

		S����()
		{
			��ʼ���� = 0;
			�������� = 0;
			�任 = mat4(1.0);
			�������� = 0;
			����ͼ���� = 0;
			��Χ�� = 0;
			��Χ������ = 0;
			ʰȡ��� = 0;
			��Χ�� = 0;
		};
		~S����()
		{

		};
	};

	vector<S����*> Ԫ��;
	vector<C������Դ::S����> ����;
	vector<C������Դ::S����> ������ͼ��;

	C������Դ::S���� ��ͼ(UINT ����);
	C������Դ::S���� ������ͼ(UINT ����);
	void ���Ԫ��(S����* ����);

	~C��������();
};
