#include"������Դ.h"

C������Դ::C������Դ()
{

}

void C������Դ::������ͼ()
{
	glGenTextures(1, &����ͼ.����);
	glBindTexture(GL_TEXTURE_2D, ����ͼ.����);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* ͼ�� = SOIL_load_image("����ͼ.dds", &����ͼ.��, &����ͼ.��, &����ͼ.ͨ��, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ����ͼ.��, ����ͼ.��, 0, GL_RGB, GL_UNSIGNED_BYTE, ͼ��);
	SOIL_free_image_data(ͼ��);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

C������Դ::~C������Դ()
{
	glDeleteTextures(1, &����ͼ.����);
}