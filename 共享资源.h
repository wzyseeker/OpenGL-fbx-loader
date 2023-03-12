#pragma once
#include<glad/glad.h>
#include<GLFW\glfw3.h>
#include<SOIL2/SOIL2.h>
#include<windows.h>

class C共享资源
{
public:
	struct S纹理
	{
		GLuint 纹理;
		int 宽;
		int 高;
		int 通道;

		S纹理() 
		{
			ZeroMemory(this, sizeof(S纹理));
		}
	};

	S纹理 白贴图;

	void 加载贴图();

	C共享资源();
	~C共享资源();

private:

};