#pragma once
#include<string>
#include<vector>
#include<map>
#include<glad/glad.h>
#include<SOIL2/SOIL2.h>
#include"模型特征定义.h"
#include"模型表现结构.h"
#include"共享资源.h"

using namespace std;
using namespace glm;

struct S拾取输出
{
	uint 是否拾取;
	float 距离;

	S拾取输出() {
		是否拾取 = 0;
		距离 = 0;
	}
	~S拾取输出() {};
};

//网格属性----------------------------------------------------------------
class C网格属性
{
public:
	struct S包围框
	{
		vec3 左下前位置;
		vec3 长宽高;
		UINT 所属;

		S包围框()
		{
			ZeroMemory(this, sizeof(S包围框));
		};
		~S包围框() {};
	};

	struct S属性
	{
		wstring 物体名称;
		UINT 起始顶点;
		UINT 顶点数量;
		mat4 变换;
		UINT 纹理索引;
		UINT 法线图索引;
		S材质 材质;
		UINT 包围框数量;
		GLuint 包围框;
		GLuint 拾取输出;
		GLuint 包围球;

		S属性()
		{
			起始顶点 = 0;
			顶点数量 = 0;
			变换 = mat4(1.0);
			纹理索引 = 0;
			法线图索引 = 0;
			包围框 = 0;
			包围框数量 = 0;
			拾取输出 = 0;
			包围球 = 0;
		};
		~S属性()
		{

		};
	};

	vector<S属性*> 元素;
	vector<C共享资源::S纹理> 纹理集;
	vector<C共享资源::S纹理> 法线贴图集;

	C共享资源::S纹理 贴图(UINT 索引);
	C共享资源::S纹理 法线贴图(UINT 索引);
	void 添加元素(S属性* 属性);

	~C网格属性();
};
