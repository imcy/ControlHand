// RobotHand.cpp: implementation of the CRobotHand class.
//整个手(20个指关节+1个手掌)对应一个RobotHand
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4996)

#include "stdafx.h"
#include "3DSLoader.h"
#include "RobotHand.h"
#include "GloableVariable.h"
#include "MatlabEngine.h"
#include <cmath>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMatlabEngine *engine = NULL;//matlab引擎

CRobotHand::CRobotHand()
{
	free = 0;
	numobjects = 0;
	maxobjects = 100;

	if (engine == NULL)
	{
		engine = new CMatlabEngine();
		if (!engine->IsInitialized())
		{
			MessageBoxA(NULL, "matlab引擎初始化失败!", NULL, MB_OK | MB_ICONWARNING);
			engine->GetLastErrorMessage();
		}
		engine->MinimizeWindow();
		//engine->SetWorkspace("E:\\3DSLoader");
		CString path = "cd 'F:\\3DSLoader'";
		engine->Execute(path);
		/*
		int choice[5] = { 1,0,0,0,0 };
		float* res=CalculateThetaByCoordinate(tVector(22, 30, 0),choice);
		
		CString str;
		str.Format("%f,%f,%f,%f",*res, *(res+1), *(res+2), *(res+3));
		PublicFuntoinHelper::ShowMessage(str);
		*/
		//CString[] values=str.
		//engine->Execute("plot([1 2],[3 5],'*r')");


	}
}

//////////////////////////////////////////////////////////////////////////
//			根据空间坐标计算各个角度,返回是角度而不是弧度
float* CRobotHand::CalculateThetaByCoordinate(tVector coordinate,int choice[])
{
	/*if (!engine->IsInitialized())
	{
		return NULL;
	}*/
	CString mstr;
	if(choice[0]){
	mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x,coordinate.y,coordinate.z,finger_lengths[0], finger_lengths[1], finger_lengths[2], finger_lengths[3],finger_L[0],finger_d[0],1.0);
	}
	if(choice[1]){
	mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[4], finger_lengths[5], finger_lengths[6], finger_lengths[7],finger_L[1],finger_d[1],0.0);
	}
	if(choice[2]){
		mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[8], finger_lengths[9], finger_lengths[10], finger_lengths[11],finger_L[2],finger_d[2],0.0);
	}
	if(choice[3]){
		mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[12], finger_lengths[13], finger_lengths[14], finger_lengths[15],finger_L[3],finger_d[3],0.0);
	}
	if(choice[4]){
		mstr.Format("[res] = CalculateThetaByCoordinate_Palm(%f,%f, %f, %f, %f, %f,%f,%f, %f,%f); disp([num2str(res(1)) ',' num2str(res(2)) ',' num2str(res(3)) ',' num2str(res(4))])",
		coordinate.x  ,coordinate.y,coordinate.z,finger_lengths[16], finger_lengths[17], finger_lengths[18], finger_lengths[19],finger_L[4],finger_d[4],0.0);
	}
		
	engine->Execute(mstr);
	LPSTR result = NULL;
	VARIANT var = engine->GetLastVResult();//var是返回的角度值
	CString str(var.bstrVal);
	str.Replace(" ", "");
	str.Replace("\n", "");
	return PublicFuntoinHelper::SplitString(str);
}

CRobotHand::~CRobotHand()
{
	for (int i=0; i <numobjects; i++)
	{
		delete objects[i];
	}

	//释放matlab引擎使用的资源
	if (engine != NULL)
	{
		engine->Quit();
		delete engine;
		engine = NULL;
	}
}
//////////////////////////////////////////////////////////////////////////
//			初始化各个指节的长度
//////////////////////////////////////////////////////////////////////////
void CRobotHand::Initial_Length()
{
	for (int index = 0; index < CGloableVariable::N-1;++index)
	{
		objects[index + 1]->length = finger_lengths[index];
		objects[index + 1]->width = finger_widths[index % 4];
	}
	objects[0]->length = 105.039;//手掌
	objects[0]->width = 116.901;//手掌

	objects[CGloableVariable::N]->length = 105.039;//手掌
	objects[CGloableVariable::N]->width = 116.901;//手掌
	
	for (int index = CGloableVariable::N; index < CGloableVariable::N + 20; ++index)
	{
		objects[index + 1]->length = finger_lengths[index-22];
		objects[index + 1]->width = 20;
	}
}

