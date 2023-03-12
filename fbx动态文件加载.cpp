#include"fbx动态文件加载.h"

C动态物体::C动态物体(C共享资源* 共享资源)
{
	this->共享资源 = 共享资源;
}

int C动态物体::加载fbx文件(wstring 文件路径, wstring 物体名称)
{
    int 结果 = 0;
    UINT j = 0;
    FbxManager* lFBX管理 = NULL;
    FbxScene* l场景 = NULL;

    this->物体名称 = 物体名称;

    lFBX管理 = FbxManager::Create();

    FbxIOSettings* 输入 = FbxIOSettings::Create(lFBX管理, IOSROOT);
    lFBX管理->SetIOSettings(输入);
    FbxImporter* l导入 = FbxImporter::Create(lFBX管理, "");

    char* 文件名字 = 0;
    FbxWCToUTF8(文件路径.c_str(), 文件名字, 0);

    if (!l导入->Initialize(文件名字, -1, 输入))
    {
        string bug = "fbx文件加载-动态物体：fbx导入错误";
        bug += l导入->GetStatus().GetErrorString();
        bug += " line:";
        bug += to_string(__LINE__) + "\n";
        OutputDebugStringA(bug.c_str());
        exit(0);
    }

    l场景 = FbxScene::Create(lFBX管理, "myScene");

    l导入->Import(l场景);
    l导入->Destroy();

    备用资料 = new S备用资料;
    属性 = new C网格属性;
    全局变换根节点 = new vector<vector<vector<S变换节点2>>>;
    根节点 = new S变换节点;
    蒙皮数据 = new S蒙皮数据;
    骨骼名称 = new vector<wstring>;
    物体控制顶点集 = new vector<S物体控制顶点>;
    三角形索引 = new vector<array<int, 3>>;
    连接顶点 = new vector<S顶点>;
    索引记录 = new vector<array<int, 3>>;
    动画数据 = new S动画数据;
    动画轨道储存 = new vector<S动画轨道储存>;
    根节点->节点名称 = L"根节点";
    骨骼名称->push_back(L"");
    FbxNode* l根节点 = l场景->GetRootNode();

    this->属性->纹理集.push_back(共享资源->白贴图);

    if (l根节点)
        for (int i = 0; i < l根节点->GetChildCount(); i++)
            加载节点(l根节点->GetChild(i));
    加载层次(l场景);
    补充骨骼树();
    骨骼数量 = 骨骼名称->size();
    //物体变换 = new mat4[物体数量];

    加载动画(l场景);
    合并物体动画信息();

    if (合并顶点蒙皮())
        return - 1;

    生成骨骼缓存();

    顶点单元大小 = sizeof(S顶点);

    if (备用资料->顶点集.size() == 0)
    {
        wstring bug = L"fbx文件加载-动态物体：无顶点 line:";
        bug += to_wstring(__LINE__) + L"\n";
        OutputDebugString(bug.c_str());
        exit(0);
    }

    顶点数量 = 备用资料->顶点集.size();
    顶点布局 = FVF位置 | FVF法向量 | FVF纹理坐标;

    S顶点* 顶点集 = new S顶点[备用资料->顶点集.size()];
    for (int i = 0; i < 备用资料->顶点集.size(); i++)
        顶点集[i] = 备用资料->顶点集[i];
    
    glCreateVertexArrays(1, &顶点对象);
    glBindVertexArray(顶点对象);

    glCreateBuffers(1, &顶点缓存);
    glBindBuffer(GL_ARRAY_BUFFER, 顶点缓存);
    glBufferData(GL_ARRAY_BUFFER, 备用资料->顶点集.size() * sizeof(S顶点), 顶点集, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)12);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)24);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 12, (void*)32);
    glVertexAttribIPointer(4, 4, GL_BYTE, sizeof(float) * 12, (void*)44);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    
    lFBX管理->Destroy();

    delete[] 顶点集;

    return 结果;
}

void C动态物体::加载层次(FbxScene* p场景)
{
    int i;
    FbxNode* l根节点 = p场景->GetRootNode();
    根节点->子节点数量 = l根节点->GetChildCount();
    if (!根节点->子节点 && 根节点->子节点数量 > 0)
        根节点->子节点 = new S变换节点[l根节点->GetChildCount()];

    for (i = 0; i < l根节点->GetChildCount(); i++)
    {
        if (!根节点->子节点[i].父节点) 根节点->子节点[i].父节点 = 根节点;
        加载层次(l根节点->GetChild(i), &根节点->子节点[i]);
    }
}

void C动态物体::加载层次(FbxNode* p节点, S变换节点* 节点)
{
    WCHAR* l节点名称;
    int i = 0;
    int j = 0;

    FbxUTF8ToWC(p节点->GetName(), l节点名称, 0);
    节点->节点名称 = l节点名称;
    节点->子节点数量 = p节点->GetChildCount();
    if (!节点->子节点 && 节点->子节点数量 > 0)
        if (节点->子节点数量)
            节点->子节点 = new S变换节点[p节点->GetChildCount()];

    for (i = 0; i < p节点->GetChildCount(); i++)
    {
        节点->子节点[i].父节点 = 节点;
        加载层次(p节点->GetChild(i), &节点->子节点[i]);
    }
}

void C动态物体::搜索骨骼树(wstring 骨骼名称, S变换节点*& 目标节点)
{
    int i = 0;

    for (i = 0; i < 根节点->子节点数量; i++)
    {
        搜索骨骼树(&根节点->子节点[i], 骨骼名称, 目标节点);
    }
}

void C动态物体::搜索骨骼树(S变换节点* 变换节点, wstring 骨骼名称, S变换节点*& 目标节点)
{
    int i = 0;

    if (变换节点->节点名称 == 骨骼名称)
    {
        目标节点 = 变换节点;
        return;
    }

    for (i = 0; i < 变换节点->子节点数量; i++)
    {
        搜索骨骼树(&变换节点->子节点[i], 骨骼名称, 目标节点);
    }
}

void C动态物体::补充骨骼树()
{
    S变换节点* p变换节点 = nullptr;
    S变换节点* p变换节点2 = nullptr;

    for (int i = 0; i < (*骨骼名称).size(); i++)
    {
        p变换节点 = nullptr;
        搜索骨骼树((*骨骼名称)[i].c_str(), p变换节点);

        if (p变换节点)
        {
            p变换节点2 = nullptr;
            p变换节点2 = 回溯根节点(p变换节点);
            遍历骨骼树(p变换节点2);
        }
    }
}

C动态物体::S变换节点* C动态物体::回溯根节点(S变换节点* p骨骼节点)
{
    S变换节点* p骨骼节点2 = p骨骼节点;
    if (p骨骼节点2->父节点)
        while (p骨骼节点2->父节点->节点名称 != L"根节点")
        {
            p骨骼节点2 = p骨骼节点2->父节点;
        }

    return p骨骼节点2;
}

void C动态物体::遍历骨骼树(S变换节点* p骨骼节点)
{
    bool 是否未记录 = false;

    是否未记录 = true;
    for (int j = 0; j < (*骨骼名称).size(); j++)
    {
        if ((*骨骼名称)[j].c_str() == p骨骼节点->节点名称)
        {
            是否未记录 = false;
        }
    }
    if (是否未记录)
    {
        (*骨骼名称).push_back(p骨骼节点->节点名称);
    }

    for (int i = 0; i < p骨骼节点->子节点数量; i++)
    {
        遍历骨骼树(&p骨骼节点->子节点[i]);
    }
}

