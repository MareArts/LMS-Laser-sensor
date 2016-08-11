// SICKDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SICK.h"
#include "SICKDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HWND hCommWnd;

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
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSICKDlg dialog

CSICKDlg::CSICKDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSICKDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSICKDlg)
	m_SendStr = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSICKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSICKDlg)
	DDX_Control(pDX, IDC_PIC, m_Picture);
	DDX_Control(pDX, IDC_CHECK1, m_SettingMode);
	DDX_Control(pDX, IDC_EDIT2, m_StatsList);
	DDX_Control(pDX, IDC_COMBO8, m_SickMeasure);
	DDX_Control(pDX, IDC_COMBO7, m_SickReSolution);
	DDX_Control(pDX, IDC_COMBO6, m_SickBau);
	DDX_Control(pDX, IDC_COMBO3, m_StopBit);
	DDX_Control(pDX, IDC_COMBO5, m_ParityBit);
	DDX_Control(pDX, IDC_COMBO2, m_DataBit);
	DDX_Control(pDX, IDC_COMBO4, m_BaudRate);
	DDX_Control(pDX, IDC_COMBO1, m_PortName);
	DDX_Text(pDX, IDC_EDIT1, m_SendStr);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSICKDlg, CDialog)
//{{AFX_MSG_MAP(CSICKDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Connect, OnConnect)
	ON_BN_CLICKED(IDC_Disconnect, OnDisconnect)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_MESSAGE(WM_COMM_READ , OnCommunication)
	ON_BN_CLICKED(IDC_SICK_START, OnSickStart)
	ON_BN_CLICKED(IDC_SICK_STOP, OnSickStop)
	ON_BN_CLICKED(IDC_SetSend, OnSetSend)
	ON_BN_CLICKED(IDC_SetSend2, OnSetSend2)
	ON_BN_CLICKED(IDC_SetSend3, OnSetSend3)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSICKDlg message handlers

BOOL CSICKDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// Add "About..." menu item to system menu.
	
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
//	m_Stats.SetCurSel(0);
	m_StopBit.SetCurSel(0);
	m_ParityBit.SetCurSel(2);
	m_DataBit.SetCurSel(3);
	m_BaudRate.SetCurSel(2);
	m_PortName.SetCurSel(0);

	m_SickBau.SetCurSel(0);
	m_SickReSolution.SetCurSel(0);
	m_SickMeasure.SetCurSel(0);

	hCommWnd = m_hWnd;

	CRect rect;
	m_Picture.GetWindowRect(rect);
	PicW = rect.Width();
	PicH = rect.Height();
	PicXS = 1000;
	PicYS = 1000;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSICKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSICKDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);
		
		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		
		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{		

		CDC* pDC = m_Picture.GetDC();		
		CDC memDC; 		
		CBitmap bmp;		
		memDC.CreateCompatibleDC(pDC);		
		bmp.CreateCompatibleBitmap( pDC, PicW, PicH);		
		memDC.SelectObject(bmp);

		memDC.SelectStockObject(WHITE_BRUSH);
		memDC.SelectStockObject(WHITE_PEN);

		pDC->SelectStockObject(WHITE_BRUSH);
		pDC->SelectStockObject(WHITE_PEN);
		

		int x,y;
		if(CSick.mode==1)
		{				
			CString a;
			for(int i=0; i<CSick.resolution/2; ++i)
			{
				//a.Format("[%d] %d %d",i,CSick.OneScanSq[0][i], CSick.OneScanSq[1][i]);
				//m_StatsList.ReplaceSel(a);
				//m_StatsList.ReplaceSel("\r\n");
				
				x = (PicW/2.0) +( CSick.OneScanSq[0][i] * (PicW/2.0)/PicXS);
				y = PicH - ( CSick.OneScanSq[1][i] * (PicH/1.0)/PicYS );
		
				if(i==0)
					memDC.MoveTo(x,y);
				
				memDC.Ellipse(x-2,y-2,x+2,y+2);
				memDC.LineTo(x,y);
				memDC.SetPixel( x, y, RGB(255,0,0));
			}
		}		
		pDC->StretchBlt(0,0,PicW,PicH,&memDC,0,0,PicW,PicH,SRCCOPY); 		
		bmp.DeleteObject();
		memDC.DeleteDC();
		ReleaseDC(pDC);
			
		CDialog::OnPaint();		
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSICKDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}




void CSICKDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
//	char msgStr[40];
//	char msgStatus[10] = "status : ";
	
	int stop;
	int parity;
	int data;
	int baudrate;
	CString strPort;

	UpdateData(true);
	int m_index = m_PortName.GetCurSel();	
	switch(m_index)
	{
		case 0: strPort = "COM1"; break;
		case 1: strPort = "COM2"; break;
		case 2: strPort = "COM3"; break;
		case 3: strPort = "COM4"; break;
		case 4: strPort = "COM5"; break;
		case 5: strPort = "COM6" ; break;
		case 6: strPort = "COM7"; break;
		case 7: strPort = "COM8"; break;
		case 8: strPort = "COM9"; break;
		case 9: strPort = "COM10"; break;

		default: strPort = "COM1"; break;
	}
	
	m_index = m_BaudRate.GetCurSel();
	switch(m_index)
	{
		case 0: baudrate = 2400; break;
		case 1: baudrate = 4800; break;
		case 2: baudrate = 9600; break;
		case 3: baudrate = 14400; break;
		case 4: baudrate = 19200; break;
		case 5: baudrate = 38400; break;
		case 6: baudrate = 57600; break;
		case 7: baudrate = 115200; break;
		default: baudrate = 9600;break;
	}
	
	m_index=m_DataBit.GetCurSel();
	switch(m_index)
	{
		case 0: data = 5; break;
		case 1: data = 6; break;
		case 2: data = 7; break;
		case 3: data = 8; break;
		default: data = 8; break;
	}
	
	m_index = m_ParityBit.GetCurSel();
	switch(m_index)
	{
		case 0: parity = 2; break;
		case 1: parity = 1; break;
		case 2: parity = 0; break;
		default: parity = 0; break;
	}
	
	m_index = m_StopBit.GetCurSel();
	switch(m_index)
	{
		case 0: stop = 0; break;
		case 1: stop = 2; break;
	}

	if(CSick.m_ComuPort.m_bConnected == FALSE)
	{		
		if(CSick.m_ComuPort.OpenPort(strPort, baudrate, data, stop, parity) == TRUE)
		{			
			CString a;
			a.Format("Connection Success %s %d %d %d %d",strPort, baudrate, data, stop, parity);			
			m_StatsList.ReplaceSel(a);
			m_StatsList.ReplaceSel("\r\n");
			m_PortName.EnableWindow(false);
			m_BaudRate.EnableWindow(false);
			m_DataBit.EnableWindow(false);
			m_StopBit.EnableWindow(false);
			m_ParityBit.EnableWindow(false);
		}else{
			m_StatsList.ReplaceSel("port open fail !!");
			m_StatsList.ReplaceSel("\r\n");
		}
	}
	else
	{			
		m_StatsList.ReplaceSel("port open fail !!");
		m_StatsList.ReplaceSel("\r\n");
	}
}

void CSICKDlg::OnDisconnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CString PortName;
	
	if(CSick.m_ComuPort.m_bConnected == TRUE)
	{	
		CSick.m_ComuPort.ClosePort();
		m_PortName.EnableWindow(true);
		m_BaudRate.EnableWindow(true);
		m_DataBit.EnableWindow(true);
		m_StopBit.EnableWindow(true);
		m_ParityBit.EnableWindow(true);
		m_StatsList.ReplaceSel("Close");
		m_StatsList.ReplaceSel("\r\n");
	}
	else
	{
		m_StatsList.ReplaceSel("close fail !!");
		m_StatsList.ReplaceSel("\r\n");
	}
}

void CSICKDlg::OnSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	
	CString sendData = m_SendStr;	//컨트롤 맴버 변수를 받는다.
	sendData.Replace(" ","");		// 공백 없애기 
	sendData.Replace("\r\n","");	//엔터 없애기
	
	if((CSick.m_ComuPort.m_bConnected == TRUE) && (m_SendStr != "")){
		CSick.m_ComuPort.WriteComm((unsigned char*)(LPCTSTR)sendData, sendData.GetLength());		
	}

	m_SendStr="";
	UpdateData(false);
}


long CSICKDlg::OnCommunication(WPARAM wParam, LPARAM lParam)
{	
	
	CString a;
	a.Format("%d ",CSick.oneResult.GetLength());
	m_StatsList.ReplaceSel(a);
	//m_StatsList.Clear();
	//m_StatsList.ReplaceSel("\r\n");
	//m_StatsList.ReplaceSel("\r\n");
	//m_StatsList.ReplaceSel(CSick.oneResult);
	OnPaint();

	return 1;
}

void CSICKDlg::OnSickStart() 
{
	// TODO: Add your control notification handler code here
	CSick.StartContinuous();
//	CSick.StopContinuous();
}

void CSICKDlg::OnSickStop() 
{
	// TODO: Add your control notification handler code here
	CSick.StopContinuous();
}

void CSICKDlg::OnSetSend() 
{
	// TODO: Add your control notification handler code here	
	int m_index = m_SickBau.GetCurSel();	
	switch(m_index)
	{
		case 0: CSick.Set9600Baud(); break;
		case 1: CSick.Set38400Baud(); break;
		case 2: CSick.Set19200Baud(); break;		
		default: ::AfxMessageBox("Baudrate Set Error"); break;
	}	
}



void CSICKDlg::OnSetSend2() 
{
	// TODO: Add your control notification handler code here
	int m_index = m_SickReSolution.GetCurSel();	
	switch(m_index)
	{
	case 0: CSick.Set0_100_1_Resolution(); break;
	case 1: CSick.Set0_100_05_Resolution(); break;
	case 2: CSick.Set0_100_025_Resolution(); break;
	case 3: CSick.Set0_180_1_Resolution(); break;
	case 4: CSick.Set0_180_05_Resolution(); break;
	default: ::AfxMessageBox("Resolution Set Error"); break;
	}
}

void CSICKDlg::OnSetSend3() 
{
	// TODO: Add your control notification handler code here
	if(m_SettingMode.GetCheck() == 1)
	{
		int m_index = m_SickMeasure.GetCurSel();	
		switch(m_index)
		{
		case 0: CSick.SetModeMM(); break;
		case 1: CSick.SetModeCM(); break;
		default: ::AfxMessageBox("Resolution Set Error"); break;
		}
	}else{
		::AfxMessageBox("Check Set mode!!");
	}
}

void CSICKDlg::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	if(m_SettingMode.GetCheck() == 1)
	{
		CSick.SetMode();
	}
}



BOOL CSICKDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	// TODO: Add your message handler code here and/or call default
	if(zDelta>0)
	{
		PicXS += 50;
		PicYS += 50;
	}else
	{
		PicXS -= 50;
		PicYS -= 50;
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}
