#pragma once
#include <string>
#include "Python.h"
#include <iostream>
using namespace std;
class getPythonData
{
public:
	getPythonData();
	int getGloveGesture(string s1);
	float getTumbData(string s2);
	void initPython();
	PyObject * pModule = NULL;//声明变量  
	PyObject * pFunc = NULL;//声明变量 
	PyObject * pFuncTumb = NULL;//声明变量
	~getPythonData();
};

