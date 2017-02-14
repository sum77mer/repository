
// autodetectDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"DetectDlg.h"
#include"SendDlg.h"


// CautodetectDlg 对话框
class CautodetectDlg : public CDialogEx
{
// 构造
public:
	CautodetectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTODETECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CTabCtrl m_tab;
	CDetectDlg m_DetectDlg;
	CSendDlg m_SendDlg;
	afx_msg void OnTcnSelchangeTab2(NMHDR *pNMHDR, LRESULT *pResult);
};