//////////////////////////////////////////////////////////////////////////
//			初始化各个指节坐标
//////////////////////////////////////////////////////////////////////////
void CRobotHand::Initial_CenterPos()
{
	for (int i = 0; i < CGloableVariable::N;i++)
	{
		objects[i]->currentPos.x = CGloableVariable::defaultPos[i][0]-150;
		objects[i]->currentPos.y = CGloableVariable::defaultPos[i][1];
		objects[i]->currentPos.z = CGloableVariable::defaultPos[i][2];
	}
	objects[1]->angle=ConvertAngleToRadian(60);

	Thumb1_Rotate(0);
	Index1_Rotate(0);
	Middle1_Rotate(0);
	Ring1_Rotate(0);
	Little1_Rotate(0);
	int j = 0;
	for (int i = CGloableVariable::N; i < CGloableVariable::N+21; i++)//右手部分
	{
		objects[i]->currentPos.x = CGloableVariable::defaultPos_r[j][0]-150;
		objects[i]->currentPos.y = CGloableVariable::defaultPos_r[j][1];
		objects[i]->currentPos.z = CGloableVariable::defaultPos_r[j][2];
		j++;

	}
	objects[CGloableVariable::N + 1]->angle = ConvertAngleToRadian(60);
	Thumb1_Rotate_r(0);
	Index1_Rotate_r(0);
	Middle1_Rotate_r(0);
	Ring1_Rotate_r(0);
	Little1_Rotate(0);

	//大拇指基部
	objects[CGloableVariable::N + 21]->currentPos.x = CGloableVariable::defaultPos_b[0][0] - 150;
	objects[CGloableVariable::N + 21]->currentPos.y = CGloableVariable::defaultPos_b[0][1];
	objects[CGloableVariable::N + 21]->currentPos.z = CGloableVariable::defaultPos_b[0][2];

	objects[CGloableVariable::N + 22]->currentPos.x = CGloableVariable::defaultPos_b[1][0] - 150;
	objects[CGloableVariable::N + 22]->currentPos.y = CGloableVariable::defaultPos_b[1][1];
	objects[CGloableVariable::N + 22]->currentPos.z = CGloableVariable::defaultPos_b[1][2];

}

BOOL CRobotHand::add(CKnuckle * _object)
{
	if (numobjects <= maxobjects)
	{
		objects[free] = _object;
		free ++;
		numobjects++;
		return TRUE;
	}
	else return FALSE;
}

//////////////////////////////////////////////////////////////////////////
//			显示当前灵巧手
//////////////////////////////////////////////////////////////////////////
void CRobotHand::drawGL()
{
	::glPushMatrix();
	::glTranslatef(-CGloableVariable::defaultPos[0][0], -CGloableVariable::defaultPos[0][1], -CGloableVariable::defaultPos[0][2]);
	  objects[0]->drawGL();
	::glPopMatrix();

	//画大拇指
	for (int i = 1; i <5; i++)
	{
		::glPushMatrix();
		
		::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
		::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
		::glRotatef(0, 0.0F, 1.0F, 0.0F);

		::glRotatef(objects[i]->sceneRot[2], 0.0F, 0.0F, 1.0F);
		::glRotatef(-30, 0.0F, 0.0F, 1.0F);
		::glRotatef(objects[i]->sceneRot[0], 1.0F, 0.0F, 0.0F);
		::glRotatef(30, 0.0F, 0.0F, 1.0F);
		::glTranslatef(-CGloableVariable::defaultPos[i][0], -CGloableVariable::defaultPos[i][1], -CGloableVariable::defaultPos[i][2]);
		objects[i]->drawGL();
		::glPopMatrix();
	}
	//画其余四指
	for (int i = 5; i <numobjects-22; i++)
	{
		::glPushMatrix();
		::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
		::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
		::glRotatef(objects[i]->sceneRot[2], 0.0F, 0.0F, 1.0F);
		::glRotatef(objects[i]->sceneRot[0], 1.0F, 0.0F, 0.0F);
		::glTranslatef(-CGloableVariable::defaultPos[i][0], -CGloableVariable::defaultPos[i][1], -CGloableVariable::defaultPos[i][2]);
		objects[i]->drawGL();
		::glPopMatrix();
	}
	

	//右手
	int i = numobjects-23;
	::glPushMatrix();
	::glMatrixMode(GL_MODELVIEW);
	::glScalef(-1.0f, 1.0f, 1.0f);//镜像
	::glTranslatef(-CGloableVariable::defaultPos_r[0][0], -CGloableVariable::defaultPos_r[0][1], -CGloableVariable::defaultPos_r[0][2]);
	objects[i]->drawGL();
	::glPopMatrix();
	
	int k = 1;
	
	for (i++; i <numobjects-18; i++)
	{
		::glPushMatrix();
		::glMatrixMode(GL_MODELVIEW);
		glScalef(-1.0f, 1.0f, 1.0f);//镜像
		::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
		::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
		::glRotatef(objects[i]->sceneRot[2], 0.0F, 0.0F, 1.0F);
		::glRotatef(-30, 0.0F, 0.0F, 1.0F);
		::glRotatef(objects[i]->sceneRot[0], 1.0F, 0.0F, 0.0F);
		::glRotatef(30, 0.0F, 0.0F, 1.0F);
		::glTranslatef(-CGloableVariable::defaultPos_r[k][0], -CGloableVariable::defaultPos_r[k][1], -CGloableVariable::defaultPos_r[k][2]);
		objects[i]->drawGL();
		::glPopMatrix();
		k++;
	}
	
	for (; i < numobjects-2; i++)
	{
		glPushMatrix();
		glScalef(-1.0f, 1.0f, 1.0f);//镜像
		::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
		::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
		::glRotatef(objects[i]->sceneRot[2], 0.0F, 0.0F, 1.0F);
		::glRotatef(objects[i]->sceneRot[0], 1.0F, 0.0F, 0.0F);
		::glTranslatef(-CGloableVariable::defaultPos_r[k][0], -CGloableVariable::defaultPos_r[k][1], -CGloableVariable::defaultPos_r[k][2]);
		objects[i]->drawGL();
		::glPopMatrix();
		k++;
	}

	//左右手基部
	::glPushMatrix();
	::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
	::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
	//::glRotatef(30, 0.0F, 1.0F, 0.0F);
	::glTranslatef(-CGloableVariable::defaultPos_b[0][0]*2, -CGloableVariable::defaultPos_b[0][1], -CGloableVariable::defaultPos_b[0][2]);
	 objects[numobjects - 2]->drawGL();
	::glPopMatrix();
	
	i++;

	::glPushMatrix();
	::glMatrixMode(GL_MODELVIEW);
	::glScalef(-1.0f, 1.0f, 1.0f);//镜像
	::glTranslatef(objects[i]->currentPos.x, objects[i]->currentPos.y, objects[i]->currentPos.z);
	::glRotatef(objects[i]->sceneRot[1], 0.0F, 1.0F, 0.0F);
	::glTranslatef(-CGloableVariable::defaultPos_b[1][0] * 2, -CGloableVariable::defaultPos_b[1][1], -CGloableVariable::defaultPos_b[1][2]);
	objects[numobjects - 1]->drawGL();
	::glPopMatrix();
	
}

