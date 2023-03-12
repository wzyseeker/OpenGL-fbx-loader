#include"主窗口.h"

int C主窗口::主窗口()
{
    glfwInit();

    窗口宽 = 800;
    窗口高 = 600;
    窗口 = glfwCreateWindow(窗口宽, 窗口高, 窗口名称.c_str(), NULL, NULL);

    glfwSetWindowUserPointer(窗口, this);
    glfwSetKeyCallback(窗口, 按键检测);
    glfwSetMouseButtonCallback(窗口, 鼠标按键检测);
	glfwSetCursorPosCallback(窗口, 鼠标位置检测);
	glfwSetScrollCallback(窗口, 鼠标滑轮检测);

    glfwMakeContextCurrent(窗口);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    int 结果 = 初始化();
    if (结果) return 结果;

    while (!glfwWindowShouldClose(窗口))
    {
		float dt = 获取时间变化();
        显示(dt);
        glfwSwapBuffers(窗口);
        glfwPollEvents();
    }

    释放();

    glfwDestroyWindow(窗口);

    glfwTerminate();

    return 0;
}

float C主窗口::获取时间变化()
{
	static int 帧数量 = 0;
	static UINT 当前时间 = 0.0f;
	static float 最新时间 = 0.0f;
	static float dt = 0.0f;

	帧数量++;
	dt = ((float)GetTickCount64() - 当前时间) / 1000;
	当前时间 = GetTickCount64();

	if ((当前时间 - 最新时间) >= 1000.0f)
	{
		最新时间 = 当前时间;

		string 窗口标题 = 窗口名称 + "  fps: " + to_string(帧数量);
		glfwSetWindowTitle(窗口, 窗口标题.c_str());

		帧数量 = 0;
	}

	return dt;
}

