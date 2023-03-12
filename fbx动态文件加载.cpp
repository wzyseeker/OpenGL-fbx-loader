#include"fbx��̬�ļ�����.h"

C��̬����::C��̬����(C������Դ* ������Դ)
{
	this->������Դ = ������Դ;
}

int C��̬����::����fbx�ļ�(wstring �ļ�·��, wstring ��������)
{
    int ��� = 0;
    UINT j = 0;
    FbxManager* lFBX���� = NULL;
    FbxScene* l���� = NULL;

    this->�������� = ��������;

    lFBX���� = FbxManager::Create();

    FbxIOSettings* ���� = FbxIOSettings::Create(lFBX����, IOSROOT);
    lFBX����->SetIOSettings(����);
    FbxImporter* l���� = FbxImporter::Create(lFBX����, "");

    char* �ļ����� = 0;
    FbxWCToUTF8(�ļ�·��.c_str(), �ļ�����, 0);

    if (!l����->Initialize(�ļ�����, -1, ����))
    {
        string bug = "fbx�ļ�����-��̬���壺fbx�������";
        bug += l����->GetStatus().GetErrorString();
        bug += " line:";
        bug += to_string(__LINE__) + "\n";
        OutputDebugStringA(bug.c_str());
        exit(0);
    }

    l���� = FbxScene::Create(lFBX����, "myScene");

    l����->Import(l����);
    l����->Destroy();

    �������� = new S��������;
    ���� = new C��������;
    ȫ�ֱ任���ڵ� = new vector<vector<vector<S�任�ڵ�2>>>;
    ���ڵ� = new S�任�ڵ�;
    ��Ƥ���� = new S��Ƥ����;
    �������� = new vector<wstring>;
    ������ƶ��㼯 = new vector<S������ƶ���>;
    ���������� = new vector<array<int, 3>>;
    ���Ӷ��� = new vector<S����>;
    ������¼ = new vector<array<int, 3>>;
    �������� = new S��������;
    ����������� = new vector<S�����������>;
    ���ڵ�->�ڵ����� = L"���ڵ�";
    ��������->push_back(L"");
    FbxNode* l���ڵ� = l����->GetRootNode();

    this->����->����.push_back(������Դ->����ͼ);

    if (l���ڵ�)
        for (int i = 0; i < l���ڵ�->GetChildCount(); i++)
            ���ؽڵ�(l���ڵ�->GetChild(i));
    ���ز��(l����);
    ���������();
    �������� = ��������->size();
    //����任 = new mat4[��������];

    ���ض���(l����);
    �ϲ����嶯����Ϣ();

    if (�ϲ�������Ƥ())
        return - 1;

    ���ɹ�������();

    ���㵥Ԫ��С = sizeof(S����);

    if (��������->���㼯.size() == 0)
    {
        wstring bug = L"fbx�ļ�����-��̬���壺�޶��� line:";
        bug += to_wstring(__LINE__) + L"\n";
        OutputDebugString(bug.c_str());
        exit(0);
    }

    �������� = ��������->���㼯.size();
    ���㲼�� = FVFλ�� | FVF������ | FVF��������;

    S����* ���㼯 = new S����[��������->���㼯.size()];
    for (int i = 0; i < ��������->���㼯.size(); i++)
        ���㼯[i] = ��������->���㼯[i];
    
    glCreateVertexArrays(1, &�������);
    glBindVertexArray(�������);

    glCreateBuffers(1, &���㻺��);
    glBindBuffer(GL_ARRAY_BUFFER, ���㻺��);
    glBufferData(GL_ARRAY_BUFFER, ��������->���㼯.size() * sizeof(S����), ���㼯, GL_STATIC_DRAW);

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
    
    lFBX����->Destroy();

    delete[] ���㼯;

    return ���;
}

void C��̬����::���ز��(FbxScene* p����)
{
    int i;
    FbxNode* l���ڵ� = p����->GetRootNode();
    ���ڵ�->�ӽڵ����� = l���ڵ�->GetChildCount();
    if (!���ڵ�->�ӽڵ� && ���ڵ�->�ӽڵ����� > 0)
        ���ڵ�->�ӽڵ� = new S�任�ڵ�[l���ڵ�->GetChildCount()];

    for (i = 0; i < l���ڵ�->GetChildCount(); i++)
    {
        if (!���ڵ�->�ӽڵ�[i].���ڵ�) ���ڵ�->�ӽڵ�[i].���ڵ� = ���ڵ�;
        ���ز��(l���ڵ�->GetChild(i), &���ڵ�->�ӽڵ�[i]);
    }
}

void C��̬����::���ز��(FbxNode* p�ڵ�, S�任�ڵ�* �ڵ�)
{
    WCHAR* l�ڵ�����;
    int i = 0;
    int j = 0;

    FbxUTF8ToWC(p�ڵ�->GetName(), l�ڵ�����, 0);
    �ڵ�->�ڵ����� = l�ڵ�����;
    �ڵ�->�ӽڵ����� = p�ڵ�->GetChildCount();
    if (!�ڵ�->�ӽڵ� && �ڵ�->�ӽڵ����� > 0)
        if (�ڵ�->�ӽڵ�����)
            �ڵ�->�ӽڵ� = new S�任�ڵ�[p�ڵ�->GetChildCount()];

    for (i = 0; i < p�ڵ�->GetChildCount(); i++)
    {
        �ڵ�->�ӽڵ�[i].���ڵ� = �ڵ�;
        ���ز��(p�ڵ�->GetChild(i), &�ڵ�->�ӽڵ�[i]);
    }
}

void C��̬����::����������(wstring ��������, S�任�ڵ�*& Ŀ��ڵ�)
{
    int i = 0;

    for (i = 0; i < ���ڵ�->�ӽڵ�����; i++)
    {
        ����������(&���ڵ�->�ӽڵ�[i], ��������, Ŀ��ڵ�);
    }
}

void C��̬����::����������(S�任�ڵ�* �任�ڵ�, wstring ��������, S�任�ڵ�*& Ŀ��ڵ�)
{
    int i = 0;

    if (�任�ڵ�->�ڵ����� == ��������)
    {
        Ŀ��ڵ� = �任�ڵ�;
        return;
    }

    for (i = 0; i < �任�ڵ�->�ӽڵ�����; i++)
    {
        ����������(&�任�ڵ�->�ӽڵ�[i], ��������, Ŀ��ڵ�);
    }
}

void C��̬����::���������()
{
    S�任�ڵ�* p�任�ڵ� = nullptr;
    S�任�ڵ�* p�任�ڵ�2 = nullptr;

    for (int i = 0; i < (*��������).size(); i++)
    {
        p�任�ڵ� = nullptr;
        ����������((*��������)[i].c_str(), p�任�ڵ�);

        if (p�任�ڵ�)
        {
            p�任�ڵ�2 = nullptr;
            p�任�ڵ�2 = ���ݸ��ڵ�(p�任�ڵ�);
            ����������(p�任�ڵ�2);
        }
    }
}

C��̬����::S�任�ڵ�* C��̬����::���ݸ��ڵ�(S�任�ڵ�* p�����ڵ�)
{
    S�任�ڵ�* p�����ڵ�2 = p�����ڵ�;
    if (p�����ڵ�2->���ڵ�)
        while (p�����ڵ�2->���ڵ�->�ڵ����� != L"���ڵ�")
        {
            p�����ڵ�2 = p�����ڵ�2->���ڵ�;
        }

    return p�����ڵ�2;
}

