#pragma once


// CSendDlg 对话框

class CSendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendDlg)

public:
	CSendDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSendDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:

	CString m_note_str;
	void OnEnChangeEdit_Note();
	afx_msg void OnBnClickedButton_Send();
	CString m_loop_str;
	CString m_tester_str;
	CString m_hours_str;
	afx_msg void OnBnClickedRadio_Pass();
	afx_msg void OnBnClickedRadio_Fail();
	afx_msg void OnEnChangeEdit_Loop();
	afx_msg void OnEnChangeEdit_Tester();
	afx_msg void OnEnChangeEdit_Hours();
};
