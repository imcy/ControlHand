// 灵巧手由一个个的单元(手指关节+手掌)组成，每个关节对应一个CRobotHand对象
//注：每只灵巧手由五个手指+手掌组成，每个手指由四个指节组成
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RobotHand_H__F4D23E1D_92BF_4F04_A498_761E19114FC0__INCLUDED_)
#define AFX_RobotHand_H__F4D23E1D_92BF_4F04_A498_761E19114FC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define WM_MYMESSAGE WM_USER+8  //自定义消息
#include "Knuckle.h"
#include <fstream>
#include <iomanip>

class CRobotHand  
{
public:
	CRobotHand();
	virtual ~CRobotHand();

	CKnuckle* getObjectByName(char* name);
	void removeAllObjects();
	void doAfterMath();
	void Init();
	int	 getNumObjects() {return numobjects;};

	void drawGL();
	BOOL add(CKnuckle* _object);
private:
	int numobjects;
	int free;
	int maxobjects;

public:
	CKnuckle* objects[100];	
	
public:
	void Initial_Length();//初始化各个指节的长度
	void Initial_CenterPos();//初始化各个指节的坐标
	//根据坐标计算手指的四个关节的角度
	//返回指向数组的指针，分别存储theta1,theta2,theta3,theta4
	//参数分别为px,py,pz
	float* CalculateThetaByCoordinate(tVector coordinate,int choice[]);

	float ConvertAngleToRadian(float angle);//将角度转化成弧度
	float ConvertRadianToAngle(float radian);//将弧度转化成角度

	void RotateFunction(int i, float angle);
	void RotateFunction_r(int i, float angle);
	void RotateFunction_b(int i, float angle);
	void Thumb1_Rotate(float angle);//大拇指基关节旋转
	void Thumb2_Rotate(float angle);//大拇指近基关节旋转
	void Thumb3_Rotate(float angle);//大拇指中间关节旋转
	void Thumb4_Rotate(float angle);//大拇指末梢关节旋转

	void Index1_Rotate(float angle);//食指基关节旋转
	void Index2_Rotate(float angle);//食指近基关节旋转
	void Index3_Rotate(float angle);//食指中间关节旋转
	void Index4_Rotate(float angle);//食指末梢关节旋转

	void Middle1_Rotate(float angle);//中指基关节旋转
	void Middle2_Rotate(float angle);//中指近基关节旋转
	void Middle3_Rotate(float angle);//中指中间关节旋转
	void Middle4_Rotate(float angle);//中指末梢关节旋转

	void Ring1_Rotate(float angle);//无名指基关节旋转
	void Ring2_Rotate(float angle);//无名指近基关节旋转
	void Ring3_Rotate(float angle);//无名指中间关节旋转
	void Ring4_Rotate(float angle);//无名指末梢关节旋转

	void Little1_Rotate(float angle);//小拇指基关节旋转
	void Little2_Rotate(float angle);//小拇指近基关节旋转
	void Little3_Rotate(float angle);//小拇指中间关节旋转
	void Little4_Rotate(float angle);//小拇指末梢关节旋转
	/*右手*/
	void Thumb1_Rotate_r(float angle);//大拇指基关节旋转
	void Thumb2_Rotate_r(float angle);//大拇指近基关节旋转
	void Thumb3_Rotate_r(float angle);//大拇指中间关节旋转
	void Thumb4_Rotate_r(float angle);//大拇指末梢关节旋转

	void Index1_Rotate_r(float angle);//食指基关节旋转
	void Index2_Rotate_r(float angle);//食指近基关节旋转
	void Index3_Rotate_r(float angle);//食指中间关节旋转
	void Index4_Rotate_r(float angle);//食指末梢关节旋转

	void Middle1_Rotate_r(float angle);//中指基关节旋转
	void Middle2_Rotate_r(float angle);//中指近基关节旋转
	void Middle3_Rotate_r(float angle);//中指中间关节旋转
	void Middle4_Rotate_r(float angle);//中指末梢关节旋转

	void Ring1_Rotate_r(float angle);//无名指基关节旋转
	void Ring2_Rotate_r(float angle);//无名指近基关节旋转
	void Ring3_Rotate_r(float angle);//无名指中间关节旋转
	void Ring4_Rotate_r(float angle);//无名指末梢关节旋转

	void Little1_Rotate_r(float angle);//小拇指基关节旋转
	void Little2_Rotate_r(float angle);//小拇指近基关节旋转
	void Little3_Rotate_r(float angle);//小拇指中间关节旋转
	void Little4_Rotate_r(float angle);//小拇指末梢关节旋转

	void Thumb_Rotate_b(float angle);//大拇指基关节旋转
	void Thumb_Rotate_br(float angle);//大拇指基关节旋转
};

#endif // !defined(AFX_RobotHand_H__F4D23E1D_92BF_4F04_A498_761E19114FC0__INCLUDED_)
