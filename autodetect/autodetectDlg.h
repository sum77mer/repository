
// autodetectDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include"DetectDlg.h"
#include"SendDlg.h"


// CautodetectDlg �Ի���
class CautodetectDlg : public CDialogEx
{
// ����
public:
	CautodetectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AUTODETECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