void C��̬����::����������(S�任�ڵ�* p�����ڵ�)
{
    bool �Ƿ�δ��¼ = false;

    �Ƿ�δ��¼ = true;
    for (int j = 0; j < (*��������).size(); j++)
    {
        if ((*��������)[j].c_str() == p�����ڵ�->�ڵ�����)
        {
            �Ƿ�δ��¼ = false;
        }
    }
    if (�Ƿ�δ��¼)
    {
        (*��������).push_back(p�����ڵ�->�ڵ�����);
    }

    for (int i = 0; i < p�����ڵ�->�ӽڵ�����; i++)
    {
        ����������(&p�����ڵ�->�ӽڵ�[i]);
    }
}

void C��̬����::���ؽڵ�(FbxNode* p�ڵ�)
{
    FbxNodeAttribute::EType �ڵ�����{};

    if (p�ڵ�->GetNodeAttribute())
    {
        �ڵ����� = p�ڵ�->GetNodeAttribute()->GetAttributeType();

        switch (�ڵ�����)
        {
        case FbxNodeAttribute::eSkeleton:
            ���ع�������(p�ڵ�);
            break;

        case FbxNodeAttribute::eMesh:
            ��������(p�ڵ�);
            ������Ƥ��Ϣ(p�ڵ�);
            break;

        default:
            break;
        }
    }

    for (int i = 0; i < p�ڵ�->GetChildCount(); ++i)
    {
        ���ؽڵ�(p�ڵ�->GetChild(i));
    }
}

void C��̬����::���ع�������(FbxNode* p�����ڵ�)
{
    WCHAR* l�������� = 0;
    size_t l����;

    FbxUTF8ToWC(p�����ڵ�->GetName(), l��������, &l����);

    ��������++;
    (*��������).resize(��������);
    (*��������)[�������� - 1] = l��������;
}