void CRobotHand::Init()
{
	free = 0;
	numobjects = 0;
	maxobjects = 100;
}

void CRobotHand::doAfterMath()
{
	for (int i=0; i <numobjects; i++)
	{
		objects[i]->applyNormals();

	}
}

void CRobotHand::removeAllObjects()
{
	for (int i=0; i <numobjects; i++)
	{
		delete objects[i];
	}
	numobjects = 0;
	free = 0;
}

CKnuckle* CRobotHand::getObjectByName(char * name)
{
	char* objname;
	for (int i=0; i <numobjects; i++)
	{
		objects[i]->getName(objname);
		if(strcmp(name, objname) == 0) return objects[i];
	}
	
	return NULL;
}

//////////////////////////////////////////////////////////////////////////
//			将角度转化成弧度
//////////////////////////////////////////////////////////////////////////
float CRobotHand::ConvertAngleToRadian(float angle)
{
	return (angle / 180)*PI;
}
//////////////////////////////////////////////////////////////////////////
//			将弧度转化成角度
//////////////////////////////////////////////////////////////////////////
float CRobotHand::ConvertRadianToAngle(float radian)
{
	return (radian * 180) / PI;
}

#pragma region 运动控制
//////////////////////////////////////////////////////////////////////////
//		各个关节的运动
//////////////////////////////////////////////////////////////////////////
void CRobotHand::RotateFunction(int i , float angle)          //转动函数
{
	if(i<=4&&i>0)              //大拇指的转动函数
	{
		if(i==1)
		{
			//如果angle大于0，则向左侧摆，否则向右侧摆    -60<angle<30
			objects[i]->sceneRot[2] += angle;
			//第一个指节与手掌相连，该指节只能侧向运动，与手掌在同一个平面内
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置
	
			objects[i]->currentPos.x = -finger_d [(i-1)/4];
			objects[i]->currentPos.y = finger_L [(i-1)/4];
			objects[i]->currentPos.z = objects[0]->currentPos.z;
		}
		if(i==2)
		{
			//先把此指节倾斜（按第一指节的角度）
			objects[i]->sceneRot[2] =objects[i-1]->sceneRot[2];

			//如果angle>0向手掌内部弯曲(弯向手掌),否则向手掌外部弯曲
			objects[i]->sceneRot[0] -= angle;
			//第二个指节只能进行弯曲(向手掌靠近方向弯曲及相反方向),不能进行侧向运动
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i-1)/4] +
				(objects[i-1]->length)*cos(objects[i-1]->angle );//x= - di + a1*c(1角+60度)
			objects[i]->currentPos.y = finger_L[(i-1)/4] +
				(objects[i-1]->length)*sin(objects[i-1]->angle );//y=li + a1*c(1角+60度)
			objects[i]->currentPos.z = objects[0]->currentPos.z ;// z= palm.z

		}
		if(i==3)
		{
			objects[i]->sceneRot[2] =objects[i-2]->sceneRot[2];
			objects[i]->sceneRot[0] -= angle;
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i-1)/4] +
				cos(objects[i-2]->angle)*(objects[i-2]->length +
					((objects[i-1]->length)*cos(objects[i-1]->angle)));//x= - di + c1*(a1 + a2*c2)
			objects[i]->currentPos.y = finger_L[(i-1)/4] +
				sin(objects[i-2]->angle)*(objects[i-2]->length +
					((objects[i-1]->length)*cos(objects[i-1]->angle)));//y=li + s1*(a1 + a2*c2)
			objects[i]->currentPos.z = objects[0]->currentPos.z -
				sin(objects[i-1]->angle)*(objects[i-1]->length);// z=0 - s2*a2
		}
		if(i==4)
		{
			objects[i]->sceneRot[2] =objects[i-3]->sceneRot[2];
			objects[i]->sceneRot[0] -= angle;
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i-1)/4] +
				cos(objects[i-3]->angle)* (objects [i-3]->length +
				cos(objects[i-2]->angle)* objects[i-2]->length +
				cos(objects[i-1]->angle) * objects[i-1]->length);
			//x=  -di + c1*(a1 + c2*a2 + c23*a3)
			objects[i]->currentPos.y = finger_L[(i-1)/4] +
				sin(objects[i-3]->angle)* (objects [i-3]->length +
				cos(objects[i-2]->angle)* objects[i-2]->length +
				cos(objects[i-1]->angle) * objects[i-1]->length);
			//y=   li + s1*(a1 + c2*a2 + c23*a3)
			objects[i]->currentPos.z = objects[0]->currentPos.z -
				sin(objects[i-2]->angle)* objects [i-2]->length -
				sin(objects[i-1]->angle)* objects[i-1]->length;

		}
		objects[i]->currentPos.x = objects[i]->currentPos.x - 150;
	}

	else
	{	//其余四指的转动函数
		if (i == 5 || i == 9 || i == 13 || i == 17)
		{
			//如果angle大于0，则向左侧摆，否则向右侧摆
			objects[i]->sceneRot[2] += angle;
			//第一个指节与手掌相连，该指节只能侧向运动，与手掌在同一个平面内
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i - 1) / 4];
			objects[i]->currentPos.y = finger_L[(i - 1) / 4];
			objects[i]->currentPos.z = objects[0]->currentPos.z;

		}

		if (i == 6 || i == 10 || i == 14 || i == 18)
		{
			//先把此指节倾斜（按第一指节的角度）
			objects[i]->sceneRot[2] = objects[i - 1]->sceneRot[2];

			//如果angle>0向手掌内部弯曲(弯向手掌),否则向手掌外部弯曲
			objects[i]->sceneRot[0] -= angle;
			//第二个指节只能进行弯曲(向手掌靠近方向弯曲及相反方向),不能进行侧向运动
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			//objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i - 1) / 4] -
				(objects[i - 1]->length)*sin(objects[i - 1]->angle);//x= - di - a1*s1
			objects[i]->currentPos.y = finger_L[(i - 1) / 4] +
				(objects[i - 1]->length)*cos(objects[i - 1]->angle);//y=li + a1*c1
			objects[i]->currentPos.z = objects[0]->currentPos.z;// z= palm.z
		}
		if (i == 7 || i == 11 || i == 15 || i == 19)
		{
			objects[i]->sceneRot[2] = objects[i - 2]->sceneRot[2];
			objects[i]->sceneRot[0] -= angle;
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i - 1) / 4] -
				sin(objects[i - 2]->angle)*(objects[i - 2]->length +
				((objects[i - 1]->length)*cos(objects[i - 1]->angle)));//x= - di - s1*(a1 + a2*c2)
			objects[i]->currentPos.y = finger_L[(i - 1) / 4] +
				cos(objects[i - 2]->angle)*(objects[i - 2]->length +
				((objects[i - 1]->length)*cos(objects[i - 1]->angle)));//y=li + c1*(a1 + a2*c2)
			objects[i]->currentPos.z = objects[0]->currentPos.z -
				sin(objects[i - 1]->angle)*(objects[i - 1]->length);//z=0- s2*a2
		}
		if (i == 8 || i == 12 || i == 16 || i == 20)
		{
			objects[i]->sceneRot[2] = objects[i - 3]->sceneRot[2];
			objects[i]->sceneRot[0] -= angle;
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(i - 1) / 4] -
				sin(objects[i - 3]->angle)* (objects[i - 3]->length +
					cos(objects[i - 2]->angle)* objects[i - 2]->length +
					cos(objects[i - 1]->angle) * objects[i - 1]->length);
			//x=  -di - s1*(a1 + c2*a2 + c23*a3)
			objects[i]->currentPos.y = finger_L[(i - 1) / 4] +
				cos(objects[i - 3]->angle)* (objects[i - 3]->length +
					cos(objects[i - 2]->angle)* objects[i - 2]->length +
					cos(objects[i - 1]->angle) * objects[i - 1]->length);
			//y=   li + c1*(a1 + c2*a2 + c23*a3))
			objects[i]->currentPos.z = objects[0]->currentPos.z -
				sin(objects[i - 2]->angle)* objects[i - 2]->length -
				sin(objects[i - 1]->angle)*objects[i - 1]->length;
			//z= 0- a2*s2 -a3*s23

		}
		objects[i]->currentPos.x = objects[i]->currentPos.x - 150;
	}
}

