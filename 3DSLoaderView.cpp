// 3DSLoaderView.cpp : implementation of the CMy3DSLoaderView class
//

#include "stdafx.h"
//#include "MatlabEng.h"

#include "3DSLoader.h"

#include "3DSLoaderDoc.h"
#include "3DSLoaderView.h"
#include "GloableVariable.h"
#include <windows.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderView

IMPLEMENT_DYNCREATE(CMy3DSLoaderView, CView)

BEGIN_MESSAGE_MAP(CMy3DSLoaderView, CView)
	//{{AFX_MSG_MAP(CMy3DSLoaderView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_Reset, &CMy3DSLoaderView::OnReset)
	ON_COMMAND(ID_Thumb, &CMy3DSLoaderView::OnThumb)
	ON_COMMAND(ID_Thumb_Inverse, &CMy3DSLoaderView::OnThumbInverse)
	ON_COMMAND(ID_Index, &CMy3DSLoaderView::OnIndex)
	ON_COMMAND(ID_Index_Inverse, &CMy3DSLoaderView::OnIndexInverse)
	ON_COMMAND(ID_Middle, &CMy3DSLoaderView::OnMiddle)
	ON_COMMAND(ID_Middle_Inverse, &CMy3DSLoaderView::OnMiddleInverse)
	ON_COMMAND(ID_Ring, &CMy3DSLoaderView::OnRing)
	ON_COMMAND(ID_Ring_Inverse, &CMy3DSLoaderView::OnRingInverse)
	ON_COMMAND(ID_Little, &CMy3DSLoaderView::OnLittle)
	ON_COMMAND(ID_Little_Inverse, &CMy3DSLoaderView::OnLittleInverse)
	ON_COMMAND(ID_grab, &CMy3DSLoaderView::OnGrab)
	ON_COMMAND(ID_Fist, &CMy3DSLoaderView::OnFist)
	ON_COMMAND(ID_Push, &CMy3DSLoaderView::OnPush)
	ON_COMMAND(ID_Clamp, &CMy3DSLoaderView::OnClamp)
	ON_COMMAND(ID_Pull, &CMy3DSLoaderView::OnPull)
	ON_COMMAND(ID_Insert, &CMy3DSLoaderView::OnInsert)
	ON_COMMAND(ID_Support, &CMy3DSLoaderView::OnSupport)
	ON_COMMAND(ID_Squeeze, &CMy3DSLoaderView::OnSqueeze)
	ON_COMMAND(ID_Cut, &CMy3DSLoaderView::OnCut)
	ON_COMMAND(ID_Rip, &CMy3DSLoaderView::OnRip)
	ON_COMMAND(ID_Tongs, &CMy3DSLoaderView::OnTongs)
	ON_COMMAND(ID_Test, &CMy3DSLoaderView::OnTest)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderView construction/destruction


CMy3DSLoaderView::CMy3DSLoaderView()
{
	// TODO: add construction code here

}

CMy3DSLoaderView::~CMy3DSLoaderView()
{
}

BOOL CMy3DSLoaderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
////////////////////////////////////////////////////////////////
//设置窗口类型
	cs.style |=WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
////////////////////////////////////////////////////////////////
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderView drawing

void CMy3DSLoaderView::OnDraw(CDC* pDC)
{
	CMy3DSLoaderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
//////////////////////////////////////////////////////////////////
	
	
	//OpenFile("C:\\Users\\robot\\Desktop\\DexterousHand\\Ring\\Ring_1.3DS");
	RenderScene();	//渲染场景
	
	//OpenFile("C:\\Users\\robot\\Desktop\\DexterousHand\\Thumb\\Palm.3DS");
	//::glPushMatrix();
	//::glTranslated(-18, -10, -25);
	//::glRotatef(22, 1.0F, 0.0F, 0.0F);
	//::glRotatef(100, 0.0F, 1.0F, 0.0F);
	//::glRotatef(50, 0.0F, 0.0F, 1.0F);

	//
	//Draw3ds();
	//::glPopMatrix();

	//::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
//////////////////////////////////////////////////////////////////
	
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderView printing

BOOL CMy3DSLoaderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy3DSLoaderView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy3DSLoaderView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderView diagnostics

#ifdef _DEBUG
void CMy3DSLoaderView::AssertValid() const
{
	CView::AssertValid();
}

void CMy3DSLoaderView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy3DSLoaderDoc* CMy3DSLoaderView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy3DSLoaderDoc)));
	return (CMy3DSLoaderDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderView message handlers

int CMy3DSLoaderView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
//////////////////////////////////////////////////////////////////
//初始化OpenGL和设置定时器
	m_pDC = new CClientDC(this);
	//SetTimer(1, 20, NULL);
	InitializeOpenGL(m_pDC);
//////////////////////////////////////////////////////////////////
	Init();	
	return 0;
}

void CMy3DSLoaderView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//删除调色板和渲染上下文、定时器
	::wglMakeCurrent(0,0);
	::wglDeleteContext( m_hRC);
	if (m_hPalette)
	    DeleteObject(m_hPalette);
	if ( m_pDC )
	{
		delete m_pDC;
	}
	//::engClose(engine);//关闭matlab引擎
	
	//KillTimer(1);		
/////////////////////////////////////////////////////////////////
	
}

void CMy3DSLoaderView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
/////////////////////////////////////////////////////////////////
//添加窗口缩放时的图形变换函数
	glViewport(0,0,cx,cy);
/////////////////////////////////////////////////////////////////
	GLdouble aspect_ratio;
	aspect_ratio = (GLdouble)cx/(GLdouble)cy;
	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();
	gluPerspective(40.0F, aspect_ratio, 1.0F, 10000.0F);
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

}

void CMy3DSLoaderView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
/////////////////////////////////////////////////////////////////
//添加定时器响应函数和场景更新函数
	Invalidate(FALSE);	
/////////////////////////////////////////////////////////////////
	
	CView::OnTimer(nIDEvent);
}

/////////////////////////////////////////////////////////////////////
//	                  设置逻辑调色板
//////////////////////////////////////////////////////////////////////
void CMy3DSLoaderView::SetLogicalPalette(void)
{
    struct
    {
        WORD Version;
        WORD NumberOfEntries;
        PALETTEENTRY aEntries[256];
    } logicalPalette = { 0x300, 256 };

	BYTE reds[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE greens[] = {0, 36, 72, 109, 145, 182, 218, 255};
	BYTE blues[] = {0, 85, 170, 255};

    for (int colorNum=0; colorNum<256; ++colorNum)
    {
        logicalPalette.aEntries[colorNum].peRed =
            reds[colorNum & 0x07];
        logicalPalette.aEntries[colorNum].peGreen =
            greens[(colorNum >> 0x03) & 0x07];
        logicalPalette.aEntries[colorNum].peBlue =
            blues[(colorNum >> 0x06) & 0x03];
        logicalPalette.aEntries[colorNum].peFlags = 0;
    }

    m_hPalette = CreatePalette ((LOGPALETTE*)&logicalPalette);
}


//////////////////////////////////////////////////////////
//						初始化openGL场景
//////////////////////////////////////////////////////////
BOOL CMy3DSLoaderView::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();
	//生成绘制描述表
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());
	//置当前绘制描述表
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	return TRUE;
}

//////////////////////////////////////////////////////////
//						设置像素格式
//////////////////////////////////////////////////////////
BOOL CMy3DSLoaderView::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = { 
	    sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小 
	    1,                                // 版本号 
	    PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图 
	    PFD_SUPPORT_OPENGL |              // 支持 OpenGL 
	    PFD_DOUBLEBUFFER,                 // 双缓存模式 
	    PFD_TYPE_RGBA,                    // RGBA 颜色模式 
	    24,                               // 24 位颜色深度 
	    0, 0, 0, 0, 0, 0,                 // 忽略颜色位 
	    0,                                // 没有非透明度缓存 
	    0,                                // 忽略移位位 
	    0,                                // 无累加缓存 
	    0, 0, 0, 0,                       // 忽略累加位 
	    32,                               // 32 位深度缓存     
	    0,                                // 无模板缓存 
	    0,                                // 无辅助缓存 
	    PFD_MAIN_PLANE,                   // 主层 
	    0,                                // 保留 
	    0, 0, 0                           // 忽略层,可见性和损毁掩模 
	}; 	
	int pixelformat;
	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);//选择像素格式
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);	//设置像素格式
	if(pfd.dwFlags & PFD_NEED_PALETTE)
		SetLogicalPalette();	//设置逻辑调色板
	return TRUE;
}



