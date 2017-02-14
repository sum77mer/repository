#pragma once
#include "afxwin.h"


// CDetectDlg 对话框

class CDetectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDetectDlg)

public:
	CDetectDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDetectDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_check_memory;
	CButton m_check_graphics;
	CButton m_check_pci;
	CButton m_check_sata;
	CButton m_check_usb;
	CButton m_check_network;
	CButton m_check_BIOS;
	CButton m_check_OS;
	CString m_result_str;
public:
	BOOL detect_flag;
	BOOL edit_flag;
	CString str_detect_result;
	CString str_log;
public:
	void InitAllCheckBoxStatus();
	void DisableAllCheckBoxStatus();
	void EnableAllCheckBoxStatus();
	void OnBnClickedButton_Detect();
	afx_msg void OnBnClickedButton_Save();
	afx_msg void OnBnClickedButton_Open();
	afx_msg void OnEnChangeEdit_result();
	unsigned int m_addr1_bus;
	unsigned int m_addr1_dev;
	unsigned int m_addr1_fun;
	unsigned int m_addr2_bus;
	unsigned int m_addr2_dev;
	unsigned int m_addr2_fun;
	unsigned int m_addr3_bus;
	unsigned int m_addr3_dev;
	unsigned int m_addr3_fun;
	unsigned int m_addr4_bus;
	unsigned int m_addr4_dev;
	unsigned int m_addr4_fun;
	unsigned int m_addr5_bus;
	unsigned int m_addr5_dev;
	unsigned int m_addr5_fun;
	unsigned int m_addr6_bus;
	unsigned int m_addr6_dev;
	unsigned int m_addr6_fun;
	afx_msg void OnBnClickedButton_PCIaddr();

	BOOL flag_addr_manual;
};
