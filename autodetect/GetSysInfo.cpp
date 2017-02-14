#include "stdafx.h"
#include "GetSysInfo.h" 
#include "float.h"  
#include "winperf.h"  
#include"Windows.h"
typedef   void(WINAPI*   FunctionGlobalMemoryStatusEx)(LPMEMORYSTATUS);//��������ԭ��ָ��

GetSysInfo::GetSysInfo()
{
}


GetSysInfo::~GetSysInfo()
{
}
//##############################################################################
void GetSysInfo::GetBIOSInfo(CString &vendor, CString &board, CString &version)
{
	HKEY keySys;
	HKEY key;
	LONG lResult;//LONG�ͱ��������溯������ֵ  
	DWORD size = 0, type = 0;
	TCHAR name[512] = { 0 };
	TCHAR sz[512] = { 0 };
	int i = 0;
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("HARDWARE\\DESCRIPTION\\System"),0,KEY_READ,&keySys);
	if (ERROR_SUCCESS != lResult)
		return;
	for (;; i++)
	{
		size = 512;
		lResult = RegEnumKeyEx(keySys, i, name, &size, NULL, NULL, NULL, NULL);
		if (lResult == ERROR_NO_MORE_ITEMS)
			break;
		lResult = RegOpenKeyEx(keySys, name, 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			RegCloseKey(keySys);
			return;
		}
		lResult = RegQueryValueEx(key, TEXT("BIOSVendor"), 0, &type, (LPBYTE)name, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			//?��������  
			RegCloseKey(key);
			continue;
		};
		Sleep(5);
		size = 512;
		lResult = RegQueryValueEx(key, TEXT("BIOSVendor"), 0, &type, (LPBYTE)sz, &size);
		vendor = sz;
		size = 512;
		lResult = RegQueryValueEx(key, TEXT("BaseBoardProduct"), 0, &type, (LPBYTE)sz, &size);
		board = sz;
		board += " ";
		size = 512;
		lResult = RegQueryValueEx(key, TEXT("BaseBoardVersion"), 0, &type, (LPBYTE)sz, &size);
		board += sz;
		size = 512;
		lResult = RegQueryValueEx(key, TEXT("BIOSVersion"), 0, &type, (LPBYTE)sz, &size);
		version = sz;
		version += " ";
		size = 512;
		lResult = RegQueryValueEx(key, TEXT("BIOSReleaseDate"), 0, &type, (LPBYTE)sz, &size);
		version += sz;
		RegCloseKey(key);
		break;
	}
	
	
}
//##############################################################################
void GetSysInfo::GetMemoryInfo(CString  &dwTotalPhys, CString  &dwTotalVirtual)
{
	//   TODO:     Add   extra   initialization   here  
	
	MEMORYSTATUS   Mem;
	GlobalMemoryStatus(&Mem);

	DWORD dwSize = (DWORD)Mem.dwTotalPhys / (1024 * 1024);
	DWORD dwVirtSize = (DWORD)Mem.dwTotalVirtual / (1024 * 1024);

	dwTotalPhys.Format(_T("Physic Memory:%ld MB"), dwSize);
	dwTotalVirtual.Format(_T("Virtual Memory:%ld MB"), dwVirtSize);
	
	
	////////////////////////////////////////////////////////////////

	/*
	HMODULE hModule;
	FunctionGlobalMemoryStatusEx GlobalMemoryStatusEx;
	MEMORYSTATUS status;
	status.dwLength = sizeof(status);
	hModule = LoadLibrary(_T("kernel32.dll"));//���붯̬���ӿ�kernel32.dll���������ľ��
	if (NULL == hModule)//�ж�����dll�Ƿ�ɹ�
	{
	//error.
	//MessageBox(NULL,TEXT("���붯̬���ӿ�kernel32.dll"),TEXT("����"),MB_OK|MB_ICONERROR);
	return;
	}
	//��kernel32.dll��������GlobalMemoryStatusEx���������ظĺ�����ָ��
	GlobalMemoryStatusEx = (FunctionGlobalMemoryStatusEx)GetProcAddress(hModule, "GlobalMemoryStatusEx");
	if (NULL == GlobalMemoryStatusEx)//�жϺ����Ƿ��ҵ�
	{
	//error
	//MessageBox(hwndDlg,TEXT("�������Ҳ���"),TEXT("����"),MB_OK|MB_ICONERROR);
	return;
	}
	GlobalMemoryStatusEx(&status);//���ú���ȡ��ϵͳ���ڴ����
	FreeLibrary(hModule);//�ͷ����ӿ���
	DWORD dwSize = (DWORD)status.dwTotalPhys / (1024 * 1024);
	DWORD dwVirtSize = (DWORD)status.dwTotalVirtual / (1024 * 1024);

	dwTotalPhys.Format(_T("Physic Memory:%ld MB"), dwSize);
	dwTotalVirtual.Format(_T("Virtual Memory:%ld MB"), dwVirtSize);
	*/
}
//##############################################################################
void GetSysInfo::GetDisplayCardInfo(DWORD & dwNum, CString chCardName[])
{
	HKEY keyigfx,keyamdkmdap,keynvhda,keynvlddmkm;
	//HKEY keyEnum;
	HKEY key,subkey;
	LONG lResult;//LONG�ͱ��������溯������ֵ  
	DWORD size = 0, type = 0;
	TCHAR name[512] = { 0 };
	//��ѯ�����Կ�
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SYSTEM\\CurrentControlSet\\services\\igfx"),0,KEY_READ,&keyigfx);
	if (lResult != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("can't find integrated displaycard"));
	}
	else
	{
		lResult = RegOpenKeyEx(keyigfx, TEXT("Enum"), 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("integrated displaycard number is 0"));
		}
		else
		{
			//���ڼ���
			unsigned int count = 0;
			size = sizeof(count);
			//RegCloseKey(keyigfx);
			lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
			dwNum = count;//�õ���������
						  //RegCloseKey(key);
			for (unsigned int i = 0; i < count; i++)
			{
				size = 512;
				lResult = RegEnumKeyEx(keyigfx, i, name, &size, NULL, NULL, NULL, NULL);
				if (lResult != ERROR_SUCCESS)
				{
					LPVOID lpMsgBuf;
					DWORD dw = GetLastError();
					TCHAR szBuf[128];
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_ALLOCATE_BUFFER,
						NULL,
						dw,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPWSTR)&lpMsgBuf,
						0,
						NULL);
					LPCTSTR error_message = (LPCTSTR)lpMsgBuf;
					AfxMessageBox(error_message);
					//AfxMessageBox(lpMsgBuf);
				}

				if (lResult == ERROR_NO_MORE_ITEMS)
					break;
				lResult = RegOpenKeyEx(keyigfx, name, 0, KEY_READ, &subkey);
				size = 512;
				lResult = RegQueryValueEx(subkey, TEXT("Device Description"), 0, &type, (LPBYTE)&name, &size);
				chCardName[i] = name;
				RegCloseKey(subkey);
				RegCloseKey(keyigfx);
			}
		}
	}
	
	//��ѯAMD�Կ�
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\amdkmdap"), 0, KEY_READ, &keyamdkmdap);
	if (lResult != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("can't find amd display card"));
	}
	else
	{
		lResult = RegOpenKeyEx(keyamdkmdap, TEXT("Enum"), 0, KEY_READ, &key);
		if (lResult != ERROR_SUCCESS)
		{
			AfxMessageBox(_T("amd display card number is 0"));
		}
		else
		{
			//����AMD
			unsigned int count = 0;
			size = sizeof(count);
			lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
			dwNum = count;//�õ�AMD����
			for (unsigned int i = 0; i < count; i++)
			{
				size = 512;
				lResult = RegEnumKeyEx(keyamdkmdap, i, name, &size, NULL, NULL, NULL, NULL);
				if (lResult != ERROR_SUCCESS)
				{
					LPVOID lpMsgBuf;
					DWORD dw = GetLastError();
					TCHAR szBuf[128];
					FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
						FORMAT_MESSAGE_ALLOCATE_BUFFER,
						NULL,
						dw,
						MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
						(LPWSTR)&lpMsgBuf,
						0,
						NULL);
					LPCTSTR error_message = (LPCTSTR)lpMsgBuf;
					AfxMessageBox(error_message);
				}

				if (lResult == ERROR_NO_MORE_ITEMS)
					break;
				lResult = RegOpenKeyEx(keyamdkmdap, name, 0, KEY_READ, &subkey);
				size = 512;
				lResult = RegQueryValueEx(subkey, TEXT("Device Description"), 0, &type, (LPBYTE)&name, &size);
				chCardName[i] = name;
				RegCloseKey(subkey);
				RegCloseKey(keyamdkmdap);
			}
		}
	}
	//��ѯnvidia�Կ�
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\NVHDA"), 0, KEY_READ, &keynvhda);
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\NVDDLMKM"), 0, KEY_READ, &keynvlddmkm);
	
	if (lResult != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("can't finf nvidia displaycard"));
		return;
	}
	lResult = RegOpenKeyEx(keynvhda, TEXT("Enum"), 0, KEY_READ, &key);
	if (lResult != ERROR_SUCCESS)
	{
		AfxMessageBox(_T("nvidia displaycard number is 0"));
		return;
	}
	else
	{
		//����NV
		unsigned int count = 0;
		size = sizeof(count);
		lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
		dwNum = count;//�õ�NV����
		for (unsigned int i = 0; i < count; i++)
		{
			size = 512;
			lResult = RegEnumKeyEx(keynvlddmkm, i, name, &size, NULL, NULL, NULL, NULL);
			if (lResult != ERROR_SUCCESS)
			{
				LPVOID lpMsgBuf;
				DWORD dw = GetLastError();
				TCHAR szBuf[128];
				FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
					FORMAT_MESSAGE_ALLOCATE_BUFFER,
					NULL,
					dw,
					MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPWSTR)&lpMsgBuf,
					0,
					NULL);
				LPCTSTR error_message = (LPCTSTR)lpMsgBuf;
				AfxMessageBox(error_message);
				//AfxMessageBox(lpMsgBuf);
			}

			if (lResult == ERROR_NO_MORE_ITEMS)
				break;
			lResult = RegOpenKeyEx(keynvlddmkm, name, 0, KEY_READ, &subkey);
			size = 512;
			lResult = RegQueryValueEx(subkey, TEXT("Device Description"), 0, &type, (LPBYTE)&name, &size);
			chCardName[i] = name;
			RegCloseKey(subkey);
			RegCloseKey(keynvlddmkm);
		}
	}
	/*
	//��ѯ"SYSTEM\\CurrentControlSet\\Services"�µ������Ӽ����浽keyServ
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &keyServ);
	if (ERROR_SUCCESS != lResult)
	return;


	//��ѯ"SYSTEM\\CurrentControlSet\\Enum"�µ������Ӽ����浽keyEnum  �о���û����
	//lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &keyEnum);
	//if (ERROR_SUCCESS != lResult)
	//	return;

	int i = 0, count = 0;

	for (;; ++i)
	{
	Sleep(5);
	size = 512;
	TCHAR name[512] = { 0 };//����keyServ�¸�������ֶ�����
	//���ö��keyServ�µĸ������ֶα��浽name��
	lResult = RegEnumKeyEx(keyServ, i, name, &size, NULL, NULL, NULL, NULL);
	//Ҫ��ȡ��������ڣ���keyServ������ȫ��������ʱ����ѭ��
	if (lResult == ERROR_NO_MORE_ITEMS)
	break;
	//��keyServ�������ֶ�Ϊname����ʶ���ֶε�ֵ���浽key
	lResult = RegOpenKeyEx(keyServ, name, 0, KEY_READ, &key);
	if (lResult != ERROR_SUCCESS)
	{
	RegCloseKey(keyServ);
	return;
	}
	size = 512;
	//��ѯkey�µ��ֶ�ΪGroup���Ӽ��ֶ������浽name
	lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
	if (lResult == ERROR_FILE_NOT_FOUND)
	{
	//?��������
	RegCloseKey(key);
	continue;
	};
	//�����ѯ����name����Video��˵���ü������Կ�������
	if (_tcscmp(TEXT("Video"), name) != 0)
	{
	RegCloseKey(key);
	continue;     //����forѭ��
	};

	//��������������ִ�еĻ�˵���Ѿ��鵽���й��Կ�����Ϣ������������Ĵ���ִ����֮��Ҫbreak��һ��forѭ������������
	lResult = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
	RegCloseKey(key);
	key = key2;
	size = sizeof(count);
	lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);//��ѯCount�ֶΣ��Կ���Ŀ��

	dwNum = count;//�����Կ���Ŀ
	for (int j = 0; j <count; ++j)
	{
	TCHAR sz[512] = { 0 };
	TCHAR name[64] = { 0 };
	wsprintf(name, TEXT("%d"), j);
	size = sizeof(sz);
	lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)sz, &size);

	//��֪������   �о�û����
	lResult = RegOpenKeyEx(keyEnum, sz, 0, KEY_READ, &key2);
	if (ERROR_SUCCESS)
	{
	RegCloseKey(keyEnum);
	return;
	}
	size = sizeof(sz);
	lResult = RegQueryValueEx(key2, TEXT("FriendlyName"), 0, &type, (LPBYTE)sz, &size);
	if (lResult == ERROR_FILE_NOT_FOUND)
	{
		size = sizeof(sz);
		lResult = RegQueryValueEx(key2, TEXT("DeviceDesc"), 0, &type, (LPBYTE)sz, &size);
		if (lResult == ERROR_FILE_NOT_FOUND)
		{
			break;//ϣ���鲻��device description�ͼ�����ѯ��һ���Ӽ�
		}
		chCardName[j] = sz;//�����Կ�����  
	};
	RegCloseKey(key2);
	key2 = NULL;
};
RegCloseKey(key);
key = NULL;
break;
	}
	*/
	
}
//##############################################################################
void GetSysInfo::GetDiskInfo(DWORD & dwNum, CString chDriveInfo[],DWORD &physic_disk_num,vector<CString> &physic_disk_name)
{
	

	/*
	DWORD DiskCount = 0;

	//����GetLogicalDrives()�������Ի�ȡϵͳ���߼����������������������ص���һ��32λ�޷����������ݡ�
	DWORD DiskInfo = GetLogicalDrives();

	//ͨ��ѭ�������鿴ÿһλ�����Ƿ�Ϊ1�����Ϊ1�����Ϊ��,���Ϊ0����̲����ڡ�
	while (DiskInfo)
	{
	//ͨ��λ������߼���������ж��Ƿ�Ϊ1
	Sleep(10);
	if (DiskInfo & 1)
	{
	DiskCount++;
	}
	DiskInfo = DiskInfo >> 1;//ͨ��λ��������Ʋ�����֤ÿѭ��һ��������λ�������ƶ�һλ��
}

//if (dwNum < DiskCount)
//{
//	return;//ʵ�ʵĴ�����Ŀ����dwNum  
//}
dwNum = DiskCount;//�����̷�����������  


				  //-------------------------------------------------------------------//  
				  //ͨ��GetLogicalDriveStrings()������ȡ�����������ַ�����Ϣ����  
int DSLength = GetLogicalDriveStrings(0, NULL);

WCHAR* DStr = new WCHAR[DSLength];
memset(DStr, 0, DSLength);

//ͨ��GetLogicalDriveStrings���ַ�����Ϣ���Ƶ�����������,���б�������������������Ϣ��  
GetLogicalDriveStrings(DSLength, DStr);

int DType;
int si = 0;
BOOL fResult;
unsigned _int64 i64FreeBytesToCaller;
unsigned _int64 i64TotalBytes;
unsigned _int64 i64FreeBytes;

//��ȡ����������Ϣ������DStr�ڲ����ݸ�ʽ��A:\NULLB:\NULLC:\NULL������DSLength/4���Ի�þ����ѭ����Χ  
for (int i = 0; i<DSLength / 4; ++i)
{
	Sleep(10);
	CString strdriver = DStr + i * 4;
	CString strTmp, strTotalBytes, strFreeBytes;
	DType = GetDriveType(strdriver);//GetDriveType���������Ի�ȡ���������ͣ�����Ϊ�������ĸ�Ŀ¼  
	switch (DType)
	{
	case DRIVE_FIXED:
	{
		strTmp.Format(_T("Local Disk"));
	}
	break;
	case DRIVE_CDROM:
	{
		strTmp.Format(_T("DVD Driver"));
	}
	break;
	case DRIVE_REMOVABLE:
	{
		strTmp.Format(_T("Removable Disk"));
	}
	break;
	case DRIVE_REMOTE:
	{
		strTmp.Format(_T("Network Disk"));
	}
	break;
	case DRIVE_RAMDISK:
	{
		strTmp.Format(_T("Virtual RAM Disk"));
	}
	break;
	case DRIVE_UNKNOWN:
	{
		strTmp.Format(_T("Virtual RAM Unknow Device"));
	}
	break;
	default:
		strTmp.Format(_T("Unknow Device"));
		break;
	}

	//GetDiskFreeSpaceEx���������Ի�ȡ���������̵Ŀռ�״̬,�������ص��Ǹ�BOOL��������  
	fResult = GetDiskFreeSpaceEx(strdriver,
		(PULARGE_INTEGER)&i64FreeBytesToCaller,
		(PULARGE_INTEGER)&i64TotalBytes,
		(PULARGE_INTEGER)&i64FreeBytes);

	if (fResult)
	{
		strTotalBytes.Format(_T("Total %fMB"), (float)i64TotalBytes / 1024 / 1024);
		strFreeBytes.Format(_T("	|| Rest %fMB"), (float)i64FreeBytesToCaller / 1024 / 1024);
	}
	else
	{
		strTotalBytes.Format(_T(""));
		strFreeBytes.Format(_T(""));
	}
	chDriveInfo[i] = strTmp + _T("(") + strdriver + _T("):") + strTotalBytes + strFreeBytes;
	si += 4;
}
	*/
	HKEY keydisk;
	HKEY key;
	LONG lResult;
	DWORD size = 0 ,type = 0;
	int i = 0;
	TCHAR name[512] = {0};
	TCHAR sz[512] = { 0 };
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\services\\Disk\\Enum"), 0, KEY_READ, &keydisk);
	if (ERROR_SUCCESS != lResult)
		return;
	lResult = RegOpenKeyEx(keydisk, name, 0, KEY_READ, &key);
	if (lResult != ERROR_SUCCESS)
	{
		RegCloseKey(keydisk);
		return;
	}
	size = 512;
	lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&physic_disk_num, &size);
	dwNum = physic_disk_num;
    for (unsigned int j = 0;j < physic_disk_num; j++)
	{
		wsprintf(name, TEXT("%d"), j);
		size = 512;
		lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)&sz, &size);
		physic_disk_name.push_back(sz);
	}
	
}
//##############################################################################
int GetSysInfo::GetInterFaceCount()
{
	/*CGetNetData pNet;
	DWORD pCount = pNet.GetNetworkInterfacesCount();
	return pCount;*/


	try
	{
#define DEFAULT_BUFFER_SIZE 40960L  

		unsigned char *data = (unsigned char*)malloc(DEFAULT_BUFFER_SIZE);
		DWORD type;
		DWORD size = DEFAULT_BUFFER_SIZE;
		DWORD ret;

		char s_key[4096];
		sprintf_s(s_key, 4096, "510");
		//RegQueryValueEx�Ĺ̶����ø�ʽ          
		CString str(s_key);

		//���RegQueryValueEx����ִ��ʧ�������ѭ��  
		while ((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size)) != ERROR_SUCCESS)
		{
			Sleep(10);
			//���RegQueryValueEx�ķ���ֵΪERROR_MORE_DATA(������ڴ���data̫С����������RegQueryValueEx���ص�����)  
			if (ret == ERROR_MORE_DATA)
			{
				Sleep(10);
				size += DEFAULT_BUFFER_SIZE;
				data = (unsigned char*)realloc(data, size);//���·����㹻����ڴ�  

				ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size);//����ִ��RegQueryValueEx����  
			}
			//���RegQueryValueEx����ֵ�Ծ�δ�ɹ���������.....(ע���ڴ�й¶��free������~~~)��  
			//���if��֤�����whileֻ�ܽ���һ��~~~������ѭ��  
			if (ret != ERROR_SUCCESS)
			{
				if (NULL != data)
				{
					free(data);
					data = NULL;
				}
				return 0;//0���ӿ�  
			}
		}

		//����ִ�гɹ�֮����ǶԷ��ص�data�ڴ������ݵĽ����ˣ��������ȥ�鿴MSDN�й�RegQueryValueEx�����������ݽṹ��˵��  
		//�õ����ݿ�       
		PERF_DATA_BLOCK  *dataBlockPtr = (PERF_DATA_BLOCK *)data;
		//�õ���һ������  
		PERF_OBJECT_TYPE *objectPtr = (PERF_OBJECT_TYPE *)((BYTE *)dataBlockPtr + dataBlockPtr->HeaderLength);

		for (int a = 0; a<(int)dataBlockPtr->NumObjectTypes; a++)
		{
			char nameBuffer[255] = { 0 };
			if (objectPtr->ObjectNameTitleIndex == 510)
			{
				DWORD processIdOffset = ULONG_MAX;
				PERF_COUNTER_DEFINITION *counterPtr = (PERF_COUNTER_DEFINITION *)((BYTE *)objectPtr + objectPtr->HeaderLength);

				for (int b = 0; b<(int)objectPtr->NumCounters; b++)
				{
					if (counterPtr->CounterNameTitleIndex == 520)
						processIdOffset = counterPtr->CounterOffset;

					counterPtr = (PERF_COUNTER_DEFINITION *)((BYTE *)counterPtr + counterPtr->ByteLength);
				}

				if (processIdOffset == ULONG_MAX) {
					if (data != NULL)
					{
						free(data);
						data = NULL;
					}
					return 0;
				}

				PERF_INSTANCE_DEFINITION *instancePtr = (PERF_INSTANCE_DEFINITION *)((BYTE *)objectPtr + objectPtr->DefinitionLength);

				for (int b = 0; b<objectPtr->NumInstances; b++)
				{
					wchar_t *namePtr = (wchar_t *)((BYTE *)instancePtr + instancePtr->NameOffset);
					PERF_COUNTER_BLOCK *counterBlockPtr = (PERF_COUNTER_BLOCK *)((BYTE *)instancePtr + instancePtr->ByteLength);

					char pName[256] = { 0 };
					WideCharToMultiByte(CP_ACP, 0, namePtr, -1, pName, sizeof(nameBuffer), 0, 0);

					DWORD bandwith = *((DWORD *)((BYTE *)counterBlockPtr + processIdOffset));
					DWORD tottraff = 0;

					Interfaces.AddTail(CString(pName)); //������������  
					Bandwidths.AddTail(bandwith);       //����  
					TotalTraffics.AddTail(tottraff);    // ������ʼ��Ϊ0  

					PERF_COUNTER_BLOCK  *pCtrBlk = (PERF_COUNTER_BLOCK *)((BYTE *)instancePtr + instancePtr->ByteLength);


					instancePtr = (PERF_INSTANCE_DEFINITION *)((BYTE *)instancePtr + instancePtr->ByteLength + pCtrBlk->ByteLength);
				}
			}
			objectPtr = (PERF_OBJECT_TYPE *)((BYTE *)objectPtr + objectPtr->TotalByteLength);
		}
		if (data != NULL)
		{
			free(data);
			data = NULL;
		}
	}
	catch (...)
	{
		return 0;
	}
	return Interfaces.GetCount();
}
//##############################################################################
void GetSysInfo::GetInterFaceName(CString & InterfaceName, int pNum)
{
	/*
	CGetNetData pNet;
	pNet.GetNetworkInterfaceName(&InterfaceName,pNum);
	*/
	

	POSITION pos = Interfaces.FindIndex(pNum);
	if (pos == NULL)
		return;

	InterfaceName = Interfaces.GetAt(pos);
	pos = Bandwidths.FindIndex(pNum);
	if (pos == NULL)
		return;
	DWORD dwBandwidth = Bandwidths.GetAt(pos);

	CString str;
	str.Format(_T("%d"), dwBandwidth);

	InterfaceName = InterfaceName + str;
}

