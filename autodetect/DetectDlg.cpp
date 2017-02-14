// DetectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "autodetect.h"
#include "DetectDlg.h"
#include "afxdialogex.h"
#include"GetSysInfo.h"
#include"PCI.h"
#include<vector>
using std::vector;


// CDetectDlg 对话框

IMPLEMENT_DYNAMIC(CDetectDlg, CDialogEx)

CDetectDlg::CDetectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DETECT, pParent)
	, m_result_str(_T(""))
	, m_addr1_bus(0)
	, m_addr1_dev(0)
	, m_addr1_fun(0)
	, m_addr2_bus(0)
	, m_addr2_dev(0)
	, m_addr2_fun(0)
	, m_addr3_bus(0)
	, m_addr3_dev(0)
	, m_addr3_fun(0)
	, m_addr4_bus(0)
	, m_addr4_dev(0)
	, m_addr4_fun(0)
	, m_addr5_bus(0)
	, m_addr5_dev(0)
	, m_addr5_fun(0)
	, m_addr6_bus(0)
	, m_addr6_dev(0)
	, m_addr6_fun(0)
{

}

CDetectDlg::~CDetectDlg()
{
}

void CDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	HKEY key;
	LONG lreturn;
	DWORD bus_temp=0, dev_temp=0, fun_temp=0;
	DWORD size = 0, type = 0;
	lreturn = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Wow6432Node\\Autodetect"), 0, KEY_READ, &key);
	if (lreturn == ERROR_SUCCESS)
	{
		size = 512;
		lreturn=RegQueryValueEx(key, TEXT("Addr1_bus"), 0, &type, (LPBYTE)&bus_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr1_bus= bus_temp;
		size = 512;
		lreturn = RegQueryValueEx(key,TEXT("Addr1_dev"),0,&type,(LPBYTE)&dev_temp,&size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr1_dev= dev_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr1_fun"), 0, &type, (LPBYTE)&fun_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr1_fun= fun_temp;

		//addr2
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr2_bus"), 0, &type, (LPBYTE)&bus_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr2_bus= bus_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr2_dev"), 0, &type, (LPBYTE)&dev_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr2_dev=dev_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr2_fun"), 0, &type, (LPBYTE)&fun_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr2_fun= fun_temp;
		//addr3
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr3_bus"), 0, &type, (LPBYTE)&bus_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr3_bus= bus_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr3_dev"), 0, &type, (LPBYTE)&dev_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr3_dev= dev_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr3_fun"), 0, &type, (LPBYTE)&fun_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr3_fun= fun_temp;
		//addr4
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr4_bus"), 0, &type, (LPBYTE)&bus_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr4_bus=bus_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr4_dev"), 0, &type, (LPBYTE)&dev_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr4_dev= dev_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr4_fun"), 0, &type, (LPBYTE)&fun_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr4_fun= fun_temp;
		//addr5
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr5_bus"), 0, &type, (LPBYTE)&bus_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr5_bus= bus_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr5_dev"), 0, &type, (LPBYTE)&dev_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr5_dev=dev_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr5_fun"), 0, &type, (LPBYTE)&fun_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr5_fun= fun_temp;
		//addr6
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr6_bus"), 0, &type, (LPBYTE)&bus_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr6_bus= bus_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr6_dev"), 0, &type, (LPBYTE)&dev_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr6_dev=dev_temp;
		size = 512;
		lreturn = RegQueryValueEx(key, TEXT("Addr6_fun"), 0, &type, (LPBYTE)&fun_temp, &size);
		if (lreturn != ERROR_SUCCESS)
			AfxMessageBox(_T("query fail!"));
		m_addr6_fun=fun_temp;
		
		RegCloseKey(key);
	}
	else
		AfxMessageBox(_T("open registry fail"));
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK1, m_check_memory);
	DDX_Control(pDX, IDC_CHECK2, m_check_graphics);
	DDX_Control(pDX, IDC_CHECK3, m_check_pci);
	DDX_Control(pDX, IDC_CHECK4, m_check_sata);
	DDX_Control(pDX, IDC_CHECK5, m_check_usb);
	DDX_Control(pDX, IDC_CHECK6, m_check_network);
	DDX_Control(pDX, IDC_CHECK7, m_check_BIOS);
	DDX_Control(pDX, IDC_CHECK8, m_check_OS);
	DDX_Text(pDX, IDC_EDIT6, m_result_str);
	DDX_Text(pDX, IDC_EDIT1, m_addr1_bus);
	DDX_Text(pDX, IDC_EDIT8, m_addr1_dev);
	DDX_Text(pDX, IDC_EDIT9, m_addr1_fun);
	DDX_Text(pDX, IDC_EDIT2, m_addr2_bus);
	DDX_Text(pDX, IDC_EDIT10, m_addr2_dev);
	DDX_Text(pDX, IDC_EDIT11, m_addr2_fun);
	DDX_Text(pDX, IDC_EDIT3, m_addr3_bus);
	DDX_Text(pDX, IDC_EDIT12, m_addr3_dev);
	DDX_Text(pDX, IDC_EDIT13, m_addr3_fun);
	DDX_Text(pDX, IDC_EDIT4, m_addr4_bus);
	DDX_Text(pDX, IDC_EDIT14, m_addr4_dev);
	DDX_Text(pDX, IDC_EDIT15, m_addr4_fun);
	DDX_Text(pDX, IDC_EDIT5, m_addr5_bus);
	DDX_Text(pDX, IDC_EDIT16, m_addr5_dev);
	DDX_Text(pDX, IDC_EDIT17, m_addr5_fun);
	DDX_Text(pDX, IDC_EDIT7, m_addr6_bus);
	DDX_Text(pDX, IDC_EDIT18, m_addr6_dev);
	DDX_Text(pDX, IDC_EDIT19, m_addr6_fun);
}

