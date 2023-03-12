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
#include"模型特征定义.h"
#include"模型表现结构.h"
#include"网格属性.h"
#include"共享资源.h"

using namespace std;
using namespace glm;

class C动态物体
{
public:
	struct S动画帧
	{
		int 骨骼数量;

		S动画帧() 
		{
			骨骼数量 = 0;
		};
	};
	struct S动画轨道
	{
		wstring 轨道名称;
		float 原始时长;
		float 当前时间;
		float 速度;
		int 帧索引;
		bool 是否循环;
		bool 是否结束;
		float 帧位;
		vector<S动画帧> 帧;

		S动画轨道()
		{
			轨道名称 = L"";
			原始时长 = 0;
			当前时间 = 0;
			速度 = 1.0f;
			是否循环 = 1;
			是否结束 = 0;
			帧位 = 0;
			帧索引 = 0;
		};
	};

	wstring 物体名称 = L"";
	C网格属性* 属性 = nullptr;

	int 顶点单元大小 = 0;
	int 顶点数量 = 0;
	int 顶点布局 = 0;
	int 骨骼数量 = 0;
	GLuint 顶点缓存 = 0;
	GLuint 顶点对象 = 0;
	GLuint 骨骼缓存 = 0;

	vector<S动画轨道> 动画轨道;
	UINT 当前轨道 = 0;
	//mat4 骨骼变换[200];
	//mat4* 物体变换;

	int 加载fbx文件(wstring 文件路径, wstring 物体名称);
	int 加载mdd文件(wstring 文件路径, wstring 物体名称);
	int 生成mdd文件(wstring 文件路径);

	void 体素化(float 体素粒度);

	void 绘制网格(UINT 属性);
	//mat4* 获取当前骨骼变换();
	//mat4* 获取当前物体变换();
	int 获取骨骼偏移();
	float 获取当前帧位();

	void 设定动画速度(UINT 轨道, float 速度倍数);
	void 设定动画轨道(UINT 轨道);
	void 设定轨道帧位置(UINT 轨道, float 百分比);
	void 设定播放模式(UINT 轨道, bool 是否循环);
	bool 检测动画结束(UINT 轨道);
	void 更新时间(float 时间变化);

	void 清除备用资料();//使用加载fbx文件后若不导出为mdd文件即可清除备用资料

	C动态物体(C共享资源* 共享资源);
	~C动态物体();

private:
	//fbx动画信息
	//规定索引为255时没有骨骼
	struct S顶点
	{
		vec3 位置;
		vec3 法向量;
		vec2 纹理坐标;
		float 顶点权重[3];
		char 关联骨骼索引[4];

		S顶点()
		{
			ZeroMemory(this, sizeof(S顶点));
			顶点权重[0] = 1.0f;
		};
		~S顶点() {  };
	};
	struct S备用资料
	{
		vector<S顶点> 顶点集;
		vector<wstring> 路径集;

		S备用资料() {};
		~S备用资料()
		{
		};
	};
	struct S物体控制顶点
	{
		wstring 物体名称;
		vector<vector<S顶点>> 控制顶点集;

		S物体控制顶点()
		{
			物体名称 = L"";
		};
		~S物体控制顶点()
		{
		};
	};
	struct S变换节点
	{
		S变换节点* 子节点;
		S变换节点* 父节点;
		UINT 子节点数量;
		wstring 节点名称;

		S变换节点()
		{
			子节点 = 0;
			父节点 = 0;
			子节点数量 = 0;
			节点名称 = L"";
		};
		~S变换节点()
		{
			if (子节点) delete[] 子节点;
		};
	};
	struct S骨骼数据
	{
		vector<uint> 索引组;
		vector<float> 权重组;
		wstring 骨骼名称;
		mat4 参考全局初始变换;
		mat4 关联全局初始变换;
		mat4 簇全局初始变换;

		S骨骼数据()
		{
			骨骼名称 = L"";
		};
		~S骨骼数据() { };
	};
	struct S物体蒙皮数据
	{
		wstring 物体名称;
		vector<S骨骼数据> 骨骼;

		S物体蒙皮数据()
		{
			物体名称 = L"";
		};
		~S物体蒙皮数据()
		{
		}
	};
	struct S蒙皮数据
	{
		vector<S物体蒙皮数据> 关联物体;

		S蒙皮数据() {  };
		~S蒙皮数据() { };
	};
	struct S音轨数据
	{
		wstring 音轨名称;
		UINT 音效数量;

		S音轨数据() { 音效数量 = 0; };
		~S音轨数据() { };
	};
	struct S音效层数据
	{
		wstring 音效层名称;
		vector<S音轨数据> 音轨;

		S音效层数据()
		{
			音效层名称 = L"";
		};
		~S音效层数据()
		{
		};
	};
	struct S动画变换
	{
		mat4 本地变换;
		mat4 全局变换;
		int 帧数;

		S动画变换() 
		{ 
			本地变换 = mat4(1.0f);
			全局变换 = mat4(1.0f);
			帧数 = 0;
		};
		~S动画变换() {  };
	};
	struct S动画物体数据
	{
		wstring 物体名称;
		vector<S动画变换> 变换;

		S动画物体数据()
		{
			物体名称 = L"";
		};
		~S动画物体数据()
		{
		};
	};
	struct S动画层数据
	{
		wstring 动画层名称;
		vector<S动画物体数据> 物体;

