
// CameraTest.h : PROJECT_NAME ���ó�ʽ����Ҫ���^�n
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �����˙n��ǰ�Ȱ��� 'stdafx.h'"
#endif

#include "resource.h"		// ��Ҫ��̖


// CCameraTestApp:
// Ո��醌�����e�� CameraTest.cpp
//

class CCameraTestApp : public CWinApp
{
public:
	CCameraTestApp();

// ����
public:
	virtual BOOL InitInstance();

// ��ʽ�a����

	DECLARE_MESSAGE_MAP()
};

extern CCameraTestApp theApp;