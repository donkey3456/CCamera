// VideoStatic.cpp : �����n
//

#include "stdafx.h"
#include "VideoStatic.h"
#include "define.h"
#include "Camera.h"

// CVideoStatic

IMPLEMENT_DYNAMIC(CVideoStatic, CStatic)

CVideoStatic::CVideoStatic()
{
	InitializeCriticalSection(&m_csProtection);
	m_nFactor = 1;
	m_nXshift = 0;
	m_nYshift = 0;

}

CVideoStatic::~CVideoStatic()
{
	DeleteCriticalSection(&m_csProtection);
}


BEGIN_MESSAGE_MAP(CVideoStatic, CStatic)
	ON_WM_PAINT()
	ON_MESSAGE(MSG_CAMERA_NOTIFY, OnCamera)
//	ON_WM_MOUSEMOVE()
//	ON_WM_LBUTTONDOWN()
//	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

void CVideoStatic::imShow( cv::Mat mat )
{
	EnterCriticalSection(&m_csProtection);
	m_bmpBuffer.CopyFromMat(mat);
	LeaveCriticalSection(&m_csProtection);
	Invalidate(FALSE);
}



// CVideoStatic ӍϢ̎��ʽ

void CVideoStatic::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˼�������ӍϢ̎��ʽ��ʽ�a
	// ��Ҫ���ЈDƬӍϢ�� CStatic::OnPaint()
	CRect rectWindowSize;
	GetWindowRect(&rectWindowSize);

	if (!m_bmpBuffer.IsEmpty())
	{
		EnterCriticalSection(&m_csProtection);
		m_bmpDraw.CopyFromBitMap(m_bmpBuffer);
		LeaveCriticalSection(&m_csProtection);

		//˫����
		CDC dcMem;
		//draw Bitmap
		CBitmap bmp; 

		bmp.CreateCompatibleBitmap(&dc,rectWindowSize.Width(),rectWindowSize.Height());
		dcMem.CreateCompatibleDC(&dc);
		dcMem.SelectObject(&bmp);
		m_bmpDraw.Draw(dcMem.GetSafeHdc(),rectWindowSize,m_nFactor,m_nXshift,m_nYshift);
		bmp.DeleteObject();	

		//output to the screen
		dc.BitBlt(0,0,rectWindowSize.Width(),rectWindowSize.Height(), &dcMem,0,0,SRCCOPY);
		dcMem.DeleteDC();
			
	}
	else
	{
		m_bmpDraw.Release();
		//draw black background
		CRect rect(0,0,rectWindowSize.Width(),rectWindowSize.Height());
		CBrush brush;
		brush.CreateSolidBrush(RGB(0,0,0));
		CBrush* pOldObject;
		pOldObject = dc.SelectObject(&brush);
		dc.Rectangle(&rect);
		dc.SelectObject(pOldObject);
	}

}

void CVideoStatic::clean()
{
	EnterCriticalSection(&m_csProtection);
	m_bmpBuffer.Release();
	LeaveCriticalSection(&m_csProtection);
}

LRESULT CVideoStatic::OnCamera( WPARAM wParam, LPARAM lParam )
{
	CCamera* pCam = CCamera::GetInstance();
	imShow(pCam->GetImage());
	return 0;
}
