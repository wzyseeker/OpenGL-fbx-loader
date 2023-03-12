#pragma once
#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include"按键检测.h"

using namespace glm;

class C自由相机
{
public:
    void 相机(mat4* 观察矩阵, vec3 初始上方向, vec3 初始前方向, vec3 初始坐标, float 转向灵敏度, float 移动速度);
    C自由相机(S按键* 按键)
    {
        this->按键 = 按键;
    };
    ~C自由相机() {};

    vec3 前方向 = { 0.0f, 0.0f, 1.0f };
    vec3 上方向 = { 0.0f, 1.0f, 0.0f };
    vec3 右方向 = { 1.0f, 0.0f, 0.0f };
    vec3 相机坐标 = { 0.0f, 0.0f, 0.0f };
    S按键* 按键;

private:
    vec3 保存前方向 = { 0.0f, 0.0f, 0.0f };
    vec3 看坐标 = { 0.0f, 0.0f, 0.0f };

    float 转向灵敏度储存 = 0;
    bool 初始化 = 1;
};

class C重力相机
{
public:
    void 相机(mat4* 观察矩阵, vec3 重力轴, vec3 开局前方向, vec3 初始坐标, float 转向灵敏度, float 移动速度);
    C重力相机(S按键* 按键)
    {
        this->按键 = 按键;
    }
    ~C重力相机() {};

    vec3 前方向 = { 0.0f, 0.0f, 1.0f };
    vec3 上方向 = { 0.0f, 1.0f, 0.0f };
    vec3 右方向 = { 1.0f, 0.0f, 0.0f };
    vec3 相机坐标 = { 0.0f, 0.0f, 0.0f };
    S按键* 按键;

private:
    vec3 看坐标 = { 0.0f, 0.0f, 0.0f };
    vec3 保存前方向 = { 0.0f, 0.0f, 0.0f };
    vec3 重力轴储存 = { 0.0f, 0.0f, 0.0f };
    vec3 重力轴前方向 = { 0.0f, 0.0f, 0.0f };
    vec3 单位重力轴储存 = { 0.0f, 0.0f, 0.0f };
    vec3 旋转向量 = { 0.0f, 0.0f, 0.0f };
    vec3 重力前向量 = { 0.0f, 0.0f, 0.0f };
    float 转向灵敏度储存 = 0;
    float 前重角度cos = 0;
    float 前重角度sin = 0;
    float 旋转向量长度 = 0;
    bool 初始化 = 1;
};

class C第三人称相机
{
public:
    void 相机(mat4* 观察矩阵);
    C第三人称相机(S按键* 按键, float Phi, float Theta, float 初始半径, float 转向灵敏度, float 移动速度, float 滑轮灵敏度, vec3 看点)
    {
        this->按键 = 按键;
        this->Phi = Phi;
        this->Theta = Theta;
        this->半径 = 初始半径;
        this->移动速度 = 移动速度;
        this->转向灵敏度 = 转向灵敏度;
        this->看坐标 = 看点;
        this->滑轮灵敏度 = 滑轮灵敏度;
    }
    ~C第三人称相机() {};

    vec3 相机坐标 = { 0.0f, 0.0f, -40.0f };
    float Phi = 0;
    float Theta = 0;
    float 半径 = 40;
    S按键* 按键;
    float 移动速度 = 0;
    float 转向灵敏度 = 0;
    float 滑轮灵敏度 = 0;

private:
    vec3 看坐标 = { 0.0f, 0.0f, 0.0f };
    vec3 前方向 = { 0.0f, 0.0f, 1.0f };
    vec3 上方向 = { 0.0f, 1.0f, 0.0f };
    vec3 右方向 = { 1.0f, 0.0f, 0.0f };
    vec3 移动距离 = { 0.0f, 0.0f, 0.0f };
    float 旋转角 = 0;
    float 方向角 = 0;
    mat4 变换 = mat4(1.0f);
};