		S动画层数据()
		{
			动画层名称 = L"";
		};
		~S动画层数据() { };
	};
	struct S动画片段数据
	{
		wstring 片段名称;
		vector<S动画层数据> 动画层;
		vector<S音效层数据> 音效层;
		int 开始帧;
		int 结束帧;
		int 帧速率;
		FbxTime 起始时间;

		S动画片段数据()
		{
			片段名称 = L"";
			开始帧 = 0;
			结束帧 = 0;
			帧速率 = 0;
			起始时间 = 0;
		};
		~S动画片段数据() { };
	};
	struct S动画数据
	{
		int 开始帧;
		int 结束帧;
		int 帧速率;
		vector<S动画片段数据> 片段;

		S动画数据()
		{
			开始帧 = 0;
			结束帧 = 0;
			帧速率 = 0;
		};
		~S动画数据() { };
	};
	struct S变换节点2
	{
		wstring 节点名称;
		FbxAMatrix 参考全局变换;
		FbxAMatrix 全局变换;

		S变换节点2()
		{
			节点名称 = L"";
		}
	};
	struct S动画帧储存
	{
		vector<mat4> 骨骼变换;
		//vector<mat4> 物体变换;		//物体变换包含属性变换
	};
	struct S动画轨道储存
	{
		wstring 轨道名称;
		float 原始时长;
		float 当前时间;
		float 速度;
		vector<S动画帧储存> 帧;
		bool 是否循环;
		bool 是否结束;
		float 帧位;

		S动画轨道储存()
		{
			轨道名称 = L"";
			原始时长 = 0;
			当前时间 = 0;
			速度 = 1.0f;
			是否循环 = 1;
			是否结束 = 0;
			帧位 = 0;
		};
	};

	vector<vector<vector<S变换节点2>>>* 全局变换根节点 = nullptr;
	S变换节点* 根节点 = nullptr;
	C共享资源* 共享资源 = nullptr;
	S备用资料* 备用资料 = nullptr;
	int 顶点计数 = 0;
	int 索引计数 = 0;
	S蒙皮数据* 蒙皮数据 = nullptr;
	vector<wstring>* 骨骼名称 = nullptr;
	vector<S物体控制顶点>* 物体控制顶点集 = nullptr;
	vector<array<int, 3>>* 三角形索引 = nullptr;
	vector<S顶点>* 连接顶点 = nullptr;
	vector<array<int, 3>>* 索引记录 = nullptr;
	int 物体数量 = 0;
	S动画数据* 动画数据 = nullptr;
	FbxNode* fbx根节点;
	FbxScene* 场景;
	vector<S动画轨道储存>* 动画轨道储存;

	int 偏移 = 0;

	void 加载层次(FbxScene* p场景);
	void 加载层次(FbxNode* p节点, S变换节点* 节点);
	void 加载节点(FbxNode* p节点);
	void 加载网格(FbxNode* p网格节点);
	void 加载材质(FbxNode* p网格节点, C网格属性::S属性* 属性);
	void 加载材质属性(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性);
	void 加载纹理(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性);
	void 加载蒙皮信息(FbxNode* p网格节点);
	FbxAMatrix 获取全局位置矩阵(FbxNode* 节点, const FbxTime& 时间, FbxPose* 姿势, FbxAMatrix* 父全局位置矩阵);
	int 合并顶点蒙皮();
	void 搜索骨骼树(wstring 骨骼名称, S变换节点*& 目标节点);
	void 搜索骨骼树(S变换节点* 变换节点, wstring 骨骼名称, S变换节点*& 目标节点);
	void 补充骨骼树();
	void 遍历骨骼树(S变换节点* p骨骼节点);
	S变换节点* 回溯根节点(S变换节点* p骨骼节点);
	void 加载骨骼数据(FbxNode* p骨骼节点);
	void 生成骨骼缓存();

	void 计算簇变形(FbxAMatrix& 全局变换, FbxMesh* 网格, FbxCluster* 簇, FbxAMatrix& 顶点变换,
		FbxTime 时间, FbxPose* 造型);
	FbxAMatrix 获取全局变换(FbxNode* 节点, const FbxTime& 时间, FbxAMatrix* 父全局变换 = nullptr);
	FbxAMatrix 获取造型矩阵(FbxPose* 造型, int 节点索引);
	FbxAMatrix 获取几何体(FbxNode* 节点);
	void 计算线性变形(FbxAMatrix& 全局变换, FbxMesh* 网格, FbxTime& 时间, FbxVector4* 顶点, FbxPose* 造型);
	void 计算皮肤变形(FbxAMatrix& 全局变换, FbxMesh* 网格, FbxTime& 时间, FbxVector4* 顶点数组, FbxPose* 造型);
	void 加载动画节点(FbxNode* p节点);

	void 加载动画(FbxScene* p场景);
	void 加载动画片段(FbxAnimStack* p动画片段, FbxNode* p节点, UINT 片段索引);
	void 加载动画层(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引);
	void 加载动画通道(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引, UINT 模型索引);
	void 加载音效层(FbxAudioLayer* p音效层, UINT 音效层索引, UINT 片段索引);
	void 合并物体动画信息();

	void 加载变换节点(FbxNode* p节点, FbxTime 时间, FbxAMatrix* 全局变换, int 片段索引, int 帧);
	void 加载网格(FbxNode* p节点, FbxTime 时间, FbxAMatrix* 全局变换, int 片段索引, int 帧);

	mat4 fbx矩阵转mat4(FbxAMatrix fbx矩阵);
};