void CDetectDlg::InitAllCheckBoxStatus()
{
	// 只选中 PCI 和 BIOS   
	m_check_memory.SetCheck(0);
	m_check_graphics.SetCheck(0);
	m_check_pci.SetCheck(1);
	m_check_sata.SetCheck(0);
	m_check_usb.SetCheck(0);
	m_check_network.SetCheck(0);
	m_check_BIOS.SetCheck(1);
}

void CDetectDlg::DisableAllCheckBoxStatus()
{
	m_check_BIOS.EnableWindow(FALSE);
	m_check_memory.EnableWindow(FALSE);
	m_check_graphics.EnableWindow(FALSE);
	m_check_pci.EnableWindow(FALSE);
	m_check_sata.EnableWindow(FALSE);
	m_check_usb.EnableWindow(FALSE);
	m_check_network.EnableWindow(FALSE);
	m_check_OS.EnableWindow(FALSE);
}

void CDetectDlg::EnableAllCheckBoxStatus()
{
	m_check_BIOS.EnableWindow(TRUE);
	m_check_memory.EnableWindow(TRUE);
	m_check_graphics.EnableWindow(TRUE);
	m_check_pci.EnableWindow(TRUE);
	m_check_sata.EnableWindow(TRUE);
	m_check_usb.EnableWindow(TRUE);
	m_check_network.EnableWindow(TRUE);
	m_check_OS.EnableWindow(TRUE);
}


BEGIN_MESSAGE_MAP(CDetectDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDetectDlg::OnBnClickedButton_Detect)
	ON_BN_CLICKED(IDC_BUTTON3, &CDetectDlg::OnBnClickedButton_Save)
	ON_BN_CLICKED(IDC_BUTTON4, &CDetectDlg::OnBnClickedButton_Open)
	ON_EN_CHANGE(IDC_EDIT6, &CDetectDlg::OnEnChangeEdit_result)
	ON_BN_CLICKED(IDC_BUTTON2, &CDetectDlg::OnBnClickedButton_PCIaddr)
END_MESSAGE_MAP()


// CDetectDlg 消息处理程序
BOOL CDetectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	InitAllCheckBoxStatus();
	
	return true;
}


