#pragma once
#include<windows.h>
#include<glm/glm.hpp>

using namespace glm;

const uint FVF位置 = 0x00000001;
const uint FVF法向量 = 0x00000002;
const uint FVF纹理坐标 = 0x00000004;
const uint FVF切向量 = 0x0000008;
const uint FVF关联骨骼 = 0x00000010;
const uint FVF权重 = 0x00000011;
const uint FVF数量 = 6;
const uint FVF描述数量 = 3;
const uint d骨骼动画描述 = 0x00000001 | 0x00000002 | 0x00000004 | 0x0000008 | 0x00000010 | 0x00000011;
const uint d骨骼动画描述无切线 = 0x00000001 | 0x00000002 | 0x00000004 | 0x00000010 | 0x00000011;
const uint d静态物体描述 = 0x00000001 | 0x00000002 | 0x00000004;
const uint d最大骨骼索引数量 = 4;
const uint d最大骨骼数量 = 200;