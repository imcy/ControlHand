#pragma once
#include "fglove.h"
#include "getPythonData.h"
#include "LineChart.h"


// GloveSampleDlg 对话框

class GloveSampleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GloveSampleDlg)

public:
	GloveSampleDlg(CWnd* pParent = NULL);   // 标准构造函数
	bool UpdateInputs();
	fdGlove *m_pGlove;	//数据手套窗口指针
	CLineChart *lineChart;	//曲线图窗口指针
	CListBox	m_ComList;
	CListBox	m_ComList_gesture;
	CCheckListBox m_check;
	CString iGesture;
	int gesture=-1;
	float tumb = 0;
	string strGesture;
	string strTumb;
	string strResult;
	float angle[15];//存储角度值
	getPythonData gpd;
	bool isSynchronize=false;//角度同步
	virtual ~GloveSampleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RobotControl };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnClickedSendGesture();
	afx_msg void OnSendAngle();
	afx_msg void OnClickedSynchronize();
	afx_msg void OnBnClickedDrawline();
};