//////////////////////////////////////////////////////////
//						场景绘制与渲染
//////////////////////////////////////////////////////////
BOOL CMy3DSLoaderView::RenderScene() 
{
	::glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	
	::glTranslatef(camPos[0], camPos[1], camPos[2]);
	::glRotatef(camRot[0], 1.0F, 0.0F, 0.0F);
	::glRotatef(camRot[1], 0.0F, 1.0F, 0.0F);
	::glRotatef(camRot[2], 0.0F, 0.0F, 1.0F);
	::glPushMatrix();
	DrawAxis();
	m_RobotHand.drawGL();
	::glPopMatrix();
	::SwapBuffers(m_pDC->GetSafeHdc());		//交互缓冲区
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//			显示指定文本
//////////////////////////////////////////////////////////////////////////
void DrawText(const char* str)
{
	static int isFirstCall = 1;
	static GLuint lists;

	if (isFirstCall)
	{ // 如果是第一次调用，执行初始化
	  // 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);


		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
	{
		glCallList(lists + *str);
	}
}
//////////////////////////////////////////////////////////
//							DrawAxis()
//////////////////////////////////////////////////////////
void CMy3DSLoaderView::DrawAxis()
{//在空间坐标(0,0,0)处为中心绘制坐标轴
	glBegin( GL_LINES);
			//每个坐标轴由6个点构成，前两个点表示直线，中间两个点画轴的左半部分箭头，最后两个点画轴的右半部份箭头
			// x轴--红色
			glColor3f(1.0F, 0.0F, 0.0F);
			glVertex3f(CGloableVariable::MIN_AXIS, 0.0f, 0.0f);
			glVertex3f(CGloableVariable::MAX_AXIS, 0.0f, 0.0f);
			glVertex3f( CGloableVariable::MAX_AXIS -CGloableVariable::ARROW_LENGTH, CGloableVariable::ARROW_LENGTH, 0.0f);
			glVertex3f(CGloableVariable::MAX_AXIS, 0.0f, 0.0f);
			glVertex3f(CGloableVariable::MAX_AXIS - CGloableVariable::ARROW_LENGTH,-CGloableVariable::ARROW_LENGTH,-0.0f);
			glVertex3f(CGloableVariable::MAX_AXIS, 0.0f, 0.0f);
			
			// y轴--绿色
			glColor3f(0.0F, 1.0F, 0.0F);
			glVertex3f( 0.0f,CGloableVariable::MIN_AXIS, 0.0f);
			glVertex3f( 0.0f, CGloableVariable::MAX_AXIS, 0.0f); 
			glVertex3f(-CGloableVariable::ARROW_LENGTH,  CGloableVariable::MAX_AXIS-CGloableVariable::ARROW_LENGTH, 0.0f);
			glVertex3f( 0.0f, CGloableVariable::MAX_AXIS, 0.0f);
			glVertex3f( CGloableVariable::ARROW_LENGTH,  CGloableVariable::MAX_AXIS-CGloableVariable::ARROW_LENGTH, 0.0f);
			glVertex3f( 0.0f, CGloableVariable::MAX_AXIS, 0.0f);

			// z轴--白色
			glColor3f(1.0F, 1.0F, 1.0F);
			glVertex3f( 0.0f, 0.0f,CGloableVariable::MIN_AXIS);
			glVertex3f( 0.0f, 0.0f, CGloableVariable::MAX_AXIS);
			glVertex3f(-CGloableVariable::ARROW_LENGTH, 0.0f,  CGloableVariable::MAX_AXIS-CGloableVariable::ARROW_LENGTH);
			glVertex3f( 0.0f, 0.0f, CGloableVariable::MAX_AXIS);
			glVertex3f( CGloableVariable::ARROW_LENGTH, 0.0f,  CGloableVariable::MAX_AXIS-CGloableVariable::ARROW_LENGTH);
			glVertex3f( 0.0f, 0.0f, CGloableVariable::MAX_AXIS);
	glEnd();
	
}

//////////////////////////////////////////////////////////
//							Draw3ds()
//////////////////////////////////////////////////////////
void CMy3DSLoaderView::Draw3ds(CRobotHand ctl)
{
	if (m_3dsLoaded) 
	{
		ctl.drawGL();
	}
}

//////////////////////////////////////////////////////////////////////////
//			初始化
//////////////////////////////////////////////////////////////////////////
void CMy3DSLoaderView::Init(GLvoid)
{
	/*if (!CGloableVariable::engine->IsInitialized())
	{
		MessageBoxA("matlab引擎初始化失败!");
		CGloableVariable::engine->GetLastErrorMessage();
	}
	CGloableVariable::engine->MinimizeWindow();
	CGloableVariable::engine->Execute("plot([1 2],[3 5],'*r')");*/
	
	m_3dsLoaded  = FALSE;

	camPos[0]	 = 0.0f;
	camPos[1]	 = 0.0f;
	camPos[2]	 = -500.0f;
	camRot[0]	 = 0.0f;
	camRot[1]	 = 0.0f;
	camRot[2]	 = 0.0f;

	mouseprevpoint.x = 0;
	mouseprevpoint.y = 0;
	mouserightdown = FALSE;
	mouseleftdown = FALSE;
	CGloableVariable::Initial();
	
	if (m_RobotHand.getNumObjects() > 0) m_RobotHand.removeAllObjects();
	m_RobotHand.Init();

	for (int i = 0; i < CGloableVariable::N+23; i++) //打开文件
	{
		OpenFile(m_RobotHand, CGloableVariable::files_3ds[i]);
	}

	m_RobotHand.Initial_Length();
	m_RobotHand.Initial_CenterPos();

	::glShadeModel(GL_FLAT);
	
	::glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
	
	::glClearDepth(1.0F);

	::glEnable(GL_DEPTH_TEST);

	::glEnable(GL_CULL_FACE);

	//设置光照
	GLfloat ambientLight[] = { 0.3f, 0.3f, 0.3f, 1.0f};
	GLfloat diffuseLight[] = { 0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat lightPos[]     = {6000.0f,6000.0f,6000.0f, 1.0f};

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
	
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
}

void CMy3DSLoaderView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture( );
	mouserightdown = FALSE;
	SetCamPos(2, (point.y - mouseprevpoint.y) , TRUE, TRUE);
	
	CView::OnRButtonUp(nFlags, point);
}

void CMy3DSLoaderView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture( );
	mouserightdown = TRUE;
	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;
	
	CView::OnRButtonDown(nFlags, point);
}

void CMy3DSLoaderView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	if(mouserightdown)
	{
		SetCamPos(2, -(point.y - mouseprevpoint.y) , TRUE,TRUE);//设置摄像机位置
	}
	else if(mouseleftdown)
	{	
		SetSceneRot(0, (point.y - mouseprevpoint.y) , TRUE,TRUE);
		SetSceneRot(2, (point.x - mouseprevpoint.x) , TRUE,TRUE);
	}
	CView::OnMouseMove(nFlags, point);

	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;	
	CView::OnMouseMove(nFlags, point);
}

void CMy3DSLoaderView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	ReleaseCapture( );
	mouseleftdown = FALSE;
	SetSceneRot(0, (point.y - mouseprevpoint.y) , TRUE, TRUE);
	SetSceneRot(2, (point.x - mouseprevpoint.x) , TRUE, TRUE);
	
	CView::OnLButtonUp(nFlags, point);
}

void CMy3DSLoaderView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	SetCapture( );
	mouseleftdown = TRUE;
	mouseprevpoint.x = point.x;
	mouseprevpoint.y = point.y;	
	CView::OnLButtonDown(nFlags, point);
}
//////////////////////////////////////////////////////////////////////////
//			设置摄像机位置
//////////////////////////////////////////////////////////////////////////
void CMy3DSLoaderView::SetCamPos(int axis, int value, BOOL increment, BOOL apply)
{//设置摄像机位置
	if(increment)
	{
		camPos[axis] += (float)value*camPos[axis]/100;
	}
	else
	{
		camPos[axis] = (float)value/2;
	}

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	RenderScene();

}
//////////////////////////////////////////////////////////////////////////
//			设置摄像机角度
//////////////////////////////////////////////////////////////////////////
void CMy3DSLoaderView::SetSceneRot(int axis, int value, BOOL increment, BOOL apply)
{
	if (increment)
	{
		camRot[axis] += (camRot[axis] >= 360) ? (-360 + value / 2) : value / 2;
	}
	else
	{
		camRot[axis] = (camRot[axis] >= 360) ? (-360 + value / 2) : value / 2;
	}		
	RenderScene();
}
//////////////////////////////////////////////////////////////////////////
//			打开3ds文件
//////////////////////////////////////////////////////////////////////////
BOOL CMy3DSLoaderView::OpenFile(CRobotHand& ctl,LPCTSTR lpszPathName)
{
	char* file = new char[strlen(lpszPathName)];
	strcpy(file, lpszPathName);

	C3dsReader Loader;
	BOOL result;
	//if( m_RobotHand.getNumObjects() > 0 ) m_RobotHand.removeAllObjects();

	result = Loader.Reader(file, &ctl);
	if (result)
	{
		m_3dsLoaded = TRUE;
		ctl.doAfterMath();

	}

	return result;
}

