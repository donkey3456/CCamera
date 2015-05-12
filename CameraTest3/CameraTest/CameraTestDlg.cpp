
// CameraTestDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "CameraTest.h"
#include "CameraTestDlg.h"
#include "afxdialogex.h"
#include "Camera.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCameraTestDlg 對話方塊




CCameraTestDlg::CCameraTestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCameraTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCameraTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDEO, m_ctrlVideo);
	DDX_Control(pDX, IDC_VIDEO2, m_ctrlVideo2);
}

BEGIN_MESSAGE_MAP(CCameraTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(MSG_CAMERA_NOTIFY, OnCamera)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CCameraTestDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_STOP, &CCameraTestDlg::OnBnClickedBtnStop)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_OPEN, &CCameraTestDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CCameraTestDlg::OnBnClickedBtnDisconnect)
	ON_BN_CLICKED(IDC_BTN_CONNECT2, &CCameraTestDlg::OnBnClickedBtnConnect2)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT2, &CCameraTestDlg::OnBnClickedBtnDisconnect2)
END_MESSAGE_MAP()


// CCameraTestDlg 訊息處理常式

BOOL CCameraTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(FALSE);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CCameraTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CCameraTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CCameraTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCameraTestDlg::OnBnClickedBtnConnect()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->AddOutputWnd(m_ctrlVideo.GetSafeHwnd(),MSG_CAMERA_NOTIFY);
	pCam->EnableNotifyMsg(m_ctrlVideo.GetSafeHwnd(),TRUE);
	pCam->AutoExpoEnable(TRUE);
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(TRUE);

}

LRESULT CCameraTestDlg::OnCamera(WPARAM wParam,LPARAM lParam){
	CCamera* pCam = CCamera::GetInstance();
	m_ctrlVideo.imShow(pCam->GetImage());
	return 0;
}

void CCameraTestDlg::OnBnClickedBtnStop()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->close();
	GetDlgItem(IDC_BTN_OPEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(FALSE);
}


void CCameraTestDlg::OnClose()
{
	// TODO: 在此加入您的訊息處理常式程式碼和 (或) 呼叫預設值
	CCamera* pCam = CCamera::GetInstance();
	pCam->Release();
	CDialogEx::OnClose();
}


void CCameraTestDlg::OnBnClickedBtnOpen()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	GetDlgItem(IDC_BTN_OPEN)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();

	if (!pCam->Open())
	{
		//message box later
		GetDlgItem(IDC_BTN_OPEN)->EnableWindow(TRUE);
		
	}
	else
	{
		pCam->AutoExpoEnable(TRUE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(TRUE);
	}
	
}


void CCameraTestDlg::OnBnClickedBtnDisconnect()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->DeleteOutputWnd(m_ctrlVideo.GetSafeHwnd());
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
}


void CCameraTestDlg::OnBnClickedBtnConnect2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->AddOutputWnd(m_ctrlVideo2.GetSafeHwnd(),MSG_CAMERA_NOTIFY);
	pCam->EnableNotifyMsg(m_ctrlVideo2.GetSafeHwnd(),TRUE);
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(TRUE);
}


void CCameraTestDlg::OnBnClickedBtnDisconnect2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->DeleteOutputWnd(m_ctrlVideo2.GetSafeHwnd());
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(TRUE);
}
