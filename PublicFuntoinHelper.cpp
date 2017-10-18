#include "StdAfx.h"
#include "PublicFuntoinHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////
//			消息框
//type=0:普通消息框;type=1:询问消息框;type=2:警告消息框;type=3:错误消息框
//////////////////////////////////////////////////////////////////////////
int PublicFuntoinHelper::ShowMessage(LPCSTR content, UINT type, LPCTSTR title)
{
	if (title==NULL)
	{
		title = _T("消息框");
	}
	switch (type)
	{
	case 0:
		return MessageBoxA(NULL, content, title, MB_OK | MB_ICONINFORMATION);
	case 1:
		return MessageBoxA(NULL, content, title, MB_YESNO | MB_ICONQUESTION);
	case 2:
		return MessageBoxA(NULL, content, title, MB_OK | MB_ICONEXCLAMATION);
	case 3:
		return MessageBoxA(NULL, content, title, MB_OK | MB_ICONSTOP);
	default:
		return MessageBoxA(NULL, content, title, MB_OK | MB_ICONINFORMATION);
		break;
	}

}
//////////////////////////////////////////////////////////////////////////
//	分割字符串并转化成浮点数 values:要处理的字符串;splitChar:分隔符
//////////////////////////////////////////////////////////////////////////
float* PublicFuntoinHelper::SplitString(CString values, CString splitChar)
{
	float* fv = new float[4];
	int index = 0;
	CString strleft;

	//查找字符，如果没找到，则返回0，找到则返回字符的位置,
	//参数可以是字符也可以是字符串
	int pos = values.Find(splitChar);
	while (pos > 0)
	{
		strleft = values.Left(pos);//取左,参数为字符串的个数
		values = values.Right(values.GetLength() - pos - 1);//取右，参数同上
		fv[index++] = atof(strleft);
		pos = values.Find(splitChar);
	}
	fv[index++] = atof(values);
	
	return fv;
}