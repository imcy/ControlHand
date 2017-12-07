// LineChart.cpp : 实现文件
//

#include "stdafx.h"
#include "3DSLoader.h"
#include "LineChart.h"
#include "afxdialogex.h"


// CLineChart 对话框

IMPLEMENT_DYNAMIC(CLineChart, CDialogEx)

CLineChart::CLineChart(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DRAW, pParent)
{
	
}

CLineChart::~CLineChart()
{
}

void CLineChart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TCHART1, CThumb);
	DDX_Control(pDX, IDC_TCHART2, CIndex);
	DDX_Control(pDX, IDC_TCHART3, CMiddle);
	DDX_Control(pDX, IDC_TCHART4, CRing);
	DDX_Control(pDX, IDC_TCHART5, CLittle);
	DDX_Control(pDX, IDC_TCHART6, CBase);
}


BEGIN_MESSAGE_MAP(CLineChart, CDialogEx)
	ON_BN_CLICKED(IDC_DRAWLINE, &CLineChart::OnBnClickedDrawline)
	ON_WM_TIMER()
END_MESSAGE_MAP()


//数组左移
void LeftMoveArray(double* ptr, size_t length, double data)
{
	for (size_t i = 1; i<length; ++i)
	{
		ptr[i - 1] = ptr[i];
	}
	ptr[length - 1] = data;
}

// CLineChart 消息处理程序
void CLineChart::OnBnClickedDrawline()
{
	// 点击绘图按钮绘图
	for (int i = 0; i < 3; i++) {
		LineThumb[i]= (CSeries)CThumb.Series(i);
		LineThumb[i].Clear();
		ZeroMemory(&m_ThumbArray[i], sizeof(double)*m_Length);

		LineIndex[i] = (CSeries)CIndex.Series(i);
		LineIndex[i].Clear();
		ZeroMemory(&m_IndexArray[i], sizeof(double)*m_Length);
		if (i < 2) {
			LineMiddle[i] = (CSeries)CMiddle.Series(i);
			LineMiddle[i].Clear();
			ZeroMemory(&m_MiddleArray[i], sizeof(double)*m_Length);
		}
		LineRing[i] = (CSeries)CRing.Series(i);
		LineRing[i].Clear();
		ZeroMemory(&m_RingArray[i], sizeof(double)*m_Length);

		LineLittle[i] = (CSeries)CLittle.Series(i);
		LineLittle[i].Clear();
		ZeroMemory(&m_LittleArray[i], sizeof(double)*m_Length);
	}
	LineBase = (CSeries)CBase.Series(0);
	LineBase.Clear();
	ZeroMemory(&m_BaseArray, sizeof(double)*m_Length);
	KillTimer(0);
	for (size_t i = 0; i<m_Length; ++i)
	{
		m_X[i] = i;
	}
	m_count = m_Length;
	SetTimer(0, 20, NULL);
}


void CLineChart::OnTimer(UINT_PTR nIDEvent)
{
	if (0 == nIDEvent)
	{
		++m_count;
		drawMoving();
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CLineChart::drawMoving()
{
	HWND hWnd = ::FindWindow(NULL, _T("数据手套数据读取面板"));      //得到对话框的句柄
	GloveSampleDlg * dlg = (GloveSampleDlg*)GloveSampleDlg::FromHandle(hWnd); //由句柄得到对话框的对象指针
	LeftMoveArray(m_X, m_Length, m_count);

	for (int i = 0; i < 3; i++) {
		LeftMoveArray(m_ThumbArray[i],m_Length, dlg->angle[i]);	//获取大拇指角度
		LeftMoveArray(m_IndexArray[i], m_Length, dlg->angle[i+3]);	//获取食指角度
		if (i < 2) {
			LeftMoveArray(m_MiddleArray[i], m_Length, dlg->angle[i+6]);	//获取中指角度
		}
		LeftMoveArray(m_RingArray[i], m_Length, dlg->angle[i+8]);	//获取无名指角度
		LeftMoveArray(m_LittleArray[i], m_Length, dlg->angle[i + 11]);	//获取小指角度
	}
	LeftMoveArray(m_BaseArray, m_Length, dlg->angle[14]);	//获取掌腕关节角度
	for (int i = 0; i < m_Length; i++)
	{
		for (int j = 0; j < 3; j++) {
			LineThumb[j].AddXY(m_X[i], m_ThumbArray[j][i], NULL, NULL);
			LineIndex[j].AddXY(m_X[i], m_IndexArray[j][i], NULL, NULL);
			if (j < 2) {
				LineMiddle[j].AddXY(m_X[i], m_MiddleArray[j][i], NULL, NULL);
			}
			LineRing[j].AddXY(m_X[i], m_RingArray[j][i], NULL, NULL);
			LineLittle[j].AddXY(m_X[i], m_LittleArray[j][i], NULL, NULL);
		}
		LineBase.AddXY(m_X[i], m_BaseArray[i], NULL, NULL);
	}
}
