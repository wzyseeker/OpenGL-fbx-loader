#pragma once
#include<glad/glad.h>
#include<GLFW\glfw3.h>
#include<SOIL2/SOIL2.h>
#include<windows.h>

class C������Դ
{
public:
	struct S����
	{
		GLuint ����;
		int ��;
		int ��;
		int ͨ��;

		S����() 
		{
			ZeroMemory(this, sizeof(S����));
		}
	};

	S���� ����ͼ;

	void ������ͼ();

	C������Դ();
	~C������Դ();

private:

};