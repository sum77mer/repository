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
	void GetMemoryInfo(CString &dwTotalPhys, CString &dwTotalVirtual);//�ڴ�
	void GetDisplayCardInfo(DWORD &dwNum, CString chCardName[]);//�Կ�
	void GetDiskInfo(DWORD &dwNum, CString chDriveInfo[], DWORD &physic_disk_num, vector<CString> &physic_disk_name);//Ӳ��
	int  GetInterFaceCount();//����
	void GetInterFaceName(CString &InterfaceName, int pNum);//����
	void GetUSBinfo(CString &namestring,DWORD &dwNum);
private:
	CStringList Interfaces;                          //������������������
	CList < DWORD, DWORD &>        Bandwidths;      //�������Ĵ���
	CList < DWORD, DWORD &>        TotalTraffics;    //��������������
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

