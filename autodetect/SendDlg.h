#pragma once


// CSendDlg �Ի���

class CSendDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSendDlg)

public:
	CSendDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSendDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SEND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