void GetSysInfo::GetUSBinfo(CString & namestring, DWORD & dwNum)
{
	HKEY key,subkey,subsubkey;
	DWORD lreturn = 0;
	DWORD size, type;
	TCHAR name[512] = {0};
	lreturn=RegOpenKeyEx(HKEY_LOCAL_MACHINE,TEXT("SYSTEM\\CurrentControlSet\\Enum\\USBSTOR"),0,KEY_READ,&key);
	if (lreturn != ERROR_SUCCESS)
		AfxMessageBox(_T("open usb fail"));

	for (unsigned int i=0;;i++)
	{
		size = 512;
		lreturn = RegEnumKeyEx(key, i, name, &size, NULL, NULL, NULL, NULL);
		if (lreturn == ERROR_NO_MORE_ITEMS)
			break;
		//��keyServ�������ֶ�Ϊname����ʶ���ֶε�ֵ���浽key  
		lreturn = RegOpenKeyEx(key, name, 0, KEY_READ, &subkey);
		if (lreturn != ERROR_SUCCESS)
		{
			RegCloseKey(key);
			return;
		}
		
		for (unsigned int j=0;;j++)
		{
			size = 512;
			lreturn = RegEnumKeyEx(subkey, j, name,&size ,NULL,NULL,NULL,NULL );
			if (lreturn == ERROR_NO_MORE_ITEMS)
				break;
			lreturn = RegOpenKeyEx(subkey, name, 0, KEY_READ, &subsubkey);
			//if (lreturn != ERROR_SUCCESS)
			//{
			//	RegCloseKey(key);
			//	return;
			//}
			size = 512;
			//��ѯkey�µ��ֶ�ΪGroup���Ӽ��ֶ������浽name  
			lreturn = RegQueryValueEx(subsubkey, TEXT("Class"), 0, &type, (LPBYTE)name, &size);
			if (lreturn == ERROR_FILE_NOT_FOUND)
			{
				//?��������  
				RegCloseKey(subsubkey);
				continue;
			};
			if (_tcscmp(TEXT("DiskDrive"), name) != 0)
			{
				RegCloseKey(subsubkey);
				continue;     //����forѭ��  
			};
			size = 512;
			RegQueryValueEx(subsubkey, TEXT("FriendlyName"), 0, &type, (LPBYTE)name, &size);
			namestring = name;
			dwNum++;
		}
		
		
	}
	

}
