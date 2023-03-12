#pragma once
#include<vector>
#include<array>
#include<map>
#include<fstream>
#include<string>
#include<random>
#include<thread>
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<SOIL2/SOIL2.h>
#include<fbxsdk.h>
#include"ģ����������.h"
#include"ģ�ͱ��ֽṹ.h"
#include"��������.h"
#include"������Դ.h"

using namespace std;
using namespace glm;

class C��̬����
{
public:
	struct S����֡
	{
		int ��������;

		S����֡() 
		{
			�������� = 0;
		};
	};
	struct S�������
	{
		wstring �������;
		float ԭʼʱ��;
		float ��ǰʱ��;
		float �ٶ�;
		int ֡����;
		bool �Ƿ�ѭ��;
		bool �Ƿ����;
		float ֡λ;
		vector<S����֡> ֡;

		S�������()
		{
			������� = L"";
			ԭʼʱ�� = 0;
			��ǰʱ�� = 0;
			�ٶ� = 1.0f;
			�Ƿ�ѭ�� = 1;
			�Ƿ���� = 0;
			֡λ = 0;
			֡���� = 0;
		};
	};

	wstring �������� = L"";
	C��������* ���� = nullptr;

	int ���㵥Ԫ��С = 0;
	int �������� = 0;
	int ���㲼�� = 0;
	int �������� = 0;
	GLuint ���㻺�� = 0;
	GLuint ������� = 0;
	GLuint �������� = 0;

	vector<S�������> �������;
	UINT ��ǰ��� = 0;
	//mat4 �����任[200];
	//mat4* ����任;

	int ����fbx�ļ�(wstring �ļ�·��, wstring ��������);
	int ����mdd�ļ�(wstring �ļ�·��, wstring ��������);
	int ����mdd�ļ�(wstring �ļ�·��);

	void ���ػ�(float ��������);

	void ��������(UINT ����);
	//mat4* ��ȡ��ǰ�����任();
	//mat4* ��ȡ��ǰ����任();
	int ��ȡ����ƫ��();
	float ��ȡ��ǰ֡λ();

	void �趨�����ٶ�(UINT ���, float �ٶȱ���);
	void �趨�������(UINT ���);
	void �趨���֡λ��(UINT ���, float �ٷֱ�);
	void �趨����ģʽ(UINT ���, bool �Ƿ�ѭ��);
	bool ��⶯������(UINT ���);
	void ����ʱ��(float ʱ��仯);

	void �����������();//ʹ�ü���fbx�ļ�����������Ϊmdd�ļ����������������

	C��̬����(C������Դ* ������Դ);
	~C��̬����();

private:
	//fbx������Ϣ
	//�涨����Ϊ255ʱû�й���
	struct S����
	{
		vec3 λ��;
		vec3 ������;
		vec2 ��������;
		float ����Ȩ��[3];
		char ������������[4];

		S����()
		{
			ZeroMemory(this, sizeof(S����));
			����Ȩ��[0] = 1.0f;
		};
		~S����() {  };
	};
	struct S��������
	{
		vector<S����> ���㼯;
		vector<wstring> ·����;

		S��������() {};
		~S��������()
		{
		};
	};
	struct S������ƶ���
	{
		wstring ��������;
		vector<vector<S����>> ���ƶ��㼯;

		S������ƶ���()
		{
			�������� = L"";
		};
		~S������ƶ���()
		{
		};
	};
	struct S�任�ڵ�
	{
		S�任�ڵ�* �ӽڵ�;
		S�任�ڵ�* ���ڵ�;
		UINT �ӽڵ�����;
		wstring �ڵ�����;