void CRobotHand::RotateFunction_b(int i, float angle) 
{
	/*加上基部的旋转角度*/
	float x;
	float y;
	float z;
	ofstream ofile;               //定义输出文件
	objects[i]->sceneRot[1] = angle;
	objects[i]->currentPos.x = objects[i]->currentPos.x + 150;
	if (i == 4) {
		x = -finger_d[(i - 1) / 4] +
			cos(objects[i - 3]->angle)* (objects[i - 3]->length +
				cos(objects[i - 2]->angle)* objects[i - 2]->length +
				cos(objects[i - 1]->angle) * objects[i - 1]->length+
				cos(objects[i]->angle)*objects[i]->length
				);
		//x=  -di + c1*(a1 + c2*a2 + c23*a3+c234*a4)
		y = finger_L[(i - 1) / 4] +
			sin(objects[i - 3]->angle)* (objects[i - 3]->length +
				cos(objects[i - 2]->angle)* objects[i - 2]->length +
				cos(objects[i - 1]->angle) * objects[i - 1]->length+
				cos(objects[i]->angle)*objects[i]->length);
		//y=   li + s1*(a1 + c2*a2 + c23*a3+c234*a4)
		z = objects[0]->currentPos.z -
			sin(objects[i - 2]->angle)* objects[i - 2]->length -
			sin(objects[i - 1]->angle)* objects[i - 1]->length-
			sin(objects[i]->angle)* objects[i]->length;
	}

	float temp = objects[i]->currentPos.x - 34.032;
	float len = sqrt(temp*temp + objects[i]->currentPos.z* objects[i]->currentPos.z);

	float t = ConvertRadianToAngle(atan2(-objects[i]->currentPos.z, temp)); //绕x转过的角度
	float theta = ConvertAngleToRadian(t + objects[i]->sceneRot[1]);

	objects[i]->currentPos.x = 34.032 + len*cos(theta);
	objects[i]->currentPos.z = -len*sin(theta);
	//大拇指指间函数
	if (i == 4) {
		float temp = x - 34.032;
		float len = sqrt(temp*temp + z*z);
		float t = ConvertRadianToAngle(atan2(-z, temp)); //绕x转过的角度
		float theta = ConvertAngleToRadian(t + objects[i]->sceneRot[1]);
		x = 34.032 + len*cos(theta);
		z = -len*sin(theta);

		ofile.open("./angle.txt");     //作为输出文件打开
		ofile << x << " " << y << " " << z << " " << endl;
		ofile << objects[i]->currentPos.x << " " << objects[i]->currentPos.y << " " << objects[i]->currentPos.z << " " << endl;
		ofile.close();
	}
	objects[i]->currentPos.x = objects[i]->currentPos.x - 150;

}//拇指基部转动函数

