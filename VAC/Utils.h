#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <Windows.h>
#include <Psapi.h>
#include <SetupAPI.h>
#include <TlHelp32.h>
#include <winternl.h>
#include <WinTrust.h>
#include <DbgHelp.h>
#define SECURITY_WIN32
#include <security.h>
#include <Snmp.h>

// 83 C8 FF 83 E9 00
INT Utils_getProtect(BYTE);

// E8 ? ? ? ? 89 7E 04 (relative jump)
LPVOID Utils_heapAlloc(SIZE_T);

// E8 ? ? ? ? 5B (relative jump)
BOOL Utils_heapFree(LPVOID);

// 83 61 10 00 83 61 14 00
VOID Utils_initializeMD5(DWORD*);

// 52 85 C9
LPVOID Utils_heapReAlloc(LPVOID, SIZE_T);

// 33 C0 38 01
INT Utils_strlen(PCSTR);

// E8 ? ? ? ? A3 ? ? ? ? (relative jump)
UINT Utils_crc32ForByte(PBYTE, INT, UINT);

// FF 74 24 04
INT Utils_compareStringW(PCNZWCH, PCNZWCH, INT);

// E8 ? ? ? ? 59 59 33 F6 (relative jump)
BOOL Utils_iceEncrypt(INT, PSTR, INT, PCSTR);

// E8 ? ? ? ? 83 4C 24 (relative jump)
BOOL Utils_iceDecrypt(INT, PSTR, INT, PCSTR);

extern HMODULE moduleHandles[16];
extern INT winapiFunctionsCount;
extern INT moduleHandlesCount;
extern BOOL(WINAPI* freeLibrary)(HMODULE);

// E8 ? ? ? ? 8B 45 F0 (relative jump)
VOID Utils_resetFunctionsAndModuleHandles(VOID);

extern UINT winapiFunctionsHash;

// E8 ? ? ? ? B3 01 (relative jump)
BOOLEAN Utils_calculateWinapiFunctionsHash(VOID);

// 56 8B F1 56
LPCWSTR Utils_skipPath(LPCWSTR);

// E8 ? ? ? ? 32 C0 59 (relative jump)
VOID Utils_copyStringW(PWSTR, PCWSTR, UINT);

typedef struct Data {
    DWORD currentProcessId;
    DWORD currentThreadId;
    SYSTEM_INFO systemInfo;
    OSVERSIONINFOEXA osVersionInfo;
    DWORD systemVersion;
    DWORD _unknown;
    BYTE _pad[6];
    WCHAR systemDirectory[MAX_PATH];
    WCHAR windowsDirectory[MAX_PATH];
} Data;

extern Data data;

