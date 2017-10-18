#ifndef _MATLAB_ENGINE_H_
#define _MATLAB_ENGINE_H_

////////////////////////////////////////////////////////////////////////////
//	Copyright : 27 May 2003
//
//	Email: a.riazi@misbah3com.com
//
//	This code may be used in compiled form in any way you desire. This
//	file may be redistributed unmodified by any means PROVIDING it is 
//	not sold for profit without the authors written consent, and 
//	providing that this notice and the authors name is included.
//
//	This file is provided 'as is' with no expressed or implied warranty.
//	The author accepts no liability if it causes any damage to your computer.
//
//	Do expect bugs.
//	Please let me know of any bugs/mods/improvements.
//	and I will try to fix/incorporate them into this file.
//	Enjoy!
//
//	Description : This class wraps Matlab Engine APIs.
//  
//  Brief Documentation:
//
//  Open 			Start up MATLAB engine
//  Close 			Shut down MATLAB engine
//  GetVariable 	Get a MATLAB array from the MATLAB engine
//  PutVariable 	Send a MATLAB array to the MATLAB engine
//  EvalString 		Execute a MATLAB command
//  OutputBuffer 	Create a buffer to store MATLAB text output
//  OpenSingleUse 	Start a MATLAB engine session for single, nonshared use 
//  GetVisible 		Determine visibility of MATLAB engine session
//  SetVisible 		Show or hide MATLAB engine session
//
////////////////////////////////////////////////////////////////////////////

#ifndef FALSE
#define FALSE	0
#endif

#ifndef TRUE
#define TRUE	1
#endif

//#include "Matlab.h"
#include "Engine.h"

//MATLAB library - Linking MATLAB libraries automatically
#pragma comment(lib, "libeng.lib")
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmatlb.lib")
#pragma comment(lib, "libmat.lib")
#pragma comment(lib, "libmmfile.lib")

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CMatlabEng  
{
public:
	
	int OutputBuffer(char *p, int n);
	/*
	Purpose			Specify buffer for MATLAB output
	Arguments		n
					Length of buffer p.
					p
					Pointer to character buffer of length n.
	Description		OutputBuffer defines a character buffer for engEvalString to 
					return any output that ordinarily appears on the screen.
					The default behavior of EvalString is to discard any standard 
					output caused by the command it is executing. 
					OutputBuffer(ep,p,n) tells any subsequent calls to 
					EvalString to save the first n characters of output in the 
					character buffer pointed to by p. 
					To turn off output buffering, use OutputBuffer(ep,NULL,0);
	*/

	void OpenSingleUse(const char *startcmd, void *dcom, int *retstatus);
	/*
	Purpose			Start a MATLAB engine session for single, nonshared use
	Arguments		startcmd
					String to start MATLAB process. 
					On Windows, the startcmd string must be NULL.
					dcom
					Reserved for future use; must be NULL.
					retstatus
					Return status; possible cause of failure.
	Description		This routine allows you to start multiple MATLAB processes for 
					the purpose of using MATLAB as a computational engine. 
					OpenSingleUse starts a MATLAB process, establishes a connection, 
					and returns a unique engine identifier, or NULL if the 
					open fails. OpenSingleUse starts a new MATLAB process each time 
					it is called.
					OpenSingleUse opens a COM channel to MATLAB. This starts the
					MATLAB that was registered during installation. 
					If you did not register during installation, on the command line 
					you can enter the command: 
						matlab /regserver
					OpenSingleUse allows single-use instances of a MATLAB engine 
					server. OpenSingleUse differs from Open, which allows multiple 
					users to use the same MATLAB engine server.
	*/

	int GetVisible(bool* value);
	/*
	Purpose			Copy a variable from a MATLAB engine’s workspace
	Arguments		name
					Name of mxArray to get from MATLAB.
	Description		return status of the window for the MATLAB engine session, 
					is visible or invisible on the Windows desktop
	Returns			SetVisible returns 0 on success, and 1 otherwise.
	*/

	int SetVisible(bool value);
	/*
	Purpose			Show or hide MATLAB engine session
	Arguments		value
					Value to set the Visible property to. Set value to 1 to make 
					the engine window visible, or to 0 to make it invisible.
	Description		SetVisible makes the window for the MATLAB engine session, 
					either visible or invisible on the Windows desktop. 
					You can use this function to enable or disable user interaction 
					with the MATLAB engine session.
	
	Returns			SetVisible returns 0 on success, and 1 otherwise.
	*/
	
	mxArray* GetVariable(const char* name);
	/*
	Purpose			Copy a variable from a MATLAB engine’s workspace 
	Arguments		name
					Name of mxArray to get from MATLAB.
	Description		reads the named mxArray from the MATLAB engine session
					associated with ep and returns a pointer to a newly allocated 
					mxArray structure, or NULL if the attempt fails. GetVariable 
					fails if the named variable does not exist.
					Be careful in your code to free the mxArray created by this 
					routine when you are finished with it.
	*/

	int PutVariable(const char *name, const mxArray *mp);
	/*
	Purpose			Put variables into a MATLAB engine’s workspace
	Arguments		name
					Name given to the mxArray in the engine’s workspace.
					mp
					mxArray pointer.
	Description		PutVariable writes mxArray mp to the engine ep, giving it 
					the variable name, name. If the mxArray does not exist in the 
					workspace, it is created. If an mxArray with the same name 
					already exists in the workspace, the existing mxArray is 
					replaced with the new mxArray.
					
	Returns			PutVariable returns 0 if successful and 1 if an error occurs.
	*/

	int EvalString(const char* string);
	/*
	Purpose			Evaluate expression in string
	Arguments		string 
					String to execute.
	Description		evaluates the expression contained in string for the MATLAB
					engine session, previously started by Open. 
	Returns			It returns a nonzero value if the MATLAB session is no 
					longer running, and zero otherwise.
	*/

	void Open(const char* StartCmd);
	/*
	Purpose			Start a MATLAB engine session
	Arguments		Startcmd
					String to start MATLAB process. On Windows, the startcmd 
					string must be NULL.
	Description		This routine allows you to start a MATLAB process for the 
					purpose of using MATLAB as a computational engine.
	*/

	int Close();
	/*
	Close			Quit a MATLAB engine session
	Arguments		-
	Description		This routine allows you to quit a MATLAB engine session.
	Returns			Close sends a quit command to the MATLAB engine session and 
					closes the connection. It returns 0 on success, and 1 otherwise. 
					Possible failure includes attempting to terminate a MATLAB 
					engine session that was already terminated.
	*/

	CMatlabEng();
	virtual ~CMatlabEng();

protected:
	Engine* pEng;
};

#endif // _MATLAB_ENGINE_H_