//////////////////////////////////////////////////////////////////////////
//		各个关节的运动
//////////////////////////////////////////////////////////////////////////
void CRobotHand::RotateFunction_r(int i, float angle)          //转动函数
{
	int j = i - 22;
	if (i == 23)
		{
			//如果angle大于0，则向左侧摆，否则向右侧摆    -60<angle<30
			objects[i]->sceneRot[2] += angle;
			//第一个指节与手掌相连，该指节只能侧向运动，与手掌在同一个平面内
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(j - 1) / 4];
			objects[i]->currentPos.y = finger_L[(j - 1) / 4];
			objects[i]->currentPos.z = objects[0]->currentPos.z;
		}
	if (i == 24)
		{
			//先把此指节倾斜（按第一指节的角度）
			objects[i]->sceneRot[2] = objects[i - 1]->sceneRot[2];

			//如果angle>0向手掌内部弯曲(弯向手掌),否则向手掌外部弯曲
			objects[i]->sceneRot[0] -= angle;
			//第二个指节只能进行弯曲(向手掌靠近方向弯曲及相反方向),不能进行侧向运动
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(j - 1) / 4] +
				(objects[i - 1]->length)*cos(objects[i - 1]->angle);//x= - di + a1*c(1角+60度)
			objects[i]->currentPos.y = finger_L[(j - 1) / 4] +
				(objects[i - 1]->length)*sin(objects[i - 1]->angle);//y=li + a1*c(1角+60度)
			objects[i]->currentPos.z = objects[0]->currentPos.z;// z= palm.z

		}
	if (i == 25)
		{
			objects[i]->sceneRot[2] = objects[i - 2]->sceneRot[2];
			objects[i]->sceneRot[0] -= angle;
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(j - 1) / 4] +
				cos(objects[i - 2]->angle)*(objects[i - 2]->length +
				((objects[i - 1]->length)*cos(objects[i - 1]->angle)));//x= - di + c1*(a1 + a2*c2)
			objects[i]->currentPos.y = finger_L[(j - 1) / 4] +
				sin(objects[i - 2]->angle)*(objects[i - 2]->length +
				((objects[i - 1]->length)*cos(objects[i - 1]->angle)));//y=li + s1*(a1 + a2*c2)
			objects[i]->currentPos.z = objects[0]->currentPos.z -
				sin(objects[i - 1]->angle)*(objects[i - 1]->length);// z=0 - s2*a2

		}
	if (i == 26)
		{
			objects[i]->sceneRot[2] = objects[i - 3]->sceneRot[2];
			objects[i]->sceneRot[0] -= angle;
			float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
			objects[i]->angle += theta;
			objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

			objects[i]->currentPos.x = -finger_d[(j - 1) / 4] +
				cos(objects[i - 3]->angle)* (objects[i - 3]->length +
					cos(objects[i - 2]->angle)* objects[i - 2]->length +
					cos(objects[i - 1]->angle) * objects[i - 1]->length);
			//x=  -di + c1*(a1 + c2*a2 + c23*a3)
			objects[i]->currentPos.y = finger_L[(j - 1) / 4] +
				sin(objects[i - 3]->angle)* (objects[i - 3]->length +
					cos(objects[i - 2]->angle)* objects[i - 2]->length +
					cos(objects[i - 1]->angle) * objects[i - 1]->length);
			//y=   li + s1*(a1 + c2*a2 + c23*a3)
			objects[i]->currentPos.z = objects[0]->currentPos.z -
				sin(objects[i - 2]->angle)* objects[i - 2]->length -
				sin(objects[i - 1]->angle)* objects[i - 1]->length;

		}
     //其余四指的转动函数
	if (i == 27||i==31||i==35 || i==39)
	{
		//如果angle大于0，则向左侧摆，否则向右侧摆
		objects[i]->sceneRot[2] += angle;
		//第一个指节与手掌相连，该指节只能侧向运动，与手掌在同一个平面内
		float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
		objects[i]->angle += theta;
		objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置
		objects[i]->currentPos.x = -finger_d[(j - 1) / 4];
		//objects[i]->currentPos.y = finger_L[(j - 1) / 4];
		objects[i]->currentPos.z = objects[0]->currentPos.z;
		
	}
	if (i ==28||i == 32 || i==36||i==40)
	{
		//先把此指节倾斜（按第一指节的角度）
		objects[i]->sceneRot[2] = objects[i - 1]->sceneRot[2];

		//如果angle>0向手掌内部弯曲(弯向手掌),否则向手掌外部弯曲
		objects[i]->sceneRot[0] -= angle;
		//第二个指节只能进行弯曲(向手掌靠近方向弯曲及相反方向),不能进行侧向运动
		float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
		objects[i]->angle += theta;
		//objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

		objects[i]->currentPos.x = -finger_d[(j - 1) / 4] -
			(objects[i - 1]->length )*sin(objects[i - 1]->angle);//x= - di - a1*s1
		objects[i]->currentPos.y = finger_L[(j - 1) / 4] +
			(objects[i - 1]->length)*cos(objects[i - 1]->angle);//y=li + a1*c1
		objects[i]->currentPos.z = objects[0]->currentPos.z;// z= palm.z

	}
	if (i == 29 || i == 33 || i==37 || i==41)
	{
		objects[i]->sceneRot[2] = objects[i - 2]->sceneRot[2];
		objects[i]->sceneRot[0] -= angle;
		float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
		objects[i]->angle += theta;
		objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

		objects[i]->currentPos.x = -finger_d[(j - 1) / 4] -
			sin(objects[i - 2]->angle)*(objects[i - 2]->length +
			((objects[i - 1]->length)*cos(objects[i - 1]->angle)));//x= - di - s1*(a1 + a2*c2)
		objects[i]->currentPos.y = finger_L[(j - 1) / 4] +
			cos(objects[i - 2]->angle)*(objects[i - 2]->length +
			((objects[i - 1]->length)*cos(objects[i - 1]->angle)));//y=li + c1*(a1 + a2*c2)
		objects[i]->currentPos.z = objects[0]->currentPos.z -
			sin(objects[i - 1]->angle)*(objects[i - 1]->length);//z=0- s2*a2

	}
	if (i == 30 || i == 34 || i==38 || i==42)
	{
		objects[i]->sceneRot[2] = objects[i - 3]->sceneRot[2];
		objects[i]->sceneRot[0] -= angle;
		float theta = ConvertAngleToRadian(angle);//将角度转化成弧度
		objects[i]->angle += theta;
		objects[i]->lastPos = objects[i]->currentPos;//更新上一次坐标位置

		objects[i]->currentPos.x = -finger_d[(j - 1) / 4] -
			sin(objects[i - 3]->angle)* (objects[i - 3]->length +
				cos(objects[i - 2]->angle)* objects[i - 2]->length +
				cos(objects[i - 1]->angle) * objects[i - 1]->length);

		//x=  -di - s1*(a1 + c2*a2 + c23*a3)
		objects[i]->currentPos.y = finger_L[(j - 1) / 4] +
			cos(objects[i - 3]->angle)* (objects[i - 3]->length +
				cos(objects[i - 2]->angle)* objects[i - 2]->length +
				cos(objects[i - 1]->angle) * objects[i - 1]->length);

		//y=   li + c1*(a1 + c2*a2 + c23*a3))
		objects[i]->currentPos.z = objects[0]->currentPos.z -
			sin(objects[i - 2]->angle)* objects[i - 2]->length -
			sin(objects[i - 1]->angle)*objects[i - 1]->length;
		//z= 0- a2*s2 -a3*s23


	}
	objects[i]->currentPos.x = objects[i]->currentPos.x - 150;
}
//////////////////////////////////////////////////////////////////////////
//			大拇指各个关节的运动
//////////////////////////////////////////////////////////////////////////
void CRobotHand::Thumb1_Rotate(float angle)
{
	RotateFunction(THUMB_ONE_INDEX,angle);
	Thumb2_Rotate(0);
}
void CRobotHand::Thumb2_Rotate(float angle)
{
	RotateFunction(THUMB_TWO_INDEX,angle);
	Thumb3_Rotate(0);
}
void CRobotHand::Thumb3_Rotate(float angle)
{
	RotateFunction(THUMB_THREE_INDEX,angle);
	Thumb4_Rotate(0);
}
void CRobotHand::Thumb4_Rotate(float angle)
{
	RotateFunction(THUMB_FOUR_INDEX,angle);
}
void CRobotHand::Index1_Rotate(float angle)
{	RotateFunction(INDEX_ONE_INDEX,angle);
	Index2_Rotate(0);
}
void CRobotHand::Index2_Rotate(float angle)
{	
	RotateFunction(INDEX_TWO_INDEX,angle);
	Index3_Rotate(0);
}
void CRobotHand::Index3_Rotate(float angle)
{

	RotateFunction(INDEX_THREE_INDEX,angle);
	Index4_Rotate(0);
}
void CRobotHand::Index4_Rotate(float angle)
{
	RotateFunction(INDEX_FOUR_INDEX,angle);
}
void CRobotHand::Middle1_Rotate(float angle)
{	
	RotateFunction(MIDDLE_ONE_INDEX,angle);
	Middle2_Rotate(0);
}
void CRobotHand::Middle2_Rotate(float angle)
{
	RotateFunction(MIDDLE_TWO_INDEX,angle);
	Middle3_Rotate(0);
}
void CRobotHand::Middle3_Rotate(float angle)
{
	RotateFunction(MIDDLE_THREE_INDEX,angle);
	Middle4_Rotate(0);
}
void CRobotHand::Middle4_Rotate(float angle)
{
	RotateFunction(MIDDLE_FOUR_INDEX,angle);
}
void CRobotHand::Ring1_Rotate(float angle)
{
	RotateFunction(RING_ONE_INDEX,angle);
	Ring2_Rotate(0);
}
void CRobotHand::Ring2_Rotate(float angle)
{
	RotateFunction(RING_TWO_INDEX,angle);
	Ring3_Rotate(0);
}
void CRobotHand::Ring3_Rotate(float angle)
{
	RotateFunction(RING_THREE_INDEX,angle);
	Ring4_Rotate(0);
}
void CRobotHand::Ring4_Rotate(float angle)
{
	RotateFunction(RING_FOUR_INDEX,angle);
}
void CRobotHand::Little1_Rotate(float angle)
{
	RotateFunction(LITTLE_ONE_INDEX,angle);
	Little2_Rotate(0);
}
void CRobotHand::Little2_Rotate(float angle)
{
	RotateFunction(LITTLE_TWO_INDEX,angle);
	Little3_Rotate(0);
}
void CRobotHand::Little3_Rotate(float angle)
{
	RotateFunction(LITTLE_THREE_INDEX,angle);
	Little4_Rotate(0);
}
void CRobotHand::Little4_Rotate(float angle)
{
	RotateFunction(LITTLE_FOUR_INDEX,angle);
}

