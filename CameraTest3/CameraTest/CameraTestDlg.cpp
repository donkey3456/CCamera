
// CameraTestDlg.cpp : �����n
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


// �� App About ʹ�� CAboutDlg ��Ԓ���K

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��Ԓ���K�Y��
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧Ԯ

// ��ʽ�a����
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


// CCameraTestDlg ��Ԓ���K




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


// CCameraTestDlg ӍϢ̎��ʽ

BOOL CCameraTestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �� [�P�...] ���ܱ����ϵ�y���ܱ�

	// IDM_ABOUTBOX �����ϵ�y�����֮�С�
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

	// �O���ˌ�Ԓ���K�ĈDʾ�������ó�ʽ����ҕ�����ǌ�Ԓ���K�r��
	// ��ܕ��Ԅӏ��´����I
	SetIcon(m_hIcon, TRUE);			// �O����Dʾ
	SetIcon(m_hIcon, FALSE);		// �O��С�Dʾ

	// TODO: �ڴ˼����~��ĳ�ʼ�O��
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(FALSE);

	return TRUE;  // ���� TRUE����������������O�����c
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

// �������С�����o�������Č�Ԓ���K������Ҫ���еĳ�ʽ�a��
// �Ա��L�u�Dʾ�����ʹ���ļ�/�zҕģʽ�� MFC ���ó�ʽ��
// ��ܕ��Ԅ���ɴ����I��

void CCameraTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �L�u���b�Ã���

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ���Dʾ������Ñ��˾���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ���L�Dʾ
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ʹ������ҷ��С��ҕ���r��
// ϵ�y�����@������ȡ���Θ��@ʾ��
HCURSOR CCameraTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCameraTestDlg::OnBnClickedBtnConnect()
{
	// TODO: �ڴ˼������헸�֪̎��ʽ��ʽ�a

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
	// TODO: �ڴ˼������헸�֪̎��ʽ��ʽ�a
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
	// TODO: �ڴ˼�������ӍϢ̎��ʽ��ʽ�a�� (��) �����A�Oֵ
	CCamera* pCam = CCamera::GetInstance();
	pCam->Release();
	CDialogEx::OnClose();
}


void CCameraTestDlg::OnBnClickedBtnOpen()
{
	// TODO: �ڴ˼������헸�֪̎��ʽ��ʽ�a
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
	// TODO: �ڴ˼������헸�֪̎��ʽ��ʽ�a
	GetDlgItem(IDC_BTN_DISCONNECT)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->DeleteOutputWnd(m_ctrlVideo.GetSafeHwnd());
	GetDlgItem(IDC_BTN_CONNECT)->EnableWindow(TRUE);
}


void CCameraTestDlg::OnBnClickedBtnConnect2()
{
	// TODO: �ڴ˼������헸�֪̎��ʽ��ʽ�a
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->AddOutputWnd(m_ctrlVideo2.GetSafeHwnd(),MSG_CAMERA_NOTIFY);
	pCam->EnableNotifyMsg(m_ctrlVideo2.GetSafeHwnd(),TRUE);
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(TRUE);
}


void CCameraTestDlg::OnBnClickedBtnDisconnect2()
{
	// TODO: �ڴ˼������헸�֪̎��ʽ��ʽ�a
	GetDlgItem(IDC_BTN_DISCONNECT2)->EnableWindow(FALSE);
	CCamera* pCam = CCamera::GetInstance();
	pCam->DeleteOutputWnd(m_ctrlVideo2.GetSafeHwnd());
	GetDlgItem(IDC_BTN_CONNECT2)->EnableWindow(TRUE);
}
