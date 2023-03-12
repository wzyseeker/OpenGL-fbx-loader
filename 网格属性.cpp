#include"网格属性.h"

void C网格属性::添加元素(S属性* 属性)
{
    元素.resize(元素.size() + 1);
    元素[元素.size() - 1] = 属性;
}

C共享资源::S纹理 C网格属性::贴图(UINT 索引)
{
    return 纹理集[元素[索引]->纹理索引];
}

C共享资源::S纹理 C网格属性::法线贴图(UINT 索引)
{
    return 法线贴图集[元素[索引]->法线图索引];
}

C网格属性::~C网格属性()
{
    for (int i = 0; i < 纹理集.size(); i++)
    {
        glDeleteTextures(1, &纹理集[i].纹理);
    }
    for (int i = 0; i < 元素.size(); i++)
    {
        delete 元素[i];
    }
}