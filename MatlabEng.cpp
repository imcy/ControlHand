// MatlabEngine.cpp: implementation of the CMatlabEng class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MatlabEng.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMatlabEng::CMatlabEng()
{
	pEng=NULL;
}

CMatlabEng::~CMatlabEng()
{
	if (pEng!=NULL)
		Close();
}

void CMatlabEng::Open(const char *StartCmd)
{
	pEng=engOpen(StartCmd);
}

int CMatlabEng::Close()
{
	int Result=engClose(pEng);
	if (Result==0)	//Success
		pEng=NULL;

	return Result;
}

int CMatlabEng::EvalString(const char *string)
{
	return (engEvalString(pEng, string));
}

mxArray* CMatlabEng::GetVariable(const char *name)
{
	return (engGetVariable(pEng, name));
}


int CMatlabEng::GetVisible(bool* value)
{
	return (engGetVisible(pEng, value));
}

void CMatlabEng::OpenSingleUse(const char *startcmd, void *dcom, int *retstatus)
{
	pEng=engOpenSingleUse(startcmd, dcom, retstatus);
}

int CMatlabEng::OutputBuffer(char *p, int n)
{
	return (engOutputBuffer(pEng, p, n));
}

int CMatlabEng::PutVariable(const char *name, const mxArray *mp)
{
	return (engPutVariable(pEng, name, mp));
}

int CMatlabEng::SetVisible(bool value)
{
	return (engSetVisible(pEng, value));
}
