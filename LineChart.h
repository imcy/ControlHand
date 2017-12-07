#pragma once
#include "GloveSampleDlg.h"
#include "tchart1.h"
#include "CSeries.h"

// CLineChart 对话框

class CLineChart : public CDialogEx
{
	DECLARE_DYNAMIC(CLineChart)

public:
	CLineChart(CWnd* pParent = NULL);   // 标准构造函数

	afx_msg void OnBnClickedDrawline();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void drawMoving();
	double m_ThumbArray[3][32];	//大拇指角度数组
	CSeries LineThumb[3];	//大拇指曲线

	double m_IndexArray[3][32];	//食指角度数组
	CSeries LineIndex[3];	//食指曲线

	double m_MiddleArray[2][32];	//中指角度数组
	CSeries LineMiddle[2];	//中指曲线

	double m_RingArray[3][32];	//无名指角度数组
	CSeries LineRing[3];	//无名指曲线

	double m_LittleArray[3][32];	//小指角度数组
	CSeries LineLittle[3];	//小指曲线

	double m_BaseArray[32];	//掌腕关节角度数组
	CSeries LineBase;	//掌腕关节曲线

	double m_X[32];
	unsigned int m_count;
	const size_t m_Length = 32;
	virtual ~CLineChart();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAW };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	
public:
	CTchart1 CThumb;
	CTchart1 CIndex;
	CTchart1 CMiddle;
	CTchart1 CRing;
	CTchart1 CLittle;
	CTchart1 CBase;
};
