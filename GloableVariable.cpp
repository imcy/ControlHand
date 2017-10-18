#include "stdafx.h"
#include "GloableVariable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CString CGloableVariable::files_3ds[N+23];
//下面均是按照大拇指、食指、中指、无名指、小拇指的顺序

float CGloableVariable::defaultPos[N][3] = { { 150,0,0 },                 //每个部件的起始位置
{ 46.186,24.331,0 },{ 56.521,42.232,0 },{ 69.047,63.927,0 },{ 81.378,85.286,0 },

{ 20.941,37.685,0 },{ 20.941,58.556,0 },{ 20.941,108.615,0 },{ 20.941,153.236,0 },

{ 0.669,40.220,0 },{ 0.669,60.894,0 },{ 0.669,125.957,0 },{ 0.669,170.576,0 },

{ -23.204,40.220,0 },{ -23.204,60.894,0 },{ -23.204,110.957,0 },{ -23.204,155.576,0 },
{ -43.541,37.685,0 },{ -43.541,58.556,0 },{ -43.541,88.615,0 },{ -43.541,118.236,0 } };

float CGloableVariable::defaultPos_r[21][3] = { {150,0,0},
{ 46.186,24.331,0 },{ 56.521,42.232,0 },{ 69.047,63.927,0 },{ 81.378,85.286,0 },

{ 20.941,37.685,0 },{ 20.941,58.556,0 },{ 20.941,108.615,0 },{ 20.941,153.236,0 },

{ 0.669,40.220,0 },{ 0.669,60.894,0 },{ 0.669,125.957,0 },{ 0.669,170.576,0 },

{ -23.204,40.220,0 },{ -23.204,60.894,0 },{ -23.204,110.957,0 },{ -23.204,155.576,0 },
{ -43.541,37.685,0 },{ -43.541,58.556,0 },{ -43.541,88.615,0 },{ -43.541,118.236,0 } };

float CGloableVariable::defaultPos_b[2][3] = {
	{ 34.032,0,0},{ 34.032,0,0 }
};
//////////////////////////////////////////////////////////////////////////
//			初始化
//////////////////////////////////////////////////////////////////////////
void CGloableVariable::Initial()
{
	Initial_3dsFilesName();
}
//////////////////////////////////////////////////////////////////////////
//			各个指关节对应的3DS文件名
//////////////////////////////////////////////////////////////////////////
void CGloableVariable::Initial_3dsFilesName()          //部件的导入来源文件
{
	int index = 0;

	files_3ds[index++] = "./3DSModels/robotic hand/palm/palm2.3DS";//手掌
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_1.3DS"; //大拇指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_2.3DS"; //大拇指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_3.3DS"; //大拇指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_4.3DS"; //大拇指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_1.3DS"; //食指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_2.3DS"; //食指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_3.3DS"; //食指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_4.3DS"; //食指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_1.3DS"; //中指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_2.3DS"; //中指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_3.3DS"; //中指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_4.3DS"; //中指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_1.3DS"; //无名指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_2.3DS"; //无名指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_3.3DS"; //无名指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_4.3DS"; //无名指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_1.3DS"; //小拇指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_2.3DS"; //小拇指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_3.3DS"; //小拇指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_4.3DS"; //小拇指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/palm/background.3DS"; //背景
	
	files_3ds[index++] = "./3DSModels/robotic hand/palm/palm2.3DS";//手掌

	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_1.3DS"; //大拇指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_2.3DS"; //大拇指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_3.3DS"; //大拇指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/1thumb/thumb_4.3DS"; //大拇指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_1.3DS"; //食指基关节

	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_2.3DS"; //食指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_3.3DS"; //食指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/2index/index_4.3DS"; //食指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_1.3DS"; //中指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_2.3DS"; //中指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_3.3DS"; //中指中间关节

	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/3middle/middle_4.3DS"; //中指末梢关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_1.3DS"; //无名指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_2.3DS"; //无名指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_3.3DS"; //无名指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/4ring/ring_4.3DS"; //无名指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_1.3DS"; //小拇指基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_2.3DS"; //小拇指近基关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_3.3DS"; //小拇指中间关节
	files_3ds[index++] = "./3DSModels/robotic hand/机械手改/5little/little_4.3DS"; //小拇指末梢关节

	files_3ds[index++] = "./3DSModels/robotic hand/palm/tumb_b.3DS";//手掌另外一部分
	files_3ds[index++] = "./3DSModels/robotic hand/palm/tumb_b.3DS";//手掌另外一部分

}