void CMy3DSLoaderView::reset()
{
	//角度置0，但不显示
	for (int i = 0; i < CGloableVariable::N; i++)
	{
		m_RobotHand.objects[i]->currentPos.x = CGloableVariable::defaultPos[i][0] - 150;
		m_RobotHand.objects[i]->currentPos.y = CGloableVariable::defaultPos[i][1];
		m_RobotHand.objects[i]->currentPos.z = CGloableVariable::defaultPos[i][2];
	}
	int j = 0;
	for (int i = CGloableVariable::N; i < CGloableVariable::N + 21; i++)//右手部分
	{
		m_RobotHand.objects[i]->currentPos.x = CGloableVariable::defaultPos_r[j][0] - 150;
		m_RobotHand.objects[i]->currentPos.y = CGloableVariable::defaultPos_r[j][1];
		m_RobotHand.objects[i]->currentPos.z = CGloableVariable::defaultPos_r[j][2];
		j++;

	}
	//右手基部
	for (int i = CGloableVariable::N + 21, j = 0; i < CGloableVariable::N + 23; i++, j++)//右手部分
	{
		m_RobotHand.objects[i]->currentPos.x = CGloableVariable::defaultPos_b[j][0] - 150;
		m_RobotHand.objects[i]->currentPos.y = CGloableVariable::defaultPos_b[j][1];
		m_RobotHand.objects[i]->currentPos.z = CGloableVariable::defaultPos_b[j][2];

	}

	for (int i = 0; i < CGloableVariable::N; i++)
	{
		if (i == 1 || i == 2 || i == 3 || i == 4)
		{
			m_RobotHand.objects[i]->sceneRot[2] = m_RobotHand.ConvertAngleToRadian(60);
			m_RobotHand.objects[1]->angle = m_RobotHand.ConvertAngleToRadian(60);
		}
		else
			m_RobotHand.objects[i]->sceneRot[2] = 0;
		m_RobotHand.objects[i]->sceneRot[1] = 0;

		m_RobotHand.objects[i]->sceneRot[0] = 0;
		m_RobotHand.objects[i]->angle = 0;
	}

	for (int i = CGloableVariable::N; i < CGloableVariable::N + 23; i++)
	{
		if (i == CGloableVariable::N + 1 || i == CGloableVariable::N + 2 || i == CGloableVariable::N + 3 || i == CGloableVariable::N + 4)
		{
			m_RobotHand.objects[i]->sceneRot[2] = m_RobotHand.ConvertAngleToRadian(60);
			m_RobotHand.objects[CGloableVariable::N + 1]->angle = m_RobotHand.ConvertAngleToRadian(60);
		}
		else
			m_RobotHand.objects[i]->sceneRot[2] = 0;
		m_RobotHand.objects[i]->sceneRot[1] = 0;

		m_RobotHand.objects[i]->sceneRot[0] = 0;
		m_RobotHand.objects[i]->angle = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//			测试
//////////////////////////////////////////////////////////////////////////
/*抓动作*/
void CMy3DSLoaderView::OnGrab(){
	reset();
	ofile.open("./angle.txt", std::ios::ate | std::ios::out);     //作为输出文件打开
	/*抓取*/
	ofile << "抓" << endl;
	//中指
	int choice[5] = { 0,0,1,0,0 };
	float* res = m_RobotHand.CalculateThetaByCoordinate(tVector(0.669, 125.957, -40.0), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	ofile << "中指:" << angle0 <<" "<< angle1 <<" "<< angle2 <<" "<< angle3 << endl;

	m_RobotHand.Middle1_Rotate(angle0);
	m_RobotHand.Middle2_Rotate(angle1);
	m_RobotHand.Middle3_Rotate(angle1 + angle2);
	m_RobotHand.Middle4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Middle1_Rotate_r(angle0); //右手部分
	m_RobotHand.Middle2_Rotate_r(angle1);
	m_RobotHand.Middle3_Rotate_r(angle1 + angle2);
	m_RobotHand.Middle4_Rotate_r(angle1 + angle2 + angle3);

	//无名指
	choice[3] = 1; choice[2] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-23.204, 125.957, -40.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	ofile << "无名指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;

	m_RobotHand.Ring1_Rotate(angle0);
	m_RobotHand.Ring2_Rotate(angle1);
	m_RobotHand.Ring3_Rotate(angle1 + angle2);
	m_RobotHand.Ring4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Ring1_Rotate_r(angle0); //右手部分
	m_RobotHand.Ring2_Rotate_r(angle1);
	m_RobotHand.Ring3_Rotate_r(angle1 + angle2);
	m_RobotHand.Ring4_Rotate_r(angle1 + angle2 + angle3);

	//食指
	choice[1] = 1; choice[3] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(20.941, 125.957, -40.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	ofile << "食指:" << angle0 << " " << angle1 << " " << angle2 << " " << angle3 << endl;

	m_RobotHand.Index1_Rotate(angle0);
	m_RobotHand.Index2_Rotate(angle1);
	m_RobotHand.Index3_Rotate(angle1 + angle2);
	m_RobotHand.Index4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Index1_Rotate_r(angle0);
	m_RobotHand.Index2_Rotate_r(angle1);
	m_RobotHand.Index3_Rotate_r(angle1 + angle2);
	m_RobotHand.Index4_Rotate_r(angle1 + angle2 + angle3);
	
	//小指
	choice[4] = 1; choice[1] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-43.541, 125.957, -40.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	ofile << "小指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;

	m_RobotHand.Little1_Rotate(angle0);
	m_RobotHand.Little2_Rotate(angle1);
	m_RobotHand.Little3_Rotate(angle1 + angle2);
	m_RobotHand.Little4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Little1_Rotate_r(angle0);
	m_RobotHand.Little2_Rotate_r(angle1);
	m_RobotHand.Little3_Rotate_r(angle1 + angle2);
	m_RobotHand.Little4_Rotate_r(angle1 + angle2 + angle3);

	//大拇指正向控制
	ofile << "大拇指:" << 5 << " " << 10 << " " << 50 << " " << 30 << endl;

	m_RobotHand.Thumb1_Rotate(5);
	m_RobotHand.Thumb2_Rotate(10);
	m_RobotHand.Thumb3_Rotate(60);
	m_RobotHand.Thumb4_Rotate(90);

	m_RobotHand.Thumb1_Rotate_r(5);
	m_RobotHand.Thumb2_Rotate_r(10);
	m_RobotHand.Thumb3_Rotate_r(60);
	m_RobotHand.Thumb4_Rotate_r(90);

	m_RobotHand.Thumb_Rotate_b(40);
	m_RobotHand.Thumb_Rotate_br(40);

	m_RobotHand.drawGL();
	RenderScene();
	ofile.close();
}
/*推动作*/
void CMy3DSLoaderView::OnPush() {
	reset();
	//大拇指正向控制
	m_RobotHand.Thumb1_Rotate(-20);
	m_RobotHand.Thumb2_Rotate(-20);
	m_RobotHand.Thumb3_Rotate(20);
	m_RobotHand.Thumb4_Rotate(25);

	m_RobotHand.Thumb1_Rotate_r(-20);
	m_RobotHand.Thumb2_Rotate_r(-20);
	m_RobotHand.Thumb3_Rotate_r(20);
	m_RobotHand.Thumb4_Rotate_r(25);
	//食指
	m_RobotHand.Index1_Rotate(-5);
	m_RobotHand.Index2_Rotate(-15);
	m_RobotHand.Index3_Rotate(15);
	m_RobotHand.Index4_Rotate(15);

	m_RobotHand.Index1_Rotate_r(-5);
	m_RobotHand.Index2_Rotate_r(-15);
	m_RobotHand.Index3_Rotate_r(15);
	m_RobotHand.Index4_Rotate_r(15);
	//中指
	m_RobotHand.Middle1_Rotate(0);
	m_RobotHand.Middle2_Rotate(-15);
	m_RobotHand.Middle3_Rotate(15);
	m_RobotHand.Middle4_Rotate(15);

	m_RobotHand.Middle1_Rotate_r(0);
	m_RobotHand.Middle2_Rotate_r(-15);
	m_RobotHand.Middle3_Rotate_r(15);
	m_RobotHand.Middle4_Rotate_r(15);
	
	//无名指
	m_RobotHand.Ring1_Rotate(5);
	m_RobotHand.Ring2_Rotate(-15);
	m_RobotHand.Ring3_Rotate(15);
	m_RobotHand.Ring4_Rotate(15);

	m_RobotHand.Ring1_Rotate_r(5);
	m_RobotHand.Ring2_Rotate_r(-15);
	m_RobotHand.Ring3_Rotate_r(15);
	m_RobotHand.Ring4_Rotate_r(15);
	
	//小指
	m_RobotHand.Little1_Rotate(5);
	m_RobotHand.Little2_Rotate(-15);
	m_RobotHand.Little3_Rotate(15);
	m_RobotHand.Little4_Rotate(15);

	m_RobotHand.Little1_Rotate_r(5);
	m_RobotHand.Little2_Rotate_r(-15);
	m_RobotHand.Little3_Rotate_r(15);
	m_RobotHand.Little4_Rotate_r(15);

	m_RobotHand.drawGL();
	RenderScene();
}
/*夹动作*/
void CMy3DSLoaderView::OnClamp() {
	reset();
	//ofile.open("./angle.txt", ios::out | ios::app);     //作为输出文件打开
	//ofile << "夹" << endl;
	/*大拇指运动*/
	//ofile << "大拇指:" << 5 << " " << 0 << " " << 50 << " " << 0 << endl;

	m_RobotHand.Thumb1_Rotate(5);
	m_RobotHand.Thumb3_Rotate(50);
	m_RobotHand.Thumb4_Rotate(50);

	m_RobotHand.Thumb1_Rotate_r(5);
	m_RobotHand.Thumb3_Rotate_r(50);
	m_RobotHand.Thumb4_Rotate_r(50);

	m_RobotHand.Thumb_Rotate_b(60);
	m_RobotHand.Thumb_Rotate_br(60);

	/*抓取*/
	//中指
	int choice[5] = { 0,0,1,0,0 };
	float* res = m_RobotHand.CalculateThetaByCoordinate(tVector(14.669, 180.957, -40.0), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	//ofile << "中指:" << angle0 << " " << angle1 << " " << angle2 << " " <<  angle3 << endl;

	m_RobotHand.Middle1_Rotate(angle0);
	m_RobotHand.Middle2_Rotate(angle1);
	m_RobotHand.Middle3_Rotate(angle1 + angle2);
	m_RobotHand.Middle4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Middle1_Rotate_r(angle0); //右手部分
	m_RobotHand.Middle2_Rotate_r(angle1);
	m_RobotHand.Middle3_Rotate_r(angle1 + angle2);
	m_RobotHand.Middle4_Rotate_r(angle1 + angle2 + angle3);

	//无名指
	choice[3] = 1; choice[2] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-9.204, 170.957, -40.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	//ofile << "无名指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;

	m_RobotHand.Ring1_Rotate(angle0);
	m_RobotHand.Ring2_Rotate(angle1);
	m_RobotHand.Ring3_Rotate(angle1 + angle2);
	m_RobotHand.Ring4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Ring1_Rotate_r(angle0); //右手部分
	m_RobotHand.Ring2_Rotate_r(angle1);
	m_RobotHand.Ring3_Rotate_r(angle1 + angle2);
	m_RobotHand.Ring4_Rotate_r(angle1 + angle2 + angle3);

	//食指
	choice[1] = 1; choice[3] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(34.941, 125.957, -40.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	//ofile << "食指:" << angle0 << " " << angle1 << " " << angle2 << " " <<  angle3 << endl;

	m_RobotHand.Index1_Rotate(angle0);
	m_RobotHand.Index2_Rotate(angle1);
	m_RobotHand.Index3_Rotate(angle1 + angle2);
	m_RobotHand.Index4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Index1_Rotate_r(angle0);
	m_RobotHand.Index2_Rotate_r(angle1);
	m_RobotHand.Index3_Rotate_r(angle1 + angle2);
	m_RobotHand.Index4_Rotate_r(angle1 + angle2 + angle3);

	//小指
	choice[4] = 1; choice[1] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-29.541, 130.957, -40.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	//	PublicFuntoinHelper::ShowMessage(str);
	//ofile << "小指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;

	m_RobotHand.Little1_Rotate(angle0);
	m_RobotHand.Little2_Rotate(angle1);
	m_RobotHand.Little3_Rotate(angle1 + angle2);
	m_RobotHand.Little4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Little1_Rotate_r(angle0);
	m_RobotHand.Little2_Rotate_r(angle1);
	m_RobotHand.Little3_Rotate_r(angle1 + angle2);
	m_RobotHand.Little4_Rotate_r(angle1 + angle2 + angle3);

	m_RobotHand.drawGL();
	RenderScene();
	//ofile.close();
}
/*握*/
void CMy3DSLoaderView::OnFist() {
	reset();
	ofile.open("./angle.txt", ios::out | ios::app);     //作为输出文件打开
	ofile << "握" << endl;
	//中指
	int choice[5] = { 0,0,1,0,0 };
	float* res = m_RobotHand.CalculateThetaByCoordinate(tVector(0.669, 30.0, -40.0), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	
	ofile << "中指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;

	m_RobotHand.Middle1_Rotate(angle0);
	m_RobotHand.Middle2_Rotate(angle1);
	m_RobotHand.Middle3_Rotate(angle1 + angle2);
	m_RobotHand.Middle4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Middle1_Rotate_r(angle0); //右手部分
	m_RobotHand.Middle2_Rotate_r(angle1);
	m_RobotHand.Middle3_Rotate_r(angle1 + angle2);
	m_RobotHand.Middle4_Rotate_r(angle1 + angle2 + angle3);

	//无名指
	choice[3] = 1; choice[2] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-23.204, 30.0, -20.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	
	ofile << "无名指:" << angle0 << " " << angle1 << " " << angle2 << " " <<  angle3 << endl;

	m_RobotHand.Ring1_Rotate(angle0);
	m_RobotHand.Ring2_Rotate(angle1);
	m_RobotHand.Ring3_Rotate(angle1 + angle2);
	m_RobotHand.Ring4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Ring1_Rotate_r(angle0); //右手部分
	m_RobotHand.Ring2_Rotate_r(angle1);
	m_RobotHand.Ring3_Rotate_r(angle1 + angle2);
	m_RobotHand.Ring4_Rotate_r(angle1 + angle2 + angle3);

	//食指
	choice[1] = 1; choice[3] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(20.941, 30.0, -20.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);

	ofile << "食指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;

	m_RobotHand.Index1_Rotate(angle0);
	m_RobotHand.Index2_Rotate(angle1);
	m_RobotHand.Index3_Rotate(angle1 + angle2);
	m_RobotHand.Index4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Index1_Rotate_r(angle0);
	m_RobotHand.Index2_Rotate_r(angle1);
	m_RobotHand.Index3_Rotate_r(angle1 + angle2);
	m_RobotHand.Index4_Rotate_r(angle1 + angle2 + angle3);
	//小指
	choice[4] = 1; choice[1] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-43.541, 30.0, -30.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);

	ofile << "小指:" << angle0 << " " << angle1 << " " << angle2 << " " <<  angle3 << endl;
	
	m_RobotHand.Little1_Rotate(angle0);
	m_RobotHand.Little2_Rotate(angle1);
	m_RobotHand.Little3_Rotate(angle1 + angle2);
	m_RobotHand.Little4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Little1_Rotate_r(angle0);
	m_RobotHand.Little2_Rotate_r(angle1);
	m_RobotHand.Little3_Rotate_r(angle1 + angle2);
	m_RobotHand.Little4_Rotate_r(angle1 + angle2 + angle3);

	//大拇指
	choice[0] = 1; choice[4] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(46.186, 30.0, -20.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);

	ofile << "大拇指:" << angle0 << " " << angle1 << " " <<  angle2 << " " << angle3 << endl;
	
	m_RobotHand.Thumb1_Rotate(angle0);
	m_RobotHand.Thumb2_Rotate(angle1);
	m_RobotHand.Thumb3_Rotate(angle1 + angle2);
	m_RobotHand.Thumb4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Thumb1_Rotate_r(angle0);
	m_RobotHand.Thumb2_Rotate_r(angle1);
	m_RobotHand.Thumb3_Rotate_r(angle1 + angle2);
	m_RobotHand.Thumb4_Rotate_r(angle1 + angle2 + angle3);

	m_RobotHand.Thumb_Rotate_b(30);
	m_RobotHand.Thumb_Rotate_br(30);
	m_RobotHand.drawGL();
	RenderScene();
	ofile.close();
}
/*拉*/
void CMy3DSLoaderView::OnPull() {
	reset();
	//食指
	m_RobotHand.Index3_Rotate(60);
	m_RobotHand.Index4_Rotate(90);

	m_RobotHand.Index3_Rotate_r(60);
	m_RobotHand.Index4_Rotate_r(90);

	//中指
	m_RobotHand.Middle3_Rotate(60);
	m_RobotHand.Middle4_Rotate(90);
	m_RobotHand.Middle3_Rotate_r(60);
	m_RobotHand.Middle4_Rotate_r(90);

	//无名指
	m_RobotHand.Ring3_Rotate(60);
	m_RobotHand.Ring4_Rotate(90);
	m_RobotHand.Ring3_Rotate_r(60);
	m_RobotHand.Ring4_Rotate_r(90);

	//小指
	m_RobotHand.Little3_Rotate(60);
	m_RobotHand.Little4_Rotate(90);
	m_RobotHand.Little3_Rotate_r(60);
	m_RobotHand.Little4_Rotate_r(90);

	//大拇指正向控制
	m_RobotHand.Thumb3_Rotate(20);
	m_RobotHand.Thumb4_Rotate(25);
	m_RobotHand.Thumb3_Rotate_r(20);
	m_RobotHand.Thumb4_Rotate_r(25);

	m_RobotHand.Thumb_Rotate_b(70);
	m_RobotHand.Thumb_Rotate_br(70);
	m_RobotHand.drawGL();
	RenderScene();
}
/*插*/
void CMy3DSLoaderView::OnInsert() {
	reset();
	ofile.open("./angle.txt", ios::out | ios::app);     //作为输出文件打开
	ofile << "插" << endl;
	/*大拇指运动*/
	m_RobotHand.Thumb1_Rotate(5);
	m_RobotHand.Thumb3_Rotate(50);
	m_RobotHand.Thumb4_Rotate(50);
	m_RobotHand.Thumb_Rotate_b(60);
	ofile << "左手大拇指:" << 5 << " " << 0 << " " << 50 << " " << 0 << endl;
	/*左手抓取*/
	//中指
	int choice[5] = { 0,0,1,0,0 };
	float* res = m_RobotHand.CalculateThetaByCoordinate(tVector(14.669, 150.957, -40.0), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	ofile << "左手中指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Middle1_Rotate(angle0);
	m_RobotHand.Middle2_Rotate(angle1);
	m_RobotHand.Middle3_Rotate(angle1 + angle2);
	m_RobotHand.Middle4_Rotate(angle1 + angle2 + angle3);

	//无名指
	choice[3] = 1; choice[2] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-9.204, 150.957, -40.0), choice);
	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "左手无名指:" << angle0 << " " << angle1 << " " << angle2 << " " <<  angle3 << endl;
	m_RobotHand.Ring1_Rotate(angle0);
	m_RobotHand.Ring2_Rotate(angle1);
	m_RobotHand.Ring3_Rotate(angle1 + angle2);
	m_RobotHand.Ring4_Rotate(angle1 + angle2 + angle3);

	//食指
	choice[1] = 1; choice[3] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(34.941, 125.957, -40.0), choice);
	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "左手食指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Index1_Rotate(angle0);
	m_RobotHand.Index2_Rotate(angle1);
	m_RobotHand.Index3_Rotate(angle1 + angle2);
	m_RobotHand.Index4_Rotate(angle1 + angle2 + angle3);

	//小指
	choice[4] = 1; choice[1] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-29.541, 130.957, -40.0), choice);
	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "左手小指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Little1_Rotate(angle0);
	m_RobotHand.Little2_Rotate(angle1);
	m_RobotHand.Little3_Rotate(angle1 + angle2);
	m_RobotHand.Little4_Rotate(angle1 + angle2 + angle3);

	//大拇指正向控制
	m_RobotHand.Thumb2_Rotate_r(60);
	m_RobotHand.Thumb3_Rotate_r(120);
	m_RobotHand.Thumb4_Rotate_r(130);
	ofile << "右手大拇指:" << 0 << " " << 60 << " " << 60 << " " << 10 << endl;
	m_RobotHand.Thumb_Rotate_br(50);
	//食指
	m_RobotHand.Index2_Rotate_r(60);
	m_RobotHand.Index3_Rotate_r(120);
	m_RobotHand.Index4_Rotate_r(160);
	ofile << "右手食指:" << 0 << " " << 60 << " " << 60 << " " << 40 << endl;
	//中指
	m_RobotHand.Middle2_Rotate_r(60);
	m_RobotHand.Middle3_Rotate_r(120);
	m_RobotHand.Middle4_Rotate_r(160);
	ofile << "右手中指:" << 0 << " " << 60 << " " << 60 << " " << 40 << endl;
	//无名指
	m_RobotHand.Ring2_Rotate_r(60);
	m_RobotHand.Ring3_Rotate_r(120);
	m_RobotHand.Ring4_Rotate_r(160);
	ofile << "右手无名指:" << 0 << " " << 60 << " " << 60 << " " << 40 << endl;
	//小指
	m_RobotHand.Little2_Rotate_r(60);
	m_RobotHand.Little3_Rotate_r(120);
	m_RobotHand.Little4_Rotate_r(160);
	ofile << "右手小指:" << 0 << " " << 60 << " " << 60 << " " << 40 << endl;
	m_RobotHand.drawGL();
	RenderScene();
	ofile.close();
}
/*托*/
void CMy3DSLoaderView::OnSupport() {
	reset();
	//食指
	m_RobotHand.Index3_Rotate(30);
	m_RobotHand.Index4_Rotate(60);

	m_RobotHand.Index3_Rotate_r(30);
	m_RobotHand.Index4_Rotate_r(60);

	//中指
	m_RobotHand.Middle3_Rotate(30);
	m_RobotHand.Middle4_Rotate(60);
	m_RobotHand.Middle3_Rotate_r(30);
	m_RobotHand.Middle4_Rotate_r(60);

	//无名指
	m_RobotHand.Ring3_Rotate(30);
	m_RobotHand.Ring4_Rotate(60);
	m_RobotHand.Ring3_Rotate_r(30);
	m_RobotHand.Ring4_Rotate_r(60);

	//小指
	m_RobotHand.Little3_Rotate(30);
	m_RobotHand.Little4_Rotate(60);
	m_RobotHand.Little3_Rotate_r(30);
	m_RobotHand.Little4_Rotate_r(60);

	//大拇指正向控制
	m_RobotHand.Thumb1_Rotate(30);
	m_RobotHand.Thumb3_Rotate(30);
	m_RobotHand.Thumb4_Rotate(30);
	m_RobotHand.Thumb1_Rotate_r(30);
	m_RobotHand.Thumb3_Rotate_r(30);
	m_RobotHand.Thumb4_Rotate_r(30);

	m_RobotHand.Thumb_Rotate_b(30);
	m_RobotHand.Thumb_Rotate_br(30);
	m_RobotHand.drawGL();
	RenderScene();
}
/*挤*/
void CMy3DSLoaderView::OnSqueeze() {
	reset();
	//大拇指正向控制
	m_RobotHand.Thumb1_Rotate(-10);
	m_RobotHand.Thumb2_Rotate(30);
	m_RobotHand.Thumb3_Rotate(60);
	m_RobotHand.Thumb4_Rotate(130);

	m_RobotHand.Thumb_Rotate_b(30);
	//食指
	m_RobotHand.Index1_Rotate(-10);
	m_RobotHand.Index2_Rotate(60);
	m_RobotHand.Index3_Rotate(120);
	m_RobotHand.Index4_Rotate(200);
	//中指
	m_RobotHand.Middle2_Rotate(60);
	m_RobotHand.Middle3_Rotate(120);
	m_RobotHand.Middle4_Rotate(200);

	//无名指
	m_RobotHand.Ring1_Rotate(10);
	m_RobotHand.Ring2_Rotate(60);
	m_RobotHand.Ring3_Rotate(120);
	m_RobotHand.Ring4_Rotate(200);

	//小指
	m_RobotHand.Little1_Rotate(10);
	m_RobotHand.Little2_Rotate(60);
	m_RobotHand.Little3_Rotate(120);
	m_RobotHand.Little4_Rotate(200);

	//右手大拇指正向控制
	m_RobotHand.Thumb1_Rotate_r(-10);
	m_RobotHand.Thumb2_Rotate_r(30);
	m_RobotHand.Thumb3_Rotate_r(60);
	m_RobotHand.Thumb4_Rotate_r(130);

	m_RobotHand.Thumb_Rotate_br(30);
	//食指
	m_RobotHand.Index1_Rotate_r(-10);
	m_RobotHand.Index2_Rotate_r(60);
	m_RobotHand.Index3_Rotate_r(120);
	m_RobotHand.Index4_Rotate_r(200);
	//中指
	m_RobotHand.Middle2_Rotate_r(60);
	m_RobotHand.Middle3_Rotate_r(120);
	m_RobotHand.Middle4_Rotate_r(200);

	//无名指
	m_RobotHand.Ring1_Rotate_r(10);
	m_RobotHand.Ring2_Rotate_r(60);
	m_RobotHand.Ring3_Rotate_r(120);
	m_RobotHand.Ring4_Rotate_r(200);

	//小指
	m_RobotHand.Little1_Rotate_r(10);
	m_RobotHand.Little2_Rotate_r(60);
	m_RobotHand.Little3_Rotate_r(120);
	m_RobotHand.Little4_Rotate_r(200);
	m_RobotHand.drawGL();
	RenderScene();
}
/*剪*/
void CMy3DSLoaderView::OnCut() 
{
	reset();
	//大拇指正向控制
	m_RobotHand.Thumb1_Rotate(-10);
	m_RobotHand.Thumb2_Rotate(30);
	m_RobotHand.Thumb3_Rotate(90);
	m_RobotHand.Thumb4_Rotate(90);

	m_RobotHand.Thumb_Rotate_b(100);
	
	//食指
	m_RobotHand.Index1_Rotate(-2);
	m_RobotHand.Index2_Rotate(-5);
	m_RobotHand.Index3_Rotate(10);
	m_RobotHand.Index4_Rotate(10);
	//中指
	m_RobotHand.Middle2_Rotate(-5);
	m_RobotHand.Middle3_Rotate(10);
	m_RobotHand.Middle4_Rotate(10);

	//无名指
	m_RobotHand.Ring1_Rotate(2);
	m_RobotHand.Ring2_Rotate(-5);
	m_RobotHand.Ring3_Rotate(10);
	m_RobotHand.Ring4_Rotate(10);

	//小指
	m_RobotHand.Little1_Rotate(4);
	m_RobotHand.Little2_Rotate(-5);
	m_RobotHand.Little3_Rotate(10);
	m_RobotHand.Little4_Rotate(10);

	/*右手拿剪刀*/
	//中指
	m_RobotHand.Middle2_Rotate_r(10);
	m_RobotHand.Middle3_Rotate_r(80);
	m_RobotHand.Middle4_Rotate_r(160);

	//无名指
	m_RobotHand.Ring2_Rotate_r(10);
	m_RobotHand.Ring3_Rotate_r(80);
	m_RobotHand.Ring4_Rotate_r(160);

	//小指
	m_RobotHand.Little2_Rotate_r(10);
	m_RobotHand.Little3_Rotate_r(80);
	m_RobotHand.Little4_Rotate_r(160);

	//大拇指正向控制
	m_RobotHand.Thumb1_Rotate_r(-10);
	m_RobotHand.Thumb3_Rotate_r(60);
	m_RobotHand.Thumb4_Rotate_r(80);

	m_RobotHand.Thumb_Rotate_br(60);
	// 食指
	m_RobotHand.Index3_Rotate_r(20);
	m_RobotHand.Index4_Rotate_r(30);

	m_RobotHand.drawGL();
	RenderScene();
}
/*撕*/
void CMy3DSLoaderView::OnRip()
{
	reset();
	ofile.open("./angle.txt", ios::out | ios::app);     //作为输出文件打开
	ofile << "撕" << endl;
	//中指
	int choice[5] = { 0,0,1,0,0 };
	float* res = m_RobotHand.CalculateThetaByCoordinate(tVector(0.669, 30, -40.0), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	ofile << "中指:" << angle0 << " " << angle1 << " " << angle2 << " " <<  angle3 << endl;
	m_RobotHand.Middle1_Rotate(angle0);
	m_RobotHand.Middle2_Rotate(angle1);
	m_RobotHand.Middle3_Rotate(angle1 + angle2);
	m_RobotHand.Middle4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Middle1_Rotate_r(angle0);
	m_RobotHand.Middle2_Rotate_r(angle1);
	m_RobotHand.Middle3_Rotate_r(angle1 + angle2);
	m_RobotHand.Middle4_Rotate_r(angle1 + angle2 + angle3);

	//无名指
	choice[3] = 1; choice[2] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-23.204, 30, -20.0), choice);
	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "无名指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Ring1_Rotate(angle0); //右手部分
	m_RobotHand.Ring2_Rotate(angle1);
	m_RobotHand.Ring3_Rotate(angle1 + angle2);
	m_RobotHand.Ring4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Ring1_Rotate_r(angle0); //右手部分
	m_RobotHand.Ring2_Rotate_r(angle1);
	m_RobotHand.Ring3_Rotate_r(angle1 + angle2);
	m_RobotHand.Ring4_Rotate_r(angle1 + angle2 + angle3);

	//小指
	choice[4] = 1; choice[3] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-43.541, 30, -20.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "小指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Little1_Rotate(angle0);
	m_RobotHand.Little2_Rotate(angle1);
	m_RobotHand.Little3_Rotate(angle1 + angle2);
	m_RobotHand.Little4_Rotate(angle1 + angle2 + angle3);

	m_RobotHand.Little1_Rotate_r(angle0);
	m_RobotHand.Little2_Rotate_r(angle1);
	m_RobotHand.Little3_Rotate_r(angle1 + angle2);
	m_RobotHand.Little4_Rotate_r(angle1 + angle2 + angle3);


	//大拇指
	m_RobotHand.Thumb1_Rotate(-10);
	m_RobotHand.Thumb3_Rotate(30);
	m_RobotHand.Thumb4_Rotate(40);
	ofile << "大拇指:" << -10 << " " << 0 << " " << 30 << " " << 10<<endl;
	m_RobotHand.Thumb1_Rotate_r(-10);
	m_RobotHand.Thumb3_Rotate_r(30);
	m_RobotHand.Thumb4_Rotate_r(40);

	m_RobotHand.Thumb_Rotate_b(60);
	m_RobotHand.Thumb_Rotate_br(60);
	
	//食指
	m_RobotHand.Index1_Rotate(-12);
	m_RobotHand.Index2_Rotate(-10);
	m_RobotHand.Index3_Rotate(80);
	m_RobotHand.Index4_Rotate(100);
	ofile << "食指:" << -12 << " " << -10 << " " << 90 << " " << 10<<endl;
	m_RobotHand.Index1_Rotate_r(-12);
	m_RobotHand.Index2_Rotate_r(-10);
	m_RobotHand.Index3_Rotate_r(80);
	m_RobotHand.Index4_Rotate_r(100);

	m_RobotHand.drawGL();
	RenderScene();
	ofile.close();
}
/*钳*/
void CMy3DSLoaderView::OnTongs() 
{
	reset();
	ofile.open("./angle.txt", ios::out | ios::app);     //作为输出文件打开
	ofile << "钳" << endl;
	//中指
	int choice[5] = { 0,0,1,0,0 };
	float* res = m_RobotHand.CalculateThetaByCoordinate(tVector(0.669, 30, -40.0), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	ofile << "左手中指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Middle1_Rotate(angle0);
	m_RobotHand.Middle2_Rotate(angle1);
	m_RobotHand.Middle3_Rotate(angle1 + angle2);
	m_RobotHand.Middle4_Rotate(angle1 + angle2 + angle3);

	//无名指
	choice[3] = 1; choice[2] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-23.204, 30, -20.0), choice);
	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "左手无名指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Ring1_Rotate(angle0); 
	m_RobotHand.Ring2_Rotate(angle1);
	m_RobotHand.Ring3_Rotate(angle1 + angle2);
	m_RobotHand.Ring4_Rotate(angle1 + angle2 + angle3);

	//小指
	choice[4] = 1; choice[3] = 0;
	res = m_RobotHand.CalculateThetaByCoordinate(tVector(-43.541, 30, -20.0), choice);

	angle0 = -(*res);
	angle1 = -*(res + 1);
	angle2 = *(res + 2);
	angle3 = *(res + 3);
	ofile << "左手小指:" << angle0 << " " << angle1 << " " <<  angle2 << " " <<  angle3 << endl;
	m_RobotHand.Little1_Rotate(angle0);
	m_RobotHand.Little2_Rotate(angle1);
	m_RobotHand.Little3_Rotate(angle1 + angle2);
	m_RobotHand.Little4_Rotate(angle1 + angle2 + angle3);

	//大拇指
	m_RobotHand.Thumb1_Rotate(-10);
	m_RobotHand.Thumb3_Rotate(30);
	m_RobotHand.Thumb4_Rotate(40);
	m_RobotHand.Thumb_Rotate_b(60);
	ofile << "左手大拇指:" << -10 << " " << 0 << " " << 30 << " " << 10 << endl;

	//食指
	m_RobotHand.Index1_Rotate(-12);
	m_RobotHand.Index2_Rotate(-10);
	m_RobotHand.Index3_Rotate(80);
	m_RobotHand.Index4_Rotate(100);
	ofile << "左手食指:" << -12 << " " << -10 << " " << 90 << " " << 10 << endl;
	/*右手拿钳*/
	//中指
	m_RobotHand.Middle2_Rotate_r(10);
	m_RobotHand.Middle3_Rotate_r(80);
	m_RobotHand.Middle4_Rotate_r(160);
	ofile << "右手中指:" << 0 << " " << 10 << " " << 70 << " " << 90 << endl;
	//无名指
	m_RobotHand.Ring2_Rotate_r(10);
	m_RobotHand.Ring3_Rotate_r(80);
	m_RobotHand.Ring4_Rotate_r(160);
	ofile << "右手无名指:" << 0 << " " << 10 << " " << 70 << " " << 90 << endl;
	//小指
	m_RobotHand.Little2_Rotate_r(10);
	m_RobotHand.Little3_Rotate_r(80);
	m_RobotHand.Little4_Rotate_r(160);
	ofile << "右手小指:" << 0 << " " << 10 << " " << 70 << " " << 90 << endl;
	//大拇指正向控制
	m_RobotHand.Thumb1_Rotate_r(-10);
	m_RobotHand.Thumb3_Rotate_r(60);
	m_RobotHand.Thumb4_Rotate_r(80);
	ofile << "右手大拇指:" << 0 << " " << 10 << " " << 70 << " " << 90 << endl;
	m_RobotHand.Thumb_Rotate_br(60);
	// 食指
	m_RobotHand.Index3_Rotate_r(20);
	m_RobotHand.Index4_Rotate_r(30);
	ofile << "右手食指:" << 0 << " " << 0 << " " << 20 << " " << 10 << endl;
	m_RobotHand.drawGL();
	RenderScene();
}

