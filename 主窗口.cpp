#include"������.h"

int C������::������()
{
    glfwInit();

    ���ڿ� = 800;
    ���ڸ� = 600;
    ���� = glfwCreateWindow(���ڿ�, ���ڸ�, ��������.c_str(), NULL, NULL);

    glfwSetWindowUserPointer(����, this);
    glfwSetKeyCallback(����, �������);
    glfwSetMouseButtonCallback(����, ��갴�����);
	glfwSetCursorPosCallback(����, ���λ�ü��);
	glfwSetScrollCallback(����, ��껬�ּ��);

    glfwMakeContextCurrent(����);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    int ��� = ��ʼ��();
    if (���) return ���;

    while (!glfwWindowShouldClose(����))
    {
		float dt = ��ȡʱ��仯();
        ��ʾ(dt);
        glfwSwapBuffers(����);
        glfwPollEvents();
    }

    �ͷ�();

    glfwDestroyWindow(����);

    glfwTerminate();

    return 0;
}

float C������::��ȡʱ��仯()
{
	static int ֡���� = 0;
	static UINT ��ǰʱ�� = 0.0f;
	static float ����ʱ�� = 0.0f;
	static float dt = 0.0f;

	֡����++;
	dt = ((float)GetTickCount64() - ��ǰʱ��) / 1000;
	��ǰʱ�� = GetTickCount64();

	if ((��ǰʱ�� - ����ʱ��) >= 1000.0f)
	{
		����ʱ�� = ��ǰʱ��;

		string ���ڱ��� = �������� + "  fps: " + to_string(֡����);
		glfwSetWindowTitle(����, ���ڱ���.c_str());

		֡���� = 0;
	}

	return dt;
}

