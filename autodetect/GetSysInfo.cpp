#include "stdafx.h"
#include "GetSysInfo.h" 
#include "float.h"  
#include "winperf.h"  
#include"Windows.h"
typedef   void(WINAPI*   FunctionGlobalMemoryStatusEx)(LPMEMORYSTATUS);//声明函数原型指针

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
	LONG lResult;//LONG型变量－保存函数返回值  
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
			//?键不存在  
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
	hModule = LoadLibrary(_T("kernel32.dll"));//载入动态链接库kernel32.dll，返回它的句柄
	if (NULL == hModule)//判断载入dll是否成功
	{
	//error.
	//MessageBox(NULL,TEXT("载入动态链接库kernel32.dll"),TEXT("错误"),MB_OK|MB_ICONERROR);
	return;
	}
	//在kernel32.dll句柄里查找GlobalMemoryStatusEx函数，返回改函数的指针
	GlobalMemoryStatusEx = (FunctionGlobalMemoryStatusEx)GetProcAddress(hModule, "GlobalMemoryStatusEx");
	if (NULL == GlobalMemoryStatusEx)//判断函数是否找到
	{
	//error
	//MessageBox(hwndDlg,TEXT("函数查找不到"),TEXT("错误"),MB_OK|MB_ICONERROR);
	return;
	}
	GlobalMemoryStatusEx(&status);//调用函数取得系统的内存情况
	FreeLibrary(hModule);//释放链接库句柄
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
	LONG lResult;//LONG型变量－保存函数返回值  
	DWORD size = 0, type = 0;
	TCHAR name[512] = { 0 };
	//查询集成显卡
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
			//存在集显
			unsigned int count = 0;
			size = sizeof(count);
			//RegCloseKey(keyigfx);
			lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
			dwNum = count;//得到集显数量
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
	
	//查询AMD显卡
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
			//存在AMD
			unsigned int count = 0;
			size = sizeof(count);
			lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
			dwNum = count;//得到AMD数量
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
	//查询nvidia显卡
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
		//存在NV
		unsigned int count = 0;
		size = sizeof(count);
		lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);
		dwNum = count;//得到NV数量
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
	//查询"SYSTEM\\CurrentControlSet\\Services"下的所有子键保存到keyServ
	lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Services"), 0, KEY_READ, &keyServ);
	if (ERROR_SUCCESS != lResult)
	return;


	//查询"SYSTEM\\CurrentControlSet\\Enum"下的所有子键保存到keyEnum  感觉并没有用
	//lResult = RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("SYSTEM\\CurrentControlSet\\Enum"), 0, KEY_READ, &keyEnum);
	//if (ERROR_SUCCESS != lResult)
	//	return;

	int i = 0, count = 0;

	for (;; ++i)
	{
	Sleep(5);
	size = 512;
	TCHAR name[512] = { 0 };//保存keyServ下各子项的字段名称
	//逐个枚举keyServ下的各子项字段保存到name中
	lResult = RegEnumKeyEx(keyServ, i, name, &size, NULL, NULL, NULL, NULL);
	//要读取的子项不存在，即keyServ的子项全部遍历完时跳出循环
	if (lResult == ERROR_NO_MORE_ITEMS)
	break;
	//打开keyServ的子项字段为name所标识的字段的值保存到key
	lResult = RegOpenKeyEx(keyServ, name, 0, KEY_READ, &key);
	if (lResult != ERROR_SUCCESS)
	{
	RegCloseKey(keyServ);
	return;
	}
	size = 512;
	//查询key下的字段为Group的子键字段名保存到name
	lResult = RegQueryValueEx(key, TEXT("Group"), 0, &type, (LPBYTE)name, &size);
	if (lResult == ERROR_FILE_NOT_FOUND)
	{
	//?键不存在
	RegCloseKey(key);
	continue;
	};
	//如果查询到的name不是Video则说明该键不是显卡驱动项
	if (_tcscmp(TEXT("Video"), name) != 0)
	{
	RegCloseKey(key);
	continue;     //返回for循环
	};

	//如果程序继续往下执行的话说明已经查到了有关显卡的信息，所以在下面的代码执行完之后要break第一个for循环，函数返回
	lResult = RegOpenKeyEx(key, TEXT("Enum"), 0, KEY_READ, &key2);
	RegCloseKey(key);
	key = key2;
	size = sizeof(count);
	lResult = RegQueryValueEx(key, TEXT("Count"), 0, &type, (LPBYTE)&count, &size);//查询Count字段（显卡数目）

	dwNum = count;//保存显卡数目
	for (int j = 0; j <count; ++j)
	{
	TCHAR sz[512] = { 0 };
	TCHAR name[64] = { 0 };
	wsprintf(name, TEXT("%d"), j);
	size = sizeof(sz);
	lResult = RegQueryValueEx(key, name, 0, &type, (LPBYTE)sz, &size);

	//不知道干嘛   感觉没有用
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
			break;//希望查不到device description就继续查询下一个子键
		}
		chCardName[j] = sz;//保存显卡名称  
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

	//利用GetLogicalDrives()函数可以获取系统中逻辑驱动器的数量，函数返回的是一个32位无符号整型数据。
	DWORD DiskInfo = GetLogicalDrives();

	//通过循环操作查看每一位数据是否为1，如果为1则磁盘为真,如果为0则磁盘不存在。
	while (DiskInfo)
	{
	//通过位运算的逻辑与操作，判断是否为1
	Sleep(10);
	if (DiskInfo & 1)
	{
	DiskCount++;
	}
	DiskInfo = DiskInfo >> 1;//通过位运算的右移操作保证每循环一次所检查的位置向右移动一位。
}

//if (dwNum < DiskCount)
//{
//	return;//实际的磁盘数目大于dwNum  
//}
dwNum = DiskCount;//将磁盘分区数量保存  


				  //-------------------------------------------------------------------//  
				  //通过GetLogicalDriveStrings()函数获取所有驱动器字符串信息长度  
int DSLength = GetLogicalDriveStrings(0, NULL);

WCHAR* DStr = new WCHAR[DSLength];
memset(DStr, 0, DSLength);

//通过GetLogicalDriveStrings将字符串信息复制到堆区数组中,其中保存了所有驱动器的信息。  
GetLogicalDriveStrings(DSLength, DStr);

int DType;
int si = 0;
BOOL fResult;
unsigned _int64 i64FreeBytesToCaller;
unsigned _int64 i64TotalBytes;
unsigned _int64 i64FreeBytes;

//读取各驱动器信息，由于DStr内部数据格式是A:\NULLB:\NULLC:\NULL，所以DSLength/4可以获得具体大循环范围  
for (int i = 0; i<DSLength / 4; ++i)
{
	Sleep(10);
	CString strdriver = DStr + i * 4;
	CString strTmp, strTotalBytes, strFreeBytes;
	DType = GetDriveType(strdriver);//GetDriveType函数，可以获取驱动器类型，参数为驱动器的根目录  
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

	//GetDiskFreeSpaceEx函数，可以获取驱动器磁盘的空间状态,函数返回的是个BOOL类型数据  
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
		//RegQueryValueEx的固定调用格式          
		CString str(s_key);

		//如果RegQueryValueEx函数执行失败则进入循环  
		while ((ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size)) != ERROR_SUCCESS)
		{
			Sleep(10);
			//如果RegQueryValueEx的返回值为ERROR_MORE_DATA(申请的内存区data太小，不能容纳RegQueryValueEx返回的数据)  
			if (ret == ERROR_MORE_DATA)
			{
				Sleep(10);
				size += DEFAULT_BUFFER_SIZE;
				data = (unsigned char*)realloc(data, size);//重新分配足够大的内存  

				ret = RegQueryValueEx(HKEY_PERFORMANCE_DATA, str, 0, &type, data, &size);//重新执行RegQueryValueEx函数  
			}
			//如果RegQueryValueEx返回值仍旧未成功则函数返回.....(注意内存泄露“free函数”~~~)。  
			//这个if保证了这个while只能进入一次~~~避免死循环  
			if (ret != ERROR_SUCCESS)
			{
				if (NULL != data)
				{
					free(data);
					data = NULL;
				}
				return 0;//0个接口  
			}
		}

		//函数执行成功之后就是对返回的data内存中数据的解析了，这个建议去查看MSDN有关RegQueryValueEx函数参数数据结构的说明  
		//得到数据块       
		PERF_DATA_BLOCK  *dataBlockPtr = (PERF_DATA_BLOCK *)data;
		//得到第一个对象  
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

					Interfaces.AddTail(CString(pName)); //各网卡的名称  
					Bandwidths.AddTail(bandwith);       //带宽  
					TotalTraffics.AddTail(tottraff);    // 流量初始化为0  

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
		//打开keyServ的子项字段为name所标识的字段的值保存到key  
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
			//查询key下的字段为Group的子键字段名保存到name  
			lreturn = RegQueryValueEx(subsubkey, TEXT("Class"), 0, &type, (LPBYTE)name, &size);
			if (lreturn == ERROR_FILE_NOT_FOUND)
			{
				//?键不存在  
				RegCloseKey(subsubkey);
				continue;
			};
			if (_tcscmp(TEXT("DiskDrive"), name) != 0)
			{
				RegCloseKey(subsubkey);
				continue;     //返回for循环  
			};
			size = 512;
			RegQueryValueEx(subsubkey, TEXT("FriendlyName"), 0, &type, (LPBYTE)name, &size);
			namestring = name;
			dwNum++;
		}
		
		
	}
	

}