typedef struct WinApi {
    HMODULE(WINAPI* LoadLibraryExA)(LPCSTR, HANDLE, DWORD);
    FARPROC(WINAPI* GetProcAddress)(HMODULE, LPCSTR);
    NTSTATUS(NTAPI* NtOpenProcess)(PHANDLE, ACCESS_MASK, PVOID, PVOID);
    BOOL(WINAPI* FreeLibrary)(HMODULE);
    BOOL(WINAPI* GetVolumeInformationW)(LPCWSTR, LPWSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPWSTR, DWORD);
    BOOL(WINAPI* GetFileInformationByHandleEx)(HANDLE, FILE_INFO_BY_HANDLE_CLASS, LPVOID, DWORD);
    BOOL(WINAPI* QueryFullProcessImageNameW)(HANDLE, DWORD, LPWSTR, PDWORD);
    DWORD(WINAPI* GetLastError)(VOID);
    HANDLE(WINAPI* OpenProcess)(DWORD, BOOL, DWORD);
    BOOL(WINAPI* CryptMsgGetParam)(HCRYPTMSG, DWORD, DWORD, void*, DWORD*);
    SC_HANDLE(WINAPI* OpenSCManagerA)(LPCSTR, LPCSTR, DWORD);
    BOOL(WINAPI* GetTokenInformation)(HANDLE, TOKEN_INFORMATION_CLASS, LPVOID, DWORD, PDWORD);
    BOOL(WINAPI* CertCloseStore)(HCERTSTORE, DWORD);
    int(WINAPI* WideCharToMultiByte)(UINT, DWORD, LPCWCH, int, LPSTR, int, LPCCH, LPBOOL);
    BOOL(WINAPI* GetModuleHandleExA)(DWORD, LPCSTR, HMODULE*);
    BOOL(WINAPI* SetFilePointerEx)(HANDLE, LARGE_INTEGER, PLARGE_INTEGER, DWORD);
    HANDLE(WINAPI* FindFirstVolumeW)(LPWSTR, DWORD);
    BOOL(WINAPI* Module32FirstW)(HANDLE, LPMODULEENTRY32W);
    BOOL(WINAPI* CryptMsgClose)(HCRYPTMSG);
    DWORD(APIENTRY* GetFileVersionInfoSizeA)(LPCSTR, LPDWORD);
    HANDLE(WINAPI* GetCurrentProcess)(VOID);
    BOOL(WINAPI* GetModuleInformation)(HANDLE, HMODULE, LPMODULEINFO, DWORD);
    BOOL(APIENTRY* VerQueryValueA)(LPCVOID, LPCSTR, LPVOID*, PUINT);
    BOOL(WINAPI* FlushInstructionCache)(HANDLE, LPCVOID, SIZE_T);
    VOID(WINAPI* Sleep)(DWORD);
    DWORD(WINAPI* ResumeThread)(HANDLE);
    LONG(WINAPI* WinVerifyTrust)(HWND, GUID*, LPVOID);
    DWORD(WINAPI* GetModuleFileNameExA)(HANDLE, HMODULE, LPSTR, DWORD);
    HANDLE(WINAPI* GetCurrentThread)(VOID);
    DWORD(WINAPI* GetProcessId)(HANDLE);
    BOOL(WINAPI* GetFileInformationByHandle)(HANDLE, LPBY_HANDLE_FILE_INFORMATION);
    BOOL(WINAPI* GetVolumePathNamesForVolumeNameW)(LPCWSTR, LPWCH, DWORD, PDWORD);
    HDEVINFO(WINAPI* SetupDiGetClassDevsA)(CONST GUID*, PCSTR, HWND, DWORD);
    HANDLE(WINAPI* CreateToolhelp32Snapshot)(DWORD, DWORD);
    BOOL(WINAPI* ConvertSidToStringSidA)(PSID, LPSTR*);
    BOOL(WINAPI* WriteFile)(HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED);
    NTSTATUS(NTAPI* NtWow64QueryVirtualMemory64)(HANDLE, PVOID64, DWORD, PVOID, ULONG64, PULONG64);
    DWORD(WINAPI* GetModuleBaseNameA)(HANDLE, HMODULE, LPSTR, DWORD);
    LSTATUS(APIENTRY* RegEnumKeyExA)(HKEY, DWORD, LPSTR, LPDWORD, LPDWORD, LPSTR, LPDWORD, PFILETIME);
    DWORD(WINAPI* CertGetNameStringW)(PCCERT_CONTEXT, DWORD, DWORD, void*, LPWSTR, DWORD);
    UINT(WINAPI* GetSystemDirectoryW)(LPWSTR, UINT);
    DWORD(WINAPI* GetProcessImageFileNameA)(HANDLE, LPSTR, DWORD);
    BOOL(WINAPI* QueryServiceConfigA)(SC_HANDLE, LPQUERY_SERVICE_CONFIGA, DWORD, LPDWORD);
    BOOLEAN(SEC_ENTRY* GetUserNameExW)(EXTENDED_NAME_FORMAT, LPWSTR, PULONG);
    BOOL(WINAPI* IsBadReadPtr)(CONST VOID*, UINT_PTR);
    BOOL(WINAPI* CryptQueryObject)(DWORD, const void*, DWORD, DWORD, DWORD, DWORD*, DWORD*, DWORD*, HCERTSTORE*, HCRYPTMSG*, const void**);
    DWORD(APIENTRY* GetFileVersionInfoSizeW)(LPCWSTR, LPDWORD);
    BOOL(WINAPI* CloseServiceHandle)(SC_HANDLE);
    LSTATUS(APIENTRY* RegQueryValueExA)(HKEY, LPCSTR, LPDWORD, LPDWORD, LPBYTE, LPDWORD);
    NTSTATUS(NTAPI* NtQuerySystemInformation)(SYSTEM_INFORMATION_CLASS, PVOID, ULONG, PULONG);
    BOOL(WINAPI* GetVolumeInformationByHandleW)(HANDLE, LPWSTR, DWORD, LPDWORD, LPDWORD, LPDWORD, LPWSTR, DWORD);
    PVOID(WINAPI* EncodePointer)(PVOID);
    HANDLE(WINAPI* OpenThread)(DWORD, BOOL, DWORD);
    BOOL(APIENTRY* GetFileVersionInfoA)(LPCSTR, DWORD, DWORD, LPVOID);
    BOOL(WINAPI* QueryServiceConfigW)(SC_HANDLE, LPQUERY_SERVICE_CONFIGW, DWORD, LPDWORD);
    NTSTATUS(NTAPI* NtMapViewOfSection)(HANDLE, HANDLE, PVOID*, ULONG, ULONG, PLARGE_INTEGER, PULONG, DWORD, ULONG, ULONG);
    BOOL(WINAPI* ReadFile)(HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED);
    BOOL(WINAPI* GetProcessTimes)(HANDLE, LPFILETIME, LPFILETIME, LPFILETIME, LPFILETIME);
    PCCERT_CONTEXT(WINAPI* CertFindCertificateInStore)(HCERTSTORE, DWORD, DWORD, DWORD, const void*, PCCERT_CONTEXT);
    BOOL(WINAPI* EnumServicesStatusA)(SC_HANDLE, DWORD, DWORD, LPENUM_SERVICE_STATUSA, DWORD, LPDWORD, LPDWORD, LPDWORD);
    BOOL(APIENTRY* VerQueryValueW)(LPCVOID, LPCWSTR, LPVOID*, PUINT);
    BOOL(WINAPI* GetComputerNameExW)(COMPUTER_NAME_FORMAT, LPWSTR, LPDWORD);
    DWORD(WINAPI* GetMappedFileNameW)(HANDLE, LPVOID, LPWSTR, DWORD);
    SIZE_T(WINAPI* VirtualQueryEx)(HANDLE, LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
    DWORD(WINAPI* GetThreadId)(HANDLE);
    HANDLE(WINAPI* GetProcessHeap)(VOID);
    DWORD(WINAPI* GetModuleBaseNameW)(HANDLE, HMODULE, LPWSTR, DWORD);
    DWORD(WINAPI* GetModuleFileNameExW)(HANDLE, HMODULE, LPWSTR, DWORD);
    BOOL(WINAPI* CloseHandle)(HANDLE);
    NTSTATUS(NTAPI* NtQueryInformationThread)(HANDLE, THREADINFOCLASS, PVOID, ULONG, PULONG);
    BOOL(WINAPI* OpenProcessToken)(HANDLE, DWORD, PHANDLE);
    int(WINAPI* MultiByteToWideChar)(UINT, DWORD, LPCCH, int, LPWSTR, int);
    BOOL(WINAPI* VirtualFreeEx)(HANDLE, LPVOID, SIZE_T, DWORD);
    BOOL(WINAPI* Module32NextW)(HANDLE, LPMODULEENTRY32W);
    SC_HANDLE(WINAPI* OpenServiceA)(SC_HANDLE, LPCSTR, DWORD);
    SC_HANDLE(WINAPI* OpenServiceW)(SC_HANDLE, LPCWSTR, DWORD);
    BOOL(WINAPI* EnumServicesStatusW)(SC_HANDLE, DWORD, DWORD, LPENUM_SERVICE_STATUSW, DWORD, LPDWORD, LPDWORD, LPDWORD);
    BOOL(WINAPI* GetFileSizeEx)(HANDLE, PLARGE_INTEGER);
    BOOL(WINAPI* LookupPrivilegeValueA)(LPCSTR, LPCSTR, PLUID);
    BOOL(WINAPI* GetThreadContext)(HANDLE, LPCONTEXT);
    UINT(WINAPI* GetWindowsDirectoryW)(LPWSTR, UINT);
    LPVOID(WINAPI* HeapAlloc)(HANDLE, DWORD, SIZE_T);
    BOOL(WINAPI* Heap32First)(LPHEAPENTRY32, DWORD, ULONG_PTR);
    BOOL(WINAPI* UnmapViewOfFile)(LPCVOID);
    LSTATUS(APIENTRY* RegCloseKey)(HKEY);
    ULONG(WINAPI* GetUdp6Table)(PMIB_UDP6TABLE, PULONG, BOOL);
    BOOL(WINAPI* EnumProcessModules)(HANDLE, HMODULE*, DWORD, LPDWORD);
    LPVOID(WINAPI* MapViewOfFile)(HANDLE, DWORD, DWORD, DWORD, SIZE_T);
    NTSTATUS(NTAPI* NtDuplicateObject)(HANDLE, PHANDLE, HANDLE, PHANDLE, ACCESS_MASK, BOOLEAN, ULONG);
    BOOL(WINAPI* Thread32Next)(HANDLE, LPTHREADENTRY32);
    HANDLE(WINAPI* CreateFileW)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    BOOL(WINAPI* StackWalk64)(DWORD, HANDLE, HANDLE, LPSTACKFRAME64, PVOID, PREAD_PROCESS_MEMORY_ROUTINE64, PFUNCTION_TABLE_ACCESS_ROUTINE64, PGET_MODULE_BASE_ROUTINE64, PTRANSLATE_ADDRESS_ROUTINE64);
    BOOL(WINAPI* HeapFree)(HANDLE, DWORD, LPVOID);
    NTSTATUS(NTAPI* NtWow64ReadVirtualMemory64)(HANDLE, PVOID64, PVOID, ULONG64, PULONG64);
    DWORD(WINAPI* GetProcessImageFileNameW)(HANDLE, LPWSTR, DWORD);
    NTSTATUS(NTAPI* NtOpenSection)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
    HANDLE(WINAPI* CreateFileMappingW)(HANDLE, LPSECURITY_ATTRIBUTES, DWORD, DWORD, DWORD, LPCWSTR);
    DWORD(WINAPI* QueryDosDeviceA)(LPCSTR, LPSTR, DWORD);
    BOOL(WINAPI* GetVersionExW)(LPOSVERSIONINFOEXW);
    BOOL(WINAPI* SwitchToThread)(VOID);
    BOOL(WINAPI* WriteProcessMemory)(HANDLE, LPVOID, LPCVOID, SIZE_T, SIZE_T*);
    HLOCAL(WINAPI* LocalAlloc)(UINT, SIZE_T);
    BOOL(WINAPI* EnumProcesses)(DWORD*, DWORD, LPDWORD);
    BOOL(APIENTRY* GetFileVersionInfoW)(LPCWSTR, DWORD, DWORD, LPVOID);
    NTSTATUS(NTAPI* NtQueryObject)(HANDLE, OBJECT_INFORMATION_CLASS, PVOID, ULONG, PULONG);
    NTSTATUS(NTAPI* NtWow64QueryInformationProcess64)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
    DWORD(WINAPI* QueryDosDeviceW)(LPCWSTR, LPWSTR, DWORD);
    HRESULT(WINAPI* WinVerifyTrustEx)(HWND, GUID*, WINTRUST_DATA*);
    DWORD(WINAPI* GetCurrentProcessId)(VOID);
    ULONG(WINAPI* GetTcp6Table)(PMIB_TCP6TABLE, PULONG, BOOL);
    DWORD_PTR(WINAPI* SetThreadAffinityMask)(HANDLE, DWORD_PTR);
    LPVOID(WINAPI* VirtualAlloc)(LPVOID, SIZE_T, DWORD, DWORD);
    SIZE_T(WINAPI* VirtualQuery)(LPCVOID, PMEMORY_BASIC_INFORMATION, SIZE_T);
    DWORD(WINAPI* SetFilePointer)(HANDLE, LONG, PLONG, DWORD);
    BOOL(WINAPI* Process32FirstW)(HANDLE, LPPROCESSENTRY32W);
    HANDLE(WINAPI* CreateRemoteThread)(HANDLE, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD);
    NTSTATUS(NTAPI* NtQueryVirtualMemory)(HANDLE, PVOID, DWORD, PVOID, ULONG, PULONG);
    DWORD(WINAPI* SuspendThread)(HANDLE);
    BOOL(WINAPI* CryptDecodeObject)(DWORD, LPCSTR, const BYTE*, DWORD, DWORD, void*, DWORD*);
    NTSTATUS(NTAPI* NtQueryInformationProcess)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
    HMODULE(WINAPI* LoadLibraryA)(LPCSTR);
    BOOL(WINAPI* SetupDiGetDeviceRegistryPropertyA)(HDEVINFO, PSP_DEVINFO_DATA, DWORD, PDWORD, PBYTE, DWORD, PDWORD);
    BOOL(WINAPI* FindVolumeClose)(HANDLE);
    NTSTATUS(NTAPI* NtReadVirtualMemory)(HANDLE, PVOID, PVOID, ULONG, PULONG);
    BOOL(WINAPI* IsWow64Process)(HANDLE, PBOOL);
    HMODULE(WINAPI* GetModuleHandleA)(LPCSTR);
    UINT(WINAPI* GetDriveTypeW)(LPCWSTR);
    LSTATUS(APIENTRY* RegQueryInfoKeyA)(HKEY, LPSTR, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, LPDWORD, PFILETIME);
    BOOL(WINAPI* AdjustTokenPrivileges)(HANDLE, BOOL, PTOKEN_PRIVILEGES, DWORD, PTOKEN_PRIVILEGES, PDWORD);
    BOOL(WINAPI* Thread32First)(HANDLE, LPTHREADENTRY32);
    BOOL(WINAPI* GetVersionExA)(LPOSVERSIONINFOEXA);
    BOOL(WINAPI* FindNextVolumeW)(HANDLE, LPWSTR, DWORD);
    DWORD(WINAPI* GetCurrentThreadId)(VOID);
    NTSTATUS(NTAPI* NtQueryDirectoryObject)(HANDLE, PVOID, ULONG, BOOLEAN, BOOLEAN, PULONG, PULONG);
    NTSTATUS(NTAPI* RtlGetCompressionWorkSpaceSize)(ULONG, PULONG, PULONG);
    UINT(WINAPI* GetSystemDirectoryA)(LPSTR, UINT);
    BOOL(WINAPI* SetupDiDestroyDeviceInfoList)(HDEVINFO);
    BOOL(WINAPI* GetUserProfileDirectoryA)(HANDLE, LPSTR, LPDWORD);
    DWORD(WINAPI* GetTickCount)(VOID);
    BOOL(WINAPI* ReadProcessMemory)(HANDLE, LPCVOID, LPVOID, SIZE_T, SIZE_T*);
    BOOL(WINAPI* VirtualFree)(LPVOID, SIZE_T, DWORD);
    BOOL(WINAPI* CryptHashCertificate)(HCRYPTPROV_LEGACY, ALG_ID, DWORD, const BYTE*, DWORD, BYTE*, DWORD*);
    LPVOID(WINAPI* VirtualAllocEx)(HANDLE, LPVOID, SIZE_T, DWORD, DWORD);
    NTSTATUS(NTAPI* NtClose)(HANDLE);
    BOOL(WINAPI* Process32NextW)(HANDLE, LPPROCESSENTRY32W);
    BOOL(WINAPI* CertFreeCertificateContext)(PCCERT_CONTEXT);
    NTSTATUS(WINAPI* NtOpenDirectoryObject)(PHANDLE, ACCESS_MASK, POBJECT_ATTRIBUTES);
    VOID(WINAPI* GetSystemTimeAsFileTime)(LPFILETIME);
    VOID(WINAPI* OutputDebugStringA)(LPCSTR);
    BOOL(WINAPI* GetUserProfileDirectoryW)(HANDLE, LPWSTR, LPDWORD);
    PVOID(WINAPI* AddVectoredExceptionHandler)(ULONG, PVECTORED_EXCEPTION_HANDLER);
    VOID(WINAPI* GetSystemInfo)(LPSYSTEM_INFO);
    DWORD(WINAPI* GetModuleFileNameA)(HMODULE, LPSTR, DWORD);
    DWORD(WINAPI* WaitForSingleObject)(HANDLE, DWORD);
    PVOID(WINAPI* SymFunctionTableAccess64)(HANDLE, DWORD64);
    BOOL(WINAPI* SetupDiEnumDeviceInfo)(HDEVINFO, DWORD, PSP_DEVINFO_DATA);
    VOID(WINAPI* SetLastError)(DWORD);
    ULONG(WINAPI* GetUdpTable)(PMIB_UDPTABLE, PULONG, BOOL);
    HLOCAL(WINAPI* LocalFree)(HLOCAL);
    LSTATUS(APIENTRY* RegOpenKeyExA)(HKEY, LPCSTR, DWORD, REGSAM, PHKEY);
    NTSTATUS(NTAPI* NtQuerySection)(HANDLE, DWORD, PVOID, ULONG, PULONG);
    DWORD64(WINAPI* SymGetModuleBase64)(HANDLE, DWORD64);
    DWORD(WINAPI* GetFileSize)(HANDLE, LPDWORD);
    NTSTATUS(NTAPI* RtlDecompressBufferEx)(USHORT, PUCHAR, ULONG, PUCHAR, ULONG, PULONG, PVOID);
    BOOL(WINAPI* VirtualProtect)(LPVOID, SIZE_T, DWORD, PDWORD);
    DWORD(WINAPI* GetLogicalDriveStringsA)(DWORD, LPSTR);
    HANDLE(WINAPI* OpenFileById)(HANDLE, LPFILE_ID_DESCRIPTOR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD);
    DWORD(WINAPI* GetLogicalDriveStringsW)(DWORD, LPWSTR);
    HANDLE(WINAPI* CreateFileA)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
    ULONG(WINAPI* GetTcpTable)(PMIB_TCPTABLE, PULONG, BOOL);
    UINT(WINAPI* GetWindowsDirectoryA)(LPSTR, UINT);
    DWORD(WINAPI* GetMappedFileNameA)(HANDLE, LPVOID, LPSTR, DWORD);
    DWORD pad[28];
} WinApi;

extern WinApi winApi;

// 51 A1 ? ? ? ?
BOOLEAN Utils_getSystemInformation(VOID);

// A1 ? ? ? ? 53 56
int Utils_wideCharToMultiByte(LPCWCH, LPSTR);

// A1 ? ? ? ? 53
int Utils_wideCharToMultiByteN(LPCWCH wideCharStr, LPSTR multiByteStr, INT count);

// E8 ? ? ? ? 59 B0 01 (relative jump)
VOID Utils_copyStringW2(PWSTR, PCWSTR);

// E8 ? ? ? ? 8D 44 24 48 (relative jump)
BOOLEAN Utils_replaceDevicePathWithName(PWSTR, INT);

typedef struct Snmp {
    VOID(WINAPI* SnmpUtilVarBindFree)(SnmpVarBind*);
    HMODULE inetmib1;
    LPVOID(WINAPI* SnmpUtilMemAlloc)(UINT);
    HMODULE snmpapi;
    BOOL(WINAPI* SnmpExtensionQuery)(BYTE, SnmpVarBindList*, AsnInteger32*, AsnInteger32*);
} Snmp;

extern Snmp snmp;

// E8 ? ? ? ? EB 07 (relative jump)
VOID Utils_freeSnmp(VOID);

// E8 ? ? ? ? 84 C0 74 6B (relative jump)
BOOLEAN Utils_initializeSnmp(VOID);

// 55 8B EC 83 EC 10
BOOLEAN Utils_retrieveAsnValue(AsnInteger32*);

// 83 EC 10 53 55
BOOLEAN Utils_findAsnString(AsnInteger32, PBYTE);

// E8 ? ? ? ? 89 45 54 (relative jump)
INT Utils_enumProcesses(DWORD[500], DWORD[500]);

// B8 ? ? ? ? 85 D2
UINT Utils_hash(LPCVOID data, INT count);