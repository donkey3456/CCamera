
// CameraTestDlg.h : 標頭檔
//

#pragma once

#include "VideoStatic.h"
#include "Camera.h"
// CCameraTestDlg 對話方塊
class CCameraTestDlg : public CDialogEx
{
// 建構
public:
	CCameraTestDlg(CWnd* pParent = NULL);	// 標準建構函式

// 對話方塊資料
	enum { IDD = IDD_CAMERATEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
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