void C主窗口::按键检测(GLFWwindow* 窗口, int 按键, int 扫描代码, int 动作, int 模式)
{
	C主窗口* pthis = (C主窗口*)glfwGetWindowUserPointer(窗口);

	switch (动作)
	{
	case(GLFW_PRESS):
		switch (按键)
		{
		case GLFW_KEY_ESCAPE:
			pthis->按键.键escape状态 = 1;
			break;

		case GLFW_KEY_0:
			pthis->按键.键0状态 = 1;
			break;

		case GLFW_KEY_1:
			pthis->按键.键1状态 = 1;
			break;

		case GLFW_KEY_2:
			pthis->按键.键2状态 = 1;
			break;

		case GLFW_KEY_3:
			pthis->按键.键3状态 = 1;
			break;

		case GLFW_KEY_4:
			pthis->按键.键4状态 = 1;
			break;

		case GLFW_KEY_5:
			pthis->按键.键5状态 = 1;
			break;

		case GLFW_KEY_6:
			pthis->按键.键6状态 = 1;
			break;

		case GLFW_KEY_7:
			pthis->按键.键7状态 = 1;
			break;

		case GLFW_KEY_8:
			pthis->按键.键8状态 = 1;
			break;

		case GLFW_KEY_9:
			pthis->按键.键9状态 = 1;
			break;

		case GLFW_KEY_A:
			pthis->按键.键A状态 = 1;
			break;

		case GLFW_KEY_W:
			pthis->按键.键W状态 = 1;
			break;

		case GLFW_KEY_S:
			pthis->按键.键S状态 = 1;
			break;

		case GLFW_KEY_D:
			pthis->按键.键D状态 = 1;
			break;

		case GLFW_KEY_E:
			pthis->按键.键E状态 = 1;
			break;

		case GLFW_KEY_Q:
			pthis->按键.键Q状态 = 1;
			break;

		case GLFW_KEY_R:
			pthis->按键.键R状态 = 1;
			break;

		case GLFW_KEY_F:
			pthis->按键.键F状态 = 1;
			break;

		case GLFW_KEY_X:
			pthis->按键.键X状态 = 1;
			break;

		case GLFW_KEY_Z:
			pthis->按键.键Z状态 = 1;
			break;

		case GLFW_KEY_ENTER:
			pthis->按键.键enter状态 = 1;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			pthis->按键.键左shift状态 = 1;
			break;

		case GLFW_KEY_SPACE:
			pthis->按键.键space状态 = 1;
			break;

		default:
			break;
		}
		break;

	case(GLFW_RELEASE):
		switch (按键)
		{
		case GLFW_KEY_ESCAPE:
			pthis->按键.键escape状态 = 0;
			break;

		case GLFW_KEY_0:
			pthis->按键.键0状态 = 0;
			break;

		case GLFW_KEY_1:
			pthis->按键.键1状态 = 0;
			break;

		case GLFW_KEY_2:
			pthis->按键.键2状态 = 0;
			break;

		case GLFW_KEY_3:
			pthis->按键.键3状态 = 0;
			break;

		case GLFW_KEY_4:
			pthis->按键.键4状态 = 0;
			break;

		case GLFW_KEY_5:
			pthis->按键.键5状态 = 0;
			break;

		case GLFW_KEY_6:
			pthis->按键.键6状态 = 0;
			break;

		case GLFW_KEY_7:
			pthis->按键.键7状态 = 0;
			break;

		case GLFW_KEY_8:
			pthis->按键.键8状态 = 0;
			break;

		case GLFW_KEY_9:
			pthis->按键.键9状态 = 0;
			break;

		case GLFW_KEY_A:
			pthis->按键.键A状态 = 0;
			break;

		case GLFW_KEY_W:
			pthis->按键.键W状态 = 0;
			break;

		case GLFW_KEY_S:
			pthis->按键.键S状态 = 0;
			break;

		case GLFW_KEY_D:
			pthis->按键.键D状态 = 0;
			break;

		case GLFW_KEY_E:
			pthis->按键.键E状态 = 0;
			break;

		case GLFW_KEY_Q:
			pthis->按键.键Q状态 = 0;
			break;

		case GLFW_KEY_R:
			pthis->按键.键R状态 = 0;
			break;

		case GLFW_KEY_F:
			pthis->按键.键F状态 = 0;
			break;

		case GLFW_KEY_X:
			pthis->按键.键X状态 = 0;
			break;

		case GLFW_KEY_Z:
			pthis->按键.键Z状态 = 0;
			break;

		case GLFW_KEY_ENTER:
			pthis->按键.键enter状态 = 0;
			break;

		case GLFW_KEY_LEFT_SHIFT:
			pthis->按键.键左shift状态 = 0;
			break;

		case GLFW_KEY_SPACE:
			pthis->按键.键space状态 = 0;
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

void C主窗口::鼠标按键检测(GLFWwindow* 窗口, int 按键, int 动作, int 模式)
{
	C主窗口* pthis = (C主窗口*)glfwGetWindowUserPointer(窗口);

	switch (动作)
	{
	case GLFW_PRESS:
		switch (按键)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			pthis->按键.鼠标左键状态 = 1;
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			pthis->按键.鼠标右键状态 = 1;
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			pthis->按键.鼠标中键状态 = 1;
			break;

		default:
			break;
		}
		break;

	case GLFW_RELEASE:
		switch (按键)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
			pthis->按键.鼠标左键状态 = 0;
			break;

		case GLFW_MOUSE_BUTTON_RIGHT:
			pthis->按键.鼠标右键状态 = 0;
			break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
			pthis->按键.鼠标中键状态 = 0;
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}
}

void C主窗口::归零开关状态()
{
	按键.键A状态 = 0;
	按键.键W状态 = 0;
	按键.键S状态 = 0;
	按键.键D状态 = 0;
	按键.键E状态 = 0;
	按键.键Q状态 = 0;
	按键.键R状态 = 0;
	按键.键F状态 = 0;
	按键.键X状态 = 0;
	按键.键Z状态 = 0;
	按键.键enter状态 = 0;
	按键.键左shift状态 = 0;
	按键.键space状态 = 0;
	按键.键escape状态 = 0;
	按键.键1状态 = 0;
	按键.键2状态 = 0;
	按键.键3状态 = 0;
	按键.键4状态 = 0;
	按键.键5状态 = 0;
	按键.键6状态 = 0;
	按键.键7状态 = 0;
	按键.键8状态 = 0;
	按键.鼠标左键状态 = 0;
	按键.鼠标右键状态 = 0;
	按键.鼠标中键状态 = 0;
	按键.鼠标位置 = POINT{ 0, 0 };
	按键.鼠标位移 = POINT{ 0, 0 };
	按键.鼠标边界状态 = 0;
	按键.鼠标滑轮状态 = 0;
}

void C主窗口::鼠标位置检测(GLFWwindow* 窗口, double 位置x, double 位置y)
{
	C主窗口* pthis = (C主窗口*)glfwGetWindowUserPointer(窗口);

	pthis->按键.鼠标位移.x = 位置x - pthis->按键.鼠标位置.x;
	pthis->按键.鼠标位移.y = 位置y - pthis->按键.鼠标位置.y;
	pthis->按键.鼠标位置.x = 位置x;
	pthis->按键.鼠标位置.y = 位置y;
}

void C主窗口::鼠标滑轮检测(GLFWwindow* 窗口, double 偏移x, double 偏移y)
{
	C主窗口* pthis = (C主窗口*)glfwGetWindowUserPointer(窗口);

	pthis->按键.鼠标滑轮状态 = 偏移y;
}

int C主窗口::初始化()
{
    glViewport(0, 0, 窗口宽, 窗口高);
    aspect = (float)窗口高 / 窗口宽;

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
    result = 加入着色器(L"着色器/骨骼动画vs.glsl", base_prog, GL_VERTEX_SHADER);
    if (result) return result;
    result = 加入着色器(L"着色器/骨骼动画fs.glsl", base_prog, GL_FRAGMENT_SHADER);
    if (result) return result;

    if (result = 连接程序(base_prog)) return result;

    基础着色器索引.world = glGetUniformLocation(base_prog, "world");
    基础着色器索引.projview = glGetUniformLocation(base_prog, "projview");
    基础着色器索引.eyeposw = glGetUniformLocation(base_prog, "eyeposw");
    基础着色器索引.dlight.方向 = glGetUniformLocation(base_prog, "dlight_direction");
    基础着色器索引.dlight.颜色 = glGetUniformLocation(base_prog, "dlight_diffuse");
    基础着色器索引.mat.不透明度 = glGetUniformLocation(base_prog, "mat_reflect");
    基础着色器索引.mat.光泽度 = glGetUniformLocation(base_prog, "mat_specular");
    基础着色器索引.mat.漫反射 = glGetUniformLocation(base_prog, "mat_diffuse");
    基础着色器索引.mat.环境光 = glGetUniformLocation(base_prog, "mat_ambient");
    基础着色器索引.mat.自发光 = glGetUniformLocation(base_prog, "mat_emissive");
    基础着色器索引.mat.高光级别 = glGetUniformLocation(base_prog, "mat_power");
    基础着色器索引.tex = glGetUniformLocation(base_prog, "tex");
	基础着色器索引.bonetransformindex = glGetUniformLocation(base_prog, "bonetransformindex");
	基础着色器索引.influence = glGetUniformLocation(base_prog, "influence");
	基础着色器索引.bonecount = glGetUniformLocation(base_prog, "bonecount");
	//基础着色器索引.bonetransform = glGetUniformLocation(base_prog, "bonetransform");
	//基础着色器索引.worldinv = glGetUniformLocation(base_prog, "worldinv");

    glUseProgram(base_prog);

    投影矩阵 = frustum(-1.0f, 1.0f, -aspect, aspect, 1.0f, 1000.0f);
    投影矩阵 = perspectiveRH(pi<float>() * 2 / 3, aspect, 1.0f, 1000.0f);

    相机位置 = vec3(0.0f, 0.0f, -100.0f);
    看坐标 = vec3(0.0f, 0.0f, 0.0f);
    上方向 = vec3(0.0f, 1.0f, 0.0f);

    观察矩阵 = lookAtRH(相机位置, 看坐标, 上方向);

    方向光源.方向 = vec3(0.0f, -1.0f, -1.0f);
    方向光源.颜色 = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    材质.不透明度 = 1.0f;
    材质.光泽度 = 2.0f;
    材质.漫反射 = vec4(0.7f, 0.7f, 0.7f, 0.7f);
    材质.环境光 = vec3(0.3f, 0.3f, 0.3f);
    材质.自发光 = vec3(0.0f, 0.0f, 0.0f);
    材质.高光级别 = 2.0f;

    共享资源 = new C共享资源();
    动态物体 = new C动态物体(共享资源);
    共享资源->加载贴图();

    动态物体->加载fbx文件(L"模型\\八重樱.FBX", L"角色");
	//动态物体->清除备用资料();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glfwSwapInterval(0);

    归零开关状态();
    相机 = new C第三人称相机(&按键, pi<float>() / 2, pi<float>() / 2, 40.0f, 0.3f, 0.002f, 2.0f, vec3{ 0.0f, 0.0f, 0.0f });

    return 0;
}

void C主窗口::显示(float dt)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    相机->相机(&观察矩阵);

    mat4 观察投影矩阵 = 投影矩阵 * 观察矩阵;
    glUniformMatrix4fv(基础着色器索引.projview, 1, GL_FALSE, &观察投影矩阵[0][0]);
    glUniform3f(基础着色器索引.eyeposw, 相机->相机坐标.x, 相机->相机坐标.y, 相机->相机坐标.z);
    glUniform3f(基础着色器索引.dlight.方向, 方向光源.方向.x, 方向光源.方向.y, 方向光源.方向.z);
    glUniform4f(基础着色器索引.dlight.颜色, 方向光源.颜色.r, 方向光源.颜色.g, 方向光源.颜色.b, 方向光源.颜色.a);
    glUniform1f(基础着色器索引.mat.不透明度, 材质.不透明度);
    float spec = 2.0f;
    glUniform1f(基础着色器索引.mat.光泽度, spec);
    glUniform4f(基础着色器索引.mat.漫反射, 材质.漫反射.r, 材质.漫反射.g, 材质.漫反射.b, 材质.漫反射.a);
    glUniform3f(基础着色器索引.mat.环境光, 材质.环境光.r, 材质.环境光.g, 材质.环境光.b);
    glUniform3f(基础着色器索引.mat.自发光, 材质.自发光.r, 材质.自发光.g, 材质.自发光.b);
    glUniform1f(基础着色器索引.mat.高光级别, 材质.高光级别);

	if (按键.键1状态 == 1)
	{
		动态物体->当前轨道 = 0;
		动态物体->动画轨道[0].当前时间 = 0.0f;
		动态物体->动画轨道[0].速度 = 1.0f;
	}
	if (按键.键2状态 == 1)
	{
		动态物体->当前轨道 = 1;
		动态物体->动画轨道[0].当前时间 = 0.0f;
		动态物体->动画轨道[0].速度 = 1.0f;
	}
	if (按键.键3状态 == 1)
	{
		动态物体->当前轨道 = 2;
		动态物体->动画轨道[0].当前时间 = 0.0f;
		动态物体->动画轨道[0].速度 = 1.0f;
	}

	动态物体->更新时间(dt);
	//mat4* 骨骼变换 = 动态物体->获取当前骨骼变换();
	
	glUniform1i(基础着色器索引.bonetransformindex, 动态物体->获取骨骼偏移());
	float 小数 = 动态物体->获取当前帧位() - (int)动态物体->获取当前帧位();
	glUniform1f(基础着色器索引.influence, 小数);
	glUniform1i(基础着色器索引.bonecount, 动态物体->骨骼数量);
	//glUniformMatrix4fv(基础着色器索引.bonetransform, d最大骨骼数量, FALSE, &骨骼变换[0][0][0]);

    //mat4 world = rotate(mat4(1.0f), -pi<float>() / 2, vec3(1.0f, 0.0f, 0.0f));
    //world = rotate(mat4(1.0f), pi<float>(), vec3(0.0f, 1.0f, 0.0f)) * world;
	mat4 world = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

	if(动态物体->属性)
		for (int i = 0; i < 动态物体->属性->元素.size(); i++)
		{
			glUniformMatrix4fv(基础着色器索引.world, 1, GL_FALSE, &world[0][0]);
			//glUniformMatrix4fv(基础着色器索引.objtransform, 1, GL_FALSE, &动态物体->获取当前物体变换()[i][0][0]);
			//glUniformMatrix4fv(基础着色器索引.world, 1, GL_FALSE, &动态物体->属性->元素[i]->变换[0][0]);
			//glUniformMatrix4fv(基础着色器索引.worldinv, 1, GL_FALSE, &inverse(动态物体->属性->元素[i]->变换)[0][0]);
			glBindTexture(GL_TEXTURE_2D, 动态物体->属性->纹理集[动态物体->属性->元素[i]->纹理索引].纹理);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			动态物体->绘制网格(i);
		}

	//glUniformMatrix4fv(基础着色器索引.world, 1, GL_FALSE, &world[0][0]);
	//glBindVertexArray(VAOs);
	//glDrawArrays(GL_TRIANGLES, 0, 6);

    按键.鼠标位移 = POINT{ 0, 0 };
}

int C主窗口::加入着色器(wstring filepath, GLuint prog, GLenum type)
{
    GLuint sh;
    ifstream file;

    file.open(filepath);
    if (!file.is_open())
    {
        wstring bug = L"找不到着色器文件: ";
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
        wstring bug = L"着色器文件无法编译: ";
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

int C主窗口::连接程序(GLuint program)
{
    glLinkProgram(program);
    GLint linked;
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked)
    {
        char log[1024];
        glGetProgramInfoLog(program, sizeof(log), nullptr, log);
        stringstream strstream;
        strstream << "着色器连接失败: " << log << std::endl;
        OutputDebugStringA(strstream.str().c_str());

        return -3;
    }

    return 0;
}

void C主窗口::释放()
{
    glDeleteProgram(base_prog);
}