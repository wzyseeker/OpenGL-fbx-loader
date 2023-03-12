#include"共享资源.h"

C共享资源::C共享资源()
{

}

void C共享资源::加载贴图()
{
	glGenTextures(1, &白贴图.纹理);
	glBindTexture(GL_TEXTURE_2D, 白贴图.纹理);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* 图像 = SOIL_load_image("白贴图.dds", &白贴图.宽, &白贴图.高, &白贴图.通道, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 白贴图.宽, 白贴图.高, 0, GL_RGB, GL_UNSIGNED_BYTE, 图像);
	SOIL_free_image_data(图像);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

C共享资源::~C共享资源()
{
	glDeleteTextures(1, &白贴图.纹理);
}