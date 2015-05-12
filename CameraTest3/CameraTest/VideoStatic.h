#pragma once
#include <opencv2\opencv.hpp>

// CVideoStatic
#include "MyBitmap.h"
class CVideoStatic : public CStatic
{
	DECLARE_DYNAMIC(CVideoStatic)

public:
	CVideoStatic();
	virtual ~CVideoStatic();

	void imShow(cv::Mat mat);

	void clean();
protected:
	afx_msg LRESULT OnCamera(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
	
protected:
	CMyBitmap m_bmpDraw;
	CMyBitmap m_bmpBuffer;
	CRITICAL_SECTION m_csProtection;
	int m_nFactor;
	int m_nXshift;
	int m_nYshift;

public:
	afx_msg void OnPaint();
};