void CDetectDlg::OnBnClickedButton_Detect()
{
	// TODO: 在此添加控件通知处理程序代码
	GetSysInfo f_getsysinfo;
	CString write_to_file1;
	CString str_temp1;
	CStdioFile file;
	CTime curtime = CTime::GetCurrentTime();
	CString time_str = curtime.Format(_T("#%Y-%m-%d						%H:%M:%S#\r\n"));
	CString write_to_file_pci;
	CString str_temp_pci;
	BOOL item_check;
	item_check = m_check_BIOS.GetCheck() || m_check_memory.GetCheck() || m_check_graphics.GetCheck() || m_check_pci.GetCheck() || m_check_sata.GetCheck() || m_check_usb.GetCheck() || m_check_network.GetCheck();
	if (item_check == 0)
		AfxMessageBox(_T("Please choose at least one item to detect!"));
	DisableAllCheckBoxStatus();
	if (1 == m_check_BIOS.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		f_getsysinfo.GetBIOSInfo(f_getsysinfo.BIOS_vendor, f_getsysinfo.board, f_getsysinfo.BIOS_version);
		write_to_file1 += f_getsysinfo.BIOS_vendor;
		write_to_file1 += " ";
		write_to_file1 += f_getsysinfo.board;
		write_to_file1 += " ";
		write_to_file1 += f_getsysinfo.BIOS_version;
		write_to_file1 += "\r\n";
	}
	if (1 == m_check_memory.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		f_getsysinfo.GetMemoryInfo(f_getsysinfo.phys_memory_str, f_getsysinfo.vir_memory_str);
		write_to_file1 += f_getsysinfo.phys_memory_str;
		write_to_file1 += "\r\n";
		write_to_file1 += f_getsysinfo.vir_memory_str;
		write_to_file1 += "\r\n";
	}
	if (1 == m_check_graphics.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		f_getsysinfo.GetDisplayCardInfo(f_getsysinfo.dis_card_num, f_getsysinfo.dis_card_str);
		str_temp1.Format(_T("Graphyics Card Num: %d\r\n"), f_getsysinfo.dis_card_num);
		write_to_file1 += str_temp1;
		write_to_file1 += f_getsysinfo.dis_card_str[0];
		write_to_file1 += "\r\n";

	}
	if (1 == m_check_pci.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		PCI pci_device;
		unsigned int device_number = 0, return_temp = 0;
		if (flag_addr_manual == 1)
		{
			vector <unsigned int> addr;
			unsigned int addr_temp[6];
			addr_temp[0] = 0x80000000 + (m_addr1_bus << 16) + (m_addr1_dev << 11) + (m_addr1_fun << 8);
			addr_temp[1] = 0x80000000 + (m_addr2_bus << 16) + (m_addr2_dev << 11) + (m_addr2_fun << 8);
			addr_temp[2] = 0x80000000 + (m_addr3_bus << 16) + (m_addr3_dev << 11) + (m_addr3_fun << 8);
			addr_temp[3] = 0x80000000 + (m_addr4_bus << 16) + (m_addr4_dev << 11) + (m_addr4_fun << 8);
			addr_temp[4] = 0x80000000 + (m_addr5_bus << 16) + (m_addr5_dev << 11) + (m_addr5_fun << 8);
			addr_temp[5] = 0x80000000 + (m_addr6_bus << 16) + (m_addr6_dev << 11) + (m_addr6_fun << 8);
			for (auto i : addr)
				addr.push_back(addr_temp[i]);
			//addr.push_back(addr_temp[0]);
			//addr.push_back(addr_temp[1]);
			//addr.push_back(addr_temp[2]);
			//addr.push_back(addr_temp[3]);
			//addr.push_back(addr_temp[4]);
			//addr.push_back(addr_temp[5]);
			pci_device.scan_dev(pci_device.pci_cfg_short, addr);
			return_temp = pci_device.pci_parser(pci_device.pci_cfg_short, pci_device.pci_info);
			auto size = pci_device.pci_cfg_short.size();
			for (unsigned int i = 0; i < size; i++)
			{
				str_temp_pci.Format(_T("%lx:"), pci_device.pci_cfg_short[i].addr);
				write_to_file_pci += str_temp_pci;
				write_to_file_pci += pci_device.pci_info[i].name_string;
				write_to_file_pci += "\r\n";
				//此部分代码功能是输出pci配置空间到文件
				// write_to_file_pci += "Config Space:\r\n";
				//for (unsigned int j = 0; j < 256; j++)
				//{
				//	str_temp_pci.Format(_T("%02x  "), pci_device.pci_cfg[i].cfg_space_byte[j]);
				//	 write_to_file_pci += str_temp_pci;
				//	if (((j + 1) % 16) == 0)
				//	{
				//		 write_to_file_pci += "\r\n";
				//	}
				//}
				// write_to_file_pci += "\r\n--------------------------------------------------------------\r\n";
			}
		}
		else
		{
			device_number = pci_device.scan_dev(pci_device.pci_cfg);
			return_temp = pci_device.pci_parser(pci_device.pci_cfg, pci_device.pci_info);
			str_temp_pci.Format(_T(" %d\r\n"), device_number);
			write_to_file_pci += str_temp_pci;
			auto size = pci_device.pci_cfg.size();
			for (unsigned int i = 0; i < size; i++)
			{
				str_temp_pci.Format(_T("%lx:"), pci_device.pci_cfg[i].addr);
				write_to_file_pci += str_temp_pci;
				write_to_file_pci += pci_device.pci_info[i].name_string;
				write_to_file_pci += "\r\n";
				//此部分代码功能是输出pci配置空间到文件
				// write_to_file_pci += "Config Space:\r\n";
				//for (unsigned int j = 0; j < 256; j++)
				//{
				//	str_temp_pci.Format(_T("%02x  "), pci_device.pci_cfg[i].cfg_space_byte[j]);
				//	 write_to_file_pci += str_temp_pci;
				//	if (((j + 1) % 16) == 0)
				//	{
				//		 write_to_file_pci += "\r\n";
				//	}
				//}
				// write_to_file_pci += "\r\n--------------------------------------------------------------\r\n";
			}
		}
		
		
		
		
	}
	if (1 == m_check_sata.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		f_getsysinfo.GetDiskInfo(f_getsysinfo.disk_num, f_getsysinfo.disk_str, f_getsysinfo.physic_disk_num, f_getsysinfo.physic_disk_name);
		str_temp1.Format(_T("Disk Num: %d\r\n"), f_getsysinfo.disk_num);
		write_to_file1 += str_temp1;
		//for (decltype(f_getsysinfo.disk_num) i = 0; i<f_getsysinfo.disk_num; i++)
		//{
		//	write_to_file1 += f_getsysinfo.disk_str[i];
		//	write_to_file1 += "\r\n";
		//}
		//str_temp1.Format(_T("Physic Disk Num: %d\r\n"), f_getsysinfo.physic_disk_num);
		for (auto i : f_getsysinfo.physic_disk_name)
		{
			write_to_file1 += i;
			write_to_file1 += "\r\n";
		}
	}
	if (1 == m_check_usb.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		f_getsysinfo.GetUSBinfo(f_getsysinfo.USBname,f_getsysinfo.USBnum);
		write_to_file1 += f_getsysinfo.USBname;
		write_to_file1 += "\r\n";
	}
	if (1 == m_check_network.GetCheck())
	{
		write_to_file1 += "-----------------------------\r\n";
		f_getsysinfo.network_num = f_getsysinfo.GetInterFaceCount();
		str_temp1.Format(_T("Network Card Num: %d\r\n"), f_getsysinfo.network_num);
		write_to_file1 += str_temp1;
		for (unsigned int i = 0; i < f_getsysinfo.network_num; i++)
		{
			f_getsysinfo.GetInterFaceName(f_getsysinfo.network_str, i);
			write_to_file1 += f_getsysinfo.network_str;
			write_to_file1 += "\r\n";
		}
	}
	detect_flag = 1;
	EnableAllCheckBoxStatus();
	m_result_str = write_to_file_pci + write_to_file1;
	SetDlgItemText(IDC_EDIT6, m_result_str);
	if (file.Open(_T("c:\\auto_detect_log.txt"), CFile::modeCreate | CFile::modeWrite))
	{
		file.SeekToEnd();
		file.Write("#################################################################\r\n", sizeof("#################################################################\r\n") - 1);
		file.WriteString(time_str);
		file.Write("#################################################################\r\n", sizeof("#################################################################\r\n") - 1);
		file.WriteString(write_to_file_pci);
		file.Write("\r\n#################################################################\r\n", sizeof("\r\n#################################################################\r\n") - 1);
		file.WriteString(write_to_file1);
		file.Flush();
		file.Close();
	}
}


