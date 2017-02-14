
// autodetectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "autodetect.h"
#include "autodetectDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CautodetectDlg �Ի���





CautodetectDlg::CautodetectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_AUTODETECT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CautodetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB2, m_tab);
}

BEGIN_MESSAGE_MAP(CautodetectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB2, &CautodetectDlg::OnTcnSelchangeTab2)
END_MESSAGE_MAP()


// CautodetectDlg ��Ϣ�������

BOOL CautodetectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	CRect tabRect;   // ��ǩ�ؼ��ͻ�����λ�úʹ�С   

	m_tab.InsertItem(0, _T("Detect"));         // �����һ����ǩ�������ס�   
	m_tab.InsertItem(1, _T("Send"));  // ����ڶ�����ǩ��Android��������   
	m_DetectDlg.Create(IDD_DIALOG_DETECT, &m_tab);    // ������һ����ǩҳ   
	m_SendDlg.Create(IDD_DIALOG_SEND, &m_tab); // �����ڶ�����ǩҳ   

	m_tab.GetClientRect(&tabRect);    // ��ȡ��ǩ�ؼ��ͻ���Rect   
									  // ����tabRect��ʹ�串�Ƿ�Χ�ʺϷ��ñ�ǩҳ   
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;
	// ���ݵ����õ�tabRect����m_jzmDlg�ӶԻ��򣬲�����Ϊ��ʾ   
	m_DetectDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
	// ���ݵ����õ�tabRect����m_androidDlg�ӶԻ��򣬲�����Ϊ����   
	m_SendDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CautodetectDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CautodetectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CautodetectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CautodetectDlg::OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	CRect tabRect;    // ��ǩ�ؼ��ͻ�����Rect   

					  // ��ȡ��ǩ�ؼ��ͻ���Rect����������������ʺϷ��ñ�ǩҳ   
	m_tab.GetClientRect(&tabRect);
	tabRect.left += 1;
	tabRect.right -= 1;
	tabRect.top += 25;
	tabRect.bottom -= 1;

	switch (m_tab.GetCurSel())
	{
		// �����ǩ�ؼ���ǰѡ���ǩΪ�������ס�������ʾm_jzmDlg�Ի�������m_androidDlg�Ի���   
	case 0:
		m_DetectDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		m_SendDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		break;
		// �����ǩ�ؼ���ǰѡ���ǩΪ��Android����������������m_jzmDlg�Ի�����ʾm_androidDlg�Ի���   
	case 1:
		m_DetectDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_HIDEWINDOW);
		m_SendDlg.SetWindowPos(NULL, tabRect.left, tabRect.top, tabRect.Width(), tabRect.Height(), SWP_SHOWWINDOW);
		break;
	default:
		break;
	}
}
