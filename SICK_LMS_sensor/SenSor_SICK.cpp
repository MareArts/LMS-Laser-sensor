// SenSor_SICK.cpp: implementation of the CSenSor_SICK class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SICK.h"
#include "SenSor_SICK.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define ppi (3.14159/180.0)

CSenSor_SICK::CSenSor_SICK()
{
	buffer = new unsigned char[1024];

	OneScanV = new unsigned int[1024];
	ResultScanV = new unsigned int[1024];
	OneScanSq = new int* [2];
	for(int i=0; i<2; ++i)
		OneScanSq[i] =  new int[1024];

	ResultScanSq = new int* [2];
	for(i=0; i<2; ++i)
		ResultScanSq[i] =  new int[1024];

	m_ComuPort.Parent = this;	
	mode=0;
}

CSenSor_SICK::~CSenSor_SICK()
{
	delete [] buffer;
	delete [] OneScanV;
	delete [] ResultScanV;

	for(int i=0; i<2; ++i)
		delete[] OneScanSq[i];
	delete[] OneScanSq;

	for(i=0; i<2; ++i)
		delete[] ResultScanSq[i];
	delete[] ResultScanSq;
}

void CSenSor_SICK::Set9600Baud()
{	
	unsigned char Fwd[] = {0x02,0x00,0x02,0x00,0x20,0x42,0x52,0x08};
	int d=m_ComuPort.WriteComm( Fwd, 8);
}

void CSenSor_SICK::Set19200Baud()
{
	unsigned char Fwd[] = {0x02,0x00,0x02,0x00,0x20,0x41,0x51,0x08};
	int d=m_ComuPort.WriteComm( Fwd, 8);
}

void CSenSor_SICK::Set38400Baud()
{	
	unsigned char Fwd[] = {0x02,0x00,0x02,0x00,0x20,0x40,0x50,0x08};
	int d=m_ComuPort.WriteComm( Fwd, 8);
}

void CSenSor_SICK::GetData()
{	
	//it's very important processing
	//I confirm that this code will be no-understand therefore I made..^^
	double interM1,interM2;
	int i,j;
	int temp;
	int index=0;
	CString str;	
	BYTE aByte; 
	int iSize =  (m_ComuPort.m_QueueRead).GetSize(); 
	
	for(i  = 0 ; i < iSize; i++)
	{			
		(m_ComuPort.m_QueueRead).GetByte(&aByte);  //글자 하나씩 읽어옴		
		//str.Format("%02x ", aByte);
				
		//continuous mode
		if(mode == 1)
		{
			//To skip 10 byte firstly.
			first10byte++;
			if(first10byte>=11)
			{
				//copy by byte
				buffer[secondByte] = aByte;
				first10byte=11;
				secondByte++;
				//if buffer is full of one packet
				if(secondByte == resolution+3+7)
				{
					index=0;					
					//change 2byte data to dec
					for(j=7; j<secondByte-3; j=j+2)
					{		
						temp=0;
						temp=(buffer[j])+(buffer[j+1]<<8);
						ResultScanV[index++]=temp;
						str.Format("%d ", temp );
						result += str;
					}

					//pole to carte
					for(j=0; j<resolution/2; ++j)
					{						
						ResultScanSq[0][j] = cos((j*sub+gap)*ppi)*ResultScanV[j];
						ResultScanSq[1][j] = sin((j*sub+gap)*ppi)*ResultScanV[j];
					}
					
					//////////////////////////////////////////////////////////////////////////
					//critical section part;
					//copy data buffer;										
					memcpy(OneScanV,ResultScanV,sizeof(int)*1024);
					memcpy(OneScanSq[0],ResultScanSq[0],sizeof(int)*1024);
					memcpy(OneScanSq[1],ResultScanSq[1],sizeof(int)*1024);				
					
					oneResult=result;
					//////////////////////////////////////////////////////////////////////////
					
					//send message
					::PostMessage(hCommWnd, WM_COMM_READ, 0, 0 );//인터페이스 담당하는 Dlg에 메시지를 보냄	

					//fulled buffer size set to zero
					secondByte=0;
					result="";
				}	
			}else
				result="";

		}else{
			//no continuous mode
			str.Format("%02x ", aByte);
			result += str;
		}
	}
	
	//if continuous mode is not, message send always.
	if(mode ==0)
	{		
		oneResult=result;
		::PostMessage(hCommWnd, WM_COMM_READ, 0, 0 );//인터페이스 담당하는 Dlg에 메시지를 보냄	
		result="";
	}	
}

void CSenSor_SICK::Set0_100_1_Resolution()
{
	resolution=202;	
	sub = 1;
	gap = 50;
	unsigned char Fwd[] = {0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x64,0x00,0x1D,0x0F};
	int d=m_ComuPort.WriteComm( Fwd, 11);
}

void CSenSor_SICK::Set0_100_05_Resolution()
{
	resolution=402;	
	sub = 0.5;
	gap = 50;
	unsigned char Fwd[] = {0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x32,0x00,0xB1,0x59};
	int d=m_ComuPort.WriteComm( Fwd, 11);
}

void CSenSor_SICK::Set0_100_025_Resolution()
{
	resolution=802;
	sub = 0.25;
	gap = 50;
	unsigned char Fwd[] = {0x02,0x00,0x05,0x00,0x3B,0x64,0x00,0x19,0x00,0xE7,0x72};
	int d=m_ComuPort.WriteComm( Fwd, 11);
}

void CSenSor_SICK::Set0_180_1_Resolution()
{
	resolution=362;
	sub = 1;
	gap = 0;
	unsigned char Fwd[] = {0x02,0x00,0x05,0x00,0x3B,0xB4,0x00,0x64,0x00,0x97,0x49};
	int d=m_ComuPort.WriteComm( Fwd, 11);
}

void CSenSor_SICK::Set0_180_05_Resolution()
{
	resolution=722;
	sub = 0.5;
	gap = 0;
	unsigned char Fwd[] = {0x02,0x00,0x05,0x00,0x3B,0xB4,0x00,0x32,0x00,0x3B,0x1F};
	int d=m_ComuPort.WriteComm( Fwd, 11);
}

void CSenSor_SICK::SetModeMM()
{	
	unsigned char Fwd2[] = {0x02,0x00,0x21,0x00,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00
		                   ,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
						   ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFC,0x7E};
	int d=m_ComuPort.WriteComm( Fwd2, 39);
}

void CSenSor_SICK::SetModeCM()
{	
	unsigned char Fwd2[] = {0x02,0x00,0x21,0x00,0x77,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		                   ,0x00,0x02,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00     
						   ,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xE8,0x72};
	int d2=m_ComuPort.WriteComm( Fwd2, 39);
}

void CSenSor_SICK::StartContinuous()
{
	mode=1;
	first10byte=0;
	secondByte=0;
	unsigned char Fwd[] = {0x02,0x00,0x02,0x00,0x20,0x24,0x34,0x08};
	int d=m_ComuPort.WriteComm( Fwd, 8);
}

void CSenSor_SICK::StopContinuous()
{
	mode=0;
	unsigned char Fwd[] = {0x02,0x00,0x02,0x00,0x20,0x25,0x35,0x08};
	int d=m_ComuPort.WriteComm( Fwd, 8);
}

void CSenSor_SICK::SetMode()
{
	unsigned char Fwd[] = {0x02,0x00,0x0A,0x00,0x20,0x00,0x53,0x49,0x43,0x4B,0x5F,0x4C,0x4D,0x53,0xBE,0xC5};
	int d=m_ComuPort.WriteComm( Fwd, 16);
}
