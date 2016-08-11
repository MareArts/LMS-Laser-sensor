// SenSor_SICK.h: interface for the CSenSor_SICK class.
// made by Kim Jeong Hyun
// feelmare@daum.net
// pusan national university V.I.S Lab ph.d 
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SENSOR_SICK_H__5541B82B_B848_4A41_80A9_DE56A48C4B3D__INCLUDED_)
#define AFX_SENSOR_SICK_H__5541B82B_B848_4A41_80A9_DE56A48C4B3D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WM_COMM_READ (WM_USER +1)
#include "CommThread.h"

extern HWND hCommWnd;

class CSenSor_SICK
{
public:
	void SetMode();
	void StopContinuous();
	void StartContinuous();
	void SetModeCM();
	void SetModeMM();
	void Set0_180_05_Resolution();
	void Set0_100_025_Resolution();
	void Set0_100_1_Resolution();
	void Set0_100_05_Resolution();
	void Set0_180_1_Resolution();
	void GetData();
	void Set38400Baud();
	void Set19200Baud();
	void Set9600Baud();
	CSenSor_SICK();
	virtual ~CSenSor_SICK();

	CCommThread m_ComuPort;

	CString result;

	unsigned int* ResultScanV; //distance buffer
	int** ResultScanSq;
	unsigned int* OneScanV; //distance buffer
	int** OneScanSq;


	CString oneResult;
	

	int mode; //start scan
	int resolution; //data size
	int first10byte; //header size
	int secondByte; //packet size
	unsigned char* buffer; //byte buffer
	
	double sub;
	double gap;
	
	
};

#endif // !defined(AFX_SENSOR_SICK_H__5541B82B_B848_4A41_80A9_DE56A48C4B3D__INCLUDED_)