void CDetectDlg::OnBnClickedButton_Save()
{
	// TODO: 在此添加控件通知处理程序代码
	if (edit_flag != 1)
		AfxMessageBox(_T("You changed nothing!"));
	CStdioFile file;
	CTime curtime = CTime::GetCurrentTime();
	CString time_str = curtime.Format(_T("#%Y-%m-%d						%H:%M:%S#\r\n"));
	CString write_to_file_pci, write_to_file1;
	if (file.Open(_T("c:\\auto_detect_log.txt"), CFile::modeCreate | CFile::modeWrite))
	{
		file.SeekToEnd();
		file.WriteString(m_result_str);
		file.Flush();
		file.Close();
	}
}


void CDetectDlg::OnBnClickedButton_Open()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT6)->SetWindowText(_T(""));
	CString read_file_str;
	CStdioFile file;
	if (file.Open(_T("c:\\auto_detect_log.txt"), CFile::modeRead | CFile::modeNoTruncate))
	{
		while (NULL != file.ReadString(read_file_str))
		{
			m_result_str += read_file_str + _T("\r\n");
		}

		SetDlgItemText(IDC_EDIT6, m_result_str);
	}
	else
	{
		AfxMessageBox(_T("No such file!"));
	}
}


void CDetectDlg::OnEnChangeEdit_result()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	edit_flag = 1;
	UpdateData(true);
}