/*右手*/
/*大拇指*/
void CRobotHand::Thumb1_Rotate_r(float angle)
{
	RotateFunction_r(THUMB_ONE_INDEX_R, angle);
	Thumb2_Rotate_r(0);
}
void CRobotHand::Thumb2_Rotate_r(float angle)
{
	RotateFunction_r(THUMB_TWO_INDEX_R, angle);
	Thumb3_Rotate_r(0);
}
void CRobotHand::Thumb3_Rotate_r(float angle)
{
	RotateFunction_r(THUMB_THREE_INDEX_R, angle);
	Thumb4_Rotate_r(0);
}
void CRobotHand::Thumb4_Rotate_r(float angle)
{
	RotateFunction_r(THUMB_FOUR_INDEX_R, angle);
}
/*食指*/
void CRobotHand::Index1_Rotate_r(float angle)
{
	RotateFunction_r(INDEX_ONE_INDEX_R, angle);
	Index2_Rotate_r(0);
}
void CRobotHand::Index2_Rotate_r(float angle)
{
	RotateFunction_r(INDEX_TWO_INDEX_R, angle);
	Index3_Rotate_r(0);
}
void CRobotHand::Index3_Rotate_r(float angle)
{

	RotateFunction_r(INDEX_THREE_INDEX_R, angle);
	Index4_Rotate_r(0);
}
void CRobotHand::Index4_Rotate_r(float angle)
{
	RotateFunction_r(INDEX_FOUR_INDEX_R, angle);
}