void C��̬����::��������(FbxNode* p����ڵ�)
{
    FbxMesh* p���� = p����ڵ�->GetMesh();
    if (p���� == NULL) return;

    vec3 lλ��[3]{};
    vec3 l������[3]{};
    vec3 l������[3]{};
    vec2 l��������[4]{};
    UINT i = 0;
    UINT j = 0;
    UINT k = 0;
    UINT l = 0;
    UINT m = 0;
    UINT l��������� = p����->GetPolygonCount();
    UINT l��ǰ������� = 0;
    uint l��ǰ�������� = 0;
    UINT l����ζ������� = 0;
    UINT l��ǰ�������� = 0;
    UINT l������������ = 0;
    int ��ǰ����ζ�������;

    for (i = 0; i < l���������; i++)
        ��ǰ����ζ������� = p����->GetPolygonSize(i);

    UINT ���ƶ������� = p����->GetControlPointsCount();

    WCHAR* ��������;
    FbxUTF8ToWC(p����ڵ�->GetName(), ��������);

    (*������ƶ��㼯).resize((*������ƶ��㼯).size() + 1);
    (*������ƶ��㼯)[(*������ƶ��㼯).size() - 1].�������� = ��������;
    (*������ƶ��㼯)[(*������ƶ��㼯).size() - 1].���ƶ��㼯.resize(���ƶ�������);

    for (i = 0; i < l���������; i++)
    {
        l����ζ������� = p����->GetPolygonSize(i);
        for (j = 0; j < l����ζ�������; j++)
        {
            int l���ƶ������� = p����->GetPolygonVertex(i, j);
            int id;
            FbxVector4* ���ƶ��� = p����->GetControlPoints();
            S���� ����;

            ����.λ��.x = ���ƶ���[l���ƶ�������].mData[0];
            ����.λ��.y = ���ƶ���[l���ƶ�������].mData[1];
            ����.λ��.z = ���ƶ���[l���ƶ�������].mData[2];

            FbxGeometryElementUV* p�������� = p����->GetElementUV(0);

            if (p��������)
                switch (p��������->GetMappingMode())
                {
                case FbxGeometryElement::eByControlPoint:
                    switch (p��������->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                        ����.��������.x = p��������->GetDirectArray().GetAt(l���ƶ�������).mData[0];
                        ����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(l���ƶ�������).mData[1];
                        break;

                    case FbxGeometryElement::eIndexToDirect:
                        id = p��������->GetIndexArray().GetAt(l���ƶ�������);
                        ����.��������.x = p��������->GetDirectArray().GetAt(id).mData[0];
                        ����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(id).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;

                case FbxGeometryElement::eByPolygonVertex:
                    switch (p��������->GetReferenceMode())
                    {
                    case FbxGeometryElement::eDirect:
                    case FbxGeometryElement::eIndexToDirect:
                        ����.��������.x = p��������->GetDirectArray().GetAt(p����->GetTextureUVIndex(i, j)).mData[0];
                        ����.��������.y = 1.0f - p��������->GetDirectArray().GetAt(p����->GetTextureUVIndex(i, j)).mData[1];
                        break;

                    default:
                        break;
                    }
                    break;
                }

            FbxGeometryElementNormal* p������ = p����->GetElementNormal(0);
            switch (p������->GetMappingMode())
            {
            case FbxGeometryElement::eByControlPoint:
                switch (p������->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    ����.������.x = p������->GetDirectArray().GetAt(l���ƶ�������).mData[0];
                    ����.������.y = p������->GetDirectArray().GetAt(l���ƶ�������).mData[1];
                    ����.������.z = p������->GetDirectArray().GetAt(l���ƶ�������).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p������->GetIndexArray().GetAt(l���ƶ�������);
                    ����.������.x = p������->GetDirectArray().GetAt(id).mData[0];
                    ����.������.y = p������->GetDirectArray().GetAt(id).mData[1];
                    ����.������.z = p������->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;

            case FbxGeometryElement::eByPolygonVertex:
                switch (p������->GetReferenceMode())
                {
                case FbxGeometryElement::eDirect:
                    ����.������.x = p������->GetDirectArray().GetAt(l��ǰ�������).mData[0];
                    ����.������.y = p������->GetDirectArray().GetAt(l��ǰ�������).mData[1];
                    ����.������.z = p������->GetDirectArray().GetAt(l��ǰ�������).mData[2];
                    break;

                case FbxGeometryElement::eIndexToDirect:
                    id = p������->GetIndexArray().GetAt(l��ǰ�������);
                    ����.������.x = p������->GetDirectArray().GetAt(id).mData[0];
                    ����.������.y = p������->GetDirectArray().GetAt(id).mData[1];
                    ����.������.z = p������->GetDirectArray().GetAt(id).mData[2];
                    break;

                default:
                    break;
                }
                break;
            }

            uint k = 0;

            k = (*������ƶ��㼯)[(*������ƶ��㼯).size() - 1].���ƶ��㼯[l���ƶ�������].size();
            (*������ƶ��㼯)[(*������ƶ��㼯).size() - 1].���ƶ��㼯[l���ƶ�������].resize(k + 1);
            (*������ƶ��㼯)[(*������ƶ��㼯).size() - 1].���ƶ��㼯[l���ƶ�������][k] = ����;
            array<int, 3> ���� = { ��������, l���ƶ�������, k };
            ������¼->push_back(����);
            �������++;
            l��ǰ�������++;
        }

        for (k = 0; k < l����ζ������� - 2; k++)
        {
            (*����������).resize((*����������).size() + 1);
            (*����������)[(*����������).size() - 1][0] = ������� - l����ζ�������;
            (*����������)[(*����������).size() - 1][1] = ������� - k - 2;
            (*����������)[(*����������).size() - 1][2] = ������� - k - 1;
            �������� += 3;
            l��ǰ�������� += 3;
        }
    }

    ��������++;

    C��������::S����* ���� = new C��������::S����;

    FbxTime ʱ�� = 0;

    WCHAR* �������� = 0;
    FbxUTF8ToWC(p����ڵ�->GetName(), ��������, 0);
    ����->�������� = ��������;
    ����->�������� = l��ǰ��������;
    ����->��ʼ���� = �������� - l��ǰ��������;

    FbxAMatrix ȫ�־��� = p����ڵ�->EvaluateGlobalTransform(ʱ��);
    FbxAMatrix ���ؾ��� = p����ڵ�->EvaluateLocalTransform(ʱ��);
    ����->�任 = fbx����תmat4(ȫ�־���);

    ���ز���(p����ڵ�, ����);

    this->����->���Ԫ��(����);
}

mat4 C��̬����::fbx����תmat4(FbxAMatrix fbx����)
{
    mat4 ���� = mat4(1.0f);

    ����[0][0] = fbx����.mData[0][0]; ����[0][1] = fbx����.mData[0][1]; ����[0][2] = fbx����.mData[0][2];
    ����[1][0] = fbx����.mData[1][0]; ����[1][1] = fbx����.mData[1][1]; ����[1][2] = fbx����.mData[1][2];
    ����[2][0] = fbx����.mData[2][0]; ����[2][1] = fbx����.mData[2][1]; ����[2][2] = fbx����.mData[2][2];
    ����[3][0] = fbx����.mData[3][0]; ����[3][1] = fbx����.mData[3][1]; ����[3][2] = fbx����.mData[3][2];

    return ����;
}

void C��̬����::���ز���(FbxNode* p����ڵ�, C��������::S����* ����)
{
    FbxMesh* p���� = p����ڵ�->GetMesh();
    int �������� = 0;

    if (p���� && p����ڵ�)
    {
        �������� = p����ڵ�->GetMaterialCount();
    }

    if (�������� > 0)
    {
        for (int i = 0; i < ��������; i++)
        {
            FbxSurfaceMaterial* p������� = p����ڵ�->GetMaterial(i);

            ���ز�������(p�������, ����);
        }
    }
    else  //Ĭ�ϲ���
    {
        ����->����.������ = { 1.0f, 1.0f, 1.0f, 1.0f };
        ����->����.������ = { 0.0f, 0.0f, 0.0f };
        ����->����.�Է��� = { 0.0f, 0.0f, 0.0f };
        ����->����.����� = 0.0f;
        ����->����.��͸���� = 1.0f;
        ����->����.�߹⼶�� = 1.0f;
        ����->�������� = 0;
    }
}

void C��̬����::������Ƥ��Ϣ(FbxNode* p����ڵ�)
{
    int i, j, k;
    int b = 0;
    int l������ = 0;
    int l�������� = 0;
    FbxCluster* l��;
    WCHAR* l�������� = 0;
    WCHAR* l�������� = 0;
    mat4 ��ת���� = mat4(1.0f);
    mat4 ��ת = mat4(1.0f);
    mat4 ��ת����2 = mat4(1.0f);
    FbxAMatrix �ο�ȫ�ֳ�ʼ�任;
    FbxAMatrix �ο�ȫ�ֵ�ǰ�任;
    FbxAMatrix ����ȫ�ֳ�ʼ�任;
    FbxAMatrix ����ȫ�ֵ�ǰ�任;
    FbxAMatrix ��ȫ�ֳ�ʼ�任;
    FbxAMatrix ��ȫ�ֵ�ǰ�任;

    FbxAMatrix �ο�������;
    FbxAMatrix ����������;
    FbxAMatrix �ؼ�����;

    FbxAMatrix �ع�����ʼ�任;
    FbxAMatrix �ع�����ǰ�任��;


    FbxGeometry* p���� = (FbxMesh*)p����ڵ�->GetNodeAttribute();
    l������ = p����->GetDeformerCount(FbxDeformer::eSkin);
    FbxUTF8ToWC(p����ڵ�->GetName(), l��������, 0);
    ��Ƥ����->��������.resize(��Ƥ����->��������.size() + 1);
    ��Ƥ����->��������[��Ƥ����->��������.size() - 1].�������� = l��������;

    for (i = 0; i != l������; i++)
    {
        l�������� = ((FbxSkin*)p����->GetDeformer(i, FbxDeformer::eSkin))->GetClusterCount();
        ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����.resize(l��������);
        for (j = 0; j != l��������; j++)
        {
            l�� = ((FbxSkin*)p����->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);

            FbxUTF8ToWC(l��->GetLink()->GetName(), l��������, 0);
            ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].�������� = l��������;

            FbxCluster::ELinkMode ��ģʽ = l��->GetLinkMode();

            if (��ģʽ == FbxCluster::eAdditive && l��->GetAssociateModel())
            {
                l��->GetTransformAssociateModelMatrix(����ȫ�ֳ�ʼ�任);
                ���������� = ��ȡ������(l��->GetAssociateModel());
                ����ȫ�ֳ�ʼ�任 *= ����������;
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].����ȫ�ֳ�ʼ�任 = fbx����תmat4(����ȫ�ֳ�ʼ�任);
                //����ȫ�ֵ�ǰ�任 = ��ȡȫ�ֱ任(l��->GetAssociateModel(), ʱ��, ����);

                l��->GetTransformMatrix(�ο�ȫ�ֳ�ʼ�任);
                ���������� = ��ȡ������(p����ڵ�);
                �ο�ȫ�ֳ�ʼ�任 *= �ο�������;
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].�ο�ȫ�ֳ�ʼ�任 = fbx����תmat4(�ο�ȫ�ֳ�ʼ�任);
                //�ο�ȫ�ֵ�ǰ�任 = ȫ�ֱ任;

                l��->GetTransformLinkMatrix(��ȫ�ֳ�ʼ�任);
                �ؼ����� = ��ȡ������(l��->GetLink());
                ��ȫ�ֳ�ʼ�任 *= �ؼ�����;
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].��ȫ�ֳ�ʼ�任 = fbx����תmat4(��ȫ�ֳ�ʼ�任);
                //��ȫ�ֵ�ǰ�任 = ��ȡȫ�ֱ任(l��->GetLink(), ʱ��, ����);

                //����任 = �ο�ȫ�ֳ�ʼ�任.Inverse() * ����ȫ�ֳ�ʼ�任 * ����ȫ�ֵ�ǰ�任.Inverse() *
                //    ��ȫ�ֵ�ǰ�任 * ��ȫ�ֳ�ʼ�任.Inverse() * ����ȫ�ֳ�ʼ�任;
            }
            else
            {
                l��->GetTransformMatrix(�ο�ȫ�ֳ�ʼ�任);
                //����ȫ�ֵ�ǰ�任 = ȫ�ֱ任;
                �ο������� = ��ȡ������(p����ڵ�);
                �ο�ȫ�ֳ�ʼ�任 *= �ο�������;
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].�ο�ȫ�ֳ�ʼ�任 = fbx����תmat4(�ο�ȫ�ֳ�ʼ�任);

                l��->GetTransformLinkMatrix(��ȫ�ֳ�ʼ�任);
                //��ȫ�ֵ�ǰ�任 = ��ȡȫ�ֱ任(l��->GetLink(), ʱ��, ����);
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].��ȫ�ֳ�ʼ�任 = fbx����תmat4(��ȫ�ֳ�ʼ�任);

                �ع�����ʼ�任 = ��ȫ�ֳ�ʼ�任.Inverse() * �ο�ȫ�ֳ�ʼ�任;
                �ع�����ǰ�任�� = ����ȫ�ֵ�ǰ�任.Inverse() * ��ȫ�ֵ�ǰ�任;

                //����任 = �ع�����ǰ�任�� * �ع�����ʼ�任;
            }
        }

        ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����.resize(l��������);
        for (j = 0; j != l��������; j++)
        {
            l�� = ((FbxSkin*)p����->GetDeformer(i, FbxDeformer::eSkin))->GetCluster(j);

            int ���ƶ������� = l��->GetControlPointIndicesCount();
            int* ���ƶ������� = l��->GetControlPointIndices();
            double* ���ƶ���Ȩ�� = l��->GetControlPointWeights();

            for (int k = 0; k < ���ƶ�������; k++)
            {
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].Ȩ����.push_back(���ƶ���Ȩ��[k]);
                ��Ƥ����->��������[��Ƥ����->��������.size() - 1].����[j].������.push_back(���ƶ�������[k]);
            }
        }
    }
}

