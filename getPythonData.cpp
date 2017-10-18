#include "stdafx.h"
#include "getPythonData.h"


getPythonData::getPythonData()
{
}
void getPythonData::initPython() {
	Py_SetPythonHome("F:/Python27/");
	Py_Initialize();//使用python之前，要调用Py_Initialize();这个函数进行初始化 
	pModule = PyImport_ImportModule("pytest");
	if (!pModule) // 加载模块失败
	{
		cout << "[ERROR] Python get module failed." << endl;
		return ;
	}
	pFunc = PyObject_GetAttrString(pModule, "caculate");
	pFuncTumb= PyObject_GetAttrString(pModule, "caculateTumb");
	/*
	if (!pFunc && !pFuncTumb) // 加载模块失败
	{
		cout << "[ERROR] Python get pFunc failed." << endl;
		return ;
	}*/
}
int getPythonData::getGloveGesture(string s1)
{
	//创建参数:
	PyObject *pArgs = PyTuple_New(1);//函数调用的参数传递均是以元组的形式打包的,2表示参数个数
	PyObject *st = Py_BuildValue("s", s1);
	PyTuple_SetItem(pArgs, 0, st);//0--序号,i表示创建int型变量
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFunc, pArgs);//调用函数
	//将返回值转换为int类型
	int result;
	PyArg_Parse(pReturn, "i", &result);//i表示转换成int型变量
	//Py_Finalize();
	return result;
}

float getPythonData::getTumbData(string s2)
{
	//创建参数:
	PyObject *pArgs = PyTuple_New(1);//函数调用的参数传递均是以元组的形式打包的,2表示参数个数
	PyObject *st = Py_BuildValue("s", s2);
	PyTuple_SetItem(pArgs, 0, st);//0--序号,i表示创建int型变量
	PyObject *pReturn = NULL;
	pReturn = PyEval_CallObject(pFuncTumb, pArgs);//调用函数
											  //将返回值转换为int类型
	float result;
	PyArg_Parse(pReturn, "f", &result);//i表示转换成int型变量
									   //Py_Finalize();
	return result;
}




getPythonData::~getPythonData()
{
}
