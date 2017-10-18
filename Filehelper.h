///////////////////////////
//文件处理相关类
//////////////////////////
#if !defined(AFX_FILEHELPER_H)
#define AFX_FILEHELPER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class FileHelper
{
public:
	FileHelper();
	~FileHelper();
	bool Load3DSFile();
	/*bool FileHelper::OpenFile(LPCTSTR lpszPathName);*/
private:

};


#endif