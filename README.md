# 通过注册表注入DLL

> 环境：Windows10 LTSC

### 如何使用

1.以管理员身份运行 CMD

2.运行 `.\RegDllIj.exe C:\Users\ab\Desktop\TipsX86.dll` 注入 TipsX86.dll

3.运行 notepad

4.使用 Dbgview 查看输出 “Tips.dll ATTACH” 或 使用 procexp 查看记事本进程是否加载TipsX86.dll

5.运行 `.\RegDllIj.exe` 重置注册表



### Tips.dll

```c++
#include "pch.h"

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		OutputDebugString(L"Tips.dll ATTACH");
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		OutputDebugString(L"Tips.dll DETACH");
		break;
	}
	return TRUE;
}
```