void CMy3DSLoaderView::OnSetAngle(float *angle)
{	//控制模型运动
	reset();
	m_RobotHand.Thumb1_Rotate(angle[2]-20);
	m_RobotHand.Thumb2_Rotate(angle[0]);
	m_RobotHand.Thumb3_Rotate(angle[0]+angle[1]);
	m_RobotHand.Thumb4_Rotate((angle[0] + angle[1]));
	//m_RobotHand.Thumb_Rotate_b(angle[2] + 15);
	m_RobotHand.Thumb_Rotate_b(angle[14]);

	m_RobotHand.Index1_Rotate(angle[5]);
	m_RobotHand.Index2_Rotate(angle[3]);
	m_RobotHand.Index3_Rotate(angle[3]+angle[4]);
	m_RobotHand.Index4_Rotate((angle[3] + angle[4])*1.67);

	m_RobotHand.Middle2_Rotate(angle[6]);
	m_RobotHand.Middle3_Rotate(angle[6]+angle[7]);
	m_RobotHand.Middle4_Rotate((angle[6] + angle[7])*1.67);

	m_RobotHand.Ring1_Rotate(-angle[8]);
	m_RobotHand.Ring2_Rotate(angle[9]);
	m_RobotHand.Ring3_Rotate(angle[9] + angle[10]);
	m_RobotHand.Ring4_Rotate((angle[9] + angle[10])*1.67);

	m_RobotHand.Little1_Rotate(-(angle[11]+angle[8]));
	m_RobotHand.Little2_Rotate(angle[12]);
	m_RobotHand.Little3_Rotate(angle[12] + angle[13]);
	m_RobotHand.Little4_Rotate((angle[12] + angle[13])*1.67);

	m_RobotHand.Thumb1_Rotate_r(angle[2] - 20);
	m_RobotHand.Thumb2_Rotate_r(angle[0]);
	m_RobotHand.Thumb3_Rotate_r(angle[0] + angle[1]);
	m_RobotHand.Thumb4_Rotate_r((angle[0] + angle[1])*1.67);
	//m_RobotHand.Thumb_Rotate_br(angle[2] + 15);
	m_RobotHand.Thumb_Rotate_br(angle[14]);

	m_RobotHand.Index1_Rotate_r(angle[5]);
	m_RobotHand.Index2_Rotate_r(angle[3]);
	m_RobotHand.Index3_Rotate_r(angle[3] + angle[4]);
	m_RobotHand.Index4_Rotate_r((angle[3] + angle[4])*1.67);

	m_RobotHand.Middle2_Rotate_r(angle[6]);
	m_RobotHand.Middle3_Rotate_r(angle[6] + angle[7]);
	m_RobotHand.Middle4_Rotate_r((angle[6] + angle[7])*1.67);

	m_RobotHand.Ring1_Rotate_r(-angle[8]);
	m_RobotHand.Ring2_Rotate_r(angle[9]);
	m_RobotHand.Ring3_Rotate_r(angle[9] + angle[10]);
	m_RobotHand.Ring4_Rotate_r((angle[9] + angle[10])*1.67);

	m_RobotHand.Little1_Rotate_r(-(angle[11] + angle[8]));
	m_RobotHand.Little2_Rotate_r(angle[12]);
	m_RobotHand.Little3_Rotate_r(angle[12] + angle[13]);
	m_RobotHand.Little4_Rotate_r((angle[12] + angle[13])*1.67);

	m_RobotHand.drawGL();
	RenderScene();
}