int C��̬����::�ϲ�������Ƥ()
{
    int ��ǰ���� = 0;
    int ��С�������� = 0;

    if (�������� > 200)
    {
        OutputDebugString(L"������������200��");
        return -1;
    }

    for (int i = 0; i < (*������ƶ��㼯).size(); i++)
    {
        for (int i2 = 0; i2 < (*������ƶ��㼯)[i].���ƶ��㼯.size(); i2++)
        {
            for (int j2 = 0; j2 < (*������ƶ��㼯)[i].���ƶ��㼯[i2].size(); j2++)
            {
                int ������������ = 0;

                for (int j = 0; j < ��Ƥ����->��������.size(); j++)
                {
                    if (��Ƥ����->��������[j].�������� == (*������ƶ��㼯)[i].��������)
                    {
                        for (int k = 0; k < ��Ƥ����->��������[j].����.size(); k++)
                        {
                            for (int l = 0; l < ��Ƥ����->��������[j].����[k].������.size(); l++)
                            {
                                if (��Ƥ����->��������[i].����[k].������[l] == i2)
                                {
                                    for (int m = 0; m < ��������; m++)
                                    {
                                        if (��Ƥ����->��������[j].����[k].�������� == (*��������)[m])
                                        {
                                            if (��Ƥ����->��������[j].����[k].Ȩ����[l] > 0.001)
                                            {
                                                //������СȨ�ع���
                                                if (������������ == d��������������)
                                                {
                                                    float ��СȨ�� = 1.0f;

                                                    for (int n = 0; n < d�������������� - 1; n++)
                                                    {
                                                        if (��СȨ�� > (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].����Ȩ��[n])
                                                        {
                                                            ��С�������� = n;
                                                            ��СȨ�� = (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].����Ȩ��[n];
                                                        }
                                                    }

                                                    if (��СȨ�� < ��Ƥ����->��������[j].����[k].Ȩ����[l])
                                                    {
                                                        (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].����Ȩ��[��С��������] =
                                                            ��Ƥ����->��������[j].����[k].Ȩ����[l] + ��СȨ��;
                                                        (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].������������[��С��������] = m;
                                                    }

                                                    continue;
                                                }

                                                (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].������������[������������] = m;
                                                if (������������ < d�������������� - 1)
                                                    (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].����Ȩ��[������������] =
                                                    ��Ƥ����->��������[j].����[k].Ȩ����[l];
                                                ������������++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                for (int k = ������������; k < d��������������; k++)
                {
                    (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].������������[k] = 0;
                    if (k < d�������������� - 1) (*������ƶ��㼯)[i].���ƶ��㼯[i2][j2].����Ȩ��[k] = 0;
                }
            }
        }
    }

    for (int i = 0; i < (*����������).size(); i++)
    {
        ��������->���㼯.resize(��������->���㼯.size() + 3);
        for (int j = 0; j < (*������¼).size(); j++)
        {
            if ((*����������)[i][0] == j)
                ��������->���㼯[��������->���㼯.size() - 3] = (*������ƶ��㼯)[(*������¼)[j][0]].���ƶ��㼯[(*������¼)[j][1]][(*������¼)[j][2]];

            if ((*����������)[i][1] == j)
                ��������->���㼯[��������->���㼯.size() - 2] = (*������ƶ��㼯)[(*������¼)[j][0]].���ƶ��㼯[(*������¼)[j][1]][(*������¼)[j][2]];

            if ((*����������)[i][2] == j)
                ��������->���㼯[��������->���㼯.size() - 1] = (*������ƶ��㼯)[(*������¼)[j][0]].���ƶ��㼯[(*������¼)[j][1]][(*������¼)[j][2]];
        }
    }

    return 0;
}

void C��̬����::���ز�������(FbxSurfaceMaterial* p�������, C��������::S����* ����)
{
    p�������->GetName();

    if (p�������->GetClassId().Is(FbxSurfacePhong::ClassId))
    {
        FbxDouble3 ������ = ((FbxSurfacePhong*)p�������)->Diffuse;
        ����->����.������.x = ������.mData[0];
        ����->����.������.y = ������.mData[1];
        ����->����.������.z = ������.mData[2];

        FbxDouble3 �Է��� = ((FbxSurfacePhong*)p�������)->Emissive;
        ����->����.�Է���.x = �Է���.mData[0];
        ����->����.�Է���.y = �Է���.mData[1];
        ����->����.�Է���.z = �Է���.mData[2];

        FbxDouble ��͸���� = 1.0 - ((FbxSurfacePhong*)p�������)->TransparencyFactor;
        ����->����.������.w = ��͸����;

        FbxDouble ����� = ((FbxSurfacePhong*)p�������)->Shininess;
        ����->����.����� = �����;

        FbxDouble �߹�ȼ� = ((FbxSurfacePhong*)p�������)->SpecularFactor;
        ����->����.�߹⼶�� = �߹�ȼ�;

        if (����->����.�߹⼶�� < 1)����->����.�߹⼶�� = 1;

        FbxDouble ������ = 1.0 - ((FbxSurfacePhong*)p�������)->ReflectionFactor;
    }

    ��������(p�������, ����);
}

void C��̬����::��������(FbxSurfaceMaterial* p�������, C��������::S����* ����)
{
    int i;
    int k = 0;
    int ��� = 1;
    FbxProperty ��������;
    WCHAR* ·�� = 0;

    for (i = 0; i < FbxLayerElement::sTypeTextureCount; i++)
    {
        �������� = p�������->FindProperty(FbxLayerElement::sTextureChannelNames[i]);
        if (��������.IsValid())
        {
            int textureCount = ��������.GetSrcObjectCount();

            for (int j = 0; j < textureCount; ++j)
            {
                FbxFileTexture* p���� = FbxCast<FbxFileTexture>(��������.GetSrcObject(j));
                if (p����)
                {
                    FbxUTF8ToWC(p����->GetFileName(), ·��, 0);
                    for (k = 0; k < ��������->·����.size(); k++)
                    {
                        if (��������->·����[k].compare(·��) == 0 && ����->�������� == 0)
                        {
                            ����->�������� = k + 1;
                            break;
                        }
                    }

                    if (����->�������� == 0)
                    {
                        ��������->·����.resize(��������->·����.size() + 1);
                        ��������->·����[��������->·����.size() - 1] = ·��;

                        wstring �ļ�����;
                        bool �Ƿ���¼ = 0;
                        for (int i = 0; i < wcslen(·��); i++)
                        {
                            if (�Ƿ���¼) �ļ����� += ·��[i];
                            if (·��[i] == '.')
                            {
                                �Ƿ���¼ = 1;
                                �ļ�����.clear();
                            }
                        }

                        this->����->����.resize(this->����->����.size() + 1);

                        unsigned char* ͼ��;
                        char ����·��A[1024];
                        int ���� = WideCharToMultiByte(CP_ACP, 0, ·��, wcslen(·��), ����·��A, 1024, 0, 0);
                        ����·��A[����] = '\0';

                        if (!(ͼ�� = SOIL_load_image(����·��A, &this->����->����[this->����->����.size() - 1].��,
                            &this->����->����[this->����->����.size() - 1].��, &this->����->����[this->����->����.size() - 1].ͨ��, SOIL_LOAD_RGBA)))
                        {
                            wstring bug = L"fbx�ļ�����-��̬���壺����ģ�Ͳ���ʱδ�ҵ���ͼ�ļ�";
                            OutputDebugString(bug.c_str());
                            exit(0);
                        }
                        glGenTextures(1, &this->����->����[this->����->����.size() - 1].����);
                        glBindTexture(GL_TEXTURE_2D, this->����->����[this->����->����.size() - 1].����);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->����->����[this->����->����.size() - 1].��,
                            this->����->����[this->����->����.size() - 1].��, 0, GL_RGBA, GL_UNSIGNED_BYTE, ͼ��);
                        delete[] ͼ��;
                        ����->�������� = this->����->����.size() - 1;
                    }
                }
            }
        }
    }
}

FbxAMatrix C��̬����::��ȡȫ�ֱ任(FbxNode* �ڵ�, const FbxTime& ʱ��, FbxAMatrix* ��ȫ�ֱ任)
{
    FbxAMatrix ȫ�ֱ任;
    bool �ҵ�ȫ�ֱ任 = false;

    FbxPose* ���� = nullptr;
    ���� = ����->GetPose(0);
    
    if (����)
    {
        int �ڵ����� = ����->Find(�ڵ�);

        if (�ڵ����� > -1)
        {
            if (����->IsBindPose() || !����->IsLocalMatrix(�ڵ�����))
            {
                ȫ�ֱ任 = ��ȡ���;���(����, �ڵ�����);
            }
            else
            {
                FbxAMatrix l��ȫ�ֱ任;

                if (��ȫ�ֱ任)
                {
                    l��ȫ�ֱ任 = *��ȫ�ֱ任;
                }
                else
                {
                    if (�ڵ�->GetParent())
                    {
                        l��ȫ�ֱ任 = ��ȡȫ�ֱ任(�ڵ�->GetParent(), ʱ��);
                    }
                }

                FbxAMatrix ���ر任 = ��ȡ���;���(����, �ڵ�����);
                ȫ�ֱ任 = l��ȫ�ֱ任 * ���ر任;
            }

            �ҵ�ȫ�ֱ任 = true;
        }
    }

    if (!�ҵ�ȫ�ֱ任)
    {
        ȫ�ֱ任 = �ڵ�->EvaluateGlobalTransform(ʱ��);
    }

    return ȫ�ֱ任;
}

FbxAMatrix C��̬����::��ȡ���;���(FbxPose* ����, int �ڵ�����)
{
    FbxAMatrix ���ͱ任;
    FbxMatrix �任 = ����->GetMatrix(�ڵ�����);

    memcpy((double*)���ͱ任, (double*)�任, sizeof(�任.mData));

    return ���ͱ任;
}

FbxAMatrix C��̬����::��ȡ������(FbxNode* �ڵ�)
{
    const FbxVector4 lT = �ڵ�->GetGeometricTranslation(FbxNode::eSourcePivot);
    const FbxVector4 lR = �ڵ�->GetGeometricRotation(FbxNode::eSourcePivot);
    const FbxVector4 lS = �ڵ�->GetGeometricScaling(FbxNode::eSourcePivot);

    return FbxAMatrix(lT, lR, lS);
}

void C��̬����::���ض���(FbxScene* p����)
{
    ��������->Ƭ��.resize(p����->GetSrcObjectCount<FbxAnimStack>());

    char lTimeString[256]{};

    FbxTime   l֡ʱ��;
    FbxTimeSpan lʱ����;
    FbxTime     l��ʼ, l����;
    FbxGlobalSettings* p�趨 = 0;
    int l֡���� = 0;
    int lʱ = 0;
    int l�� = 0;
    int l�� = 0;
    int l֡ = 0;
    int l�� = 0;
    int l��ֵ = 0;

    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);
    ��������->֡���� = l֡����;

    p�趨 = &p����->GetGlobalSettings();

    p�趨->GetTimelineDefaultTimeSpan(lʱ����);
    l��ʼ = lʱ����.GetStart();
    l���� = lʱ����.GetStop();
    l��ʼ.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    ��������->��ʼ֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
    l����.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    ��������->����֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;

    fbx���ڵ� = p����->GetRootNode();
    ���� = p����;

    for (UINT i = 0; i < p����->GetSrcObjectCount<FbxAnimStack>(); i++)
    {
        FbxAnimStack* l����Ƭ�� = p����->GetSrcObject<FbxAnimStack>(i);

        WCHAR* Ƭ������ = 0;
        FbxUTF8ToWC(l����Ƭ��->GetName(), Ƭ������, 0);
        ��������->Ƭ��[i].Ƭ������ = Ƭ������;

        p����->SetCurrentAnimationStack(l����Ƭ��);

        (*ȫ�ֱ任���ڵ�).resize((*ȫ�ֱ任���ڵ�).size() + 1);

        ���ض���Ƭ��(l����Ƭ��, p����->GetRootNode(), i);
    }
}

void C��̬����::���ض���Ƭ��(FbxAnimStack* p����Ƭ��, FbxNode* p�ڵ�, UINT Ƭ������)
{
    int l;
    int ���������� = p����Ƭ��->GetMemberCount<FbxAnimLayer>();
    int ��Ч������ = p����Ƭ��->GetMemberCount<FbxAudioLayer>();
    FbxTimeSpan ʱ����;
    FbxTime l֡ʱ��;
    FbxTime l��ʼ, l����;
    int l֡���� = 0;
    int lʱ = 0;
    int l�� = 0;
    int l�� = 0;
    int l֡ = 0;
    int l�� = 0;
    int l��ֵ = 0;

    if (����������)
        ��������->Ƭ��[Ƭ������].������.resize(����������);

    if (��Ч������)
        ��������->Ƭ��[Ƭ������].��Ч��.resize(��Ч������);

    ʱ���� = p����Ƭ��->GetLocalTimeSpan();
    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

    l��ʼ = ʱ����.GetStart();
    l���� = ʱ����.GetStop();
    l��ʼ.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    ��������->Ƭ��[Ƭ������].��ʼ֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
    l����.GetTime(lʱ, l��, l��, l֡, l��, l��ֵ);
    ��������->Ƭ��[Ƭ������].����֡ = lʱ * l֡���� * l֡���� * l֡���� + l�� * l֡���� * l֡���� + l�� * l֡���� + l֡;
    ��������->Ƭ��[Ƭ������].֡���� = l֡����;
    ��������->Ƭ��[Ƭ������].��ʼʱ�� = l��ʼ;

    for (l = 0; l < ����������; l++)
    {
        FbxAnimLayer* l������ = p����Ƭ��->GetMember<FbxAnimLayer>(l);

        WCHAR* ���������� = 0;
        FbxUTF8ToWC(l������->GetName(), ����������);
        ��������->Ƭ��[Ƭ������].������[l].����������, ���������� = ����������;

        ���ض�����(l������, p�ڵ�, Ƭ������, l);
    }

    for (l = 0; l < ��Ч������; l++)
    {
        FbxAudioLayer* l��Ч�� = p����Ƭ��->GetMember<FbxAudioLayer>(l);
        ������Ч��(l��Ч��, l, Ƭ������);
    }
}

void C��̬����::������Ч��(FbxAudioLayer* p��Ч��, UINT ��Ч������, UINT Ƭ������)
{
    int l��������;
    WCHAR* l��Ч������ = 0;
    WCHAR* l�������� = 0;

    l�������� = p��Ч��->GetMemberCount<FbxAudio>();

    ��������->Ƭ��[Ƭ������].��Ч��[��Ч������].����.resize(l��������);

    FbxUTF8ToWC(p��Ч��->GetName(), l��Ч������);
    ��������->Ƭ��[Ƭ������].��Ч��[��Ч������].��Ч������ = l��Ч������;

    for (int i = 0; i < l��������; i++)
    {
        FbxAudio* l���� = p��Ч��->GetMember<FbxAudio>(i);
        FbxUTF8ToWC(l����->GetName(), l��������, 0);
        ��������->Ƭ��[Ƭ������].��Ч��[��Ч������].����[i].�������� = l��������;
    }
}

void C��̬����::���ض�����(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������)
{
    int lģ������;
    WCHAR* l��������;

    for (lģ������ = 0; lģ������ < p�ڵ�->GetChildCount(); lģ������++)
    {
        ���ض�����(p������, p�ڵ�->GetChild(lģ������), Ƭ������, ����������);
    }

    FbxUTF8ToWC(p�ڵ�->GetName(), l��������, 0);
    ��������->Ƭ��[Ƭ������].������[����������].����.resize(��������->Ƭ��[Ƭ������].������[����������].����.size() + 1);
    ��������->Ƭ��[Ƭ������].������[����������].����[��������->Ƭ��[Ƭ������].������[����������].����.size() - 1].�������� = l��������;

    ���ض���ͨ��(p������, p�ڵ�, Ƭ������, ����������, ��������->Ƭ��[Ƭ������].������[����������].����.size() - 1);
}

void C��̬����::���ض���ͨ��(FbxAnimLayer* p������, FbxNode* p�ڵ�, UINT Ƭ������, UINT ����������, UINT ģ������)
{
    FbxAnimCurve* l�������� = NULL;

    FbxTimeSpan ʱ����;
    FbxTime l֡ʱ��;
    FbxTime l��ʼ, l����;
    int l֡����;
    float   lֵ֡;
    int     l֡����;
    int l֡����;

    int lʱ;
    int l��;
    int l��;
    int l֡;
    int l��;
    int l��ֵ;
    int l���� = 0;
    int l���� = 0;

    l֡���� = l֡ʱ��.GetFrameRate(l֡ʱ��.eDefaultMode);

    l֡���� = ��������->Ƭ��[Ƭ������].����֡ - ��������->Ƭ��[Ƭ������].��ʼ֡;
    l֡���� = ��������->Ƭ��[Ƭ������].֡����;

    (*ȫ�ֱ任���ڵ�)[Ƭ������].resize(l֡����);

    for (l֡���� = 0; l֡���� < l֡����; l֡����++)
    {
        lʱ = l֡���� / (l֡���� * l֡���� * l֡����);
        l�� = (l֡���� - (lʱ * l֡���� * l֡���� * l֡����)) / (l֡���� * l֡����);
        l�� = (l֡���� - (lʱ * l֡���� * l֡���� * l֡����) - (l�� * l֡���� * l֡����)) / l֡����;
        l֡ = l֡���� - (lʱ * l֡���� * l֡���� * l֡����) - (l�� * l֡���� * l֡����) - (l�� * l֡����);
        l֡ʱ��.SetTime(lʱ, l��, l��, l֡);
        l֡ʱ�� += ��������->Ƭ��[Ƭ������].��ʼʱ��;

        for (int i = 0; i < ��������; i++)
        {
            WCHAR* �ڵ�����w = 0;

            FbxAnsiToWC(p�ڵ�->GetName(), �ڵ�����w);

            if ((*��������)[i] == �ڵ�����w)
            {
                FbxAMatrix ����֡���ؾ��� = p�ڵ�->EvaluateLocalTransform(l֡ʱ��);
                FbxAMatrix ����֡������� = p�ڵ�->EvaluateGlobalTransform(l֡ʱ��);

                mat4 ȫ�ֱ任 = mat4(1.0f);
                mat4 ���ر任 = mat4(1.0f);
                ȫ�ֱ任 = fbx����תmat4(����֡�������);
                ���ر任 = fbx����תmat4(����֡���ؾ���);

                S�����任 �����任;
                �����任.֡�� = l֡����;
                �����任.ȫ�ֱ任 = ȫ�ֱ任;
                �����任.���ر任 = ���ر任;

                ��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�任.push_back(�����任);

                //���ر任�ڵ�(fbx���ڵ�, l֡ʱ��, 0, Ƭ������, l֡����);
            }
        }

        for (int i = 0; i < ����->Ԫ��.size(); i++)
        {
            WCHAR* �ڵ�����w = 0;

            FbxAnsiToWC(p�ڵ�->GetName(), �ڵ�����w);

            if (����->Ԫ��[i]->�������� == �ڵ�����w)
            {
                FbxAMatrix ����֡���ؾ��� = p�ڵ�->EvaluateLocalTransform(l֡ʱ��);
                FbxAMatrix ����֡������� = p�ڵ�->EvaluateGlobalTransform(l֡ʱ��);

                mat4 ȫ�ֱ任 = mat4(1.0f);
                mat4 ���ر任 = mat4(1.0f);
                ȫ�ֱ任 = fbx����תmat4(����֡�������);
                ���ر任 = fbx����תmat4(����֡���ؾ���);

                S�����任 �����任;
                �����任.֡�� = l֡����;
                �����任.ȫ�ֱ任 = ȫ�ֱ任;
                �����任.���ر任 = ���ر任;

                ��������->Ƭ��[Ƭ������].������[����������].����[ģ������].�任.push_back(�����任);
            }
        }
    }
}

void C��̬����::���ر任�ڵ�(FbxNode* p�ڵ�, FbxTime ʱ��, FbxAMatrix* ȫ�ֱ任, int Ƭ������, int ֡)
{
    FbxAMatrix ȫ�ֱ任2 = ��ȡȫ�ֱ任(p�ڵ�, ʱ��, ȫ�ֱ任);

    if (p�ڵ�->GetNodeAttribute())
    {
        FbxAMatrix lGeometryOffset = ��ȡ������(p�ڵ�);
        FbxAMatrix ȫ��ƫ�Ʊ任 = ȫ�ֱ任2 * lGeometryOffset;

        if (p�ڵ�->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
            ��������(p�ڵ�, ʱ��, &ȫ��ƫ�Ʊ任, Ƭ������, ֡);
    }

    const int lChildCount = p�ڵ�->GetChildCount();
    for (int lChildIndex = 0; lChildIndex < lChildCount; ++lChildIndex)
    {
        ���ر任�ڵ�(p�ڵ�->GetChild(lChildIndex), ʱ��, &ȫ�ֱ任2, Ƭ������, ֡);
    }
}

void C��̬����::��������(FbxNode* p�ڵ�, FbxTime ʱ��, FbxAMatrix* ȫ�ֱ任, int Ƭ������, int ֡)
{
    WCHAR* l�������� = nullptr;
    FbxUTF8ToWC(p�ڵ�->GetName(), l��������, 0);
    S�任�ڵ�2 �任�ڵ�;

    �任�ڵ�.�ο�ȫ�ֱ任 = *ȫ�ֱ任;
    �任�ڵ�.�ڵ����� = l��������;
    �任�ڵ�.ȫ�ֱ任 = ��ȡȫ�ֱ任(p�ڵ�, ʱ��);

    (*ȫ�ֱ任���ڵ�)[Ƭ������][֡].push_back(�任�ڵ�);
}

void C��̬����::�ϲ����嶯����Ϣ()
{
    uint ֡ƫ�� = 0;
    mat4 ��ʼ���� = mat4(1.0f);

    (*�����������).resize(��������->Ƭ��.size());
    for (int i = 0; i < (*�����������).size(); i++)
    {
        (*�����������)[i].ԭʼʱ�� = (float)(��������->Ƭ��[i].����֡ - ��������->Ƭ��[i].��ʼ֡ + 1) / ��������->Ƭ��[i].֡����;
        (*�����������)[i].֡.resize(��������->Ƭ��[i].����֡ - ��������->Ƭ��[i].��ʼ֡);
        (*�����������)[i].�Ƿ�ѭ�� = 1;
        (*�����������)[i].������� = ��������->Ƭ��[i].Ƭ������;
        (*�����������)[i].�ٶ� = 1.0f;
        ֡ƫ�� = ��������->Ƭ��[i].��ʼ֡;

        for (int j = ֡ƫ��; j < (*�����������)[i].֡.size() + ֡ƫ��; j++)
        {
            (*�����������)[i].֡[j - ֡ƫ��].�����任.resize(��������, ��ʼ����);
            //(*�����������)[i].֡[j - ֡ƫ��].����任.resize(����->Ԫ��.size(), ��ʼ����);

            for (int k = 0; k < ��������->Ƭ��[i].������.size(); k++)
            {
                for (int m = 0; m < ��������->Ƭ��[i].������[k].����.size(); m++)
                {
                    //���ع����任
                    for (int n = 0; n < ��������; n++)
                    {
                        if ((*��������)[n].compare(��������->Ƭ��[i].������[k].����[m].��������) == 0)
                        {
                            for (int u = 0; u < ��Ƥ����->��������.size(); u++)
                            {
                                for (int v = 0; v < ��Ƥ����->��������[u].����.size(); v++)
                                {
                                    if (��Ƥ����->��������[u].����[v].�������� == (*��������)[n])
                                    {
                                        mat4 �ο�ȫ�ֳ�ʼ�任 = ��Ƥ����->��������[u].����[v].�ο�ȫ�ֳ�ʼ�任;
                                        mat4 ��ȫ�ֳ�ʼ�任 = ��Ƥ����->��������[u].����[v].��ȫ�ֳ�ʼ�任;
                                        mat4 ȫ�ֱ任 = ��������->Ƭ��[i].������[k].����[m].�任[j - ֡ƫ��].ȫ�ֱ任;
                                        mat4 �ֲ��任 = ��������->Ƭ��[i].������[k].����[m].�任[j - ֡ƫ��].���ر任;

                                        //for (int w = 0; w < (*ȫ�ֱ任���ڵ�)[i][j - ֡ƫ��].size(); w++)
                                        //{
                                        //    if ((*ȫ�ֱ任���ڵ�)[i][j - ֡ƫ��][w].�ڵ����� == (*��������)[n])
                                        //    {
                                        //        �ο�ȫ�ֵ�ǰ�任 = fbx����תmat4((*ȫ�ֱ任���ڵ�)[i][j - ֡ƫ��][w].�ο�ȫ�ֱ任);
                                        //        ȫ�ֱ任 = fbx����תmat4((*ȫ�ֱ任���ڵ�)[i][j - ֡ƫ��][w].ȫ�ֱ任);
                                        //    }
                                        //}

                                        (*�����������)[i].֡[j - ֡ƫ��].�����任[n] = ȫ�ֱ任
                                            * inverse(��ȫ�ֳ�ʼ�任) * �ο�ȫ�ֳ�ʼ�任;
                                    }
                                }
                            }
                        }
                    }

                    ////��������任
                    //for (int n = 0; n < ��������; n++)
                    //{
                    //    if (����->Ԫ��[n]->��������.compare(��������->Ƭ��[i].������[k].����[m].��������) == 0)
                    //    {
                    //        mat4 �ο�ȫ�ֵ�ǰ�任;

                    //        �ο�ȫ�ֵ�ǰ�任 = ����->Ԫ��[n]->�任;

                    //        (*�����������)[i].֡[j - ֡ƫ��].����任[n] = inverse(�ο�ȫ�ֵ�ǰ�任) 
                    //            * ��������->Ƭ��[i].������[k].����[m].�任[j - ֡ƫ��].ȫ�ֱ任;
                    //    }
                    //}
                }
            }
        }
    }
}

void C��̬����::���ɹ�������()
{
    glCreateBuffers(1, &��������);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ��������);

    int ֡��������С = 0;
    for (int i = 0; i < (*�����������).size(); i++)
        for (int j = 0; j < (*�����������)[i].֡.size(); j++)
            ֡��������С += sizeof(mat4) * (*�����������)[i].֡[j].�����任.size();

    int ��ǰ֡������ƫ�� = 0;
    glBufferData(GL_SHADER_STORAGE_BUFFER, ֡��������С, 0, GL_STATIC_DRAW);
    for (int i = 0; i < (*�����������).size(); i++)
        for (int j = 0; j < (*�����������)[i].֡.size(); j++)
            for (int k = 0; k < (*�����������)[i].֡[j].�����任.size(); k++)
            {
                glBufferSubData(GL_SHADER_STORAGE_BUFFER, ��ǰ֡������ƫ��, sizeof(mat4),
                    &(*�����������)[i].֡[j].�����任[k][0][0]);
                ��ǰ֡������ƫ�� += sizeof(mat4);
            }

    �������.resize((*�����������).size());
    for (int i = 0; i < (*�����������).size(); i++)
    {
        �������[i].ԭʼʱ�� = (*�����������)[i].ԭʼʱ��;
        �������[i].������� = (*�����������)[i].�������;
        
        �������[i].֡.resize((*�����������)[i].֡.size());
        for (int j = 0; j < (*�����������)[i].֡.size(); j++)
        {
            �������[i].֡[j].�������� = (*�����������)[i].֡[j].�����任.size();
        }
    }
}

//mat4* C��̬����::��ȡ��ǰ�����任()
//{
//    uint l֡�� = 0;
//    float lС�� = 0;
//    vec3 l����{};
//    vec3 l��ʼ��ת{};
//    vec3 ����λ��{};
//    mat4 l���ձ任 = mat4(1.0f);
//    mat4 l����任 = mat4(1.0f);
//    vec3 ��תx{};
//    vec3 ��תy{};
//    vec3 ��תz{};
//    vec3 ��תx2{};
//    vec3 ��תy2{};
//    vec3 ��תz2{};
//    vec3 λ��{};
//    vec3 λ��2{};
//    mat4 ��ת = mat4(1.0f);
//
//    l֡�� = (int)�������[��ǰ���].֡λ;
//    lС�� = �������[��ǰ���].֡λ - l֡��;
//
//    for (UINT i = 0; i < ��������; i++)
//    {
//        l���ձ任 = (*�����������)[��ǰ���].֡[l֡��].�����任[i];
//        λ�� = vec3{ (*�����������)[��ǰ���].֡[l֡��].�����任[i][3][0], (*�����������)[��ǰ���].֡[l֡��].�����任[i][3][1],
//            (*�����������)[��ǰ���].֡[l֡��].�����任[i][3][2] };
//        λ��2 = vec3{ (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][3][0], (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][3][1],
//            (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][3][2] };
//        ��תx = vec3{ (*�����������)[��ǰ���].֡[l֡��].�����任[i][0][0], (*�����������)[��ǰ���].֡[l֡��].�����任[i][0][1],
//            (*�����������)[��ǰ���].֡[l֡��].�����任[i][0][2] };
//        ��תy = vec3{ (*�����������)[��ǰ���].֡[l֡��].�����任[i][1][0], (*�����������)[��ǰ���].֡[l֡��].�����任[i][1][1],
//            (*�����������)[��ǰ���].֡[l֡��].�����任[i][1][2] };
//        ��תz = vec3{ (*�����������)[��ǰ���].֡[l֡��].�����任[i][2][0], (*�����������)[��ǰ���].֡[l֡��].�����任[i][2][1],
//            (*�����������)[��ǰ���].֡[l֡��].�����任[i][2][2] };
//        ��תx2 = vec3{ (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][0][0], (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][0][1],
//            (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][0][2] };
//        ��תy2 = vec3{ (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][1][0], (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][1][1],
//            (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][1][2] };
//        ��תz2 = vec3{ (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][2][0], (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][2][1],
//            (*�����������)[��ǰ���].֡[l֡�� + 1].�����任[i][2][2] };
//        λ�� = λ�� * (1 - lС��) + λ��2 * lС��;
//        ��תx = ��תx * (1 - lС��) + ��תx2 * lС��;
//        ��תy = ��תy * (1 - lС��) + ��תy2 * lС��;
//        ��תz = ��תz * (1 - lС��) + ��תz2 * lС��;
//        l���ձ任[0][0] = ��תx[0]; l���ձ任[0][1] = ��תx[1]; l���ձ任[0][2] = ��תx[2];
//        l���ձ任[1][0] = ��תy[0]; l���ձ任[1][1] = ��תy[1]; l���ձ任[1][2] = ��תy[2];
//        l���ձ任[2][0] = ��תz[0]; l���ձ任[2][1] = ��תz[1]; l���ձ任[2][2] = ��תz[2];
//        l���ձ任[3][0] = λ��[0]; l���ձ任[3][1] = λ��[1]; l���ձ任[3][2] = λ��[2];
//
//        �����任[i] = l���ձ任;
//    }
//
//    return �����任;
//}

//mat4* C��̬����::��ȡ��ǰ����任()
//{
//    uint l֡�� = 0;
//    float lС�� = 0;
//    vec3 l����{};
//    vec3 l��ʼ��ת{};
//    vec3 ����λ��{};
//    mat4 l���ձ任 = mat4(1.0f);
//    mat4 l����任 = mat4(1.0f);
//    vec3 ��תx{};
//    vec3 ��תy{};
//    vec3 ��תz{};
//    vec3 ��תx2{};
//    vec3 ��תy2{};
//    vec3 ��תz2{};
//    vec3 λ��{};
//    vec3 λ��2{};
//    mat4 ��ת = mat4(1.0f);
//
//    l֡�� = (int)(*�����������)[��ǰ���].֡λ;
//    lС�� = (*�����������)[��ǰ���].֡λ - l֡��;
//
//    for (UINT i = 0; i < ��������; i++)
//    {
//        l���ձ任 = (*�����������)[��ǰ���].֡[l֡��].����任[i];
//        λ�� = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][3][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][3][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][3][2] };
//        λ��2 = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][3][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][3][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][3][2] };
//        ��תx = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][0][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][0][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][0][2] };
//        ��תy = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][1][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][1][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][1][2] };
//        ��תz = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][2][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][2][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][2][2] };
//        ��תx2 = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][0][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][0][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][0][2] };
//        ��תy2 = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][1][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][1][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][1][2] };
//        ��תz2 = vec3{ (*�����������)[��ǰ���].֡[l֡��].����任[i][2][0], (*�����������)[��ǰ���].֡[l֡��].����任[i][2][1], 
//            (*�����������)[��ǰ���].֡[l֡��].����任[i][2][2] };
//        λ�� = λ�� * (1 - lС��) + λ��2 * lС��;
//        ��תx = ��תx * (1 - lС��) + ��תx2 * lС��;
//        ��תy = ��תy * (1 - lС��) + ��תy2 * lС��;
//        ��תz = ��תz * (1 - lС��) + ��תz2 * lС��;
//        l���ձ任[0][0] = ��תx[0]; l���ձ任[0][1] = ��תx[1]; l���ձ任[0][2] = ��תx[2];
//        l���ձ任[1][0] = ��תy[0]; l���ձ任[1][1] = ��תy[1]; l���ձ任[1][2] = ��תy[2];
//        l���ձ任[2][0] = ��תz[0]; l���ձ任[2][1] = ��תz[1]; l���ձ任[2][2] = ��תz[2];
//        l���ձ任[3][0] = λ��[0]; l���ձ任[3][1] = λ��[1]; l���ձ任[3][2] = λ��[2];
//
//        ����任[i] = l���ձ任;
//    }
//
//    return ����任;
//}

void C��̬����::�趨�����ٶ�(UINT ���, float �ٶȱ���)
{
    (*�����������)[���].�ٶ� = �ٶȱ���;
}

void C��̬����::�趨�������(UINT ���)
{
    ��ǰ��� = ���;
}

void C��̬����::�趨���֡λ��(UINT ���, float �ٷֱ�)
{
    �������[���].��ǰʱ�� = �������[���].ԭʼʱ�� * �ٷֱ�;
}

void C��̬����::�趨����ģʽ(UINT ���, bool �Ƿ�ѭ��)
{
    �������[���].�Ƿ�ѭ�� = �Ƿ�ѭ��;
}

bool C��̬����::��⶯������(UINT ���)
{
    if (�������[���].�Ƿ����) return 1;
    else return 0;
}

void C��̬����::����ʱ��(float ʱ��仯)
{
    �������[��ǰ���].��ǰʱ�� += ʱ��仯 * �������[��ǰ���].�ٶ�;
    if (�������[��ǰ���].��ǰʱ�� >= �������[��ǰ���].ԭʼʱ��)
    {
        �������[��ǰ���].�Ƿ���� = 1;
        if (�������[��ǰ���].�Ƿ�ѭ��)
            �������[��ǰ���].��ǰʱ�� = 0;
        else
            �������[��ǰ���].��ǰʱ�� = �������[��ǰ���].ԭʼʱ�� - 0.001;
    }

    �������[��ǰ���].֡λ = �������[��ǰ���].��ǰʱ�� / �������[��ǰ���].ԭʼʱ�� * (�������[��ǰ���].֡.size() - 1);
}

int C��̬����::��ȡ����ƫ��()
{
    ƫ�� = 0;
    int l֡�� = (int)�������[��ǰ���].֡λ;

    for (int i = 0; i < ��ǰ���; i++)
        ƫ�� += �������[i].֡.size() * �������[i].֡[0].��������;

    ƫ�� += l֡�� * �������[��ǰ���].֡[0].��������;

    return ƫ��;
}

float C��̬����::��ȡ��ǰ֡λ()
{
    return �������[��ǰ���].֡λ;
}

void C��̬����::��������(UINT ����)
{
    glBindVertexArray(�������);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ��������);;
    glDrawArrays(GL_TRIANGLES, this->����->Ԫ��[����]->��ʼ����, this->����->Ԫ��[����]->��������);
}

void C��̬����::�����������()
{
    delete ��������; 
    �������� = nullptr;
    delete ȫ�ֱ任���ڵ�; 
    ȫ�ֱ任���ڵ� = nullptr;
    delete ���ڵ�;
    ���ڵ� = nullptr;
    delete ��Ƥ����;
    ��Ƥ���� = nullptr;
    delete ��������;
    �������� = nullptr;
    delete ������ƶ��㼯;
    ������ƶ��㼯 = nullptr;
    delete ����������;
    ���������� = nullptr;
    delete ���Ӷ���;
    ���Ӷ��� = nullptr;
    delete ������¼;
    ������¼ = nullptr;
    delete ��������;
    �������� = nullptr;
    FbxNode* fbx���ڵ� = 0;
    FbxScene* ���� = 0;
    delete �����������;
    ����������� = nullptr;
}

C��̬����::~C��̬����()
{
    delete ����; 
    ���� = nullptr;
}