void CDetectDlg::OnBnClickedButton_PCIaddr()
{
	CString button_str;
	GetDlgItemText(IDC_BUTTON2,button_str);
	if (button_str == "Manual Address")
	{
		SetDlgItemText(IDC_BUTTON2, _T("Set New Address"));
	}
	else if (button_str == "Set New Address")
	{
		SetDlgItemText(IDC_BUTTON2,_T("Done"));
		GetDlgItem(IDC_EDIT1)->EnableWindow(true);
		GetDlgItem(IDC_EDIT2)->EnableWindow(true);
		GetDlgItem(IDC_EDIT3)->EnableWindow(true);
		GetDlgItem(IDC_EDIT4)->EnableWindow(true);
		GetDlgItem(IDC_EDIT5)->EnableWindow(true);
		GetDlgItem(IDC_EDIT7)->EnableWindow(true);
		GetDlgItem(IDC_EDIT8)->EnableWindow(true);
		GetDlgItem(IDC_EDIT9)->EnableWindow(true);
		GetDlgItem(IDC_EDIT10)->EnableWindow(true);
		GetDlgItem(IDC_EDIT11)->EnableWindow(true);
		GetDlgItem(IDC_EDIT12)->EnableWindow(true);
		GetDlgItem(IDC_EDIT13)->EnableWindow(true);
		GetDlgItem(IDC_EDIT14)->EnableWindow(true);
		GetDlgItem(IDC_EDIT15)->EnableWindow(true);
		GetDlgItem(IDC_EDIT16)->EnableWindow(true);
		GetDlgItem(IDC_EDIT17)->EnableWindow(true);
		GetDlgItem(IDC_EDIT18)->EnableWindow(true);
		GetDlgItem(IDC_EDIT19)->EnableWindow(true);
	}
	else if (button_str == "Done")
	{
		//抓取地址
		m_addr1_bus=GetDlgItemInt(IDC_EDIT1);
		m_addr1_dev=GetDlgItemInt(IDC_EDIT8);
		m_addr1_fun=GetDlgItemInt(IDC_EDIT9);
		m_addr2_bus=GetDlgItemInt(IDC_EDIT2);
		m_addr2_dev=GetDlgItemInt(IDC_EDIT10);
		m_addr2_fun=GetDlgItemInt(IDC_EDIT11);
		m_addr3_bus=GetDlgItemInt(IDC_EDIT3);
		m_addr3_dev=GetDlgItemInt(IDC_EDIT12);
		m_addr3_fun=GetDlgItemInt(IDC_EDIT13);
		m_addr4_bus=GetDlgItemInt(IDC_EDIT4);
		m_addr4_dev=GetDlgItemInt(IDC_EDIT14);
		m_addr4_fun=GetDlgItemInt(IDC_EDIT15);
		m_addr5_bus=GetDlgItemInt(IDC_EDIT5);
		m_addr5_dev=GetDlgItemInt(IDC_EDIT16);
		m_addr5_fun=GetDlgItemInt(IDC_EDIT17);
		m_addr6_bus=GetDlgItemInt(IDC_EDIT6);
		m_addr6_dev=GetDlgItemInt(IDC_EDIT18);
		m_addr6_fun=GetDlgItemInt(IDC_EDIT19);
		

		//disable编辑框
		GetDlgItem(IDC_EDIT1)->EnableWindow(false);
		GetDlgItem(IDC_EDIT2)->EnableWindow(false);
		GetDlgItem(IDC_EDIT3)->EnableWindow(false);
		GetDlgItem(IDC_EDIT4)->EnableWindow(false);
		GetDlgItem(IDC_EDIT5)->EnableWindow(false);
		GetDlgItem(IDC_EDIT7)->EnableWindow(false);
		GetDlgItem(IDC_EDIT8)->EnableWindow(false);
		GetDlgItem(IDC_EDIT9)->EnableWindow(false);
		GetDlgItem(IDC_EDIT10)->EnableWindow(false);
		GetDlgItem(IDC_EDIT11)->EnableWindow(false);
		GetDlgItem(IDC_EDIT12)->EnableWindow(false);
		GetDlgItem(IDC_EDIT13)->EnableWindow(false);
		GetDlgItem(IDC_EDIT14)->EnableWindow(false);
		GetDlgItem(IDC_EDIT15)->EnableWindow(false);
		GetDlgItem(IDC_EDIT16)->EnableWindow(false);
		GetDlgItem(IDC_EDIT17)->EnableWindow(false);
		GetDlgItem(IDC_EDIT18)->EnableWindow(false);
		GetDlgItem(IDC_EDIT19)->EnableWindow(false);
		//写注册表
		HKEY key;
		LONG lreturn;
		//将数据转换成整数类型
		unsigned int bus_temp = 0, dev_temp = 0, fun_temp = 0;
		
		if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Wow6432Node\\Autodetect"), 0, KEY_WRITE, &key) == ERROR_SUCCESS)
		{			
			AfxMessageBox(_T("open success"));
			//打开  写值
			bus_temp =  m_addr1_bus;
			dev_temp =  m_addr1_dev;
			fun_temp =  m_addr1_fun;
			RegSetValueEx(key, TEXT("Addr1_bus"),0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr1_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr1_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

			bus_temp =  m_addr2_bus;
			dev_temp =  m_addr2_dev;
			fun_temp =  m_addr2_fun;
			RegSetValueEx(key, TEXT("Addr2_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr2_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr2_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

			bus_temp =  m_addr3_bus;
			dev_temp =  m_addr3_dev;
			fun_temp =  m_addr3_fun;
			RegSetValueEx(key, TEXT("Addr3_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr3_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr3_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

			bus_temp =  m_addr4_bus;
			dev_temp =  m_addr4_dev;
			fun_temp =  m_addr4_fun;
			RegSetValueEx(key, TEXT("Addr4_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr4_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr4_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

			bus_temp =  m_addr5_bus;
			dev_temp =  m_addr5_dev;
			fun_temp =  m_addr5_fun;
			RegSetValueEx(key, TEXT("Addr5_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr5_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr5_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

			bus_temp =  m_addr6_bus;
			dev_temp =  m_addr6_dev;
			fun_temp =  m_addr6_fun;
			RegSetValueEx(key, TEXT("Addr6_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr6_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
			RegSetValueEx(key, TEXT("Addr6_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));
			
			
			RegCloseKey(key);
		}
		else
		{
			lreturn=RegCreateKey(HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Wow6432Node\\Autodetect"), &key);
			if (lreturn==ERROR_SUCCESS)
			{
				//创建  写值
				AfxMessageBox(_T("begin to create registry"));
				bus_temp =  m_addr1_bus;
				dev_temp =  m_addr1_dev;
				fun_temp =  m_addr1_fun;
				RegSetValueEx(key, TEXT("Addr1_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr1_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr1_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

				bus_temp =  m_addr2_bus;
				dev_temp =  m_addr2_dev;
				fun_temp =  m_addr2_fun;
				RegSetValueEx(key, TEXT("Addr2_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr2_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr2_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

				bus_temp =  m_addr3_bus;
				dev_temp =  m_addr3_dev;
				fun_temp =  m_addr3_fun;
				RegSetValueEx(key, TEXT("Addr3_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr3_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr3_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

				bus_temp =  m_addr4_bus;
				dev_temp =  m_addr4_dev;
				fun_temp =  m_addr4_fun;
				RegSetValueEx(key, TEXT("Addr4_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr4_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr4_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

				bus_temp =  m_addr5_bus;
				dev_temp =  m_addr5_dev;
				fun_temp =  m_addr5_fun;
				RegSetValueEx(key, TEXT("Addr5_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr5_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr5_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

				bus_temp =  m_addr6_bus;
				dev_temp =  m_addr6_dev;
				fun_temp =  m_addr6_fun;
				RegSetValueEx(key, TEXT("Addr6_bus"), 0, REG_DWORD, (LPBYTE)&bus_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr6_dev"), 0, REG_DWORD, (LPBYTE)&dev_temp, sizeof(DWORD));
				RegSetValueEx(key, TEXT("Addr6_fun"), 0, REG_DWORD, (LPBYTE)&fun_temp, sizeof(DWORD));

				RegCloseKey(key);
			}
			else
			AfxMessageBox(_T("create registry wrong!"));
		}
		SetDlgItemText(IDC_BUTTON2, _T("Set New Address"));
	}
	
}