void CMy3DSLoaderView::OnReset()
{
	for (int i = 0; i < CGloableVariable::N; i++)
	{
		m_RobotHand.objects[i]->currentPos.x = CGloableVariable::defaultPos[i][0]-150;
		m_RobotHand.objects[i]->currentPos.y = CGloableVariable::defaultPos[i][1];
		m_RobotHand.objects[i]->currentPos.z = CGloableVariable::defaultPos[i][2];
	}
	int j = 0;
	for (int i = CGloableVariable::N; i < CGloableVariable::N + 21; i++)//右手部分
	{
		m_RobotHand.objects[i]->currentPos.x = CGloableVariable::defaultPos_r[j][0]-150;
		m_RobotHand.objects[i]->currentPos.y = CGloableVariable::defaultPos_r[j][1];
		m_RobotHand.objects[i]->currentPos.z = CGloableVariable::defaultPos_r[j][2];
		j++;

	}
	//右手基部
	for (int i = CGloableVariable::N+21,j=0; i < CGloableVariable::N + 23; i++,j++)//右手部分
	{
		m_RobotHand.objects[i]->currentPos.x = CGloableVariable::defaultPos_b[j][0] - 150;
		m_RobotHand.objects[i]->currentPos.y = CGloableVariable::defaultPos_b[j][1];
		m_RobotHand.objects[i]->currentPos.z = CGloableVariable::defaultPos_b[j][2];

	}

	for (int i = 0; i < CGloableVariable::N;i++)
	{
		if( i==1 || i==2 || i==3 || i==4 )
		{
			m_RobotHand.objects[i]->sceneRot[2]=m_RobotHand.ConvertAngleToRadian(60);
			m_RobotHand.objects[1]->angle=m_RobotHand.ConvertAngleToRadian(60);
		}
		else 
		m_RobotHand.objects[i]->sceneRot[2] =  0;
		m_RobotHand.objects[i]->sceneRot[1] =  0;
		
		m_RobotHand.objects[i]->sceneRot[0] =  0;
		m_RobotHand.objects[i]->angle =  0;
	}

	for (int i = CGloableVariable::N; i < CGloableVariable::N+23; i++)
	{
		if (i == CGloableVariable::N+1 || i == CGloableVariable::N+2 || i == CGloableVariable::N+3 || i == CGloableVariable::N+4)
		{
			m_RobotHand.objects[i]->sceneRot[2] = m_RobotHand.ConvertAngleToRadian(60);
			m_RobotHand.objects[CGloableVariable::N+1]->angle = m_RobotHand.ConvertAngleToRadian(60);
		}
		else
		m_RobotHand.objects[i]->sceneRot[2] = 0;
		m_RobotHand.objects[i]->sceneRot[1] = 0;

		m_RobotHand.objects[i]->sceneRot[0] = 0;
		m_RobotHand.objects[i]->angle = 0;
	}

	m_RobotHand.drawGL();
	RenderScene();
	return;
}
void CMy3DSLoaderView::OnThumb()
{
	m_RobotHand.Thumb1_Rotate(10);
	m_RobotHand.Thumb2_Rotate(30);
	m_RobotHand.Thumb3_Rotate(60);
	m_RobotHand.Thumb4_Rotate(80);

	m_RobotHand.Thumb1_Rotate_r(10);
	m_RobotHand.Thumb2_Rotate_r(30);
	m_RobotHand.Thumb3_Rotate_r(60);
	m_RobotHand.Thumb4_Rotate_r(80);

	m_RobotHand.Thumb_Rotate_b(60);
	m_RobotHand.Thumb_Rotate_br(60);
	m_RobotHand.drawGL();
	RenderScene();

	return;
}
void CMy3DSLoaderView::OnThumbInverse()
{
//这一块代码是用来完成逆向计算和旋转的。
	
		int choice[5]={1,0,0,0,0};
		float *res = m_RobotHand.CalculateThetaByCoordinate(tVector(46.186, 85.286, 60.0), choice);
		CString str;
		float angle0 = -(*res);
		float angle1 = -*(res + 1);
		float angle2 = *(res + 2);
		float angle3 = *(res + 3);
		str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
		PublicFuntoinHelper::ShowMessage(str);
		m_RobotHand.Thumb1_Rotate(angle0);
		m_RobotHand.Thumb2_Rotate(angle1);
		m_RobotHand.Thumb3_Rotate(angle1 + angle2);
		m_RobotHand.Thumb4_Rotate(angle1 + angle2 + angle3);

		m_RobotHand.Thumb1_Rotate_r(angle0);
		m_RobotHand.Thumb2_Rotate_r(angle1);
		m_RobotHand.Thumb3_Rotate_r(angle1 + angle2);
		m_RobotHand.Thumb4_Rotate_r(angle1 + angle2 + angle3);

		m_RobotHand.drawGL();
		RenderScene();
	
}
void CMy3DSLoaderView::OnIndex()
{

	m_RobotHand.Index1_Rotate(20);
	m_RobotHand.Index2_Rotate(10);
	m_RobotHand.Index3_Rotate(10);
	m_RobotHand.Index4_Rotate(10);

	m_RobotHand.Index1_Rotate_r(10);//基关节
	m_RobotHand.Index2_Rotate_r(10);
	m_RobotHand.Index3_Rotate_r(10);
	m_RobotHand.Index4_Rotate_r(10);

	m_RobotHand.drawGL();
	RenderScene();

	return;
}
void CMy3DSLoaderView::OnIndexInverse()
{
		int choice[5]={0,1,0,0,0};
		float* res= m_RobotHand.CalculateThetaByCoordinate(tVector(22.68,141.24,74.81),choice);
		CString str;
		float angle0= -(*res);
		float angle1= -*(res+1);
		float angle2= -*(res+2);
		float angle3= -*(res+3);
		str.Format("%f,%f,%f,%f",angle0 , angle1, angle2,angle3);
		PublicFuntoinHelper::ShowMessage(str);
	
		m_RobotHand.Index1_Rotate(angle0);
		m_RobotHand.Index2_Rotate(angle1);
		m_RobotHand.Index3_Rotate(angle1+angle2);
		m_RobotHand.Index4_Rotate(angle1+angle2+angle3);

		m_RobotHand.Index1_Rotate_r(angle0);
		m_RobotHand.Index2_Rotate_r(angle1);
		m_RobotHand.Index3_Rotate_r(angle1 + angle2);
		m_RobotHand.Index4_Rotate_r(angle1 + angle2 + angle3);
		
	return;
}
void CMy3DSLoaderView::OnMiddle()
{
	m_RobotHand.Middle1_Rotate(10);
	m_RobotHand.Middle2_Rotate(10);
	m_RobotHand.Middle3_Rotate(10);
	m_RobotHand.Middle4_Rotate(10);

	m_RobotHand.Middle1_Rotate_r(10);
	m_RobotHand.Middle2_Rotate_r(10);
	m_RobotHand.Middle3_Rotate_r(10);
	m_RobotHand.Middle4_Rotate_r(10);

	m_RobotHand.drawGL();
	RenderScene();

	return;
}
void CMy3DSLoaderView::OnMiddleInverse()
{	int choice[5]={0,0,1,0,0};
		float* res= m_RobotHand.CalculateThetaByCoordinate(tVector(22.68,141.24,74.81),choice);
		CString str;
		float angle0= (*res);	
		float angle1= -*(res+1);
		float angle2= -*(res+2);
		float angle3= -*(res+3);
		
		m_RobotHand.Middle1_Rotate(angle0);
		m_RobotHand.Middle2_Rotate(angle1);
		m_RobotHand.Middle3_Rotate(angle1+angle2);
		m_RobotHand.Middle4_Rotate(angle1+angle2+angle3);

		m_RobotHand.Middle1_Rotate_r(angle0);
		m_RobotHand.Middle2_Rotate_r(angle1);
		m_RobotHand.Middle3_Rotate_r(angle1 + angle2);
		m_RobotHand.Middle4_Rotate_r(angle1 + angle2 + angle3);
		m_RobotHand.drawGL();
		RenderScene();

		str.Format("%f,%f,%f,%f",angle0 , angle1, angle2,angle3);
		PublicFuntoinHelper::ShowMessage(str);
		
	return;
}
void CMy3DSLoaderView::OnRing()
{
	m_RobotHand.Ring1_Rotate(10);
	m_RobotHand.Ring2_Rotate(10);
	m_RobotHand.Ring3_Rotate(10);
	m_RobotHand.Ring4_Rotate(10);

	m_RobotHand.Ring1_Rotate_r(10);
	m_RobotHand.Ring2_Rotate_r(10);
	m_RobotHand.Ring3_Rotate_r(10);
	m_RobotHand.Ring4_Rotate_r(10);

	m_RobotHand.drawGL();
	RenderScene();

	return;
}
void CMy3DSLoaderView::OnRingInverse()
{	int choice[5]={0,0,0,1,0};
		float* res= m_RobotHand.CalculateThetaByCoordinate(tVector(22.68,141.24,74.81),choice);
		CString str;
		float angle0= (*res);
		float angle1= -*(res+1);
		float angle2= -*(res+2);
		float angle3= -*(res+3);
		str.Format("%f,%f,%f,%f",angle0 , angle1, angle2,angle3);
		PublicFuntoinHelper::ShowMessage(str);
		
		m_RobotHand.Ring1_Rotate(angle0);
		m_RobotHand.Ring2_Rotate(angle1);
		m_RobotHand.Ring3_Rotate(angle1+angle2);
		m_RobotHand.Ring4_Rotate(angle1+angle2+angle3);	

		m_RobotHand.Ring1_Rotate_r(angle0);
		m_RobotHand.Ring2_Rotate_r(angle1);
		m_RobotHand.Ring3_Rotate_r(angle1 + angle2);
		m_RobotHand.Ring4_Rotate_r(angle1 + angle2 + angle3);
		
	return;
	return;
}
void CMy3DSLoaderView::OnLittle()
{
	m_RobotHand.Little1_Rotate(10);
	m_RobotHand.Little2_Rotate(10);
	m_RobotHand.Little3_Rotate(10);
	m_RobotHand.Little4_Rotate(10);

	m_RobotHand.Little1_Rotate_r(10);
	m_RobotHand.Little2_Rotate_r(10);
	m_RobotHand.Little3_Rotate_r(10);
	m_RobotHand.Little4_Rotate_r(10);

	m_RobotHand.drawGL();
	RenderScene();

	return;
}
void CMy3DSLoaderView::OnLittleInverse()
{	int choice[5]={0,0,0,0,1};
		float* res= m_RobotHand.CalculateThetaByCoordinate(tVector(22.68,80.24,34.81),choice);
				CString str;
		float angle0= -(*res);
		float angle1= -*(res+1);
		float angle2= -*(res+2);
		float angle3= -*(res+3);
		str.Format("%f,%f,%f,%f",angle0 , angle1, angle2,angle3);
		PublicFuntoinHelper::ShowMessage(str);
		
		m_RobotHand.Little1_Rotate(angle0);
		m_RobotHand.Little2_Rotate(angle1);
		m_RobotHand.Little3_Rotate(angle1+angle2);
		m_RobotHand.Little4_Rotate(angle1+angle2+angle3);

		m_RobotHand.Little1_Rotate_r(angle0);
		m_RobotHand.Little2_Rotate_r(angle1);
		m_RobotHand.Little3_Rotate_r(angle1 + angle2);
		m_RobotHand.Little4_Rotate_r(angle1 + angle2 + angle3);
		
	return;
	
}