		S�任�ڵ�()
		{
			�ӽڵ� = 0;
			���ڵ� = 0;
			�ӽڵ����� = 0;
			�ڵ����� = L"";
		};
		~S�任�ڵ�()
		{
			if (�ӽڵ�) delete[] �ӽڵ�;
		};
	};
	struct S��������
	{
		vector<uint> ������;
		vector<float> Ȩ����;
		wstring ��������;
		mat4 �ο�ȫ�ֳ�ʼ�任;
		mat4 ����ȫ�ֳ�ʼ�任;
		mat4 ��ȫ�ֳ�ʼ�任;

		S��������()
		{
			�������� = L"";
		};
		~S��������() { };
	};
	struct S������Ƥ����
	{
		wstring ��������;
		vector<S��������> ����;

		S������Ƥ����()
		{
			�������� = L"";
		};
		~S������Ƥ����()
		{
		}
	};
	struct S��Ƥ����
	{
		vector<S������Ƥ����> ��������;

		S��Ƥ����() {  };
		~S��Ƥ����() { };
	};
	struct S��������
	{
		wstring ��������;
		UINT ��Ч����;

		S��������() { ��Ч���� = 0; };
		~S��������() { };
	};
	struct S��Ч������
	{
		wstring ��Ч������;
		vector<S��������> ����;

		S��Ч������()
		{
			��Ч������ = L"";
		};
		~S��Ч������()
		{
		};
	};
	struct S�����任
	{
		mat4 ���ر任;
		mat4 ȫ�ֱ任;
		int ֡��;

		S�����任() 
		{ 
			���ر任 = mat4(1.0f);
			ȫ�ֱ任 = mat4(1.0f);
			֡�� = 0;
		};
		~S�����任() {  };
	};
	struct S������������
	{
		wstring ��������;
		vector<S�����任> �任;

		S������������()
		{
			�������� = L"";
		};
		~S������������()
		{
		};
	};
	struct S����������
	{
		wstring ����������;
		vector<S������������> ����;

		S����������()
		{
			���������� = L"";
		};
		~S����������() { };
	};
	struct S����Ƭ������
	{
		wstring Ƭ������;
		vector<S����������> ������;
		vector<S��Ч������> ��Ч��;
		int ��ʼ֡;
		int ����֡;
		int ֡����;
		FbxTime ��ʼʱ��;

		S����Ƭ������()
		{
			Ƭ������ = L"";
			��ʼ֡ = 0;
			����֡ = 0;
			֡���� = 0;
			��ʼʱ�� = 0;
		};
		~S����Ƭ������() { };
	};
	struct S��������
	{
		int ��ʼ֡;
		int ����֡;
		int ֡����;
		vector<S����Ƭ������> Ƭ��;

		S��������()
		{
			��ʼ֡ = 0;
			����֡ = 0;
			֡���� = 0;
		};
		~S��������() { };
	};
	struct S�任�ڵ�2
	{
		wstring �ڵ�����;
		FbxAMatrix �ο�ȫ�ֱ任;
		FbxAMatrix ȫ�ֱ任;

		S�任�ڵ�2()
		{
			�ڵ����� = L"";
		}
	};
	struct S����֡����
	{
		vector<mat4> �����任;
		//vector<mat4> ����任;		//����任�������Ա任
	};
	struct S�����������
	{
		wstring �������;
		float ԭʼʱ��;
		float ��ǰʱ��;
		float �ٶ�;
		vector<S����֡����> ֡;
		bool �Ƿ�ѭ��;
		bool �Ƿ����;
		float ֡λ;

		S�����������()
		{
			������� = L"";
			ԭʼʱ�� = 0;
			��ǰʱ�� = 0;
			�ٶ� = 1.0f;
			�Ƿ�ѭ�� = 1;
			�Ƿ���� = 0;
			֡λ = 0;
		};
	};