void C动态物体::加载节点(FbxNode* p节点)
{
    FbxNodeAttribute::EType 节点属性{};

    if (p节点->GetNodeAttribute())
    {
        节点属性 = p节点->GetNodeAttribute()->GetAttributeType();

        switch (节点属性)
        {
        case FbxNodeAttribute::eSkeleton:
            加载骨骼数据(p节点);
            break;

        case FbxNodeAttribute::eMesh:
            加载网格(p节点);
            加载蒙皮信息(p节点);
            break;

        default:
            break;
        }
    }

    for (int i = 0; i < p节点->GetChildCount(); ++i)
    {
        加载节点(p节点->GetChild(i));
    }
}

void C动态物体::加载骨骼数据(FbxNode* p骨骼节点)
{
    WCHAR* l骨骼名称 = 0;
    size_t l长度;

    FbxUTF8ToWC(p骨骼节点->GetName(), l骨骼名称, &l长度);

    骨骼数量++;
    (*骨骼名称).resize(骨骼数量);
    (*骨骼名称)[骨骼数量 - 1] = l骨骼名称;
}

void C动态物体::加载网格(FbxNode* p网格节点)
{
    FbxMesh* p网格 = p网格节点->GetMesh();
    if (p网格 == NULL) return;

    vec3 l位置[3]{};
    vec3 l法向量[3]{};
    vec3 l切向量[3]{};
    vec2 l纹理坐标[4]{};
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT l = 0;
    UINT m = 0;
    UINT l多边形数量 = p网格->GetPolygonCount();
    UINT l当前顶点计数 = 0;
    uint l当前索引计数 = 0;
    UINT l多边形顶点数量 = 0;
    UINT l当前索引数量 = 0;
    UINT l骨骼索引计数 = 0;
    int 当前多边形顶点数量;

    for (i = 0; i < l多边形数量; i++)
        当前多边形顶点数量 = p网格->GetPolygonSize(i);

    UINT 控制顶点数量 = p网格->GetControlPointsCount();

    WCHAR* 物体名称;
    FbxUTF8ToWC(p网格节点->GetName(), 物体名称);

    (*物体控制顶点集).resize((*物体控制顶点集).size() + 1);
    (*物体控制顶点集)[(*物体控制顶点集).size() - 1].物体名称 = 物体名称;
    (*物体控制顶点集)[(*物体控制顶点集).size() - 1].控制顶点集.resize(控制顶点数量);

    for (i = 0; i < l多边形数量; i++)
    {
        l多边形顶点数量 = p网格->GetPolygonSize(i);
        for (j = 0; j < l多边形顶点数量; j++)
        {
            int l控制顶点索引 = p网格->GetPolygonVertex(i, j);
            int id;
            FbxVector4* 控制顶点 = p网格->GetControlPoints();
            S顶点 顶点;

            顶点.位置.x = 控制顶点[l控制顶点索引].mData[0];
            顶点.位置.y = 控制顶点[l控制顶点索引].mData[1];
            顶点.位置.z = 控制顶点[l控制顶点索引].mData[2];

            FbxGeometryElementUV* p纹理坐标 = p网格->GetElementUV(0);

            if (p纹理坐标)
                switch (p纹理坐标->GetMappingMode())
                {
                case FbxGeometryElement::eByControlPoint:
                    switch (p纹理坐标->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(l控制顶点索引).mData[0];
                        顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(l控制顶点索引).mData[1];
                        break;

                    case FbxGeometryElement::eIndexToDirect:
                        id = p纹理坐标->GetIndexArray().GetAt(l控制顶点索引);
                        顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(id).mData[0];
                        顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(id).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;

                case FbxGeometryElement::eByPolygonVertex:
                    switch (p纹理坐标->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    case FbxGeometryElement::eIndexToDirect:
                        顶点.纹理坐标.x = p纹理坐标->GetDirectArray().GetAt(p网格->GetTextureUVIndex(i, j)).mData[0];
                        顶点.纹理坐标.y = 1.0f - p纹理坐标->GetDirectArray().GetAt(p网格->GetTextureUVIndex(i, j)).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;
                }

            FbxGeometryElementNormal* p法向量 = p网格->GetElementNormal(0);
            switch (p法向量->GetMappingMode())
            {
            case FbxGeometryElement::eByControlPoint:
                switch (p法向量->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    顶点.法向量.x = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[0];
                    顶点.法向量.y = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[1];
                    顶点.法向量.z = p法向量->GetDirectArray().GetAt(l控制顶点索引).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p法向量->GetIndexArray().GetAt(l控制顶点索引);
                    顶点.法向量.x = p法向量->GetDirectArray().GetAt(id).mData[0];
                    顶点.法向量.y = p法向量->GetDirectArray().GetAt(id).mData[1];
                    顶点.法向量.z = p法向量->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                switch (p法向量->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    顶点.法向量.x = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[0];
                    顶点.法向量.y = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[1];
                    顶点.法向量.z = p法向量->GetDirectArray().GetAt(l当前顶点计数).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p法向量->GetIndexArray().GetAt(l当前顶点计数);
                    顶点.法向量.x = p法向量->GetDirectArray().GetAt(id).mData[0];
                    顶点.法向量.y = p法向量->GetDirectArray().GetAt(id).mData[1];
                    顶点.法向量.z = p法向量->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;
            }

            uint k = 0;

            k = (*物体控制顶点集)[(*物体控制顶点集).size() - 1].控制顶点集[l控制顶点索引].size();
            (*物体控制顶点集)[(*物体控制顶点集).size() - 1].控制顶点集[l控制顶点索引].resize(k + 1);
            (*物体控制顶点集)[(*物体控制顶点集).size() - 1].控制顶点集[l控制顶点索引][k] = 顶点;
            array<int, 3> 数组 = { 物体数量, l控制顶点索引, k };
            索引记录->push_back(数组);
            顶点计数++;
            l当前顶点计数++;
        }

        for (k = 0; k < l多边形顶点数量 - 2; k++)
        {
            (*三角形索引).resize((*三角形索引).size() + 1);
            (*三角形索引)[(*三角形索引).size() - 1][0] = 顶点计数 - l多边形顶点数量;
            (*三角形索引)[(*三角形索引).size() - 1][1] = 顶点计数 - k - 2;
            (*三角形索引)[(*三角形索引).size() - 1][2] = 顶点计数 - k - 1;
            索引计数 += 3;
            l当前索引计数 += 3;
        }
    }

    物体数量++;

    C网格属性::S属性* 属性 = new C网格属性::S属性;

    FbxTime 时间 = 0;

    WCHAR* 网格名称 = 0;
    FbxUTF8ToWC(p网格节点->GetName(), 网格名称, 0);
    属性->物体名称 = 网格名称;
    属性->顶点数量 = l当前索引计数;
    属性->起始顶点 = 索引计数 - l当前索引计数;

    FbxAMatrix 全局矩阵 = p网格节点->EvaluateGlobalTransform(时间);
    FbxAMatrix 本地矩阵 = p网格节点->EvaluateLocalTransform(时间);
    属性->变换 = fbx矩阵转mat4(全局矩阵);

    加载材质(p网格节点, 属性);

    this->属性->添加元素(属性);
}

mat4 C动态物体::fbx矩阵转mat4(FbxAMatrix fbx矩阵)
{
    mat4 矩阵 = mat4(1.0f);

    矩阵[0][0] = fbx矩阵.mData[0][0]; 矩阵[0][1] = fbx矩阵.mData[0][1]; 矩阵[0][2] = fbx矩阵.mData[0][2];
    矩阵[1][0] = fbx矩阵.mData[1][0]; 矩阵[1][1] = fbx矩阵.mData[1][1]; 矩阵[1][2] = fbx矩阵.mData[1][2];
    矩阵[2][0] = fbx矩阵.mData[2][0]; 矩阵[2][1] = fbx矩阵.mData[2][1]; 矩阵[2][2] = fbx矩阵.mData[2][2];
    矩阵[3][0] = fbx矩阵.mData[3][0]; 矩阵[3][1] = fbx矩阵.mData[3][1]; 矩阵[3][2] = fbx矩阵.mData[3][2];

    return 矩阵;
}

void C动态物体::加载材质(FbxNode* p网格节点, C网格属性::S属性* 属性)
{
    FbxMesh* p网格 = p网格节点->GetMesh();
    int 材质数量 = 0;

    if (p网格 && p网格节点)
    {
        材质数量 = p网格节点->GetMaterialCount();
    }

    if (材质数量 > 0)
    {
        for (int i = 0; i < 材质数量; i++)
        {
            FbxSurfaceMaterial* p表面材质 = p网格节点->GetMaterial(i);

            加载材质属性(p表面材质, 属性);
        }
    }
    else  //默认材质
    {
        属性->材质.漫反射 = { 1.0f, 1.0f, 1.0f, 1.0f };
        属性->材质.环境光 = { 0.0f, 0.0f, 0.0f };
        属性->材质.自发光 = { 0.0f, 0.0f, 0.0f };
        属性->材质.光泽度 = 0.0f;
        属性->材质.不透明度 = 1.0f;
        属性->材质.高光级别 = 1.0f;
        属性->纹理索引 = 0;
    }
}

void C动态物体::加载蒙皮信息(FbxNode* p网格节点)
{
    int i, j, k;
    int b = 0;
    int l簇数量 = 0;
    int l骨骼数量 = 0;
    FbxCluster* l簇;
    WCHAR* l骨骼名字 = 0;
    WCHAR* l物体名字 = 0;
    mat4 旋转矩阵 = mat4(1.0f);
    mat4 旋转 = mat4(1.0f);
    mat4 旋转矩阵2 = mat4(1.0f);
    FbxAMatrix 参考全局初始变换;
    FbxAMatrix 参考全局当前变换;
    FbxAMatrix 关联全局初始变换;
    FbxAMatrix 关联全局当前变换;
    FbxAMatrix 簇全局初始变换;
    FbxAMatrix 簇全局当前变换;

    FbxAMatrix 参考几何体;
    FbxAMatrix 关联几何体;
    FbxAMatrix 簇几何体;

    FbxAMatrix 簇关联初始变换;
    FbxAMatrix 簇关联当前变换逆;


    FbxGeometry* p几何 = (FbxMesh*)p网格节点->GetNodeAttribute();
    l簇数量 = p几何->GetDeformerCount(FbxDeformer::eSkin);
    FbxUTF8ToWC(p网格节点->GetName(), l物体名字, 0);
    蒙皮数据->关联物体.resize(蒙皮数据->关联物体.size() + 1);
    蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].物体名称 = l物体名字;

    for (i = 0; i != l簇数量; i++)
    {
        l骨骼数量 = ((FbxSkin*)p几何->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
        蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼.resize(l骨骼数量);
        for (j = 0; j != l骨骼数量; j++)
        {
            l簇 = ((FbxSkin*)p几何->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);

            FbxUTF8ToWC(l簇->GetLink()->GetName(), l骨骼名字, 0);
            蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].骨骼名称 = l骨骼名字;

            FbxCluster::ELinkMode 簇模式 = l簇->GetLinkMode();

            if (簇模式 == FbxCluster::eAdditive && l簇->GetAssociateModel())
            {
                l簇->GetTransformAssociateModelMatrix(关联全局初始变换);
                关联几何体 = 获取几何体(l簇->GetAssociateModel());
                关联全局初始变换 *= 关联几何体;
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].关联全局初始变换 = fbx矩阵转mat4(关联全局初始变换);
                //关联全局当前变换 = 获取全局变换(l簇->GetAssociateModel(), 时间, 造型);

                l簇->GetTransformMatrix(参考全局初始变换);
                关联几何体 = 获取几何体(p网格节点);
                参考全局初始变换 *= 参考几何体;
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].参考全局初始变换 = fbx矩阵转mat4(参考全局初始变换);
                //参考全局当前变换 = 全局变换;

                l簇->GetTransformLinkMatrix(簇全局初始变换);
                簇几何体 = 获取几何体(l簇->GetLink());
                簇全局初始变换 *= 簇几何体;
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].簇全局初始变换 = fbx矩阵转mat4(簇全局初始变换);
                //簇全局当前变换 = 获取全局变换(l簇->GetLink(), 时间, 造型);

                //顶点变换 = 参考全局初始变换.Inverse() * 关联全局初始变换 * 关联全局当前变换.Inverse() *
                //    簇全局当前变换 * 簇全局初始变换.Inverse() * 关联全局初始变换;
            }
            else
            {
                l簇->GetTransformMatrix(参考全局初始变换);
                //关联全局当前变换 = 全局变换;
                参考几何体 = 获取几何体(p网格节点);
                参考全局初始变换 *= 参考几何体;
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].参考全局初始变换 = fbx矩阵转mat4(参考全局初始变换);

                l簇->GetTransformLinkMatrix(簇全局初始变换);
                //簇全局当前变换 = 获取全局变换(l簇->GetLink(), 时间, 造型);
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].簇全局初始变换 = fbx矩阵转mat4(簇全局初始变换);

                簇关联初始变换 = 簇全局初始变换.Inverse() * 参考全局初始变换;
                簇关联当前变换逆 = 关联全局当前变换.Inverse() * 簇全局当前变换;

                //顶点变换 = 簇关联当前变换逆 * 簇关联初始变换;
            }
        }

        蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼.resize(l骨骼数量);
        for (j = 0; j != l骨骼数量; j++)
        {
            l簇 = ((FbxSkin*)p几何->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);

            int 控制顶点数量 = l簇->GetControlPointIndicesCount();
            int* 控制顶点索引 = l簇->GetControlPointIndices();
            double* 控制顶点权重 = l簇->GetControlPointWeights();

            for (int k = 0; k < 控制顶点数量; k++)
            {
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].权重组.push_back(控制顶点权重[k]);
                蒙皮数据->关联物体[蒙皮数据->关联物体.size() - 1].骨骼[j].索引组.push_back(控制顶点索引[k]);
            }
        }
    }
}