void CMy3DSLoaderView::OnTest()
{
	// 食指与大拇指尖触碰
	/*
	m_RobotHand.Thumb1_Rotate(5);
	m_RobotHand.Thumb3_Rotate(50);
	m_RobotHand.Thumb4_Rotate(50);
	m_RobotHand.Thumb_Rotate_b(55);
	int choice[5] = { 0,1,0,0,0 };
	float *res = m_RobotHand.CalculateThetaByCoordinate(tVector(15.1712 ,80.301, - 38.2533), choice);
	CString str;
	float angle0 = -(*res);
	float angle1 = -*(res + 1);
	float angle2 = *(res + 2);
	float angle3 = *(res + 3);
	str.Format("%f,%f,%f,%f", angle0, angle1, angle2, angle3);
	PublicFuntoinHelper::ShowMessage(str);

	m_RobotHand.Index1_Rotate(angle0);
	m_RobotHand.Index2_Rotate(angle1+20);
	m_RobotHand.Index3_Rotate(angle1 + angle2+10);
	m_RobotHand.Index4_Rotate(angle1 + angle2 + angle3+10);
	m_RobotHand.drawGL();
	RenderScene();
	
	reset();
	*/
	m_RobotHand.Thumb1_Rotate(5);
	m_RobotHand.Thumb3_Rotate(50);
	m_RobotHand.Thumb4_Rotate(50);
	m_RobotHand.Thumb_Rotate_b(80);


	m_RobotHand.Middle2_Rotate(30);
	m_RobotHand.Middle3_Rotate(90);
	m_RobotHand.Middle4_Rotate(160);

	m_RobotHand.drawGL();
	RenderScene();
}