	vector<vector<vector<S�任�ڵ�2>>>* ȫ�ֱ任���ڵ� = nullptr;
	S�任�ڵ�* ���ڵ� = nullptr;
	C������Դ* ������Դ = nullptr;
	S��������* �������� = nullptr;
	int ������� = 0;
	int �������� = 0;
	S��Ƥ����* ��Ƥ���� = nullptr;
	vector<wstring>* �������� = nullptr;
	vector<S������ƶ���>* ������ƶ��㼯 = nullptr;
	vector<array<int, 3>>* ���������� = nullptr;
	vector<S����>* ���Ӷ��� = nullptr;
	vector<array<int, 3>>* ������¼ = nullptr;
	int �������� = 0;
	S��������* �������� = nullptr;
	FbxNode* fbx���ڵ�;
	FbxScene* ����;
	vector<S�����������>* �����������;

	int ƫ�� = 0;

	void ���ز��(FbxScene* p����);
	void ���ز��(FbxNode* p�ڵ�, S�任�ڵ�* �ڵ�);
	void ���ؽڵ�(FbxNode* p�ڵ�);
	void ��������(FbxNode* p����ڵ�);
	void ���ز���(FbxNode* p����ڵ�, C��������::S����* ����);
	void ���ز�������(FbxSurfaceMaterial* p�������, C��������::S����* ����);
	void ��������(FbxSurfaceMaterial* p�������, C��������::S����* ����);
	void ������Ƥ��Ϣ(FbxNode* p����ڵ�);
	FbxAMatrix ��ȡȫ��λ�þ���(FbxNode* �ڵ�, const FbxTime& ʱ��, FbxPose* ����, FbxAMatrix* ��ȫ��λ�þ���);
	int �ϲ�������Ƥ();
	void ����������(wstring ��������, S�任�ڵ�*& Ŀ��ڵ�);
	void ����������(S�任�ڵ�* �任�ڵ�, wstring ��������, S�任�ڵ�*& Ŀ��ڵ�);
	void ���������();
	void ����������(S�任�ڵ�* p�����ڵ�);
	S�任�ڵ�* ���ݸ��ڵ�(S�任�ڵ�* p�����ڵ�);
	void ���ع�������(FbxNode* p�����ڵ�);
	void ���ɹ�������();

	void ����ر���(FbxAMatrix& ȫ�ֱ任, FbxMesh* ����, FbxCluster* ��, FbxAMatrix& ����任,
		FbxTime ʱ��, FbxPose* ����);
	FbxAMatrix ��ȡȫ�ֱ任(FbxNode* �ڵ�, const FbxTime& ʱ��, FbxAMatrix* ��ȫ�ֱ任 = nullptr);
	FbxAMatrix ��ȡ���;���(FbxPose* ����, int �ڵ�����);
	FbxAMatrix ��ȡ������(FbxNode* �ڵ�);
	void �������Ա���(FbxAMatrix& ȫ�ֱ任, FbxMesh* ����, FbxTime& ʱ��, FbxVector4* ����, FbxPose* ����);
	void ����Ƥ������(FbxAMatrix& ȫ�ֱ任, FbxMesh* ����, FbxTime& ʱ��, FbxVector4* ��������, FbxPose* ����);
	void ���ض����ڵ�(FbxNode* p�ڵ�);

	void ���ض���(FbxScene* p����);
	void ���ض���Ƭ��(FbxAnimStack* p����Ƭ��, FbxNode* p�ڵ�, UINT Ƭ������);
	void ���ض�����(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������);
	void ���ض���ͨ��(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������, UINT ģ������);
	void ������Ч��(FbxAudioLayer* p��Ч��, UINT ��Ч������, UINT Ƭ������);
	void �ϲ����嶯����Ϣ();

	void ���ر任�ڵ�(FbxNode* p�ڵ�, FbxTime ʱ��, FbxAMatrix* ȫ�ֱ任, int Ƭ������, int ֡);
	void ��������(FbxNode* p�ڵ�, FbxTime ʱ��, FbxAMatrix* ȫ�ֱ任, int Ƭ������, int ֡);

	mat4 fbx����תmat4(FbxAMatrix fbx����);
};