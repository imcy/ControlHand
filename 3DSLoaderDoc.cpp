// 3DSLoaderDoc.cpp : implementation of the CMy3DSLoaderDoc class
//

#include "stdafx.h"
#include "3DSLoader.h"

#include "3DSLoaderDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderDoc

IMPLEMENT_DYNCREATE(CMy3DSLoaderDoc, CDocument)

BEGIN_MESSAGE_MAP(CMy3DSLoaderDoc, CDocument)
	//{{AFX_MSG_MAP(CMy3DSLoaderDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderDoc construction/destruction

CMy3DSLoaderDoc::CMy3DSLoaderDoc()
{
	// TODO: add one-time construction code here

}

CMy3DSLoaderDoc::~CMy3DSLoaderDoc()
{
}

BOOL CMy3DSLoaderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderDoc serialization

void CMy3DSLoaderDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderDoc diagnostics

#ifdef _DEBUG
void CMy3DSLoaderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMy3DSLoaderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMy3DSLoaderDoc commands

BOOL CMy3DSLoaderDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	//if (!CDocument::OnOpenDocument(lpszPathName))
	//	return FALSE;
	//
	//// TODO: Add your specialized creation code here
	//if( ((CMy3DSLoaderApp*)AfxGetApp())->OpenFile(lpszPathName) ) return TRUE;
	
	return TRUE;
}
