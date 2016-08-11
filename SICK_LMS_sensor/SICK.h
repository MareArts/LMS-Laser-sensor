// SICK.h : main header file for the SICK application
//

#if !defined(AFX_SICK_H__F6E4D40E_3779_41CC_8722_D58DAEE73EA7__INCLUDED_)
#define AFX_SICK_H__F6E4D40E_3779_41CC_8722_D58DAEE73EA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSICKApp:
// See SICK.cpp for the implementation of this class
//

class CSICKApp : public CWinApp
{
public:
	CSICKApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSICKApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSICKApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICK_H__F6E4D40E_3779_41CC_8722_D58DAEE73EA7__INCLUDED_)
