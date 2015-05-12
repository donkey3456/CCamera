
// CameraTestDlg.h : ���^�n
//

#pragma once

#include "VideoStatic.h"
#include "Camera.h"
// CCameraTestDlg ��Ԓ���K
class CCameraTestDlg : public CDialogEx
{
// ����
public:
	CCameraTestDlg(CWnd* pParent = NULL);	// �˜ʽ�����ʽ

// ��Ԓ���K�Y��
	enum { IDD = IDD_CAMERATEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧Ԯ


// ��ʽ�a����
protected:
	HICON m_hIcon;

	// �a����ӍϢ������ʽ
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnCamera(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnConnect();
	CVideoStatic m_ctrlVideo;
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnClose();
//	afx_msg void OnStnClickedVideo2();
//	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnDisconnect();
	afx_msg void OnBnClickedBtnConnect2();
	CVideoStatic m_ctrlVideo2;
	afx_msg void OnBnClickedBtnDisconnect2();
};