/*中指*/
void CRobotHand::Middle1_Rotate_r(float angle)
{
	RotateFunction_r(MIDDLE_ONE_INDEX_R, angle);
	Middle2_Rotate_r(0);
}
void CRobotHand::Middle2_Rotate_r(float angle)
{
	RotateFunction_r(MIDDLE_TWO_INDEX_R, angle);
	Middle3_Rotate_r(0);
}
void CRobotHand::Middle3_Rotate_r(float angle)
{

	RotateFunction_r(MIDDLE_THREE_INDEX_R, angle);
	Middle4_Rotate_r(0);
}
void CRobotHand::Middle4_Rotate_r(float angle)
{
	RotateFunction_r(MIDDLE_FOUR_INDEX_R, angle);
}
/*无名指*/
void CRobotHand::Ring1_Rotate_r(float angle)
{
	RotateFunction_r(RING_ONE_INDEX_R, angle);
	Ring2_Rotate_r(0);
}
void CRobotHand::Ring2_Rotate_r(float angle)
{
	RotateFunction_r(RING_TWO_INDEX_R, angle);
	Ring3_Rotate_r(0);
}
void CRobotHand::Ring3_Rotate_r(float angle)
{
	RotateFunction_r(RING_THREE_INDEX_R, angle);
	Ring4_Rotate_r(0);
}
void CRobotHand::Ring4_Rotate_r(float angle)
{
	RotateFunction_r(RING_FOUR_INDEX_R, angle);
}
/*小指*/
void CRobotHand::Little1_Rotate_r(float angle)
{
	RotateFunction_r(LITTLE_ONE_INDEX_R, angle);
	Little2_Rotate_r(0);
}
void CRobotHand::Little2_Rotate_r(float angle)
{
	RotateFunction_r(LITTLE_TWO_INDEX_R, angle);
	Little3_Rotate_r(0);
}
void CRobotHand::Little3_Rotate_r(float angle)
{
	RotateFunction_r(LITTLE_THREE_INDEX_R, angle);
	Little4_Rotate(0);
}
void CRobotHand::Little4_Rotate_r(float angle)
{
	RotateFunction_r(LITTLE_FOUR_INDEX_R, angle);
}
/*大拇指基部旋转*/
void CRobotHand::Thumb_Rotate_b(float angle)
{
	objects[numobjects - 2]->sceneRot[1] = angle;
	RotateFunction_b(THUMB_ONE_INDEX, angle);
	RotateFunction_b(THUMB_TWO_INDEX, angle);
	RotateFunction_b(THUMB_THREE_INDEX, angle);
	RotateFunction_b(THUMB_FOUR_INDEX, angle);
}
/*右手大拇指基部旋转*/
void CRobotHand::Thumb_Rotate_br(float angle)
{
	objects[numobjects - 1]->sceneRot[1] = angle;
	RotateFunction_b(THUMB_ONE_INDEX_R, angle);
	RotateFunction_b(THUMB_TWO_INDEX_R, angle);
	RotateFunction_b(THUMB_THREE_INDEX_R, angle);
	RotateFunction_b(THUMB_FOUR_INDEX_R, angle);
}
#pragma endregion