void C������::�������(GLFWwindow* ����, int ����, int ɨ�����, int ����, int ģʽ)
{
	C������* pthis = (C������*)glfwGetWindowUserPointer(����);

	switch (����)
	{
	case(GLFW_PRESS):
		switch (����)
		{
		case GLFW_KEY_ESCAPE:
			pthis->����.��escape״̬ = 1;
			break;

		case GLFW_KEY_0:
			pthis->����.��0״̬ = 1;
			break;

		case GLFW_KEY_1:
			pthis->����.��1״̬ = 1;
			break;

		case GLFW_KEY_2:
			pthis->����.��2״̬ = 1;
			break;

		case GLFW_KEY_3:
			pthis->����.��3״̬ = 1;
			break;

		case GLFW_KEY_4:
			pthis->����.��4״̬ = 1;
			break;

		case GLFW_KEY_5:
			pthis->����.��5״̬ = 1;
			break;

		case GLFW_KEY_6:
			pthis->����.��6״̬ = 1;
			break;

		case GLFW_KEY_7:
			pthis->����.��7״̬ = 1;
			break;

		case GLFW_KEY_8:
			pthis->����.��8״̬ = 1;
			break;

		case GLFW_KEY_9:
			pthis->����.��9״̬ = 1;
			break;

		case GLFW_KEY_A:
			pthis->����.��A״̬ = 1;
			break;

		case GLFW_KEY_W:
			pthis->����.��W״̬ = 1;
			break;

		case GLFW_KEY_S:
			pthis->����.��S״̬ = 1;
			break;

		case GLFW_KEY_D:
			pthis->����.��D״̬ = 1;
			break;

		case GLFW_KEY_E:
			pthis->����.��E״̬ = 1;
			break;

		case GLFW_KEY_Q:
			pthis->����.��Q״̬ = 1;
			break;

		case GLFW_KEY_R:
			pthis->����.��R״̬ = 1;
			break;

		case GLFW_KEY_F:
			pthis->����.��F״̬ = 1;
			break;

		case GLFW_KEY_X:
			pthis->����.��X״̬ = 1;
			break;

		case GLFW_KEY_Z:
			pthis->����.��Z״̬ = 1;
			break;

		case GLFW_KEY_ENTER:
			pthis->����.��enter״̬ = 1;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			pthis->����.����shift״̬ = 1;
			break;

		case GLFW_KEY_SPACE:
			pthis->����.��space״̬ = 1;
			break;

		default:
			break;
		}
		break;

	case(GLFW_RELEASE):
		switch (����)
		{
		case GLFW_KEY_ESCAPE:
			pthis->����.��escape״̬ = 0;
			break;

		case GLFW_KEY_0:
			pthis->����.��0״̬ = 0;
			break;

		case GLFW_KEY_1:
			pthis->����.��1״̬ = 0;
			break;

		case GLFW_KEY_2:
			pthis->����.��2״̬ = 0;
			break;

		case GLFW_KEY_3:
			pthis->����.��3״̬ = 0;
			break;

		case GLFW_KEY_4:
			pthis->����.��4״̬ = 0;
			break;

		case GLFW_KEY_5:
			pthis->����.��5״̬ = 0;
			break;

		case GLFW_KEY_6:
			pthis->����.��6״̬ = 0;
			break;

		case GLFW_KEY_7:
			pthis->����.��7״̬ = 0;
			break;

		case GLFW_KEY_8:
			pthis->����.��8״̬ = 0;
			break;

		case GLFW_KEY_9:
			pthis->����.��9״̬ = 0;
			break;

		case GLFW_KEY_A:
			pthis->����.��A״̬ = 0;
			break;

		case GLFW_KEY_W:
			pthis->����.��W״̬ = 0;
			break;

		case GLFW_KEY_S:
			pthis->����.��S״̬ = 0;
			break;

		case GLFW_KEY_D:
			pthis->����.��D״̬ = 0;
			break;

		case GLFW_KEY_E:
			pthis->����.��E״̬ = 0;
			break;

		case GLFW_KEY_Q:
			pthis->����.��Q״̬ = 0;
			break;

		case GLFW_KEY_R:
			pthis->����.��R״̬ = 0;
			break;

		case GLFW_KEY_F:
			pthis->����.��F״̬ = 0;
			break;

		case GLFW_KEY_X:
			pthis->����.��X״̬ = 0;
			break;

		case GLFW_KEY_Z:
			pthis->����.��Z״̬ = 0;
			break;

		case GLFW_KEY_ENTER:
			pthis->����.��enter״̬ = 0;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			pthis->����.����shift״̬ = 0;
			break;

		case GLFW_KEY_SPACE:
			pthis->����.��space״̬ = 0;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return;
}

void C������::��갴�����(GLFWwindow* ����, int ����, int ����, int ģʽ)
{
	C������* pthis = (C������*)glfwGetWindowUserPointer(����);

	switch (����)
	{
	case GLFW_PRESS:
		switch (����)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			pthis->����.������״̬ = 1;
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			pthis->����.����Ҽ�״̬ = 1;
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			pthis->����.����м�״̬ = 1;
			break;

		default:
			break;
		}
		break;

	case GLFW_RELEASE:
		switch (����)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			pthis->����.������״̬ = 0;
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			pthis->����.����Ҽ�״̬ = 0;
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			pthis->����.����м�״̬ = 0;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void C������::���㿪��״̬()
{
	����.��A״̬ = 0;
	����.��W״̬ = 0;
	����.��S״̬ = 0;
	����.��D״̬ = 0;
	����.��E״̬ = 0;
	����.��Q״̬ = 0;
	����.��R״̬ = 0;
	����.��F״̬ = 0;
	����.��X״̬ = 0;
	����.��Z״̬ = 0;
	����.��enter״̬ = 0;
	����.����shift״̬ = 0;
	����.��space״̬ = 0;
	����.��escape״̬ = 0;
	����.��1״̬ = 0;
	����.��2״̬ = 0;
	����.��3״̬ = 0;
	����.��4״̬ = 0;
	����.��5״̬ = 0;
	����.��6״̬ = 0;
	����.��7״̬ = 0;
	����.��8״̬ = 0;
	����.������״̬ = 0;
	����.����Ҽ�״̬ = 0;
	����.����м�״̬ = 0;
	����.���λ�� = POINT{ 0, 0 };
	����.���λ�� = POINT{ 0, 0 };
	����.���߽�״̬ = 0;
	����.��껬��״̬ = 0;
}

void C������::���λ�ü��(GLFWwindow* ����, double λ��x, double λ��y)
{
	C������* pthis = (C������*)glfwGetWindowUserPointer(����);

	pthis->����.���λ��.x = λ��x - pthis->����.���λ��.x;
	pthis->����.���λ��.y = λ��y - pthis->����.���λ��.y;
	pthis->����.���λ��.x = λ��x;
	pthis->����.���λ��.y = λ��y;
}

void C������::��껬�ּ��(GLFWwindow* ����, double ƫ��x, double ƫ��y)
{
	C������* pthis = (C������*)glfwGetWindowUserPointer(����);

	pthis->����.��껬��״̬ = ƫ��y;
}

int C������::��ʼ��()
{
    glViewport(0, 0, ���ڿ�, ���ڸ�);
    aspect = (float)���ڸ� / ���ڿ�;

    glGenVertexArrays(1, &VAOs);
    glBindVertexArray(VAOs);

    GLfloat  vertices[6][3] = {
        { -0.90f, -0.90f, 0.0f }, {  0.85f, -0.90f, 0.0f }, { -0.90f,  0.85f, 0.0f },  // Triangle 1
        {  0.90f, -0.85f, 0.0f }, {  0.90f,  0.90f, 0.0f }, { -0.85f,  0.90f, 0.0f }   // Triangle 2
    };

    glGenBuffers(1, &Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_STORAGE_BIT);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

    base_prog = glCreateProgram();

    int result = 0;
    result = ������ɫ��(L"��ɫ��/��������vs.glsl", base_prog, GL_VERTEX_SHADER);
    if (result) return result;
    result = ������ɫ��(L"��ɫ��/��������fs.glsl", base_prog, GL_FRAGMENT_SHADER);
    if (result) return result;

    if (result = ���ӳ���(base_prog)) return result;

    ������ɫ������.world = glGetUniformLocation(base_prog, "world");
    ������ɫ������.projview = glGetUniformLocation(base_prog, "projview");
    ������ɫ������.eyeposw = glGetUniformLocation(base_prog, "eyeposw");
    ������ɫ������.dlight.���� = glGetUniformLocation(base_prog, "dlight_direction");
    ������ɫ������.dlight.��ɫ = glGetUniformLocation(base_prog, "dlight_diffuse");
    ������ɫ������.mat.��͸���� = glGetUniformLocation(base_prog, "mat_reflect");
    ������ɫ������.mat.����� = glGetUniformLocation(base_prog, "mat_specular");
    ������ɫ������.mat.������ = glGetUniformLocation(base_prog, "mat_diffuse");
    ������ɫ������.mat.������ = glGetUniformLocation(base_prog, "mat_ambient");
    ������ɫ������.mat.�Է��� = glGetUniformLocation(base_prog, "mat_emissive");
    ������ɫ������.mat.�߹⼶�� = glGetUniformLocation(base_prog, "mat_power");
    ������ɫ������.tex = glGetUniformLocation(base_prog, "tex");
	������ɫ������.bonetransformindex = glGetUniformLocation(base_prog, "bonetransformindex");
	������ɫ������.influence = glGetUniformLocation(base_prog, "influence");
	������ɫ������.bonecount = glGetUniformLocation(base_prog, "bonecount");
	//������ɫ������.bonetransform = glGetUniformLocation(base_prog, "bonetransform");
	//������ɫ������.worldinv = glGetUniformLocation(base_prog, "worldinv");

    glUseProgram(base_prog);

    ͶӰ���� = frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 1000.0f);
    ͶӰ���� = perspectiveRH(pi<float>() * 2 / 3, aspect, 1.0f, 1000.0f);

    ���λ�� = vec3(0.0f, 0.0f, -100.0f);
    ������ = vec3(0.0f, 0.0f, 0.0f);
    �Ϸ��� = vec3(0.0f, 1.0f, 0.0f);

    �۲���� = lookAtRH(���λ��, ������, �Ϸ���);

    �����Դ.���� = vec3(0.0f, -1.0f, -1.0f);
    �����Դ.��ɫ = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    ����.��͸���� = 1.0f;
    ����.����� = 2.0f;
    ����.������ = vec4(0.7f, 0.7f, 0.7f, 0.7f);
    ����.������ = vec3(0.3f, 0.3f, 0.3f);
    ����.�Է��� = vec3(0.0f, 0.0f, 0.0f);
    ����.�߹⼶�� = 2.0f;

    ������Դ = new C������Դ();
    ��̬���� = new C��̬����(������Դ);
    ������Դ->������ͼ();

    ��̬����->����fbx�ļ�(L"ģ��\\����ӣ.FBX", L"��ɫ");
	//��̬����->�����������();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glfwSwapInterval(0);

    ���㿪��״̬();
    ��� = new C�����˳����(&����, pi<float>() / 2, pi<float>() / 2, 40.0f, 0.3f, 0.002f, 2.0f, vec3{ 0.0f, 0.0f, 0.0f });

    return 0;
}

void C������::��ʾ(float dt)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ���->���(&�۲����);

    mat4 �۲�ͶӰ���� = ͶӰ���� * �۲����;
    glUniformMatrix4fv(������ɫ������.projview, 1, GL_FALSE, &�۲�ͶӰ����[0][0]);
    glUniform3f(������ɫ������.eyeposw, ���->�������.x, ���->�������.y, ���->�������.z);
    glUniform3f(������ɫ������.dlight.����, �����Դ.����.x, �����Դ.����.y, �����Դ.����.z);
    glUniform4f(������ɫ������.dlight.��ɫ, �����Դ.��ɫ.r, �����Դ.��ɫ.g, �����Դ.��ɫ.b, �����Դ.��ɫ.a);
    glUniform1f(������ɫ������.mat.��͸����, ����.��͸����);
    float spec = 2.0f;
    glUniform1f(������ɫ������.mat.�����, spec);
    glUniform4f(������ɫ������.mat.������, ����.������.r, ����.������.g, ����.������.b, ����.������.a);
    glUniform3f(������ɫ������.mat.������, ����.������.r, ����.������.g, ����.������.b);
    glUniform3f(������ɫ������.mat.�Է���, ����.�Է���.r, ����.�Է���.g, ����.�Է���.b);
    glUniform1f(������ɫ������.mat.�߹⼶��, ����.�߹⼶��);

	if (����.��1״̬ == 1)
	{
		��̬����->��ǰ��� = 0;
		��̬����->�������[0].��ǰʱ�� = 0.0f;
		��̬����->�������[0].�ٶ� = 1.0f;
	}
	if (����.��2״̬ == 1)
	{
		��̬����->��ǰ��� = 1;
		��̬����->�������[0].��ǰʱ�� = 0.0f;
		��̬����->�������[0].�ٶ� = 1.0f;
	}
	if (����.��3״̬ == 1)
	{
		��̬����->��ǰ��� = 2;
		��̬����->�������[0].��ǰʱ�� = 0.0f;
		��̬����->�������[0].�ٶ� = 1.0f;
	}

	��̬����->����ʱ��(dt);
	//mat4* �����任 = ��̬����->��ȡ��ǰ�����任();
	
	glUniform1i(������ɫ������.bonetransformindex, ��̬����->��ȡ����ƫ��());
	float С�� = ��̬����->��ȡ��ǰ֡λ() - (int)��̬����->��ȡ��ǰ֡λ();
	glUniform1f(������ɫ������.influence, С��);
	glUniform1i(������ɫ������.bonecount, ��̬����->��������);
	//glUniformMatrix4fv(������ɫ������.bonetransform, d����������, FALSE, &�����任[0][0][0]);

    //mat4 world = rotate(mat4(1.0f), -pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));
    //world = rotate(mat4(1.0f), pi<float>(), vec3(0.0f, 1.0f, 0.0f)) * world;
	mat4 world = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	if(��̬����->����)
		for (int i = 0; i < ��̬����->����->Ԫ��.size(); i++)
		{
			glUniformMatrix4fv(������ɫ������.world, 1, GL_FALSE, &world[0][0]);
			//glUniformMatrix4fv(������ɫ������.objtransform, 1, GL_FALSE, &��̬����->��ȡ��ǰ����任()[i][0][0]);
			//glUniformMatrix4fv(������ɫ������.world, 1, GL_FALSE, &��̬����->����->Ԫ��[i]->�任[0][0]);
			//glUniformMatrix4fv(������ɫ������.worldinv, 1, GL_FALSE, &inverse(��̬����->����->Ԫ��[i]->�任)[0][0]);
			glBindTexture(GL_TEXTURE_2D, ��̬����->����->����[��̬����->����->Ԫ��[i]->��������].����);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			��̬����->��������(i);
		}

	//glUniformMatrix4fv(������ɫ������.world, 1, GL_FALSE, &world[0][0]);
	//glBindVertexArray(VAOs);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

    ����.���λ�� = POINT{ 0, 0 };
}

int C������::������ɫ��(wstring filepath, GLuint prog, GLenum type)
{
    GLuint sh;
    ifstream file;

    file.open(filepath);
    if (!file.is_open())
    {
        wstring bug = L"�Ҳ�����ɫ���ļ�: ";
        OutputDebugString(bug.c_str());
        return -1;
    }
    file.seekg(0, ios::end);
    int len = file.tellg();
    file.seekg(0, ios::beg);
    char* shaderBuffer = new char[len + 1];
    shaderBuffer[len] = '\0';
    file.read(shaderBuffer, len);
    file.close();

    sh = glCreateShader(type);
    glShaderSource(sh, 1, &shaderBuffer, NULL);
    glCompileShader(sh);
    GLint compiled;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        wstring bug = L"��ɫ���ļ��޷�����: ";
        OutputDebugString(bug.c_str());
        char buffer[1024];
        glGetShaderInfoLog(sh, sizeof(buffer), nullptr, buffer);
        OutputDebugStringA(buffer);
        return -2;
    }

    glAttachShader(prog, sh);
    glDeleteShader(sh);
    delete[] shaderBuffer;

    return 0;
}

int C������::���ӳ���(GLuint program)
{
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        stringstream strstream;
        strstream << "��ɫ������ʧ��: " << log << std::endl;
        OutputDebugStringA(strstream.str().c_str());

        return -3;
    }

    return 0;
}

void C������::�ͷ�()
{
    glDeleteProgram(base_prog);
}