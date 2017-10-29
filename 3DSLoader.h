// 3DSLoader.h : main header file for the 3DSLOADER application
//

#if !defined(AFX_MYSDOPENGL_H__991FDB70_0EB8_4CD6_B11E_20D1AAAF5177__INCLUDED_)
#define AFX_MYSDOPENGL_H__991FDB70_0EB8_4CD6_B11E_20D1AAAF5177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif 
#include "resource.h"       // main symbols
#include "RobotHand.h"
#include "GloveSampleDlg.h"
#include "KinectWin.h"
/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderApp:
// See 3DSLoader.cpp for the implementation of this class
//
class CMy3DSLoaderApp : public CWinApp
{
public:
	CMy3DSLoaderApp();
	BOOL OpenFile(CRobotHand& ctl, LPCTSTR lpszPathName);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMy3DSLoaderApp)
	public:
	virtual BOOL InitInstance();
	GloveSampleDlg *dlg;
	KinectWin *kinwin;
	void OnTest();
	void OnAngle(); //角度处理函数
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CMy3DSLoaderApp)
	afx_msg void OnAppAbout();
	afx_msg void OnControl();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnOpenKinect();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSDOPENGL_H__991FDB70_0EB8_4CD6_B11E_20D1AAAF5177__INCLUDED_)
