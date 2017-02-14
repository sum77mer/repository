// SendDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "autodetect.h"
#include "SendDlg.h"
#include "afxdialogex.h"


// CSendDlg 对话框

IMPLEMENT_DYNAMIC(CSendDlg, CDialogEx)

CSendDlg::CSendDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SEND, pParent)
	, m_note_str(_T(""))
	, m_loop_str(_T(""))
	, m_tester_str(_T(""))
	, m_hours_str(_T(""))
{

}

CSendDlg::~CSendDlg()
{
}

void CSendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_note_str);
	DDX_Text(pDX, IDC_EDIT4, m_loop_str);
	DDX_Text(pDX, IDC_EDIT3, m_tester_str);
	DDX_Text(pDX, IDC_EDIT5, m_hours_str);
}


BEGIN_MESSAGE_MAP(CSendDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CSendDlg::OnEnChangeEdit_Note)
	ON_BN_CLICKED(IDC_BUTTON2, &CSendDlg::OnBnClickedButton_Send)
	ON_BN_CLICKED(IDC_RADIO1, &CSendDlg::OnBnClickedRadio_Pass)
	ON_BN_CLICKED(IDC_RADIO2, &CSendDlg::OnBnClickedRadio_Fail)
	ON_EN_CHANGE(IDC_EDIT4, &CSendDlg::OnEnChangeEdit_Loop)
	ON_EN_CHANGE(IDC_EDIT3, &CSendDlg::OnEnChangeEdit_Tester)
	ON_EN_CHANGE(IDC_EDIT5, &CSendDlg::OnEnChangeEdit_Hours)
END_MESSAGE_MAP()
BOOL CSendDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CheckDlgButton(IDC_RADIO1, 1);
	OnBnClickedRadio_Pass();
	return true;
}


// CSendDlg 消息处理程序


void CSendDlg::OnEnChangeEdit_Note()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}


void CSendDlg::OnBnClickedButton_Send()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSendDlg::OnBnClickedRadio_Pass()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSendDlg::OnBnClickedRadio_Fail()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSendDlg::OnEnChangeEdit_Loop()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}


void CSendDlg::OnEnChangeEdit_Tester()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}


void CSendDlg::OnEnChangeEdit_Hours()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);
}
