// 3DSLoader.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "3DSLoader.h"
#include "MainFrm.h"
#include "3DSLoaderDoc.h"
#include "3DSLoaderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderApp

BEGIN_MESSAGE_MAP(CMy3DSLoaderApp, CWinApp)
	//{{AFX_MSG_MAP(CMy3DSLoaderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnControl)
	ON_COMMAND(ID_OPENGLOVE, OnControl)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_OPENK, &CMy3DSLoaderApp::OnOpenKinect)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderApp construction

CMy3DSLoaderApp::CMy3DSLoaderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMy3DSLoaderApp object

CMy3DSLoaderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderApp initialization

BOOL CMy3DSLoaderApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		//IDR_MAINFRAME,
		IDR_MENU1,  //初始化菜单栏
		RUNTIME_CLASS(CMy3DSLoaderDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CMy3DSLoaderView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

void CMy3DSLoaderApp::OnTest()
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CMy3DSLoaderView *pView = (CMy3DSLoaderView *)pMain->GetActiveView();
	switch (dlg->gesture)
	{
	case 0:
		pView->OnSqueeze();
		break;
	case 1:
		pView->OnClamp();
		break;
	case 3:
		pView->OnReset();
		break;
	case 4:
		pView->OnRip();
		break;
	case 5:
		pView->OnPush();
		break;
	case 6:
		pView->OnSupport();
		break;
	case 7:
		pView->OnFist();
		break;
	case 8:
		pView->OnGrab();
		break;
	default:
		break;
	}
}

void CMy3DSLoaderApp::OnAngle()
{
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CMy3DSLoaderView *pView = (CMy3DSLoaderView *)pMain->GetActiveView();
	pView->OnSetAngle(dlg->angle);
}
void CMy3DSLoaderApp::OnGetAngle()
{
	//获取角度
	CMainFrame *pMain = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	CMy3DSLoaderView *pView = (CMy3DSLoaderView *)pMain->GetActiveView();
	pView->GetAngle();
}
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMy3DSLoaderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

void CMy3DSLoaderApp::OnControl()
{
	dlg = new GloveSampleDlg();
	dlg->Create(IDD_DIALOG_RobotControl);
	dlg->ShowWindow(SW_SHOWNORMAL);

}
/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderApp message handlers

BOOL CMy3DSLoaderApp::OpenFile(CRobotHand& ctl, LPCTSTR lpszPathName)
{
	return true;
	//return ((CMy3DSLoaderView*)((CFrameWnd*)m_pMainWnd)->GetActiveView())->OpenFile(0,lpszPathName);
}


void CMy3DSLoaderApp::OnOpenKinect()
{
	// TODO: 在此添加命令处理程序代码
	kinwin = new KinectWin();
	kinwin->Create(IDD_Kinect);
	kinwin->ShowWindow(SW_SHOWNORMAL);
}
