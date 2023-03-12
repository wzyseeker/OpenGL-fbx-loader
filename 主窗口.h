#pragma once
#include<glad/glad.h>
#include<GLFW\glfw3.h>
#include<Windows.h>
#include<sstream>
#include"fbx动态文件加载.h"
#include"自由相机.h"
#include"按键检测.h"

class C主窗口
{
public:
	int 窗口宽 = 0;
	int 窗口高 = 0;
	GLFWwindow* 窗口 = 0;
    string 窗口名称 = "fbx loader";

    float aspect = 0.0f;

    GLuint  VAOs = 0;
    GLuint  Buffers = 0;

    GLuint base_prog = 0;
    S方向光源 方向光源;
    S材质 材质;
    mat4 世界矩阵 = mat4(1.0f);
    mat4 观察矩阵 = mat4(1.0f);
    mat4 投影矩阵 = mat4(1.0f);
    vec3 相机位置 = vec3(0.0f, 0.0f, 0.0f);
    vec3 看坐标 = vec3(0.0f, 0.0f, 0.0f);
    vec3 上方向 = vec3(0.0f, 0.0f, 0.0f);
    unsigned int m_appStartTime = 0;

    mat4* 骨骼变换;

    struct S基础着色器索引
    {
        S方向光源索引 dlight;
        S材质索引 mat;
        GLint projview;
        GLint world;
        GLint eyeposw;
        GLint tex;
        GLint bonetransform;
        GLint worldinv;
        GLint bonetransformindex;
        GLint influence;
        GLint bonecount;

        S基础着色器索引()
        {
            projview = -1;
            world = -1;
            eyeposw = -1;
            tex = -1;
            bonetransform = -1;
            worldinv = -1;
            bonetransformindex = -1;
            influence = -1;
            bonecount = -1;
        }

    } 基础着色器索引;

    S按键 按键;
    C动态物体* 动态物体 = 0;
    C共享资源* 共享资源 = 0;
    C第三人称相机* 相机 = 0;

    void 归零开关状态();
    static void 鼠标按键检测(GLFWwindow* 窗口, int 按键, int 动作, int 模式);
    static void 按键检测(GLFWwindow* 窗口, int 按键, int 扫描模式, int 动作, int 模式);
    static void 鼠标位置检测(GLFWwindow* 窗口, double 位置x, double 位置y);
    static void 鼠标滑轮检测(GLFWwindow* 窗口, double 偏移x, double 偏移y);

    int 初始化();
    void 显示(float dt);
    void 释放();
    int 加入着色器(wstring filepath, GLuint prog, GLenum type);
    int 连接程序(GLuint program);
	int 主窗口();
    float 获取时间变化();

};