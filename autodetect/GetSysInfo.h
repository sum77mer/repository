#pragma once
#include<afxtempl.h>
#include<vector>
using std::vector;
class GetSysInfo
{
public:
	GetSysInfo();

	virtual ~GetSysInfo();
	void GetBIOSInfo(CString &vendor,CString &board,CString &version);//BIOS
	void GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual);//内存
	void GetDisplayCardInfo(DWORD &dwNum, CString chCardName[]);//显卡
	void GetDiskInfo(DWORD &dwNum, CString chDriveInfo[], DWORD &physic_disk_num, vector<CString> &physic_disk_name);//硬盘
	int  GetInterFaceCount();//网卡
	void GetInterFaceName(CString &InterfaceName, int pNum);//网卡
	void GetUSBinfo(CString &namestring,DWORD &dwNum);
private:
	CStringList Interfaces;                          //保存所有网卡的名字
	CList < DWORD, DWORD &>        Bandwidths;      //各网卡的带宽
	CList < DWORD, DWORD &>        TotalTraffics;    //各网卡的总流量
public:
	CString BIOS_vendor, BIOS_version;
	CString board;
	CString phys_memory_str, vir_memory_str;
	CString dis_card_str[2];
	CString disk_str[5];
	DWORD physic_disk_num;
	vector<CString> physic_disk_name;
	CString network_str;
	DWORD dis_card_num;
	DWORD disk_num;
	int network_num;
	DWORD USBnum;
	CString USBname;
};

