// SICKDlg.h : header file
//

#if !defined(AFX_SICKDLG_H__D6ABEE28_86BD_4DFE_BDC7_0FC5E96EB1FE__INCLUDED_)
#define AFX_SICKDLG_H__D6ABEE28_86BD_4DFE_BDC7_0FC5E96EB1FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SenSor_SICK.h"

/////////////////////////////////////////////////////////////////////////////
// CSICKDlg dialog

class CSICKDlg : public CDialog
{
// Construction
public:
	int PicW;
	int PicH;
	int PicXS;
	int PicYS;

	CSICKDlg(CWnd* pParent = NULL);	// standard constructor

	CSenSor_SICK CSick;
// Dialog Data
	//{{AFX_DATA(CSICKDlg)
	enum { IDD = IDD_SICK_DIALOG };
	CStatic	m_Picture;
	CButton	m_SettingMode;
	CEdit	m_StatsList;
	CComboBox	m_SickMeasure;
	CComboBox	m_SickReSolution;
	CComboBox	m_SickBau;
	CComboBox	m_StopBit;
	CComboBox	m_ParityBit;
	CComboBox	m_DataBit;
	CComboBox	m_BaudRate;
	CComboBox	m_PortName;
	CString	m_SendStr;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSICKDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSICKDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnect();
	afx_msg void OnDisconnect();
	afx_msg void OnSend();
	afx_msg long OnCommunication(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSickStart();
	afx_msg void OnSickStop();
	afx_msg void OnSetSend();
	afx_msg void OnSetSend2();
	afx_msg void OnSetSend3();
	afx_msg void OnCheck1();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SICKDLG_H__D6ABEE28_86BD_4DFE_BDC7_0FC5E96EB1FE__INCLUDED_)