int C动态物体::合并顶点蒙皮()
{
    int 当前顶点 = 0;
    int 最小骨骼索引 = 0;

    if (骨骼数量 > 200)
    {
        OutputDebugString(L"骨骼数量超出200个");
        return -1;
    }

    for (int i = 0; i < (*物体控制顶点集).size(); i++)
    {
        for (int i2 = 0; i2 < (*物体控制顶点集)[i].控制顶点集.size(); i2++)
        {
            for (int j2 = 0; j2 < (*物体控制顶点集)[i].控制顶点集[i2].size(); j2++)
            {
                int 骨骼索引计数 = 0;

                for (int j = 0; j < 蒙皮数据->关联物体.size(); j++)
                {
                    if (蒙皮数据->关联物体[j].物体名称 == (*物体控制顶点集)[i].物体名称)
                    {
                        for (int k = 0; k < 蒙皮数据->关联物体[j].骨骼.size(); k++)
                        {
                            for (int l = 0; l < 蒙皮数据->关联物体[j].骨骼[k].索引组.size(); l++)
                            {
                                if (蒙皮数据->关联物体[i].骨骼[k].索引组[l] == i2)
                                {
                                    for (int m = 0; m < 骨骼数量; m++)
                                    {
                                        if (蒙皮数据->关联物体[j].骨骼[k].骨骼名称 == (*骨骼名称)[m])
                                        {
                                            if (蒙皮数据->关联物体[j].骨骼[k].权重组[l] > 0.001)
                                            {
                                                //丢弃最小权重骨骼
                                                if (骨骼索引计数 == d最大骨骼索引数量)
                                                {
                                                    float 最小权重 = 1.0f;

                                                    for (int n = 0; n < d最大骨骼索引数量 - 1; n++)
                                                    {
                                                        if (最小权重 > (*物体控制顶点集)[i].控制顶点集[i2][j2].顶点权重[n])
                                                        {
                                                            最小骨骼索引 = n;
                                                            最小权重 = (*物体控制顶点集)[i].控制顶点集[i2][j2].顶点权重[n];
                                                        }
                                                    }

                                                    if (最小权重 < 蒙皮数据->关联物体[j].骨骼[k].权重组[l])
                                                    {
                                                        (*物体控制顶点集)[i].控制顶点集[i2][j2].顶点权重[最小骨骼索引] =
                                                            蒙皮数据->关联物体[j].骨骼[k].权重组[l] + 最小权重;
                                                        (*物体控制顶点集)[i].控制顶点集[i2][j2].关联骨骼索引[最小骨骼索引] = m;
                                                    }

                                                    continue;
                                                }

                                                (*物体控制顶点集)[i].控制顶点集[i2][j2].关联骨骼索引[骨骼索引计数] = m;
                                                if (骨骼索引计数 < d最大骨骼索引数量 - 1)
                                                    (*物体控制顶点集)[i].控制顶点集[i2][j2].顶点权重[骨骼索引计数] =
                                                    蒙皮数据->关联物体[j].骨骼[k].权重组[l];
                                                骨骼索引计数++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                for (int k = 骨骼索引计数; k < d最大骨骼索引数量; k++)
                {
                    (*物体控制顶点集)[i].控制顶点集[i2][j2].关联骨骼索引[k] = 0;
                    if (k < d最大骨骼索引数量 - 1) (*物体控制顶点集)[i].控制顶点集[i2][j2].顶点权重[k] = 0;
                }
            }
        }
    }

    for (int i = 0; i < (*三角形索引).size(); i++)
    {
        备用资料->顶点集.resize(备用资料->顶点集.size() + 3);
        for (int j = 0; j < (*索引记录).size(); j++)
        {
            if ((*三角形索引)[i][0] == j)
                备用资料->顶点集[备用资料->顶点集.size() - 3] = (*物体控制顶点集)[(*索引记录)[j][0]].控制顶点集[(*索引记录)[j][1]][(*索引记录)[j][2]];

            if ((*三角形索引)[i][1] == j)
                备用资料->顶点集[备用资料->顶点集.size() - 2] = (*物体控制顶点集)[(*索引记录)[j][0]].控制顶点集[(*索引记录)[j][1]][(*索引记录)[j][2]];

            if ((*三角形索引)[i][2] == j)
                备用资料->顶点集[备用资料->顶点集.size() - 1] = (*物体控制顶点集)[(*索引记录)[j][0]].控制顶点集[(*索引记录)[j][1]][(*索引记录)[j][2]];
        }
    }

    return 0;
}

void C动态物体::加载材质属性(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性)
{
    p表面材质->GetName();

    if (p表面材质->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
        FbxDouble3 漫反射 = ((FbxSurfacePhong*)p表面材质)->Diffuse;
        属性->材质.漫反射.x = 漫反射.mData[0];
        属性->材质.漫反射.y = 漫反射.mData[1];
        属性->材质.漫反射.z = 漫反射.mData[2];

        FbxDouble3 自发光 = ((FbxSurfacePhong*)p表面材质)->Emissive;
        属性->材质.自发光.x = 自发光.mData[0];
        属性->材质.自发光.y = 自发光.mData[1];
        属性->材质.自发光.z = 自发光.mData[2];

        FbxDouble 不透明度 = 1.0 - ((FbxSurfacePhong*)p表面材质)->TransparencyFactor;
        属性->材质.漫反射.w = 不透明度;

        FbxDouble 光泽度 = ((FbxSurfacePhong*)p表面材质)->Shininess;
        属性->材质.光泽度 = 光泽度;

        FbxDouble 高光等级 = ((FbxSurfacePhong*)p表面材质)->SpecularFactor;
        属性->材质.高光级别 = 高光等级;

        if (属性->材质.高光级别 < 1)属性->材质.高光级别 = 1;

        FbxDouble 反射率 = 1.0 - ((FbxSurfacePhong*)p表面材质)->ReflectionFactor;
    }

    加载纹理(p表面材质, 属性);
}

void C动态物体::加载纹理(FbxSurfaceMaterial* p表面材质, C网格属性::S属性* 属性)
{
    int i;
    int k = 0;
    int 结果 = 1;
    FbxProperty 材质属性;
    WCHAR* 路径 = 0;

    for (i = 0; i < FbxLayerElement::sTypeTextureCount; i++)
    {
        材质属性 = p表面材质->FindProperty(FbxLayerElement::sTextureChannelNames[i]);
        if (材质属性.IsValid())
        {
            int textureCount = 材质属性.GetSrcObjectCount();

            for (int j = 0; j < textureCount; ++j)
            {
                FbxFileTexture* p纹理 = FbxCast<FbxFileTexture>(材质属性.GetSrcObject(j));
                if (p纹理)
                {
                    FbxUTF8ToWC(p纹理->GetFileName(), 路径, 0);
                    for (k = 0; k < 备用资料->路径集.size(); k++)
                    {
                        if (备用资料->路径集[k].compare(路径) == 0 && 属性->纹理索引 == 0)
                        {
                            属性->纹理索引 = k + 1;
                            break;
                        }
                    }

                    if (属性->纹理索引 == 0)
                    {
                        备用资料->路径集.resize(备用资料->路径集.size() + 1);
                        备用资料->路径集[备用资料->路径集.size() - 1] = 路径;

                        wstring 文件类型;
                        bool 是否启录 = 0;
                        for (int i = 0; i < wcslen(路径); i++)
                        {
                            if (是否启录) 文件类型 += 路径[i];
                            if (路径[i] == '.')
                            {
                                是否启录 = 1;
                                文件类型.clear();
                            }
                        }

                        this->属性->纹理集.resize(this->属性->纹理集.size() + 1);

                        unsigned char* 图像;
                        char 纹理路径A[1024];
                        int 长度 = WideCharToMultiByte(CP_ACP, 0, 路径, wcslen(路径), 纹理路径A, 1024, 0, 0);
                        纹理路径A[长度] = '\0';

                        if (!(图像 = SOIL_load_image(纹理路径A, &this->属性->纹理集[this->属性->纹理集.size() - 1].宽,
                            &this->属性->纹理集[this->属性->纹理集.size() - 1].高, &this->属性->纹理集[this->属性->纹理集.size() - 1].通道, SOIL_LOAD_RGBA)))
                        {
                            wstring bug = L"fbx文件加载-动态物体：加载模型材质时未找到贴图文件";
                            OutputDebugString(bug.c_str());
                            exit(0);
                        }
                        glGenTextures(1, &this->属性->纹理集[this->属性->纹理集.size() - 1].纹理);
                        glBindTexture(GL_TEXTURE_2D, this->属性->纹理集[this->属性->纹理集.size() - 1].纹理);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->属性->纹理集[this->属性->纹理集.size() - 1].宽,
                            this->属性->纹理集[this->属性->纹理集.size() - 1].高, 0, GL_RGBA, GL_UNSIGNED_BYTE, 图像);
                        delete[] 图像;
                        属性->纹理索引 = this->属性->纹理集.size() - 1;
                    }
                }
            }
        }
    }
}

FbxAMatrix C动态物体::获取全局变换(FbxNode* 节点, const FbxTime& 时间, FbxAMatrix* 父全局变换)
{
    FbxAMatrix 全局变换;
    bool 找到全局变换 = false;

    FbxPose* 造型 = nullptr;
    造型 = 场景->GetPose(0);
    
    if (造型)
    {
        int 节点索引 = 造型->Find(节点);

        if (节点索引 > -1)
        {
            if (造型->IsBindPose() || !造型->IsLocalMatrix(节点索引))
            {
                全局变换 = 获取造型矩阵(造型, 节点索引);
            }
            else
            {
                FbxAMatrix l父全局变换;

                if (父全局变换)
                {
                    l父全局变换 = *父全局变换;
                }
                else
                {
                    if (节点->GetParent())
                    {
                        l父全局变换 = 获取全局变换(节点->GetParent(), 时间);
                    }
                }

                FbxAMatrix 本地变换 = 获取造型矩阵(造型, 节点索引);
                全局变换 = l父全局变换 * 本地变换;
            }

            找到全局变换 = true;
        }
    }

    if (!找到全局变换)
    {
        全局变换 = 节点->EvaluateGlobalTransform(时间);
    }

    return 全局变换;
}

FbxAMatrix C动态物体::获取造型矩阵(FbxPose* 造型, int 节点索引)
{
    FbxAMatrix 造型变换;
    FbxMatrix 变换 = 造型->GetMatrix(节点索引);

    memcpy((double*)造型变换, (double*)变换, sizeof(变换.mData));

    return 造型变换;
}

FbxAMatrix C动态物体::获取几何体(FbxNode* 节点)
{
    const FbxVector4 lT = 节点->GetGeometricTranslation(FbxNode::eSourcePivot);
    const FbxVector4 lR = 节点->GetGeometricRotation(FbxNode::eSourcePivot);
    const FbxVector4 lS = 节点->GetGeometricScaling(FbxNode::eSourcePivot);

    return FbxAMatrix(lT, lR, lS);
}

void C动态物体::加载动画(FbxScene* p场景)
{
    动画数据->片段.resize(p场景->GetSrcObjectCount<FbxAnimStack>());

    char lTimeString[256]{};

    FbxTime   l帧时间;
    FbxTimeSpan l时间跨度;
    FbxTime     l开始, l结束;
    FbxGlobalSettings* p设定 = 0;
    int l帧速率 = 0;
    int l时 = 0;
    int l分 = 0;
    int l秒 = 0;
    int l帧 = 0;
    int l域 = 0;
    int l残值 = 0;

    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);
    动画数据->帧速率 = l帧速率;

    p设定 = &p场景->GetGlobalSettings();

    p设定->GetTimelineDefaultTimeSpan(l时间跨度);
    l开始 = l时间跨度.GetStart();
    l结束 = l时间跨度.GetStop();
    l开始.GetTime(l时, l分, l秒, l帧, l域, l残值);
    动画数据->开始帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
    l结束.GetTime(l时, l分, l秒, l帧, l域, l残值);
    动画数据->结束帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;

    fbx根节点 = p场景->GetRootNode();
    场景 = p场景;

    for (UINT i = 0; i < p场景->GetSrcObjectCount<FbxAnimStack>(); i++)
    {
        FbxAnimStack* l动画片段 = p场景->GetSrcObject<FbxAnimStack>(i);

        WCHAR* 片段名称 = 0;
        FbxUTF8ToWC(l动画片段->GetName(), 片段名称, 0);
        动画数据->片段[i].片段名称 = 片段名称;

        p场景->SetCurrentAnimationStack(l动画片段);

        (*全局变换根节点).resize((*全局变换根节点).size() + 1);

        加载动画片段(l动画片段, p场景->GetRootNode(), i);
    }
}

void C动态物体::加载动画片段(FbxAnimStack* p动画片段, FbxNode* p节点, UINT 片段索引)
{
    int l;
    int 动画层数量 = p动画片段->GetMemberCount<FbxAnimLayer>();
    int 音效层数量 = p动画片段->GetMemberCount<FbxAudioLayer>();
    FbxTimeSpan 时间跨度;
    FbxTime l帧时间;
    FbxTime l开始, l结束;
    int l帧速率 = 0;
    int l时 = 0;
    int l分 = 0;
    int l秒 = 0;
    int l帧 = 0;
    int l域 = 0;
    int l残值 = 0;

    if (动画层数量)
        动画数据->片段[片段索引].动画层.resize(动画层数量);

    if (音效层数量)
        动画数据->片段[片段索引].音效层.resize(音效层数量);

    时间跨度 = p动画片段->GetLocalTimeSpan();
    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

    l开始 = 时间跨度.GetStart();
    l结束 = 时间跨度.GetStop();
    l开始.GetTime(l时, l分, l秒, l帧, l域, l残值);
    动画数据->片段[片段索引].开始帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
    l结束.GetTime(l时, l分, l秒, l帧, l域, l残值);
    动画数据->片段[片段索引].结束帧 = l时 * l帧速率 * l帧速率 * l帧速率 + l分 * l帧速率 * l帧速率 + l秒 * l帧速率 + l帧;
    动画数据->片段[片段索引].帧速率 = l帧速率;
    动画数据->片段[片段索引].起始时间 = l开始;

    for (l = 0; l < 动画层数量; l++)
    {
        FbxAnimLayer* l动画层 = p动画片段->GetMember<FbxAnimLayer>(l);

        WCHAR* 动画层名称 = 0;
        FbxUTF8ToWC(l动画层->GetName(), 动画层名称);
        动画数据->片段[片段索引].动画层[l].动画层名称, 动画层名称 = 动画层名称;

        加载动画层(l动画层, p节点, 片段索引, l);
    }

    for (l = 0; l < 音效层数量; l++)
    {
        FbxAudioLayer* l音效层 = p动画片段->GetMember<FbxAudioLayer>(l);
        加载音效层(l音效层, l, 片段索引);
    }
}

void C动态物体::加载音效层(FbxAudioLayer* p音效层, UINT 音效层索引, UINT 片段索引)
{
    int l音轨数量;
    WCHAR* l音效层名称 = 0;
    WCHAR* l音轨名称 = 0;

    l音轨数量 = p音效层->GetMemberCount<FbxAudio>();

    动画数据->片段[片段索引].音效层[音效层索引].音轨.resize(l音轨数量);

    FbxUTF8ToWC(p音效层->GetName(), l音效层名称);
    动画数据->片段[片段索引].音效层[音效层索引].音效层名称 = l音效层名称;

    for (int i = 0; i < l音轨数量; i++)
    {
        FbxAudio* l音轨 = p音效层->GetMember<FbxAudio>(i);
        FbxUTF8ToWC(l音轨->GetName(), l音轨名称, 0);
        动画数据->片段[片段索引].音效层[音效层索引].音轨[i].音轨名称 = l音轨名称;
    }
}

void C动态物体::加载动画层(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引)
{
    int l模型数量;
    WCHAR* l物体名称;

    for (l模型数量 = 0; l模型数量 < p节点->GetChildCount(); l模型数量++)
    {
        加载动画层(p动画层, p节点->GetChild(l模型数量), 片段索引, 动画层索引);
    }

    FbxUTF8ToWC(p节点->GetName(), l物体名称, 0);
    动画数据->片段[片段索引].动画层[动画层索引].物体.resize(动画数据->片段[片段索引].动画层[动画层索引].物体.size() + 1);
    动画数据->片段[片段索引].动画层[动画层索引].物体[动画数据->片段[片段索引].动画层[动画层索引].物体.size() - 1].物体名称 = l物体名称;

    加载动画通道(p动画层, p节点, 片段索引, 动画层索引, 动画数据->片段[片段索引].动画层[动画层索引].物体.size() - 1);
}

void C动态物体::加载动画通道(FbxAnimLayer* p动画层, FbxNode* p节点, UINT 片段索引, UINT 动画层索引, UINT 模型索引)
{
    FbxAnimCurve* l动画曲线 = NULL;

    FbxTimeSpan 时间跨度;
    FbxTime l帧时间;
    FbxTime l开始, l结束;
    int l帧数量;
    float   l帧值;
    int     l帧计数;
    int l帧速率;

    int l时;
    int l分;
    int l秒;
    int l帧;
    int l域;
    int l残值;
    int l倍数 = 0;
    int l余数 = 0;

    l帧速率 = l帧时间.GetFrameRate(l帧时间.eDefaultMode);

    l帧数量 = 动画数据->片段[片段索引].结束帧 - 动画数据->片段[片段索引].开始帧;
    l帧速率 = 动画数据->片段[片段索引].帧速率;

    (*全局变换根节点)[片段索引].resize(l帧数量);

    for (l帧计数 = 0; l帧计数 < l帧数量; l帧计数++)
    {
        l时 = l帧计数 / (l帧速率 * l帧速率 * l帧速率);
        l分 = (l帧计数 - (l时 * l帧速率 * l帧速率 * l帧速率)) / (l帧速率 * l帧速率);
        l秒 = (l帧计数 - (l时 * l帧速率 * l帧速率 * l帧速率) - (l分 * l帧速率 * l帧速率)) / l帧速率;
        l帧 = l帧计数 - (l时 * l帧速率 * l帧速率 * l帧速率) - (l分 * l帧速率 * l帧速率) - (l秒 * l帧速率);
        l帧时间.SetTime(l时, l分, l秒, l帧);
        l帧时间 += 动画数据->片段[片段索引].起始时间;

        for (int i = 0; i < 骨骼数量; i++)
        {
            WCHAR* 节点名称w = 0;

            FbxAnsiToWC(p节点->GetName(), 节点名称w);

            if ((*骨骼名称)[i] == 节点名称w)
            {
                FbxAMatrix 曲线帧本地矩阵 = p节点->EvaluateLocalTransform(l帧时间);
                FbxAMatrix 曲线帧世界矩阵 = p节点->EvaluateGlobalTransform(l帧时间);

                mat4 全局变换 = mat4(1.0f);
                mat4 本地变换 = mat4(1.0f);
                全局变换 = fbx矩阵转mat4(曲线帧世界矩阵);
                本地变换 = fbx矩阵转mat4(曲线帧本地矩阵);

                S动画变换 动画变换;
                动画变换.帧数 = l帧计数;
                动画变换.全局变换 = 全局变换;
                动画变换.本地变换 = 本地变换;

                动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].变换.push_back(动画变换);

                //加载变换节点(fbx根节点, l帧时间, 0, 片段索引, l帧计数);
            }
        }

        for (int i = 0; i < 属性->元素.size(); i++)
        {
            WCHAR* 节点名称w = 0;

            FbxAnsiToWC(p节点->GetName(), 节点名称w);

            if (属性->元素[i]->物体名称 == 节点名称w)
            {
                FbxAMatrix 曲线帧本地矩阵 = p节点->EvaluateLocalTransform(l帧时间);
                FbxAMatrix 曲线帧世界矩阵 = p节点->EvaluateGlobalTransform(l帧时间);

                mat4 全局变换 = mat4(1.0f);
                mat4 本地变换 = mat4(1.0f);
                全局变换 = fbx矩阵转mat4(曲线帧世界矩阵);
                本地变换 = fbx矩阵转mat4(曲线帧本地矩阵);

                S动画变换 动画变换;
                动画变换.帧数 = l帧计数;
                动画变换.全局变换 = 全局变换;
                动画变换.本地变换 = 本地变换;

                动画数据->片段[片段索引].动画层[动画层索引].物体[模型索引].变换.push_back(动画变换);
            }
        }
    }
}

void C动态物体::加载变换节点(FbxNode* p节点, FbxTime 时间, FbxAMatrix* 全局变换, int 片段索引, int 帧)
{
    FbxAMatrix 全局变换2 = 获取全局变换(p节点, 时间, 全局变换);

    if (p节点->GetNodeAttribute())
    {
        FbxAMatrix lGeometryOffset = 获取几何体(p节点);
        FbxAMatrix 全局偏移变换 = 全局变换2 * lGeometryOffset;

        if (p节点->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
            加载网格(p节点, 时间, &全局偏移变换, 片段索引, 帧);
    }

    const int lChildCount = p节点->GetChildCount();
    for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
    {
        加载变换节点(p节点->GetChild(lChildIndex), 时间, &全局变换2, 片段索引, 帧);
    }
}

void C动态物体::加载网格(FbxNode* p节点, FbxTime 时间, FbxAMatrix* 全局变换, int 片段索引, int 帧)
{
    WCHAR* l物体名称 = nullptr;
    FbxUTF8ToWC(p节点->GetName(), l物体名称, 0);
    S变换节点2 变换节点;

    变换节点.参考全局变换 = *全局变换;
    变换节点.节点名称 = l物体名称;
    变换节点.全局变换 = 获取全局变换(p节点, 时间);

    (*全局变换根节点)[片段索引][帧].push_back(变换节点);
}

void C动态物体::合并物体动画信息()
{
    uint 帧偏移 = 0;
    mat4 初始矩阵 = mat4(1.0f);

    (*动画轨道储存).resize(动画数据->片段.size());
    for (int i = 0; i < (*动画轨道储存).size(); i++)
    {
        (*动画轨道储存)[i].原始时长 = (float)(动画数据->片段[i].结束帧 - 动画数据->片段[i].开始帧 + 1) / 动画数据->片段[i].帧速率;
        (*动画轨道储存)[i].帧.resize(动画数据->片段[i].结束帧 - 动画数据->片段[i].开始帧);
        (*动画轨道储存)[i].是否循环 = 1;
        (*动画轨道储存)[i].轨道名称 = 动画数据->片段[i].片段名称;
        (*动画轨道储存)[i].速度 = 1.0f;
        帧偏移 = 动画数据->片段[i].开始帧;

        for (int j = 帧偏移; j < (*动画轨道储存)[i].帧.size() + 帧偏移; j++)
        {
            (*动画轨道储存)[i].帧[j - 帧偏移].骨骼变换.resize(骨骼数量, 初始矩阵);
            //(*动画轨道储存)[i].帧[j - 帧偏移].物体变换.resize(属性->元素.size(), 初始矩阵);

            for (int k = 0; k < 动画数据->片段[i].动画层.size(); k++)
            {
                for (int m = 0; m < 动画数据->片段[i].动画层[k].物体.size(); m++)
                {
                    //加载骨骼变换
                    for (int n = 0; n < 骨骼数量; n++)
                    {
                        if ((*骨骼名称)[n].compare(动画数据->片段[i].动画层[k].物体[m].物体名称) == 0)
                        {
                            for (int u = 0; u < 蒙皮数据->关联物体.size(); u++)
                            {
                                for (int v = 0; v < 蒙皮数据->关联物体[u].骨骼.size(); v++)
                                {
                                    if (蒙皮数据->关联物体[u].骨骼[v].骨骼名称 == (*骨骼名称)[n])
                                    {
                                        mat4 参考全局初始变换 = 蒙皮数据->关联物体[u].骨骼[v].参考全局初始变换;
                                        mat4 簇全局初始变换 = 蒙皮数据->关联物体[u].骨骼[v].簇全局初始变换;
                                        mat4 全局变换 = 动画数据->片段[i].动画层[k].物体[m].变换[j - 帧偏移].全局变换;
                                        mat4 局部变换 = 动画数据->片段[i].动画层[k].物体[m].变换[j - 帧偏移].本地变换;

                                        //for (int w = 0; w < (*全局变换根节点)[i][j - 帧偏移].size(); w++)
                                        //{
                                        //    if ((*全局变换根节点)[i][j - 帧偏移][w].节点名称 == (*骨骼名称)[n])
                                        //    {
                                        //        参考全局当前变换 = fbx矩阵转mat4((*全局变换根节点)[i][j - 帧偏移][w].参考全局变换);
                                        //        全局变换 = fbx矩阵转mat4((*全局变换根节点)[i][j - 帧偏移][w].全局变换);
                                        //    }
                                        //}

                                        (*动画轨道储存)[i].帧[j - 帧偏移].骨骼变换[n] = 全局变换
                                            * inverse(簇全局初始变换) * 参考全局初始变换;
                                    }
                                }
                            }
                        }
                    }

                    ////加载物体变换
                    //for (int n = 0; n < 物体数量; n++)
                    //{
                    //    if (属性->元素[n]->物体名称.compare(动画数据->片段[i].动画层[k].物体[m].物体名称) == 0)
                    //    {
                    //        mat4 参考全局当前变换;

                    //        参考全局当前变换 = 属性->元素[n]->变换;

                    //        (*动画轨道储存)[i].帧[j - 帧偏移].物体变换[n] = inverse(参考全局当前变换) 
                    //            * 动画数据->片段[i].动画层[k].物体[m].变换[j - 帧偏移].全局变换;
                    //    }
                    //}
                }
            }
        }
    }
}

void C动态物体::生成骨骼缓存()
{
    glCreateBuffers(1, &骨骼缓存);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 骨骼缓存);

    int 帧缓冲区大小 = 0;
    for (int i = 0; i < (*动画轨道储存).size(); i++)
        for (int j = 0; j < (*动画轨道储存)[i].帧.size(); j++)
            帧缓冲区大小 += sizeof(mat4) * (*动画轨道储存)[i].帧[j].骨骼变换.size();

    int 当前帧缓冲区偏移 = 0;
    glBufferData(GL_SHADER_STORAGE_BUFFER, 帧缓冲区大小, 0, GL_STATIC_DRAW);
    for (int i = 0; i < (*动画轨道储存).size(); i++)
        for (int j = 0; j < (*动画轨道储存)[i].帧.size(); j++)
            for (int k = 0; k < (*动画轨道储存)[i].帧[j].骨骼变换.size(); k++)
            {
                glBufferSubData(GL_SHADER_STORAGE_BUFFER, 当前帧缓冲区偏移, sizeof(mat4),
                    &(*动画轨道储存)[i].帧[j].骨骼变换[k][0][0]);
                当前帧缓冲区偏移 += sizeof(mat4);
            }

    动画轨道.resize((*动画轨道储存).size());
    for (int i = 0; i < (*动画轨道储存).size(); i++)
    {
        动画轨道[i].原始时长 = (*动画轨道储存)[i].原始时长;
        动画轨道[i].轨道名称 = (*动画轨道储存)[i].轨道名称;
        
        动画轨道[i].帧.resize((*动画轨道储存)[i].帧.size());
        for (int j = 0; j < (*动画轨道储存)[i].帧.size(); j++)
        {
            动画轨道[i].帧[j].骨骼数量 = (*动画轨道储存)[i].帧[j].骨骼变换.size();
        }
    }
}

//mat4* C动态物体::获取当前骨骼变换()
//{
//    uint l帧数 = 0;
//    float l小数 = 0;
//    vec3 l缩放{};
//    vec3 l初始旋转{};
//    vec3 骨骼位置{};
//    mat4 l最终变换 = mat4(1.0f);
//    mat4 l物体变换 = mat4(1.0f);
//    vec3 旋转x{};
//    vec3 旋转y{};
//    vec3 旋转z{};
//    vec3 旋转x2{};
//    vec3 旋转y2{};
//    vec3 旋转z2{};
//    vec3 位置{};
//    vec3 位置2{};
//    mat4 旋转 = mat4(1.0f);
//
//    l帧数 = (int)动画轨道[当前轨道].帧位;
//    l小数 = 动画轨道[当前轨道].帧位 - l帧数;
//
//    for (UINT i = 0; i < 骨骼数量; i++)
//    {
//        l最终变换 = (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i];
//        位置 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][3][0], (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][3][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][3][2] };
//        位置2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][3][0], (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][3][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][3][2] };
//        旋转x = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][0][0], (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][0][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][0][2] };
//        旋转y = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][1][0], (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][1][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][1][2] };
//        旋转z = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][2][0], (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][2][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数].骨骼变换[i][2][2] };
//        旋转x2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][0][0], (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][0][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][0][2] };
//        旋转y2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][1][0], (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][1][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][1][2] };
//        旋转z2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][2][0], (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][2][1],
//            (*动画轨道储存)[当前轨道].帧[l帧数 + 1].骨骼变换[i][2][2] };
//        位置 = 位置 * (1 - l小数) + 位置2 * l小数;
//        旋转x = 旋转x * (1 - l小数) + 旋转x2 * l小数;
//        旋转y = 旋转y * (1 - l小数) + 旋转y2 * l小数;
//        旋转z = 旋转z * (1 - l小数) + 旋转z2 * l小数;
//        l最终变换[0][0] = 旋转x[0]; l最终变换[0][1] = 旋转x[1]; l最终变换[0][2] = 旋转x[2];
//        l最终变换[1][0] = 旋转y[0]; l最终变换[1][1] = 旋转y[1]; l最终变换[1][2] = 旋转y[2];
//        l最终变换[2][0] = 旋转z[0]; l最终变换[2][1] = 旋转z[1]; l最终变换[2][2] = 旋转z[2];
//        l最终变换[3][0] = 位置[0]; l最终变换[3][1] = 位置[1]; l最终变换[3][2] = 位置[2];
//
//        骨骼变换[i] = l最终变换;
//    }
//
//    return 骨骼变换;
//}

//mat4* C动态物体::获取当前物体变换()
//{
//    uint l帧数 = 0;
//    float l小数 = 0;
//    vec3 l缩放{};
//    vec3 l初始旋转{};
//    vec3 骨骼位置{};
//    mat4 l最终变换 = mat4(1.0f);
//    mat4 l物体变换 = mat4(1.0f);
//    vec3 旋转x{};
//    vec3 旋转y{};
//    vec3 旋转z{};
//    vec3 旋转x2{};
//    vec3 旋转y2{};
//    vec3 旋转z2{};
//    vec3 位置{};
//    vec3 位置2{};
//    mat4 旋转 = mat4(1.0f);
//
//    l帧数 = (int)(*动画轨道储存)[当前轨道].帧位;
//    l小数 = (*动画轨道储存)[当前轨道].帧位 - l帧数;
//
//    for (UINT i = 0; i < 物体数量; i++)
//    {
//        l最终变换 = (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i];
//        位置 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][3][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][3][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][3][2] };
//        位置2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][3][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][3][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][3][2] };
//        旋转x = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][0][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][0][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][0][2] };
//        旋转y = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][1][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][1][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][1][2] };
//        旋转z = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][2][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][2][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][2][2] };
//        旋转x2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][0][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][0][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][0][2] };
//        旋转y2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][1][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][1][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][1][2] };
//        旋转z2 = vec3{ (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][2][0], (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][2][1], 
//            (*动画轨道储存)[当前轨道].帧[l帧数].物体变换[i][2][2] };
//        位置 = 位置 * (1 - l小数) + 位置2 * l小数;
//        旋转x = 旋转x * (1 - l小数) + 旋转x2 * l小数;
//        旋转y = 旋转y * (1 - l小数) + 旋转y2 * l小数;
//        旋转z = 旋转z * (1 - l小数) + 旋转z2 * l小数;
//        l最终变换[0][0] = 旋转x[0]; l最终变换[0][1] = 旋转x[1]; l最终变换[0][2] = 旋转x[2];
//        l最终变换[1][0] = 旋转y[0]; l最终变换[1][1] = 旋转y[1]; l最终变换[1][2] = 旋转y[2];
//        l最终变换[2][0] = 旋转z[0]; l最终变换[2][1] = 旋转z[1]; l最终变换[2][2] = 旋转z[2];
//        l最终变换[3][0] = 位置[0]; l最终变换[3][1] = 位置[1]; l最终变换[3][2] = 位置[2];
//
//        物体变换[i] = l最终变换;
//    }
//
//    return 物体变换;
//}

void C动态物体::设定动画速度(UINT 轨道, float 速度倍数)
{
    (*动画轨道储存)[轨道].速度 = 速度倍数;
}

void C动态物体::设定动画轨道(UINT 轨道)
{
    当前轨道 = 轨道;
}

void C动态物体::设定轨道帧位置(UINT 轨道, float 百分比)
{
    动画轨道[轨道].当前时间 = 动画轨道[轨道].原始时长 * 百分比;
}

void C动态物体::设定播放模式(UINT 轨道, bool 是否循环)
{
    动画轨道[轨道].是否循环 = 是否循环;
}

bool C动态物体::检测动画结束(UINT 轨道)
{
    if (动画轨道[轨道].是否结束) return 1;
    else return 0;
}

void C动态物体::更新时间(float 时间变化)
{
    动画轨道[当前轨道].当前时间 += 时间变化 * 动画轨道[当前轨道].速度;
    if (动画轨道[当前轨道].当前时间 >= 动画轨道[当前轨道].原始时长)
    {
        动画轨道[当前轨道].是否结束 = 1;
        if (动画轨道[当前轨道].是否循环)
            动画轨道[当前轨道].当前时间 = 0;
        else
            动画轨道[当前轨道].当前时间 = 动画轨道[当前轨道].原始时长 - 0.001;
    }

    动画轨道[当前轨道].帧位 = 动画轨道[当前轨道].当前时间 / 动画轨道[当前轨道].原始时长 * (动画轨道[当前轨道].帧.size() - 1);
}

int C动态物体::获取骨骼偏移()
{
    偏移 = 0;
    int l帧数 = (int)动画轨道[当前轨道].帧位;

    for (int i = 0; i < 当前轨道; i++)
        偏移 += 动画轨道[i].帧.size() * 动画轨道[i].帧[0].骨骼数量;

    偏移 += l帧数 * 动画轨道[当前轨道].帧[0].骨骼数量;

    return 偏移;
}

float C动态物体::获取当前帧位()
{
    return 动画轨道[当前轨道].帧位;
}

void C动态物体::绘制网格(UINT 属性)
{
    glBindVertexArray(顶点对象);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, 骨骼缓存);;
    glDrawArrays(GL_TRIANGLES, this->属性->元素[属性]->起始顶点, this->属性->元素[属性]->顶点数量);
}

void C动态物体::清除备用资料()
{
    delete 备用资料; 
    备用资料 = nullptr;
    delete 全局变换根节点; 
    全局变换根节点 = nullptr;
    delete 根节点;
    根节点 = nullptr;
    delete 蒙皮数据;
    蒙皮数据 = nullptr;
    delete 骨骼名称;
    骨骼名称 = nullptr;
    delete 物体控制顶点集;
    物体控制顶点集 = nullptr;
    delete 三角形索引;
    三角形索引 = nullptr;
    delete 连接顶点;
    连接顶点 = nullptr;
    delete 索引记录;
    索引记录 = nullptr;
    delete 动画数据;
    动画数据 = nullptr;
    FbxNode* fbx根节点 = 0;
    FbxScene* 场景 = 0;
    delete 动画轨道储存;
    动画轨道储存 = nullptr;
}

C动态物体::~C动态物体()
{
    delete 属性; 
    属性 = nullptr;
}